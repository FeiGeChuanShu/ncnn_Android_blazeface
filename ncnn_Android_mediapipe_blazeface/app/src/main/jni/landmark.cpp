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


    return 0;
}

int LandmarkDetect::detect(const cv::Mat& rgb,const cv::Mat& trans_mat, std::vector<cv::Point2f> &landmarks)
{
    cv::Mat input = rgb.clone();

    ncnn::Mat in = ncnn::Mat::from_pixels(input.data, ncnn::Mat::PIXEL_RGB, input.cols, input.rows);

    const float norm_vals[3] = { 1 / 255.f, 1 / 255.f, 1 / 255.f };
    in.substract_mean_normalize(0, norm_vals);
    ncnn::Mat points,score;
    {
        ncnn::Extractor ex = landmark.create_extractor();
        ex.input("input", in);
        ex.extract("output", points);
    }

    float* points_data = (float*)points.data;
    for (int i = 0; i < 468; i++)
    {
        cv::Point2f pt;
        float x = points_data[i * 3];
        float y = points_data[i * 3 + 1];

        pt.x = x * trans_mat.at<double>(0, 0) + y * trans_mat.at<double>(0, 1) + trans_mat.at<double>(0, 2);
        pt.y = x * trans_mat.at<double>(1, 0) + y * trans_mat.at<double>(1, 1) + trans_mat.at<double>(1, 2);

        landmarks.push_back(pt);
    }
    return 0;
}

