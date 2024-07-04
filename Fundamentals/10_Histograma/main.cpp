#include <iostream>
using namespace std;

#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
using namespace cv;

bool histogram(string winTitle, const Mat& src, bool std0_cum1);
//int imgMonoHistogramShow(string winTitle, const Mat &src, bool isCumulative);

int main(void)
{
    cout << "Histograma de una imagen" << endl;
    string filename = "../cvImages/cameraman.tif";
    //string filename = "../cvImages/lena_gray.bmp";
    //string filename = "../cvImages/ImageTest.png";

    // Lectura de la imagen
    Mat input = imread(filename, IMREAD_COLOR);
    if(input.empty())
    {
        cout << "La imagen se encuentra vacia" << endl;
        return -1;
    }
    else
    {
        imshow("Imagen de entrada", input);
        histogram("Histograma estandar", input, 0);
        histogram("Histograma acumulativo", input, 1);
        waitKey();
        return 0;
    }
}

bool histogram(string winTitle, const Mat& src, bool std0_cum1)
{
   /** \brief Muestra el histograma de una imagen de 1 o 3 canales
   *
   * \param winTitle. Nombre de la ventana donde se mostrara el histograma
   * \param src. Imagen de entrada
   * \param std0_cum1. 0 para indicar si se calcula el histograma estandar o 1 si es el acumulativo
   * \return bool.
   *
   */

   int histSize = 256;
   float range[] = { 0, 256 };
   const float* histRange[] = { range };
   bool uniform = true, accumulate = false;

   int hist_w = 512, hist_h = 400;
   int bin_w = cvRound( (double) hist_w/histSize );

   Mat histImage( hist_h, hist_w, CV_8UC3, Scalar(128,128,128) );

   switch( src.channels() )
   {
      case 1:
      {
         Mat y_hist;
         calcHist( &src, 1, 0, Mat(), y_hist,
                  1, &histSize, histRange, uniform, accumulate );

         // Si es histograma acumulativo
         if ( std0_cum1 )
         {
            for (int i = 1; i < histSize; i++)
               y_hist.at<float>(i) += y_hist.at<float>(i - 1);
         }
         normalize(y_hist, y_hist, 0, histImage.rows,
                   NORM_MINMAX, -1, Mat() );

         // Dibujar histograma
         for( int i = 1; i < histSize; i++ )
         {
            line( histImage, Point( bin_w*(i-1),
                  hist_h - cvRound(y_hist.at<float>(i-1)) ),
                  Point( bin_w*(i), hist_h - cvRound(y_hist.at<float>(i)) ),
                  Scalar( 0, 255, 0), 2, 8, 0  );
         }
      }
      break;

      case 3:
      {
         vector<Mat> bgr_planes;
         split( src, bgr_planes );
         Mat b_hist, g_hist, r_hist;
         calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
         calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate );
         calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate );

         if (std0_cum1)
         {
            for (int i = 1; i < histSize; i++)
            {
               b_hist.at<float>(i) += b_hist.at<float>(i - 1);
               g_hist.at<float>(i) += g_hist.at<float>(i - 1);
               r_hist.at<float>(i) += r_hist.at<float>(i - 1);
            }
         }

         normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
         normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
         normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

         for( int i = 1; i < histSize; i++ )
         {
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
                 Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                 Scalar( 255, 0, 0), 2, 8, 0  ); // blue line
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
                 Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                 Scalar( 0, 255, 0), 2, 8, 0  ); // green line
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
                 Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                 Scalar( 0, 0, 255), 2, 8, 0  ); // red line
         }
      }
      break;

      default:
          cout << "\n Esta funcion solo esta definida para imagenes de 3 o 1 canal" << endl;
   }

   namedWindow(winTitle, WINDOW_NORMAL);
   imshow(winTitle, histImage);
   return true;
}
