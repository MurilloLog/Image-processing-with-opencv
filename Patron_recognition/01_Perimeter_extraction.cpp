#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>

using namespace std;
using namespace cv;

/* Classes definition */
class muFigure
{
    private:
        int wide;
        int high;
        int perimeter;
        int area;
        int xCentroid;
        int yCentroid;
        int xIniBoundingBox;
        int yIniBoundingBox;
    public:
        muFigure() : wide(0), high(0), perimeter(0), area(0), xCentroid(0), yCentroid(0), xIniBoundingBox(0), yIniBoundingBox(0) {}
        muFigure(int w, int h, int p, int a, int xC, int yC, int xBB, int yBB) : wide(w), high(h), perimeter(p), area(a), xCentroid(xC), yCentroid(yC), xIniBoundingBox(xBB), yIniBoundingBox(yBB) {}

        // Setters
        void setWide(int w) { wide = w; }
        void setHigh(int h) { high = h; }
        void setPerimeter(int p) { perimeter = p; }
        void setArea(int a) { area = a; }
        void setXCentroid(int xC) { xCentroid = xC; }
        void setYCentroid(int yC) { yCentroid = yC; }
        void setXIniBoundingBox(int xBB) { xIniBoundingBox = xBB; }
        void setYIniBoundingBox(int yBB) { yIniBoundingBox = yBB; }

        // Getters
        int getWide() const { return wide; }
        int getHigh() const { return high; }
        int getPerimeter() const { return perimeter; }
        int getArea() const { return area; }
        int getXCentroid() const { return xCentroid; }
        int getYCentroid() const { return yCentroid; }
        int getXIniBoundingBox() const { return xIniBoundingBox; }
        int getYIniBoundingBox() const { return yIniBoundingBox; }

        void getData() const
        {
            std::cout << "Wide: " << wide << std::endl;
            std::cout << "High: " << high << std::endl;
            std::cout << "Perimeter: " << perimeter << std::endl;
            std::cout << "Area: " << area << std::endl;
            std::cout << "X Centroid: " << xCentroid << std::endl;
            std::cout << "Y Centroid: " << yCentroid << std::endl;
            std::cout << "X Initial Bounding Box: " << xIniBoundingBox << std::endl;
            std::cout << "Y Initial Bounding Box: " << yIniBoundingBox << std::endl;
        }
};

void muGetImageData(Mat &imgSource);
void muGetContour(Mat &Input, muFigure &Fig);
void FindNextPixelContour(int dir, int i, int j, Mat& Input, int& Inew, int& Jnew, int &dirA);
int PreviousDir(int ia, int ja, int in, int jn);

int main(void)
{
    Mat Input;
    muFigure Figure;

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

    muGetContour(Input, Figure);

    // Showing figure data
    Figure.getData();

    // Saving image
    imshow("Contour", Input);
    imwrite("Output.jpg", Input);
    waitKey(0);
    return true;
}


// Function to get pixel contour
void muGetContour(Mat &Input, muFigure &Fig)
{
    //  Initial variables
    int dirA, high, wide, Rini_i, Rini_j, Rfin_i, Rfin_j;
    int perimeter = 0;
    int area = 0;

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
        perimeter++;
    }
    while(!((Is == Inew)&&(Js == Jnew)));

    // Area
    for(int i=0; i<Input.rows; i++)
        for(int j=0; j<Input.cols; j++)
        {
            r = (float)Input.at<Vec3b>(i,j)[0];
            if(r==0)
            {
                area++;
            }
        }

    // Bounding box
    int ymin, ymax, xmin, xmax;
    int rini_i, rini_j, rfin_i, rfin_j;
    int cx, cy;
    xmax = 0;
    xmin = Input.cols;
    ymax = 0;
    ymin = Input.rows;

    for(int i = 0; i < Input.rows ; i++)
        for(int j = 0; j < Input.cols; j++)
        {
            r = (float)Input.at<Vec3b>(i,j)[0];
            if(r == 0)
            {
                if(i < ymin) ymin = i;
                if(i > ymax) ymax = i;
                if(j < xmin) xmin = j;
                if(j > xmax) xmax = j;
            }
        }
    Fig.setHigh(ymax - ymin);
    Fig.setWide(xmax - xmin);

    rini_i = ymin;
    rini_j = xmin;
    rfin_i = ymax;
    rfin_j = xmax;

    for(int j = rini_j; j < rfin_j; j++)
    {
        Input.at<Vec3b>(rini_i,j)[0] = 0;
        Input.at<Vec3b>(rini_i,j)[1] = 0;
        Input.at<Vec3b>(rini_i,j)[2] = 255;
        Input.at<Vec3b>(rfin_i,j)[0] = 0;
        Input.at<Vec3b>(rfin_i,j)[1] = 0;
        Input.at<Vec3b>(rfin_i,j)[2] = 255;
    }
    for(int i = rini_i; i < rfin_i; i++)
    {
        Input.at<Vec3b>(i,rini_j)[0] = 0;
        Input.at<Vec3b>(i,rini_j)[1] = 0;
        Input.at<Vec3b>(i,rini_j)[2] = 255;
        Input.at<Vec3b>(i,rfin_j)[0] = 0;
        Input.at<Vec3b>(i,rfin_j)[1] = 0;
        Input.at<Vec3b>(i,rfin_j)[2] = 255;
    }

    // Centroid
    cx = (rfin_j - rini_j)/2 + rini_j;
	cy = (rfin_i - rini_i)/2 + rini_i;
	Input.at<Vec3b>(cy,cx)[0] = 0;
	Input.at<Vec3b>(cy,cx)[1] = 0;
    Input.at<Vec3b>(cy,cx)[2] = 255;

    Fig.setPerimeter(perimeter);
    Fig.setArea(area);
    Fig.setXIniBoundingBox(rini_j);
    Fig.setYIniBoundingBox(rini_i);
    Fig.setXCentroid(cx);
    Fig.setYCentroid(cy);

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
