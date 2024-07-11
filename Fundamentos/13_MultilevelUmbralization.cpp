#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void muGetImageData(Mat &imgSource);
void muImageBinarization(const Mat& input, Mat& output, const int umbral);
void multiLevelThresholding(const Mat& input, Mat& output, int numThresholds);
void multiLevelThresholding(const Mat& input, Mat& output, const vector<int>& thresholds);

int main(void)
{
    cout << "\n\t\tUmbralization\n";

    Mat Input, Gray, muBinarization, muUmbralization, OpenCVUmbralization;
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
    int umbral = 128;
    OpenCVUmbralization = Gray.clone();
    threshold(Gray, OpenCVUmbralization, umbral, maxVal, THRESH_BINARY);
    imshow("Image binarized by OpenCV", OpenCVUmbralization);

    // Binarization
    muBinarization = Gray.clone();
    muImageBinarization(Gray, muBinarization, umbral);
    imshow("Image binarized by mu", muBinarization);

    // Umbralización equidistante
    Mat nUmbralization = Gray.clone();
    int numThresholds = 2;
    multiLevelThresholding(Gray, nUmbralization, numThresholds);
    imshow("Image equidistantly binarized", nUmbralization);

    // Multilevel umbralization
    Mat multiLevelUmbralization = Gray.clone();
    vector<int> thresholds = {128, 255}; // Dos niveles: [0, 128), [128, 255]
    multiLevelThresholding(Gray, multiLevelUmbralization, thresholds);
    imshow("Image multilevel umbralization", multiLevelUmbralization);

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



// Image binarization
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


// Multilevel thresholding with equidistant thresholds
void multiLevelThresholding(const Mat& input, Mat& output, int numThresholds)
{
    int maxIntensity = 255;

    // Check if the input matrix has the same size as the output matrix
    if (input.size() != output.size())
    {
        cerr << "Error: Las matrices de entrada y salida deben tener el mismo tamaño." << endl;
        return;
    }

    // Getting the interval between thresholds
    int interval = (maxIntensity / numThresholds) + 1;

    // Assigning the corresponding value according to the threshold
    for (int i = 0; i < input.rows; i++)
    {
        for (int j = 0; j < input.cols; j++)
        {
            int pixelValue = input.at<uchar>(i, j);
            int newValue = 0;

            // Finding the threshold to which the pixel belongs
            for (int k = 0; k < numThresholds; k++)
            {
                if (pixelValue < (k + 1) * interval)
                {
                    newValue = k * (maxIntensity / (numThresholds-1) );
                    break;
                }
            }
            output.at<uchar>(i, j) = newValue;
        }
    }
}


// Multilevel thresholding with specific thresholds
void multiLevelThresholding(const Mat& input, Mat& output, const vector<int>& thresholds)
{
    // Check if the input matrix has the same size as the output matrix
    if (input.size() != output.size())
    {
        cerr << "Error: Las matrices de entrada y salida deben tener el mismo size." << endl;
        return;
    }

    // Checking if the thresholds are in ascending order
    for (size_t i = 1; i < thresholds.size(); i++)
    {
        if (thresholds[i] <= thresholds[i - 1])
        {
            cerr << "Error: Los umbrales deben estar en orden ascendente" << endl;
            return;
        }
    }

    // Assigning the corresponding value according to the threshold
    for (int i = 0; i < input.rows; i++)
    {
        for (int j = 0; j < input.cols; j++)
        {
            int pixelValue = input.at<uchar>(i, j);
            int newValue = 0;
            for (size_t k = 0; k < thresholds.size(); k++)
            {
                if (pixelValue < thresholds[k])
                {
                    newValue = k * (255 / (thresholds.size() - 1));
                    break;
                }
            }
            output.at<uchar>(i, j) = newValue;
        }
    }
}
