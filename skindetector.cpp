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

#include "skindetector.h"

//Constructurs
SkinDetector::SkinDetector()
{
    this->covariance = (cv::Mat_<float>(2,2) << 0.0038,-0.0009,-0.0009, 0.0009 );
    this->mean = (cv::Mat_<float>(2,1) << 0.4404, 0.3111);
    cv::invert(covariance, inverse_covariance);
    this->threshold = 0.33f;
}
SkinDetector::SkinDetector(cv::Mat _mcovariance, cv::Mat _mean, float _mthreshold)
    : covariance(_mcovariance), threshold(_mthreshold),
      mean(_mean)
{
    cv::invert(covariance, inverse_covariance);
}
SkinDetector::SkinDetector(cv::Mat _mcovariance, cv::Mat _minverse_covariance, cv::Mat _mean, float _mthreshold)
    : covariance(_mcovariance), inverse_covariance(_minverse_covariance),
      threshold(_mthreshold), mean(_mean)
{
}

// Destructor
SkinDetector::~SkinDetector()
{
    covariance.release();
    inverse_covariance.release();
    mean.release();
    bgr_img.release();
    skin_map.release();
    for (unsigned int ii=0; ii<layers.size(); ii++)
        layers[ii].release();
    layers.clear();
}

// Setters
void SkinDetector::set_threshold(float _mthreshold)
{
    this-> threshold = _mthreshold;
}

void SkinDetector::set_covariance(cv::Mat _mcovariance)
{
    this->covariance = _mcovariance.clone();
    cv::invert(covariance, inverse_covariance);
}
void SkinDetector::set_bgr_image(cv::Mat _bgr_image)
{
    if(_bgr_image.data)
        this->bgr_img = _bgr_image.clone();
}
void SkinDetector::set_mean(cv::Mat _mean)
{
    this->mean = _mean.clone();
}

// Getters
cv::Mat SkinDetector::get_covariance()
{
    return this->covariance.clone();
}
cv::Mat SkinDetector::get_inverse_covariance()
{
    return this-> inverse_covariance.clone();
}
cv::Mat SkinDetector::get_mean()
{
    return this->mean.clone();
}

cv::Mat SkinDetector::get_skin_map()
{
    normalize_image();
    cv::Mat gate;
    gate = -0.5f * (((n_r.mul(n_r))*inverse_covariance.at<float>(0,0))
                    + (2*inverse_covariance.at<float>(0,1)*(n_r.mul(n_g)))
                    + ((n_g.mul(n_g))*inverse_covariance.at<float>(1,1)));
    exp(gate,gate);
    cv::threshold(gate, skin_map, threshold, 255, CV_THRESH_BINARY);
    skin_map.convertTo(skin_map,CV_8U);
    gate.release();
    return skin_map.clone();
}
float SkinDetector::get_threshold()
{
    return this->threshold;
}

// self functions
void SkinDetector::normalize_image()
{
    // Allocate temporal image
    cv::Mat temp;
    bgr_img.convertTo(temp, CV_32F);

    // split image into channels
    cv::split(temp, layers);

    // Change color space to normalized rgb:  b = B / B+G+R, g = G/ B+G+R, r = R/ B+G+R
    // we kep only the two important components  for skin detection G and R
    n_g = (layers[1] / (layers[0]+layers[1]+layers[2])) - mean.at<float>(0,1);
    n_r = (layers[2] / (layers[0]+layers[1]+layers[2])) - mean.at<float>(0,0);

    // free memory
    for (auto ii=0; ii<layers.size(); ii++)
        layers[ii].release();
    layers.clear();
    temp.release();
}
