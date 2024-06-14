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

void fillGR(Mat& src);
void eyeGradient(Mat& src);

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
    channelRowGradient(bluePad, 0);
    channelRowGradient(greenPad, 1);
    channelRowGradient(redPad, 2);
    imshow("Row Blue Gradient", bluePad);
    imshow("Row Green Gradient", greenPad);
    imshow("Row Red Gradient", redPad);

    imwrite("rowBluePad.png", bluePad);
    imwrite("rowGreenPad.png", greenPad);
    imwrite("rowRedPad.png", redPad);

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


void eyeGradient(Mat& src)
{
    if(src.empty()) { cout<<"Source empty"<<endl;}

    // Longitud maxima en la diagonal
    double max_dist = sqrt(pow(src.rows - 1, 2) + pow(src.cols - 1, 2));

    if(src.channels()==1)
    {
        for(int row=0; row < src.rows; row++)
            for(int col=0; col < src.cols; col++){
                // Calcular la distancia del pixel actual al origen (0,0)
                double dist = sqrt(pow(row, 2) + pow(col, 2));
                // Mapear la distancia a una escala de 0 a 255
                uchar value = (uchar)(255 * dist / max_dist);
                src.at<uchar>(row,col) = value;
            }
    }

    else if(src.channels()==3)
    {
        for(int row=0; row < src.rows; row++)
            for(int col=0; col < src.cols; col++)
            {
                // Calcular la distancia del píxel actual al origen (0,0)
                double dist = sqrt(pow(row, 2) + pow(col, 2));
                // Mapear la distancia a una escala de 0 a 255
                uchar value = (uchar)(255 * dist / max_dist);
                // Asignar el valor de intensidad a los tres canales (BGR)
                src.at<Vec3b>(row,col)[1] = value;
                //src.at<Vec3b>(row,col)[2] = value;
                //src.at<Vec3b>(row,col)[0] = 255;
            }
    }
}

void fillGR(Mat& src)
{
    if(src.empty()) { cout<<"Source empty"<<endl;}

    // Filling
    for(int row=0; row < src.rows; row++)
    {
        for(int col=0; col < src.cols; col++)
        {
            uchar gValue = (uchar)(255 * col / src.cols);
            uchar rValue = (uchar)(255 * row / src.rows);
            src.at<Vec3b>(row,col)[0] = gValue;
//            src.at<Vec3b>(row,col)[1] = gValue;
            src.at<Vec3b>(row,col)[2] = rValue;
        }
    }


}

