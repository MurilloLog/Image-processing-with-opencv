#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>

using namespace std;
using namespace cv;

void muGetImageData(Mat &imgSource);
void muGetContour(Mat &Input);
void FindNextPixelContour(int dir, int i, int j, Mat& Input, int& Inew, int& Jnew, int &dirA);
int PreviousDir(int ia, int ja, int in, int jn);

int main(void)
{
    Mat Input;
    string source = "lightning.bmp";
//  string source = "cloud.bmp";
//  string source = "star.bmp";

//  Reading image
    Input = imread(source, IMREAD_UNCHANGED);
    muGetImageData(Input);
    if (Input.empty())
    {
        cout << "\nWrong filename or folder.\n" << endl;
        return false;
    }

    muGetContour(Input);

    // Saving image
    imshow("Contour", Input);
    imwrite("Output.jpg", Input);
    waitKey(0);
    return true;
}


// Function to get pixel contour
void muGetContour(Mat &Input)
{
    //  Initial variables
    int dirA, high, wide, Rini_i, Rini_j, Rfin_i, Rfin_j;

    // Initial Pixel Identification
    float r, g, b;
    int Is, Js, Iact, Jact, Inew, Jnew;
    for(int i=0; i<Input.rows; i++)
        for(int j=0; j<Input.cols; j++)
        {
            r = (float)Input.at<Vec3b>(i,j)[0];
            //g = (float)Input.at<Vec3b>(i,j)[1];
            //b = (float)Input.at<Vec3b>(i,j)[2];
            if(r == 0)
            {
                Input.at<Vec3b>(i,j)[0] = 0;
                Input.at<Vec3b>(i,j)[1] = 0;
                Input.at<Vec3b>(i,j)[2] = 255;
                Iact = i;
                Jact = j;
                i = Input.rows;
                break;
            }
        }
    Is = Iact;
    Js = Jact;
    int dir = 4;

    do
    {
        FindNextPixelContour(dir, Iact, Jact, Input, Inew, Jnew, dirA);
        Iact = Inew;
        Jact = Jnew;
        dir = dirA;
        // perimetro++;
    }
    while(!((Is == Inew)&&(Js == Jnew)));
}


// Function to get next pixel contour
void FindNextPixelContour(int dir, int i, int j, Mat& Input, int& Inew, int& Jnew, int &dirA)
{
    float r;
    int ia = i;
    int ja = j;

    for(int k=0; k<7;k++)
    {
        i = ia;
        j = ja;

        dir-=1;
        if(dir<0)
            dir = 7;
        switch(dir)
        {
            case 0:
                j+=1;
                break;
            case 1:
                i-=1;
                j+=1;
                break;
            case 2:
                i-=1;
                break;
            case 3:
                i-=1;
                j-=1;
                break;
            case 4:
                j-=1;
                break;
            case 5:
                i+=1;
                j-=1;
                break;
            case 6:
                i+=1;
                break;
            case 7:
                j+=1;
                i+=1;
                break;
            default:
                break;
        }
        r = (float)Input.at<Vec3b>(i,j)[0];
        if(r == 0)
        {
            Input.at<Vec3b>(i,j)[0] = 0;
            Input.at<Vec3b>(i,j)[1] = 255;
            Input.at<Vec3b>(i,j)[2] = 0;
            Inew = i;
            Jnew = j;
            dirA = PreviousDir(ia, ja, Inew, Jnew);
            break;
        }
    }
}


// Function to get previous contour pixel direction
int PreviousDir(int ia, int ja, int in, int jn)
{
    int difi, difj;
    difi = in-ia;
    difj = jn-ja;
    if((difi == 0) && (difj == -1))
        return 0;
    if((difi == 1) && (difj == -1))
        return 1;
    if((difi == 1) && (difj == 0))
        return 2;
    if((difi == 1) && (difj == 1))
        return 3;
    if((difi ==0) && (difj ==1))
        return 4;
    if((difi == -1) && (difj == 1))
        return 5;
    if((difi == -1) && (difj == 0))
        return 6;
    if((difi == -1) && (difj == -1))
        return 7;
    return 0;
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
