/*
    BGR Color Pad
    Author: Gustavo Murillo
    Date: June 2024

    Description: This program generates different types of gradients on a 1-channel and 3-channel image.
*/

#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

void channelColumnGradient(Mat& src, int channel);
void channelRowGradient(Mat& src, int channel);
void channelDiagonalGradient(Mat& src, int channel);
void grColumnGradient(Mat& src, int blue);
void bgColumnGradient(Mat& src, int red);
void brColumnGradient(Mat& src, int green);

int main(void)
{
    cout << "\n\t\t BGR Color Gradient \n";

    int imgRows = 350;
    int imgColumns = 350;
    Mat bluePad  = Mat::zeros(imgRows, imgColumns, CV_8UC3);
    Mat greenPad = Mat::zeros(imgRows, imgColumns, CV_8UC3);
    Mat redPad   = Mat::zeros(imgRows, imgColumns, CV_8UC3);

    Mat grayPad = Mat::zeros(imgRows, imgColumns, CV_8UC1);
    Mat colorPad = Mat::zeros(imgRows, imgColumns, CV_8UC3);

    //eyeGradient(grayPad);
    //eyeGradient(colorPad);

//    fillGR(colorPad);
    //imshow("Gray Pad", grayPad);
//    imshow("Color Pad", colorPad);

    // 1-channel Column Gradient
//    channelColumnGradient(bluePad, 0);
//    channelColumnGradient(greenPad, 1);
//    channelColumnGradient(redPad, 2);
//    imshow("Column Blue Gradient", bluePad);
//    imshow("Column Green Gradient", greenPad);
//    imshow("Column Red Gradient", redPad);

    // 1-channel Row Gradient
//    channelRowGradient(bluePad, 0);
//    channelRowGradient(greenPad, 1);
//    channelRowGradient(redPad, 2);
//    imshow("Row Blue Gradient", bluePad);
//    imshow("Row Green Gradient", greenPad);
//    imshow("Row Red Gradient", redPad);

    // 1-channel Diagonal Gradient
//    channelDiagonalGradient(bluePad, 0);
//    channelDiagonalGradient(greenPad, 1);
//    channelDiagonalGradient(redPad, 2);
//    imshow("Diagonal Blue Gradient", bluePad);
//    imshow("Diagonal Green Gradient", greenPad);
//    imshow("Diagonal Red Gradient", redPad);

    // Green-Red Gradient
//    channelDiagonalGradient(bluePad, 0);
//    channelDiagonalGradient(greenPad, 1);
//    channelDiagonalGradient(redPad, 2);
//    imshow("Diagonal Blue Gradient", bluePad);
//    imshow("Diagonal Green Gradient", greenPad);
//    imshow("Diagonal Red Gradient", redPad);

    // Green-Red Gradient
//    grColumnGradient(colorPad, 0);
//    imshow("Green-Red Gradient", colorPad);


    // Blue-Green Gradient
//    bgColumnGradient(colorPad, 0);
//    imshow("Blue-Green Gradient", colorPad);

    // Blue-Red Gradient
    brColumnGradient(colorPad, 0);
    imshow("Blue-Red Gradient", colorPad);

    imwrite("blueRedPad.png", colorPad);
//    imwrite("diagonalGreenPad.png", greenPad);
//    imwrite("diagonalRedPad.png", redPad);

    waitKey(0);
    return 0;
}


void channelColumnGradient(Mat& src, int channel)
{
    /** \brief Generates a gradient across the columns of an image
      * \param src: Image input
      * \param channel: Color channel in BGR format
    **/

    if(src.empty()) { cout << "Source empty" << endl; }

    switch(channel)
    {
        case 0:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    uchar bValue = (uchar)(255 * col / src.cols);
                    src.at<Vec3b>(row,col)[0] = bValue;
                    src.at<Vec3b>(row,col)[1] = 0;
                    src.at<Vec3b>(row,col)[2] = 0;
                }
            }
            break;
        case 1:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    uchar gValue = (uchar)(255 * col / src.cols);
                    src.at<Vec3b>(row,col)[0] = 0;
                    src.at<Vec3b>(row,col)[1] = gValue;
                    src.at<Vec3b>(row,col)[2] = 0;
                }
            }
            break;
        case 2:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    uchar rValue = (uchar)(255 * col / src.cols);
                    src.at<Vec3b>(row,col)[0] = 0;
                    src.at<Vec3b>(row,col)[1] = 0;
                    src.at<Vec3b>(row,col)[2] = rValue;
                }
            }
            break;
        default:
            cout << "Not defined..." << endl;
    }
}


void channelRowGradient(Mat& src, int channel)
{
    /** \brief Generates a gradient across the rows of an image
      * \param src: Image input
      * \param channel: Color channel in BGR format
    **/

    if(src.empty()) { cout << "Source empty" << endl; }

    switch(channel)
    {
        case 0:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    uchar bValue = (uchar)(255 * row / src.rows);
                    src.at<Vec3b>(row,col)[0] = bValue;
                    src.at<Vec3b>(row,col)[1] = 0;
                    src.at<Vec3b>(row,col)[2] = 0;
                }
            }
            break;
        case 1:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    uchar gValue = (uchar)(255 * row / src.rows);
                    src.at<Vec3b>(row,col)[0] = 0;
                    src.at<Vec3b>(row,col)[1] = gValue;
                    src.at<Vec3b>(row,col)[2] = 0;
                }
            }
            break;
        case 2:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    uchar rValue = (uchar)(255 * row / src.rows);
                    src.at<Vec3b>(row,col)[0] = 0;
                    src.at<Vec3b>(row,col)[1] = 0;
                    src.at<Vec3b>(row,col)[2] = rValue;
                }
            }
            break;
        default:
            cout << "Not defined..." << endl;
    }
}


void channelDiagonalGradient(Mat& src, int channel)
{
    /** \brief Generates a gradient across the diagonal of an image
      * \param src: Image input
      * \param channel: Color channel in BGR format
    **/

    if(src.empty()) { cout << "Source empty" << endl; }

    // Maximum length on the diagonal
    double max_dist = sqrt(pow(src.rows - 1, 2) + pow(src.cols - 1, 2));
    switch(channel)
    {
        case 0:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    double dist = sqrt(pow(row, 2) + pow(col, 2));
                    uchar bValue = (uchar)(255 * dist / max_dist);
                    src.at<Vec3b>(row,col)[0] = bValue;
                    src.at<Vec3b>(row,col)[1] = 0;
                    src.at<Vec3b>(row,col)[2] = 0;
                }
            }
            break;
        case 1:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    double dist = sqrt(pow(row, 2) + pow(col, 2));
                    uchar gValue = (uchar)(255 * dist / max_dist);
                    src.at<Vec3b>(row,col)[0] = 0;
                    src.at<Vec3b>(row,col)[1] = gValue;
                    src.at<Vec3b>(row,col)[2] = 0;
                }
            }
            break;
        case 2:
            for(int row=0; row < src.rows; row++)
            {
                for(int col=0; col < src.cols; col++)
                {
                    double dist = sqrt(pow(row, 2) + pow(col, 2));
                    uchar rValue = (uchar)(255 * dist / max_dist);
                    src.at<Vec3b>(row,col)[0] = 0;
                    src.at<Vec3b>(row,col)[1] = 0;
                    src.at<Vec3b>(row,col)[2] = rValue;
                }
            }
            break;
        default:
            cout << "Not defined..." << endl;
    }
}


void grColumnGradient(Mat& src, int blue)
{
    /** \brief Generates a column gradient on the plane Green-Red of an image
      * \param src: Image input
      * \param blue: Color value for channel blue
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}


    for(int row=0; row < src.rows; row++)
    {
        for(int col=0; col < src.cols; col++)
        {
            uchar gValue = (uchar)(255 * col / src.cols);
            uchar rValue = (uchar)(255 * col / src.cols);
            src.at<Vec3b>(row,col)[0] = blue;
            src.at<Vec3b>(row,col)[1] = gValue;
            src.at<Vec3b>(row,col)[2] = rValue;
        }
    }

}


void bgColumnGradient(Mat& src, int red)
{
    /** \brief Generates a column gradient on the plane Green-Red of an image
      * \param src: Image input
      * \param blue: Color value for channel blue
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}


    for(int row=0; row < src.rows; row++)
    {
        for(int col=0; col < src.cols; col++)
        {
            uchar bValue = (uchar)(255 * col / src.cols);
            uchar gValue = (uchar)(255 * col / src.cols);
            src.at<Vec3b>(row,col)[0] = bValue;
            src.at<Vec3b>(row,col)[1] = gValue;
            src.at<Vec3b>(row,col)[2] = red;
        }
    }

}


void brColumnGradient(Mat& src, int green)
{
    /** \brief Generates a column gradient on the plane Green-Red of an image
      * \param src: Image input
      * \param blue: Color value for channel blue
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}


    for(int row=0; row < src.rows; row++)
    {
        for(int col=0; col < src.cols; col++)
        {
            uchar bValue = (uchar)(255 * col / src.cols);
            uchar rValue = (uchar)(255 * col / src.cols);
            src.at<Vec3b>(row,col)[0] = bValue;
            src.at<Vec3b>(row,col)[1] = green;
            src.at<Vec3b>(row,col)[2] = rValue;
        }
    }

}
