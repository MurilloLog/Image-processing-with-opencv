/*
    Grayscale images
    Author: @Murillo.log
    Date: March 2024

    Description: This program was designed to test
    several algorithms for generating grayscale images
    and compare their outputs using OpenCV.
*/

#include <iostream>
#include <core.hpp>
#include <highgui.hpp>

using namespace std;
using namespace cv;

void muGetImageData(Mat& input);
void muCreateImage8UC1(Mat& input, Mat& output);
void muIntensityGrayscale(Mat& input, Mat& output);

int main(void)
{
    cout << "\n\t\tGray image scale\n";

    Mat Input, Output;
    string src = "../cvImages/ImageTest.png"; // Color image

    Input = imread(src);
    if (Input.empty())
    {
        cout << "\nWrong filename or folder.\n" << endl;
        return false;
    }

	imshow("Input image", Input);
    muGetImageData(Input);

    // Create the output image using the input image size
    muCreateImage8UC1(Input, Output);

    // Applying grayscale using the Intensity algorithm
    muIntensityGrayscale(Input, Output);
    imshow("Intensity algorithm", Output);
    muGetImageData(Output);

    waitKey(0);
    return true;
}


// Function to get columns, rows, channels and type from an image
void muGetImageData(Mat &input)
{
    // Checking if input has data
    if(input.empty())
    {
        cout << "\nThe source is empty. Check the image file or directory" << endl;
    }
    else
    {
        cout << "\nThe opened image has: " << endl;
        cout << "Columns: " << input.cols << endl;
        cout << "Rows: " << input.rows << endl;
        cout << "Channels: " << input.channels() << endl;
        cout << "Data type: ";

        switch(input.type())
        {
            case CV_8UC1: cout << "CV_8UC1: Unsigned char, monochrome.\n"; break;
            case CV_8UC3: cout << "CV_8UC3: Unsigned char, color.\n"; break;
            case CV_32FC1: cout << "CV_32FC1: Floating point, monochrome.\n"; break;
            case CV_32FC3: cout << "CV_32FC3: Floating point, color.\n"; break;
            default: cout << input.type() << ".\n";
        }
    }
}


/* Create Image
 * Function to create a single-channel image from an input image size.
 */
void muCreateImage8UC1(Mat& input, Mat& output) { output.Mat::create(input.rows, input.cols, CV_8UC1); }


/* INTENSITY: Color to Grayscale Algorithm
 * Function to apply grayscale by calculating the intensity (mean value) of all channels in a BGR image.
 */
void muIntensityGrayscale(Mat& input, Mat& output)
{
    for(int rows=0; rows<output.rows; rows++)
        for(int cols=0; cols<output.cols; cols++)
        {
            int grayMean = 0;
            for(int channel=0; channel<input.channels(); channel++)
                        grayMean += input.at<Vec3b>(rows, cols)[channel];
            output.at<uchar>(rows, cols) = grayMean/input.channels();
        }
}
