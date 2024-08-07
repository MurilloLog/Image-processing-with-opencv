#include <iostream>
#include <core.hpp>
#include <highgui.hpp>

using namespace std;
using namespace cv;

void muApplyImageNegative(Mat& output);

int main(void)
{
    cout << "\n\t\tNegative image" << endl;

    Mat Input, Output;

    string src = "../cvImages/ImageTest.png"; // Color image
//    string src = "../cvImages/cameraman.tif"; // BW image

    Input = imread(src, IMREAD_UNCHANGED);

    if (Input.empty())
    {
        cout << "\nWrong filename or folder.\n" << endl;
        return false;
    }

    // Showing input image
    Output = Input.clone();
	imshow("Input image", Input);

    // Applying and showing the negative image
    muApplyImageNegative(Output);
	imshow("Negative image", Output);

	// Applying and showing the negative image using OpenCV
    bitwise_not(Input, Output);
	imshow("OpenCV - Negative image", Output);

    waitKey(0);
    return true;
}

// Function to apply the negative process pixel by pixel of all channels in a BGR image
void muApplyImageNegative(Mat& output)
{
    // Checking if input has data
    if(output.empty())
    {
        cout << "\nThe source is empty. Check the image file or directory" << endl;
    }
    else
    {
        switch(output.type())
        {
            case CV_8UC1:
                for(int rows=0; rows<output.rows; rows++)
                    for(int cols=0; cols<output.cols; cols++)
                        output.at<uchar>(rows, cols) = 255 - output.at<uchar>(rows, cols);
                break;
            case CV_8UC3:
                for(int rows=0; rows<output.rows; rows++)
                    for(int cols=0; cols<output.cols; cols++)
                        for(int channel=0; channel<output.channels(); channel++)
                            output.at<Vec3b>(rows, cols)[channel] = 255 - output.at<Vec3b>(rows, cols)[channel];
                break;
            default: cout << "This funtion only works with CV_8UC1 and CV_8UC3 source type." << endl;
        }
    }
}
