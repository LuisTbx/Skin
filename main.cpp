#include <iostream>
#include "skindetector.h"

using namespace std;

int main(int argc, char * argv[] )
{
    // Set classification parameters
    cv::Mat myCovariance = (cv::Mat_<float>(2,2) << 0.0038,-0.0009,-0.0009, 0.0009 );
    cv::Mat myInverseCovariance;
    cv::Mat myMean = (cv::Mat_<float>(2,1) << 0.4404, 0.3111);
    cv::invert(myCovariance, myInverseCovariance);
    float th = 0.33f;

    // Create an instance of the skin detector, display its values
    SkinDetector LO(myCovariance, myInverseCovariance, myMean, th);
    std::cout<< "Covariance: \n" << LO.get_covariance() << std::endl;
    std::cout<< "Inverse Covariance: \n"<< LO.get_inverse_covariance() << std::endl;
    std::cout<< "Mean: \n" << LO.get_mean() << std::endl;
    std::cout<< "Threshold: \n" << LO.get_threshold() << std::endl;

    // create an image to store video frames
    cv::Mat bgr_image;

    // initilialise camera feed, loop until user enter a command.
    cv::VideoCapture capture(0);
    auto loop = true;
    while (loop)
    {
        capture >> bgr_image;
        cv::flip(bgr_image, bgr_image, 1 );
        LO.set_bgr_image(bgr_image);
        cv::Mat skin_map = LO.get_skin_map();
        cv::Mat masked_img;
        bgr_image.copyTo(masked_img, skin_map);
        if (!masked_img.empty())
        {
            cv::imshow("camera", masked_img);
            int keyCode = cv::waitKey(30);
            switch (keyCode){
            case 27:
                loop = false;
                break;
            case 'q':
            case 'Q':
                loop = false;
                break;
            }
        }
        else
        {
            std::cout<< "Video stream is empty" << std::endl;
            break;
        }

    }
    return 0;
}
