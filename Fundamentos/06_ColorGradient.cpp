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
void grColumnRowGradient(Mat& src, int blue);
void bgColumnRowGradient(Mat& src, int red);
void brColumnRowGradient(Mat& src, int green);
void muColumnGradient(Mat& src);
void muRowGradient(Mat& src);
void muDiagonalGradient(Mat& src);
void muColumnRowGradient(Mat& src, int channel, int value);
void muGradientTest();

int main(void)
{
    cout << "\n\t\t BGR Color Gradient \n";
    muGradientTest();

    return 0;
}


void muGradientTest()
{
    int imgRows = 350;
    int imgColumns = 350;

    Mat grayPad  = Mat::zeros(imgRows, imgColumns, CV_8UC1);
    Mat bluePad  = Mat::zeros(imgRows, imgColumns, CV_8UC3);
    Mat greenPad = Mat::zeros(imgRows, imgColumns, CV_8UC3);
    Mat redPad   = Mat::zeros(imgRows, imgColumns, CV_8UC3);

    Mat colorPad = Mat::zeros(imgRows, imgColumns, CV_8UC3);

    //  Monochrome Column Gradient
    muColumnGradient(grayPad);
    imshow("Monochrome Column Gradient", grayPad);

    // Monochrome Row Gradient
    muRowGradient(grayPad);
    imshow("Monochrome Row Gradient", grayPad);

    // Monochrome Diagonal Gradient
    muDiagonalGradient(grayPad);
    imshow("Monochrome Diagonal Gradient", grayPad);

    // 1-channel Column Gradient
    channelColumnGradient(bluePad, 0);
    channelColumnGradient(greenPad, 1);
    channelColumnGradient(redPad, 2);
    imshow("Column Blue Gradient", bluePad);
    imshow("Column Green Gradient", greenPad);
    imshow("Column Red Gradient", redPad);

    // 1-channel Row Gradient
    channelRowGradient(bluePad, 0);
    channelRowGradient(greenPad, 1);
    channelRowGradient(redPad, 2);
    imshow("Row Blue Gradient", bluePad);
    imshow("Row Green Gradient", greenPad);
    imshow("Row Red Gradient", redPad);

    // 1-channel Diagonal Gradient
    channelDiagonalGradient(bluePad, 0);
    channelDiagonalGradient(greenPad, 1);
    channelDiagonalGradient(redPad, 2);
    imshow("Diagonal Blue Gradient", bluePad);
    imshow("Diagonal Green Gradient", greenPad);
    imshow("Diagonal Red Gradient", redPad);

    // Green-Red Gradient
    channelDiagonalGradient(bluePad, 0);
    channelDiagonalGradient(greenPad, 1);
    channelDiagonalGradient(redPad, 2);
    imshow("Diagonal Blue Gradient", bluePad);
    imshow("Diagonal Green Gradient", greenPad);
    imshow("Diagonal Red Gradient", redPad);

    // Green-Red Gradient
    grColumnGradient(colorPad, 0);
    imshow("Green-Red Gradient", colorPad);


    // Blue-Green Gradient
    bgColumnGradient(colorPad, 0);
    imshow("Blue-Green Gradient", colorPad);

    // Blue-Red Gradient
    brColumnGradient(colorPad, 0);
    imshow("Blue-Red Gradient", colorPad);

    // Green-Red Column Row Gradient
    grColumnRowGradient(colorPad, 255);
    imshow("Green-Red Column-Row Gradient", colorPad);

    // Green-Red Column Row Gradient
    bgColumnRowGradient(colorPad, 255);
    imshow("Blue-Green Column-Row Gradient", colorPad);

    // Green-Red Column Row Gradient
    brColumnRowGradient(colorPad, 255);
    imshow("Blue-Red Column-Row Gradient", colorPad);

    // Color Column-Row Gradient
    muColumnRowGradient(colorPad, 0, 255); // Plano Green-Red
    imshow("Color Column-Row Gradient", colorPad);

    waitKey(0);
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


void grColumnRowGradient(Mat& src, int blue)
{
    /** \brief Generates a column x row gradient on the plane Green-Red of an image
      * \param src: Image input
      * \param blue: Color value for channel blue
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}


    for(int row=0; row < src.rows; row++)
    {
        for(int col=0; col < src.cols; col++)
        {
            uchar gValue = (uchar)(255 * col / src.cols);
            uchar rValue = (uchar)(255 * row / src.rows);
            src.at<Vec3b>(row,col)[0] = blue;
            src.at<Vec3b>(row,col)[1] = gValue;
            src.at<Vec3b>(row,col)[2] = rValue;
        }
    }

}

void bgColumnRowGradient(Mat& src, int red)
{
    /** \brief Generates a column x row gradient on the plane Blue-Green of an image
      * \param src: Image input
      * \param blue: Color value for channel red
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}


    for(int row=0; row < src.rows; row++)
    {
        for(int col=0; col < src.cols; col++)
        {
            uchar bValue = (uchar)(255 * col / src.cols);
            uchar gValue = (uchar)(255 * row / src.rows);
            src.at<Vec3b>(row,col)[0] = bValue;
            src.at<Vec3b>(row,col)[1] = gValue;
            src.at<Vec3b>(row,col)[2] = red;
        }
    }

}


void brColumnRowGradient(Mat& src, int green)
{
    /** \brief Generates a column x row gradient on the plane Blue-Red of an image
      * \param src: Image input
      * \param blue: Color value for channel green
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}


    for(int row=0; row < src.rows; row++)
    {
        for(int col=0; col < src.cols; col++)
        {
            uchar bValue = (uchar)(255 * col / src.cols);
            uchar rValue = (uchar)(255 * row / src.rows);
            src.at<Vec3b>(row,col)[0] = bValue;
            src.at<Vec3b>(row,col)[1] = green;
            src.at<Vec3b>(row,col)[2] = rValue;
        }
    }

}


void muColumnGradient(Mat& src)
{
    /** \brief Generates a gradient across the columns of all image's channels
      * \param src: Image input
    **/

    if(src.empty()) { cout << "Source empty" << endl; }

    if(src.channels() == 1)
    {
        for(int row=0; row < src.rows; row++)
            for(int col=0; col < src.cols; col++)
            {
                uchar value = (uchar)(255 * col / src.cols);
                src.at<uchar>(row,col) = value;
            }
    }
    else if(src.channels() == 3)
    {
        for(int row=0; row < src.rows; row++)
            for(int col=0; col < src.cols; col++)
            {
                uchar value = (uchar)(255 * col / src.cols);
                src.at<Vec3b>(row,col)[0] = value;
                src.at<Vec3b>(row,col)[1] = value;
                src.at<Vec3b>(row,col)[2] = value;
            }
    }
}


void muRowGradient(Mat& src)
{
    /** \brief Generates a gradient across the rows of all image's channels
      * \param src: Image input
    **/

    if(src.empty()) { cout << "Source empty" << endl; }

    if(src.channels() == 1)
    {
        for(int row=0; row < src.rows; row++)
            for(int col=0; col < src.cols; col++)
            {
                uchar value = (uchar)(255 * row / src.rows);
                src.at<uchar>(row,col) = value;
            }
    }
    else if(src.channels() == 3)
    {
        for(int row=0; row < src.rows; row++)
            for(int col=0; col < src.cols; col++)
            {
                uchar value = (uchar)(255 * row / src.rows);
                src.at<Vec3b>(row,col)[0] = value;
                src.at<Vec3b>(row,col)[1] = value;
                src.at<Vec3b>(row,col)[2] = value;
            }
    }
}


void muDiagonalGradient(Mat& src)
{
    /** \brief Generates a diagonal gradient
      * \param src: Image input
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}

    // Maximum length on the diagonal
    double max_dist = sqrt(pow(src.rows - 1, 2) + pow(src.cols - 1, 2));
    for(int row=0; row < src.rows; row++)
        for(int col=0; col < src.cols; col++)
        {
            double dist = sqrt(pow(row, 2) + pow(col, 2));
            uchar value = (uchar)(255 * dist / max_dist);
            src.at<uchar>(row,col) = value;
        }
}


void muColumnRowGradient(Mat& src, int channel, int value)
{
    /** \brief Generates a column x row gradient selecting a specific plane-value of an image
      * \param src: Image input
      * \param channel: Channel that you want to modify
      * \param value: Color value for the channel selected
    **/

    if(src.empty()) { cout<<"Source empty"<<endl;}

    switch(channel)
    {
        case 0:
            for(int row=0; row < src.rows; row++)
                for(int col=0; col < src.cols; col++)
                {
                    uchar gValue = (uchar)(255 * col / src.cols);
                    uchar rValue = (uchar)(255 * row / src.rows);
                    src.at<Vec3b>(row,col)[0] = value;
                    src.at<Vec3b>(row,col)[1] = gValue;
                    src.at<Vec3b>(row,col)[2] = rValue;
                }
            break;

        case 1:
            for(int row=0; row < src.rows; row++)
                for(int col=0; col < src.cols; col++)
                {
                    uchar bValue = (uchar)(255 * col / src.cols);
                    uchar rValue = (uchar)(255 * row / src.rows);
                    src.at<Vec3b>(row,col)[0] = bValue;
                    src.at<Vec3b>(row,col)[1] = value;
                    src.at<Vec3b>(row,col)[2] = rValue;
                }
            break;

        case 2:
            for(int row=0; row < src.rows; row++)
                for(int col=0; col < src.cols; col++)
                {
                    uchar bValue = (uchar)(255 * col / src.cols);
                    uchar gValue = (uchar)(255 * row / src.rows);
                    src.at<Vec3b>(row,col)[0] = bValue;
                    src.at<Vec3b>(row,col)[1] = gValue;
                    src.at<Vec3b>(row,col)[2] = value;
                }
            break;

        default:
            cout << "Channel not supported..." << endl;

    }
}

