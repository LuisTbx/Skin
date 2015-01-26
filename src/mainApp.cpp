#include <iostream>
#include "mainApp.h"

using namespace std;

/******************************************************************************/
// setup the cameras properly based on OS platform

// 0 in linux gives first camera for v4l
//-1 in windows gives first device or user dialog selection

#ifdef linux
    #define CAMERA_INDEX 0
#else
    #define CAMERA_INDEX -1
#endif
/******************************************************************************/

MainApp::MainApp()
{
}

MainApp::~MainApp()
{
}

int MainApp::Init(void)
{
    std::cout<< "Covariance: \n" << theDetector.get_covariance() << std::endl;
    std::cout<< "Inverse Covariance: \n"<< theDetector.get_inverse_covariance() << std::endl;
    std::cout<< "Mean: \n" << theDetector.get_mean() << std::endl;
    std::cout<< "Threshold: \n" << theDetector.get_threshold() << std::endl;

    if(InitCamera())
        {
             return -1;
        }

    return 0;
}

int MainApp::Update(void)
{
    char key = 0;
    capture >> bgr_image;
    cv::flip(bgr_image, bgr_image, 1 );
    theDetector.set_bgr_image(bgr_image);
    cv::Mat skin_map = theDetector.get_skin_map();
    cv::Mat masked_img;
    bgr_image.copyTo(masked_img, skin_map);
    if (!masked_img.empty())
    {
        cv::imshow("camera", masked_img);
    }
    else
    {
        std::cout<< "Video stream is empty" << std::endl;
        return -1;
    }
    key = cv::waitKey(30);
    switch (key)
    {
        case 27:
            return -1;
        case 'q':
        case 'Q':
            return -1;
    }

    return 0;
}

int MainApp::InitCamera(void)
{
    capture.open(CAMERA_INDEX);

    // Check if we succeeded
    if(!capture.isOpened())
    {
        cout << "The camera could not be opened!!" << endl;
        return -1;
    }

    return 0;
}
