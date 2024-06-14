/*
    Imagenes con OpenCV
    Autor: Gustavo Murillo
    Fecha: Junio de 2024

    Descripcion: Acceso a pixeles en datos Mat
*/

#include <iostream>
#include <core.hpp>
#include <highgui.hpp>

using namespace std;
using namespace cv;

int ImgNegative(const Mat &src, Mat &out);
int ImgNegative(Mat &src);
int ImgNegativeUsingAt(const Mat& Mono, Mat& Neg3);
int MatImage(void)
{
//
//    // No es la mejor manera de manipular pixeles, pero es la mas rapida e intuitiva
//    for(int r=0; r<Input.rows; r++)
//        for(int c=0; c<Input.cols; c++)
//        {
//            Input.at<uchar>(r,c) = c;
//        }
//    imshow("Input", Input);
//    //imwrite("Degraded.jpg", Input);

    return 0;
}

int pixelAccess_Test(void);

int main(void) { pixelAccess_Test(); return 0; }

int pixelAccess_Test()
{
    cout << "\n\t\tAcceso a pixeles \n";
    string filename = "../images/lena_gray.bmp";

    Mat Mono;
    Mono = imread(filename, IMREAD_GRAYSCALE);
    if (Mono.empty()) { cout << "\nInput file not found." << endl; return -1;}
    imshow("Mono", Mono);

//    // Negativo de una imagen
//    Mat Neg1;
//    // ¿Que recibo si accedo a los datos de Neg1?
//    ImgNegative(Mono, Neg1);
//    imshow("Negativo Monocromatico", Neg1);
//
//    // Negativo de una imagen sobre la misma imagen
//    ImgNegative(Neg1);
//    imshow("Negativo Monocromatico 2", Neg1);
//
//    // Negativo de una imagen a color
//    Mat Neg2;
    string filenameColor = "../images/color.jpg";
    Mat Color;
    Color = imread(filenameColor, IMREAD_COLOR);
//    ImgNegative(Color, Neg2);
//    imshow("Negativo color", Neg2);

    // Negativo de una imagen usando At
    Mat Neg3;
    ImgNegativeUsingAt(Mono, Neg3);
    imshow("Negativo Monocromatico usando At", Neg3);

    // Negativo de una imagen a color usando At
    Mat Color4;
    ImgNegativeUsingAt(Color, Color4);
    imshow("Negativo Monocromatico en color usando At", Color4);

    waitKey(0);
}

int ImgNegative(const Mat &src, Mat &out)
{
    /** \brief El negativo de una imagen de entrada usando
      * \param src: Imagen de entrada
      * \param out: Imagen modificada
      * \return out
    **/

    if(src.empty())
    {
        cout << "Imagen vacia" << endl; return -1;
    }
    if(out.empty())
        out = src.clone();
    else{
        cout << "Imagen de salida no vacia" << endl; return -1;
    }

    if(out.channels()==1)
       out = 255-out;
    else if(out.channels()==3)
        out = Scalar(255, 255, 255) - out;
}

int ImgNegative(Mat &src)
{
    /** \brief El negativo de una imagen de entrada usando
      * \param src: Imagen de entrada
      * \param out: Imagen modificada
      * \return out
    **/

    if(src.empty())
    {
        cout << "Imagen vacia" << endl; return -1;
    }
    if(src.channels()==1)
       src = 255-src;
    else if(src.channels()==3)
        src = Scalar(255, 255, 255) - src;
}

int ImgNegativeUsingAt(const Mat &src, Mat &out)
{
    /** \brief El negativo de una imagen de entrada usando
      * \param src: Imagen de entrada
      * \param out: Imagen modificada
      * \return out
    **/

    if(src.empty())
    {
        cout << "Imagen vacia" << endl; return -1;
    }
    if(out.empty())
        out = src.clone();
    else{
        cout << "Imagen de salida no vacia" << endl; return -1;
    }


    switch(src.type())
    {
        case CV_8UC1:
            for(int r=0; r<src.rows; r++)
                for(int c=0; c<src.cols; c++)
                {
                    out.at<uchar>(r,c) = 255 - src.at<uchar>(r, c);
                }
            break;

        case CV_8UC3:
            for(int r=0; r<src.rows; r++)
                for(int c=0; c<src.cols; c++)
                {
                    out.at<Vec3b>(r,c)[0] = 255 - src.at<Vec3b>(r,c)[0];
                    out.at<Vec3b>(r,c)[1] = 255 - src.at<Vec3b>(r,c)[1];
                    out.at<Vec3b>(r,c)[2] = 255 - src.at<Vec3b>(r,c)[2];
                }
            break;

        case CV_32FC1:
            for(int r=0; r<src.rows; r++)
                for(int c=0; c<src.cols; c++)
                {
                    out.at<float>(r,c) = 255 - src.at<float>(r, c);
                }
            break;

        case CV_32FC3:
            for(int r=0; r<src.rows; r++)
                for(int c=0; c<src.cols; c++)
                    for(int ch=0; ch<src.channels(); ch++)
                    {
                        out.at<Vec3b>(r,c)[ch] = 255.0 - src.at<Vec3b>(r,c)[ch];
                    }
            break;

        default: cout << src.type() << ".\n";
    }
}
