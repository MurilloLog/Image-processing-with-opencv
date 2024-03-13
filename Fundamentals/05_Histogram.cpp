#include <iostream>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

void muGetImageData(Mat& imgSource);

int main(void)
{
    cout << "\n\t\tHistogram of a grayscale image\n";

    Mat Input, Hist;
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;

    string src = "../cvImages/ImageTest.png";
    //string src = "../cvImages/cameraman.tif";
    //string src = "../cvImages/lena_gray.bmp";

    Input = imread(src, IMREAD_GRAYSCALE);
    if (Input.empty())
    {
        cout << "\nWrong filename or folder.\n" << endl;
        return false;
    }

    namedWindow("Input", WINDOW_AUTOSIZE);
    imshow("Input", Input);
    muGetImageData(Input);

    // Getting histogram using OpenCV
    //calcHist(image_reference, source_array, channel_dim, mask_if_it_desire, output_Mat_objet, histogram_dimensionality, histogram_size, histogram_bins, is_uniform, is_accumulative)
    calcHist(&Input, 1, 0, Mat(), Hist, 1, &histSize, histRange, uniform, accumulate );

    // Showing histogram image
    //histImage(height, width, image_type, background_color)
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(Hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(Hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
    }

    namedWindow("Histogram", WINDOW_AUTOSIZE);
    imshow("Histogram", histImage );

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
