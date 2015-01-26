/**
 * @file run_demo.cpp
 * @brief Main file for running a demo of the Skin Detector application
 * @date Jan 23rd, 2015
 * @author Luis Tobias
 */

#include "mainApp.h"

// Namespaces
using namespace std;
using namespace cv;

//*******************************************************************************
//*******************************************************************************

/**
 * @brief Main function with command line input arguments
*/
int main( int argc, char *argv[] )
{
    MainApp app;

    if( app.Init() )
    {
        cout << "Error encountered. Finishing application!!" << endl;
        return -1;
    }

    while(1)
    {
        if( app.Update() )
        {
            break;
        }
    }
}

