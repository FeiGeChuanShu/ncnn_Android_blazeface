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

#ifndef LANDMARK_H
#define LANDMARK_H

#include <opencv2/core/core.hpp>
#include <net.h>

struct TransformParam
{
    int left_roration_idx;
    int output_height;
    int output_width;
    int right_rotation_idx;
    float scale_x;
    float scale_y;
    std::vector<float> output_trans_matrix;
    std::string input;
    std::vector<std::string> outputs;
};
typedef std::array<float, 4> float4;
const std::vector<int> left_eye_idxs = {
        33, 7, 163, 144, 145, 153, 154, 155, 133, 246, 161, 160, 159, 158, 157, 173, 130, 25, 110, 24, 23, 22, 26, 112, 243, 247, 30, 29, 27, 28, 56, 190, 226, 31, 228, 229, 230, 231, 232, 233, 244, 113, 225, 224, 223, 222, 221, 189, 35, 124, 46, 53, 52, 65, 143, 111, 117, 118, 119, 120, 121, 128, 245, 156, 70, 63, 105, 66, 107, 55, 193 };
const std::vector<int> right_eye_idxs = {
        263, 249, 390, 373, 374, 380, 381, 382, 362, 466, 388, 387, 386, 385, 384, 398, 359, 255, 339, 254, 253, 252, 256, 341, 463, 467, 260, 259, 257, 258, 286, 414, 446, 261, 448, 449, 450, 451, 452, 453, 464, 342, 445, 444, 443, 442, 441, 413, 265, 353, 276, 283, 282, 295, 372, 340, 346, 347, 348, 349, 350, 357, 465, 383, 300, 293, 334, 296, 336, 285, 417 };
const std::vector<int> lips_idxs = { 61, 146, 91, 181, 84, 17, 314, 405, 321, 375, 291, 185, 40, 39, 37, 0, 267, 269, 270, 409, 78, 95, 88, 178, 87, 14, 317, 402, 318, 324, 308, 191, 80, 81, 82, 13, 312, 311, 310, 415, 76, 77, 90, 180, 85, 16, 315, 404, 320, 307, 306, 184, 74, 73, 72, 11, 302, 303, 304, 408, 62, 96, 89, 179, 86, 15, 316, 403, 319, 325, 292, 183, 42, 41, 38, 12, 268, 271, 272, 407 };

const float trans_matrix_scale[16] = { 1.0,1.0,4.0,4.0,
                                 1.0,1.0,4.0,4.0,
                                 0.25,0.25,1.0,1.0,
                                 0.25,0.25,1.0,1.0 };

using float2 =  cv::Point2f;
using float3 = cv::Point3f;
using int3 = cv::Point3i;
struct Mat3 {
    Mat3() { data.resize(9); }
    Mat3(float x00, float x01, float x02, float x10, float x11, float x12,
         float x20, float x21, float x22)
            : data{ x00, x01, x02, x10, x11, x12, x20, x21, x22 } {}

    Mat3 operator*(const Mat3& other) {
        Mat3 result;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                float sum = 0;
                for (int k = 0; k < 3; k++) {
                    sum += this->Get(r, k) * other.Get(k, c);
                }
                result.Set(r, c, sum);
            }
        }
        return result;
    }
    float3 operator*(const float3& vec) const {
        float3 result;
        result.x = this->Get(0, 0) * vec.x + this->Get(0, 1) * vec.y + this->Get(0, 2) * vec.z;
        result.y = this->Get(1, 0) * vec.x + this->Get(1, 1) * vec.y + this->Get(1, 2) * vec.z;
        result.z = this->Get(2, 0) * vec.x + this->Get(2, 1) * vec.y + this->Get(2, 2) * vec.z;

        return result;
    }
    float Get(int x, int y) const { return data[x * 3 + y]; }
    void Set(int x, int y, float val) { data[x * 3 + y] = val; }

    std::vector<float> data;
};

struct Mat4 {
    Mat4() { data.resize(16); }
    Mat4(float x00, float x01, float x02, float x03, float x10, float x11,
         float x12, float x13, float x20, float x21, float x22, float x23,
         float x30, float x31, float x32, float x33)
            : data{ x00, x01, x02, x03, x10, x11, x12, x13,
                    x20, x21, x22, x23, x30, x31, x32, x33 } {}
    void operator*=(const Mat4& other) {
        Mat4 result;
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                float sum = 0;
                for (int k = 0; k < 4; k++) {
                    sum += this->Get(r, k) * other.Get(k, c);
                }
                result.Set(r, c, sum);
            }
        }
        std::memcpy(this->data.data(), result.data.data(),
                    result.data.size() * sizeof(float));
    }
    float Get(int x, int y) const { return data[x * 4 + y]; }
    void Set(int x, int y, float val) { data[x * 4 + y] = val; }

    std::vector<float> data;
};
class LandmarkDetect
{
public:
    int load(AAssetManager* mgr, const char* modeltype, bool use_gpu = false);
    int detect(const cv::Mat& rgb, const cv::Mat& trans_mat, std::vector<cv::Point2f> &landmarks,
               std::vector<cv::Point2f>& left_eyes,std::vector<cv::Point2f>& right_eyes);

private:
    TransformParam left_transform_param;
    TransformParam right_transform_param;
    TransformParam lip_transform_param;
    ncnn::Net landmark;
};

#endif // LANDMARK_H
