/*L///////////////////////////////////////////////////////////////////////////////////////
Copyright (c) 2013-2014, Luis Tobias, Sidibe Desire, France
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of the Authors nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//L*/

#ifndef SKINDETECTOR_H
#define SKINDETECTOR_H
#include <opencv2/opencv.hpp>

class SkinDetector
{
public:
    // Constructors
    SkinDetector(); // Need further initialization
    SkinDetector(cv::Mat _mcovariance, cv::Mat _mean, float _mthreshold);
    SkinDetector(cv::Mat _mcovariance, cv::Mat _inverse_covariance, cv::Mat _mean, float _mthreshold);
    // Destructure
    ~SkinDetector();

    void normalize_image();
    // Setters
    void set_bgr_image(cv::Mat _bgr_image);
    void set_threshold(float _mthreshold);
    void set_covariance(cv::Mat _covariance);
    void set_mean(cv::Mat _mean);

    // Getters
    cv::Mat get_skin_map();
    cv::Mat get_covariance();
    cv::Mat get_inverse_covariance();
    cv::Mat get_mean();
    float get_threshold();

private:
    cv::Mat covariance;
    cv::Mat inverse_covariance;
    cv::Mat mean;
    cv::Mat n_g;
    cv::Mat n_r;
    cv::Mat bgr_img;
    cv::Mat skin_map;
    std::vector<cv::Mat> layers;
    float threshold;
};

#endif // SKINDETECTOR_H
