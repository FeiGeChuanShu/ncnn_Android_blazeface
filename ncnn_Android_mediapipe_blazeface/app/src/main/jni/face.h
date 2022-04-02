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

#ifndef FACE_H
#define FACE_H

#include <opencv2/core/core.hpp>
#include <net.h>
#include "landmark.h"
struct Object
{
    cv::Rect_<float> rect;
    int label;
    float score;
    std::vector<cv::Point2f> pts;
    float  rotation;
    float  cx;
    float  cy;
    float  w;
    float  h;
    cv::Point2f  pos[4];
    cv::Mat trans_image;
    std::vector<cv::Point2f> skeleton;
    std::vector<cv::Point2f> left_eyes;
    std::vector<cv::Point2f> right_eyes;
};

class Face
{
public:
    Face();

    int load(AAssetManager* mgr, const char* modeltype, int target_size, bool use_gpu = false);

    int detect(const cv::Mat& rgb, std::vector<Object>& objects, float prob_threshold = 0.55f, float nms_threshold = 0.3f);

    int draw(cv::Mat& rgb, const std::vector<Object>& objects);

private:

    ncnn::Net blazepalm_net;
    LandmarkDetect landmark;
    int target_size;
    float mean_vals[3];
    float norm_vals[3];
    ncnn::UnlockedPoolAllocator blob_pool_allocator;
    ncnn::PoolAllocator workspace_pool_allocator;
};

#endif // FACE_H
