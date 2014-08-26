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
