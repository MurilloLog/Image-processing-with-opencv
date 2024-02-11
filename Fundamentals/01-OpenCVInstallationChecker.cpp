/*
    Open CV installation checker
    Author: Gustavo Murillo
    Date: February 2024

    Description: This program was designed to verify if
    OpenCV is correctly configured and installed on your
    computer. For the test, is included the main OpenCV
    libraries and the image is opened.
    If all is ok, you'll get information about that image
    and it'll be showed on a new window.
*/

// I/O C++ library
#include <iostream>

// OpenCV libraries
#include <core.hpp>
#include <highgui.hpp>

using namespace std;
using namespace cv;

void muGetImageData(Mat &imgSource);

int main(void)
{
    cout << "\n\t\tChecking OpenCV installation.\n";

    Mat Input;
    Input = imread("../cvImages/ImageTest.png");
    if (Input.empty())
    {
        cout << "\nWrong filename or folder.\n" << endl;
        return false;
    }

	imshow("Showing the input image", Input);
    muGetImageData(Input);

    waitKey(0);
    return true;
}

// Function to get columns, rows and channels from an image
void muGetImageData(Mat &imgSource)
{
    // Checking if imgSource has data
    if(imgSource.empty())
    {
        cout << "\nThe source is empty. Check the image file or directory" << endl;
    }
    else
    {
        cout << "\nOpenCV is correctly installed." << endl;
        cout << "\nThe opened image has: " << endl;
        cout << "Columns: " << imgSource.cols << endl;
        cout << "Rows: " << imgSource.rows << endl;
        cout << "Channels: " << imgSource.channels() << endl;
        cout << "Data type: ";

        switch(imgSource.type())
        {
            case CV_8UC1: cout << "CV_8UC1: Unsigned char, monochrome.\n"; break;
            case CV_8UC3: cout << "CV_8UC3: Unsigned char, color.\n"; break;
            case CV_32FC1: cout << "CV_32FC1: Floating point, monochrome.\n"; break;
            case CV_32FC3: cout << "CV_32FC3: Floating point, color.\n"; break;
            default: cout << imgSource.type() << ".\n";
        }
    }
}
