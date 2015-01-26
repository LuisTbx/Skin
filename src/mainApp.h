#ifndef MAINAPP_H
#define MAINAPP_H
#include <iostream>
#include <skindetector.h>

using namespace std;

class MainApp
{
    public:
        MainApp();
        ~MainApp();

        cv::VideoCapture capture;
        cv::Mat bgr_image;
        cv::Mat skinMap;
        SkinDetector theDetector;

        int Init(void);
        int Update(void);
        int InitCamera(void);

    protected:
    private:
};

#endif // MAINAPP_H
