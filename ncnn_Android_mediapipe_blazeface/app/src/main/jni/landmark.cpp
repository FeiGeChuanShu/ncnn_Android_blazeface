// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "landmark.h"

#include <string.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cpu.h"

float2 read3DLandmarkXY(const float* data, int idx)
{
    float2 result;
    result.x = data[idx * 3];
    result.y = data[idx * 3 + 1];
    return result;
}

float3 read3DLandmarkXYZ(const float* data, int idx)
{
    float3 result;
    result.x = data[idx * 3]*0.25;
    result.y = data[idx * 3 + 1] * 0.25;
    result.z = data[idx * 3 + 2] * 0.25;
    return result;
}

void estimateRotationRadians(const float* input_data_0, int left_rotation_idx,int right_rotation_idx,
        float target_rotation_radians,float* rotation_radians)
{
    const float3 left_landmark = read3DLandmarkXYZ(input_data_0, left_rotation_idx);
    const float3 right_landmark = read3DLandmarkXYZ(input_data_0, right_rotation_idx);
    const float left_x = left_landmark.x;
    const float left_y = left_landmark.y;
    const float right_x = right_landmark.x;
    const float right_y = right_landmark.y;
    float rotation = std::atan2(right_y - left_y, right_x - left_x);
    rotation = target_rotation_radians - rotation;
    *rotation_radians = rotation;
}

void estimateCenterAndSize(const float* input_data_0,std::vector<int> subset_idxs,float rotation_radians,
        float* crop_x, float* crop_y, float* crop_width, float* crop_height)
 {
    std::vector<float3> landmarks;
    landmarks.reserve(subset_idxs.size());
    for (int i = 0; i < subset_idxs.size(); i++)
    {
        landmarks.push_back(read3DLandmarkXYZ(input_data_0, subset_idxs[i]));
    }
    for (int i = 0; i < landmarks.size(); i++)
    {
        landmarks[i].z = 1.0;
    }
    const float& r = rotation_radians;
    const Mat3 t_rotation = Mat3(std::cos(r), -std::sin(r), 0.0,
                                 std::sin(r), std::cos(r), 0.0,
                                 0.0, 0.0, 1.0);
    const Mat3 t_rotation_inverse =
            Mat3(std::cos(-r), -std::sin(-r), 0.0,
                 std::sin(-r), std::cos(-r), 0.0,
                 0.0, 0.0, 1.0);
    for (int i = 0; i < landmarks.size(); i++)
    {
        landmarks[i] = t_rotation * landmarks[i];
    }
    float3 xy1_max = landmarks[0], xy1_min = landmarks[0];
    for (int i = 1; i < landmarks.size(); i++)
    {
        if (xy1_max.x < landmarks[i].x) xy1_max.x = landmarks[i].x;
        if (xy1_max.y < landmarks[i].y) xy1_max.y = landmarks[i].y;

        if (xy1_min.x > landmarks[i].x) xy1_min.x = landmarks[i].x;
        if (xy1_min.y > landmarks[i].y) xy1_min.y = landmarks[i].y;
    }
    *crop_width = xy1_max.x - xy1_min.x;
    *crop_height = xy1_max.y - xy1_min.y;
    float3 crop_xy1 = xy1_min;
    crop_xy1.x += xy1_max.x;
    crop_xy1.y += xy1_max.y;
    crop_xy1.x /= 2;
    crop_xy1.y /= 2;
    crop_xy1 = t_rotation_inverse * crop_xy1;
    *crop_x = crop_xy1.x;
    *crop_y = crop_xy1.y;
}

static void landmarksToTransformMatrix(const int left_rotation_idx,const int& right_rotation_idx,
        const int& target_rotation_radians, const std::vector<int32_t>& subset_idxs, const float& scale_x_,
        const float& scale_y_, const int& output_width, const int& output_height, const float* landmarks, float* output_data)
{
    float rotation_radians = 0.0;
    estimateRotationRadians(landmarks, left_rotation_idx,right_rotation_idx,target_rotation_radians, &rotation_radians);
    float crop_x = 0.0, crop_y = 0.0, crop_width = 0.0, crop_height = 0.0;
    estimateCenterAndSize(landmarks, subset_idxs, rotation_radians,&crop_x, &crop_y, &crop_width, &crop_height);

    Mat4 t = Mat4(1.0, 0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0, 0.0,
                  0.0, 0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0, 1.0);
    const Mat4 t_shift = Mat4(1.0, 0.0, 0.0, crop_x,
                              0.0, 1.0, 0.0, crop_y,
                              0.0, 0.0, 1.0, 0.0,
                              0.0, 0.0, 0.0, 1.0);
    t *= t_shift;
    const float& r = -rotation_radians;
    const Mat4 t_rotation = Mat4(std::cos(r), -std::sin(r), 0.0, 0.0,
                                 std::sin(r), std::cos(r), 0.0, 0.0,
                                 0.0, 0.0, 1.0, 0.0,
                                 0.0, 0.0, 0.0, 1.0);
    t *= t_rotation;
    const float scale_x = scale_x_ * crop_width / output_width;
    const float scale_y = scale_y_ * crop_height / output_height;
    const Mat4 t_scale = Mat4(scale_x, 0.0, 0.0, 0.0,
                              0.0, scale_y, 0.0, 0.0,
                              0.0, 0.0, 1.0, 0.0,
                              0.0, 0.0, 0.0, 1.0);
    t *= t_scale;
    const float shift_x = -1.0 * (output_width / 2.0);
    const float shift_y = -1.0 * (output_height / 2.0);
    const Mat4 t_shift2 = Mat4(1.0, 0.0, 0.0, shift_x,
                               0.0, 1.0, 0.0, shift_y,
                               0.0, 0.0, 1.0, 0.0,
                               0.0, 0.0, 0.0, 1.0);
    t *= t_shift2;
    std::memcpy(output_data, t.data.data(), 16 * sizeof(float));
}

float dotProduct(const float4& l, const float4& r)
{
    return l[0] * r[0] + l[1] * r[1] + l[2] * r[2] + l[3] * r[3];
}

static void transformTensorBilinear(const std::vector<int>& input0_shape, const float* input_data_0,
        const float* input_data_1, const std::vector<int>& output_shape, float* output_data)
{

    const int output_height = output_shape[0];
    const int output_width = output_shape[1];
    const int output_channels = output_shape[2];

    const int input_height = input0_shape[0];
    const int input_width = input0_shape[1];
    const int input_channels = input0_shape[2];

    std::vector<int> input_shape_with_batch{/*batch=*/1, input_height,
                                                      input_width, input_channels };
    std::vector<int> output_shape_with_batch{/*batch=*/1, output_height,
                                                       output_width, output_channels };

    float4 y_transform{ input_data_1[0], input_data_1[1],
                        input_data_1[2], input_data_1[3] };
    float4 x_transform{ input_data_1[4], input_data_1[5],
                        input_data_1[6], input_data_1[7] };

    for (int out_y = 0; out_y < output_height; ++out_y)
    {
        for (int out_x = 0; out_x < output_width; ++out_x)
        {
            float4 coord{static_cast<float>(out_x), static_cast<float>(out_y),
                    static_cast<float>(0.0), static_cast<float>(1.0) };

            // Transformed coordinates.
            float2 tc{ dotProduct(x_transform, coord), dotProduct(y_transform, coord) };

            bool out_of_bound = tc.x < 0.0 || tc.x > input_width - 1 || tc.y < 0.0 ||
                                tc.y > input_height - 1;

            for (int out_z = 0; out_z < output_channels; ++out_z)
            {
                float result = 0;
                if (!out_of_bound)
                {
                    auto ReadValue = [&](int h, int w) -> float{
                        return h < 0 || w < 0 || h >= input_height || w >= input_width
                               ? 0
                               : input_data_0[h * input_width * input_channels + w * input_channels + out_z];
                    };

                    float q_11 = ReadValue(floor(tc.x), floor(tc.y));
                    float q_12 = ReadValue(floor(tc.x), floor(tc.y) + 1);
                    float q_22 = ReadValue(floor(tc.x) + 1, floor(tc.y));
                    float q_21 = ReadValue(floor(tc.x) + 1, floor(tc.y) + 1);

                    float right_contrib = tc.x - floor(tc.x);
                    float lower_contrib = tc.y - floor(tc.y);

                    float upper = right_contrib * (1.0 - lower_contrib) * q_22 + lower_contrib * (1.0 - right_contrib) * q_12;
                    float lower = (1.0 - right_contrib) * (1.0 - lower_contrib) * q_11 + right_contrib * lower_contrib * q_21;
                    result = lower + upper;
                }

                const int out_offset = out_y * output_channels * output_width + out_x * output_channels + out_z;
                output_data[out_offset] = result;
            }
        }
    }
}

static void refine_part(const ncnn::Net& net, TransformParam& transform_param, const ncnn::Mat& face_mesh,const std::vector<int>& eye_idxs,
                 const ncnn::Mat& features,const float* trans_matrix_scale, ncnn::Mat& refine_eye, ncnn::Mat& refine_iris)
{

    landmarksToTransformMatrix(transform_param.left_roration_idx, transform_param.right_rotation_idx, 0,
                                 eye_idxs, transform_param.scale_x, transform_param.scale_y, transform_param.output_width,
                                 transform_param.output_height, (float*)face_mesh.data, transform_param.output_trans_matrix.data());

    std::vector<int> input_shape{ 48,48,32 };
    std::vector<int> output_shape{ 16,16,32 };

    ncnn::Mat output_trans_bilinear = ncnn::Mat(32, 16, 16, sizeof(float));
    transformTensorBilinear(input_shape, (float*)features.data, transform_param.output_trans_matrix.data(),
            output_shape, (float*)output_trans_bilinear.data);

    ncnn::Extractor ex = net.create_extractor();
    ex.input(transform_param.input.c_str(), output_trans_bilinear);

    if (transform_param.outputs.size()==1)
    {
        ex.extract(transform_param.outputs[0].c_str(), refine_eye);
    }
    else
    {
        ex.extract(transform_param.outputs[0].c_str(), refine_eye);
        ex.extract(transform_param.outputs[1].c_str(), refine_iris);
    }

    float q_11 = transform_param.output_trans_matrix[0] * trans_matrix_scale[0];
    float q_12 = transform_param.output_trans_matrix[1] * trans_matrix_scale[1];
    float q_13 = transform_param.output_trans_matrix[3] * trans_matrix_scale[3];
    float q_21 = transform_param.output_trans_matrix[4] * trans_matrix_scale[4];
    float q_22 = transform_param.output_trans_matrix[5] * trans_matrix_scale[5];
    float q_23 = transform_param.output_trans_matrix[7] * trans_matrix_scale[7];
    int w = refine_eye.w;
    for (int i = 0; i < refine_eye.c; i++)
    {
        float* ptr = refine_eye.channel(i);
        for (int j = 0; j < refine_eye.h; j++)
        {
            float a = ptr[j * w + 0] * q_11 + ptr[j * w + 1] * q_12 + q_13;
            float b = ptr[j * w + 0] * q_21 + ptr[j * w + 1] * q_22 + q_23;
            ptr[j * w + 0] = a;
            ptr[j * w + 1] = b;
        }
    }

    if (!refine_iris.empty())
    {
        w = refine_iris.w;
        for (int i = 0; i < refine_iris.c; i++)
        {
            float* ptr = refine_iris.channel(i);
            for (int j = 0; j < refine_iris.h; j++)
            {
                float a = ptr[j * w + 0] * q_11 + ptr[j * w + 1] * q_12 + q_13;
                float b = ptr[j * w + 0] * q_21 + ptr[j * w + 1] * q_22 + q_23;
                ptr[j * w + 0] = a;
                ptr[j * w + 1] = b;
            }
        }
    }

}


int LandmarkDetect::load(AAssetManager* mgr, const char* modeltype, bool use_gpu)
{
    landmark.clear();

    ncnn::set_cpu_powersave(2);
    ncnn::set_omp_num_threads(ncnn::get_big_cpu_count());

    landmark.opt = ncnn::Option();

#if NCNN_VULKAN
    landmark.opt.use_vulkan_compute = use_gpu;
#endif

    landmark.opt.num_threads = ncnn::get_big_cpu_count();

    char parampath[256];
    char modelpath[256];
    sprintf(parampath, "%s.param", modeltype);
    sprintf(modelpath, "%s.bin", modeltype);

    landmark.load_param(mgr, parampath);
    landmark.load_model(mgr, modelpath);

    left_transform_param.left_roration_idx = 33;
    left_transform_param.output_height = 16;
    left_transform_param.output_width = 16;
    left_transform_param.right_rotation_idx = 133;
    left_transform_param.scale_x = 1.5;
    left_transform_param.scale_y = 1.5;
    left_transform_param.output_trans_matrix.reserve(16);
    left_transform_param.input = "left/input";
    left_transform_param.outputs.emplace_back("left/eye");
    left_transform_param.outputs.emplace_back("left/iris");

    right_transform_param.left_roration_idx = 362;
    right_transform_param.output_height = 16;
    right_transform_param.output_width = 16;
    right_transform_param.right_rotation_idx = 263;
    right_transform_param.scale_x = 1.5;
    right_transform_param.scale_y = 1.5;
    right_transform_param.output_trans_matrix.reserve(16);
    right_transform_param.input = "right/input";
    right_transform_param.outputs.emplace_back("right/eye");
    right_transform_param.outputs.emplace_back("right/iris");

    lip_transform_param.left_roration_idx = 61;
    lip_transform_param.output_height = 16;
    lip_transform_param.output_width = 16;
    lip_transform_param.right_rotation_idx = 291;
    lip_transform_param.scale_x = 1.5;
    lip_transform_param.scale_y = 1.5;
    lip_transform_param.output_trans_matrix.reserve(16);
    lip_transform_param.input = "lips/input";
    lip_transform_param.outputs.emplace_back("lips/output");
    return 0;
}

int LandmarkDetect::detect(const cv::Mat& rgb,const cv::Mat& trans_mat, std::vector<cv::Point2f> &landmarks,
        std::vector<cv::Point2f>& left_eyes,std::vector<cv::Point2f>& right_eyes)
{
    cv::Mat input = rgb.clone();

    const float mean_vals[3] = { 127.5f, 127.5f,  127.5f };
    const float norm_vals[3] = { 1/127.5f, 1 / 127.5f, 1 / 127.5f };
    ncnn::Mat in = ncnn::Mat::from_pixels(input.data, ncnn::Mat::PIXEL_RGB, input.cols, input.rows);
    in.substract_mean_normalize(mean_vals, norm_vals);
    ncnn::Extractor ex = landmark.create_extractor();
    ex.input("net/input", in);

    ncnn::Mat face_mesh, features;
    ex.extract("net/output", face_mesh);
    ex.extract("net/features", features);

    std::vector<cv::Point2f> pts;
    ncnn::Mat data = face_mesh.channel(0);
    float* points_data = (float*)data.data;

    for (int i = 0; i < 468; i++)
    {
        cv::Point2f pt;
        float x = points_data[i * 3];
        float y = points_data[i * 3 + 1];
        pt.x = x * trans_mat.at<double>(0, 0) + y * trans_mat.at<double>(0, 1) + trans_mat.at<double>(0, 2);
        pt.y = x * trans_mat.at<double>(1, 0) + y * trans_mat.at<double>(1, 1) + trans_mat.at<double>(1, 2);
        landmarks.push_back(pt);
    }

    ncnn::Mat left_eye, left_iris;
    refine_part(landmark, left_transform_param, face_mesh,left_eye_idxs, features, trans_matrix_scale, left_eye, left_iris);

    ncnn::Mat right_eye, right_iris;
    refine_part(landmark, right_transform_param, face_mesh,right_eye_idxs, features, trans_matrix_scale, right_eye, right_iris);

    ncnn::Mat lips,tmp;
    refine_part(landmark, lip_transform_param, face_mesh, lips_idxs, features, trans_matrix_scale, lips, tmp);

    for(int i = 0;  i < 71; i++)
    {
        cv::Point2f left_pt;
        float x = left_eye[i * 2];
        float y = left_eye[i * 2 + 1];
        left_pt.x = x * trans_mat.at<double>(0, 0) + y * trans_mat.at<double>(0, 1) + trans_mat.at<double>(0, 2);
        left_pt.y = x * trans_mat.at<double>(1, 0) + y * trans_mat.at<double>(1, 1) + trans_mat.at<double>(1, 2);
        left_eyes.push_back(left_pt);

        cv::Point2f right_pt;
        x = right_eye[i * 2];
        y = right_eye[i * 2 + 1];
        right_pt.x = x * trans_mat.at<double>(0, 0) + y * trans_mat.at<double>(0, 1) + trans_mat.at<double>(0, 2);
        right_pt.y = x * trans_mat.at<double>(1, 0) + y * trans_mat.at<double>(1, 1) + trans_mat.at<double>(1, 2);
        right_eyes.push_back(right_pt);
    }
    for (int i = 0; i < lips_idxs.size(); i++)
    {
        cv::Point2f lip_pt;
        float x = lips[i * 2];
        float y = lips[i * 2 + 1];
        lip_pt.x = x * trans_mat.at<double>(0, 0) + y * trans_mat.at<double>(0, 1) + trans_mat.at<double>(0, 2);
        lip_pt.y = x * trans_mat.at<double>(1, 0) + y * trans_mat.at<double>(1, 1) + trans_mat.at<double>(1, 2);
        landmarks[lips_idxs[i]] = lip_pt;
    }
    return 0;
}

