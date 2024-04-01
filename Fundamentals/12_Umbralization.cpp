#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void muGetImageData(Mat &imgSource);
void muImageBinarization(const Mat& input, Mat& output, const int umbral);

int main(void)
{
    cout << "\n\t\tUmbralization\n";

    Mat Input, Gray, muUmbralization, OpenCVUmbralization;
    string filename = "../cvImages/lena_gray.bmp";

    Input = imread(filename, IMREAD_UNCHANGED);
    cout << "\n   Input image:" << endl;
    muGetImageData(Input);

    if (Input.empty())
    {
        cout << "\nWrong filename or folder.\n" << endl;
        return false;
    }

    // Grayscale
    Gray = Input.clone();
	//cvtColor(Input, Gray, IMREAD_GRAYSCALE);
	//imshow("Input image in grayscale", Gray);
	//cout << "\n   Input image in grayscale:" << endl;
    //muGetImageData(Gray);

    // Umbralization using OpenCV
    int maxVal = 255;
    int umbral = 150;
    OpenCVUmbralization = Gray.clone();
    threshold(Gray, OpenCVUmbralization, umbral, maxVal, THRESH_BINARY);
    imshow("Image binarized by OpenCV", OpenCVUmbralization);

    // Umbralization
    muUmbralization = Gray.clone();
    muImageBinarization(Gray, muUmbralization, umbral);
    imshow("Image binarized by mu", muUmbralization);
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



// Image umbralization
void muImageBinarization(const Mat& input, Mat& output, const int umbral)
{
    for(int rows=0; rows<input.rows; rows++)
        for(int cols=0; cols<input.cols; cols++)
        {
            if(input.at<uchar>(rows, cols) < umbral)
                output.at<uchar>(rows, cols) = 0;
            else
                output.at<uchar>(rows, cols) = 255;
        }
}
