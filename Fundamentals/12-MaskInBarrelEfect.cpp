/*
    Mask on an image
    Author: Gustavo Murillo
    Date: February 2024

    Description: In this program, a dynamic mask is
    designed and implemented over an input image using
    a second image.
    The output reveals the original image through a
    dynamic mask that is moving around a hidden area
    as the "barrel" effect.
*/

// I/O C++ library
#include <iostream>

// OpenCV libraries
#include <core.hpp>
#include <highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

/* Classes definition */
class PixelPosition
{
    private:
        int x;
        int y;
        bool xDirection;
        bool yDirection;
        bool inColor;
    public:
        // Constructor
        PixelPosition(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

        // Methods
        int getX() const { return x; }
        int getY() const { return y; }
        bool getInColor() { return inColor; }
        void setX(int setX) { x = setX; }
        void setY(int setY) { y = setY; }
        void setDirectionX() {xDirection = true; inColor = true;}
        void setDirectionY() {yDirection = true; }
        void toogleColor() { inColor = !inColor; }
        bool toogleDirection(int radius, Mat& src)
        {
            // If the mask touch any image limit, change its direction
            if( ((x-radius)<=0) || ((x+radius)>=src.cols)){
                xDirection=!xDirection; inColor = !inColor;}

            if( ((y-radius)<=0) || ((y+radius)>=src.rows)){
                yDirection=!yDirection; inColor = !inColor;}

            (xDirection) ? x++ : x--;
            (yDirection) ? y+=3 : y-=3;
        }
};

/* Function prototypes */
void muDrawACircleMask(Mat& src, int radius, int line, int color, PixelPosition& maskPixelOrigin);
void muCreateMask(const Mat& imgSrc, const Mat& imgMask, Mat& imgResult, PixelPosition& maskStatus);
void muClearMask(Mat& mask);
void getImageData(Mat& imgSource);

int main(void)
{
    cout << "\n\t\tPDI - Tarea 01\n" << endl;
    cout << "Procesamiento digital de imagenes" << endl;
    cout << "Gustavo Adolfo Murillo Gutierrez" << endl;
    cout << "MIE" << endl;

    // Verification data
    string filename = "../cvImages/ImageTest.png";
    Mat imgInput;
    imgInput = imread(filename);
    if (imgInput.empty())
    {
        cout << "\nWrong filename or folder.\n" << endl;
        return false;
    }

    // Processing image data
    Mat imgOutput, imgGrayOutput, mask;
    PixelPosition maskPixelOrigin(50,50);
    int radius = 45;
    int areaFilling = -1;
    int updateFrame_ms = 1;
    int maskColor = 255;

    imgOutput = Mat(imgInput.rows, imgInput.cols, imgInput.type(), Scalar{0,0,0});
    maskPixelOrigin.setDirectionX();
    maskPixelOrigin.setDirectionY();

    // Creating mask
    mask.create(imgInput.rows, imgInput.cols, CV_8UC1);
    muClearMask(mask);

    // Barring mask until you press any "arrow" key
    while(waitKey(updateFrame_ms))
    {
        muDrawACircleMask(mask, radius, areaFilling, maskColor, maskPixelOrigin);
        muCreateMask(imgInput, mask, imgOutput, maskPixelOrigin);

        imshow("Barrel effect", imgOutput);

        muClearMask(mask);
    }

    return 1;
}

// Function to draw a filled circle using a specific position
void muDrawACircleMask(Mat& src, int radius, int line, int color, PixelPosition& maskPixelOrigin)
{
    maskPixelOrigin.toogleDirection(radius, src);
    circle(src,
           Point(maskPixelOrigin.getX(), maskPixelOrigin.getY()),
           radius,
           color,
           line,
           LINE_AA,
           0
           );
}

// Function to create a mask over an image
void muCreateMask(const Mat& imgSrc, const Mat& imgMask, Mat& imgResult, PixelPosition& maskStatus)
{
    if(maskStatus.getInColor())
    {
        for(int row=0; row<imgSrc.rows; row++)
        for(int col=0; col<imgSrc.cols; col++)
            if (imgMask.at<uchar>(row, col) == 255)
                imgResult.at<Vec3b>(row, col) = imgSrc.at<Vec3b>(row, col);
            else
                imgResult.at<Vec3b>(row, col) = {0,0,0};
    }
    else

    {
        Mat imgGrayOutput;
        cv::cvtColor(imgSrc, imgGrayOutput, cv::COLOR_BGR2GRAY);
        for(int row=0; row<imgSrc.rows; row++)
        for(int col=0; col<imgSrc.cols; col++)
            if (imgMask.at<uchar>(row, col) == 255)
                imgResult.at<Vec3b>(row, col) = imgGrayOutput.at<uchar>(row, col);
            else
                imgResult.at<Vec3b>(row, col) = {0,0,0};
    }
}

// Function to clear a mask
void muClearMask(Mat& mask)
{
    for(int row=0; row<mask.rows; row++)
        for(int col=0; col<mask.cols; col++)
            mask.at<uchar>(row, col) = {0};
}

// Function to get columns, rows and channels from an image
void getImageData(Mat& imgSource)
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