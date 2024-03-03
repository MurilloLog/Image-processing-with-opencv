/*
    Gray scale images
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

void muGetImageData(const Mat& input);
void muCreateImage8UC1(const Mat& input, Mat& output);
void muIntensityGrayscale(const Mat& input, Mat& output);
void muLuminanceGrayscale(const Mat& input, Mat& output);
void muValueGrayscale(const Mat& input, Mat& output);
void muValue2Grayscale(const Mat& input, Mat& output);
void muLusterGrayscale(const Mat& input, Mat& output);
void bubbleSort(int arr[], int n);

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

    // Applying grayscale using the Luminance algorithm
    muLuminanceGrayscale(Input, Output);
    imshow("Luminance algorithm", Output);
    muGetImageData(Output);

    // Applying grayscale using the Value algorithm
    muValueGrayscale(Input, Output);
    imshow("Value algorithm", Output);
    muGetImageData(Output);

    // Applying grayscale using the Value2 algorithm
    muValue2Grayscale(Input, Output);
    imshow("Value2 algorithm", Output);
    muGetImageData(Output);

    // Applying grayscale using the Luster algorithm
    muLusterGrayscale(Input, Output);
    imshow("Luster algorithm", Output);
    muGetImageData(Output);

    waitKey(0);
    return true;
}


// Function to get columns, rows, channels and type from an image
void muGetImageData(const Mat &input)
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
void muCreateImage8UC1(const Mat& input, Mat& output) { output.Mat::create(input.rows, input.cols, CV_8UC1); }


/* INTENSITY: Color to Grayscale Algorithm
 * Function to apply grayscale by calculating the intensity (mean value) of all channels in a BGR image.
 */
void muIntensityGrayscale(const Mat& input, Mat& output)
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


/* LUMINANCE: Color to Grayscale Algorithm
 * Function to apply grayscale by calculating the luminance (0.3R+0.59G+0.11B) of all channels in a BGR image.
 */
void muLuminanceGrayscale(const Mat& input, Mat& output)
{
    for(int rows=0; rows<output.rows; rows++)
        for(int cols=0; cols<output.cols; cols++)
            output.at<uchar>(rows, cols) = (0.11*input.at<Vec3b>(rows, cols)[0])+
                                           (0.59*input.at<Vec3b>(rows, cols)[1])+
                                           (0.3*input.at<Vec3b>(rows, cols)[2]);
}


/* VALUE: Color to Grayscale Algorithm
 * Function to apply grayscale by calculating the maximum RGB of all channels.
 */
void muValueGrayscale(const Mat& input, Mat& output)
{
    for(int rows=0; rows<input.rows; rows++)
        for(int cols=0; cols<input.cols; cols++)
        {
            int maximum = 0;
            for(int channel=0; channel<input.channels(); channel++)
                if(input.at<Vec3b>(rows, cols)[channel] > maximum)
                    maximum = input.at<Vec3b>(rows, cols)[channel];
            output.at<uchar>(rows, cols) = maximum;
        }
}


/* VALUE2: Color to Grayscale Algorithm
 * Function to apply grayscale by calculating the minimum RGB of all channels.
 */
void muValue2Grayscale(const Mat& input, Mat& output)
{
    for(int rows=0; rows<input.rows; rows++)
        for(int cols=0; cols<input.cols; cols++)
        {
            int minimum = 255;
            for(int channel=0; channel<input.channels(); channel++)
                if(input.at<Vec3b>(rows, cols)[channel] < minimum)
                    minimum = input.at<Vec3b>(rows, cols)[channel];
            output.at<uchar>(rows, cols) = minimum;
        }
}


/* LUSTER: Color to Grayscale Algorithm
 * Function to apply grayscale by calculating the mean of the minimum + maximum RGB of all channels.
 */
void muLusterGrayscale(const Mat& input, Mat& output)
{
    for(int rows=0; rows<input.rows; rows++)
        for(int cols=0; cols<input.cols; cols++)
        {
            int pixels[] = {input.at<Vec3b>(rows, cols)[0], input.at<Vec3b>(rows, cols)[1], input.at<Vec3b>(rows, cols)[2]};
            int n = sizeof(pixels)/sizeof(pixels[0]);
            bubbleSort(pixels, n);

            output.at<uchar>(rows, cols) = (pixels[0] + pixels[n-1])/2;
        }
}


void bubbleSort(int arr[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
