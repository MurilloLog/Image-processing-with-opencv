/*
    Recuperacion de la posicion y orientacion de marcadores de realidad aumentada (AR tags)
    Author: Gustavo Murillo
    Date: July 2024

    Description:

    Referencia: https://docs.opencv.org/4.x/d5/dae/tutorial_aruco_detection.html
*/

#include <iostream>
using namespace std;

#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
using namespace cv;

#include <objdetect/aruco_detector.hpp>

#define ESC_ASCII 27
#define RIGHT_ASCII 2555904
#define UP_ASCII 2490368
#define LEFT_ASCII 2424832
#define DOWN_ASCII 2621440



void makeMarker(Mat& markerImage, const int& id, const int& sizeImg, const int& borderBits);
void detectMarker(Mat& inputImage);

int main(void)
{
    cout << "\n\t Recuperacion de la posicion y orientacion de marcadores de realidad aumentada (AR tags) \n";

    string filename = "./imagenes/labTest.jpg";
    Mat markerImage; // Contenedor Mat donde se almacenara el marcador ArUco
    Mat inputImage;  // Contenedor Mat donde se almacenara la imagen con el posible marcador ArUco a detectar
    inputImage = imread(filename, IMREAD_COLOR);

    int idMarker = 27; // Indice del diccionario que se usara como marcador. El limite queda definido por DICT_4x4_LIMIT
    int sidePixels = 350; // Tamanio en pixeles de markerImage
    int borderBits = 1; // Dimension del borde de la imagen en bits (unidad ArUco). El minimo es 1.

    // Verificando que exista la imagen a procesar
    if(inputImage.empty()) { cout << "Imagen de entrada vacia." << endl; return -1;}
    imshow("Imagen de entrada", inputImage);

    // Creacion del marcador ArUco
    makeMarker(markerImage, idMarker, sidePixels, borderBits);

    // Deteccion del marcador ArUco
    detectMarker(inputImage);



    waitKeyEx(0);

    return 0;
}

void makeMarker(Mat& markerImage, const int& id, const int& sizeImg, const int& borderBits)
{
    /**
     * \brief Genera un marcador ArUco con el ID especificado y lo almacena en `markerImage`.
     *
     * \param markerImage Referencia a un objeto Mat donde se almacenara la imagen del marcador ArUco generado.
     * \param id ID del marcador ArUco que se desea generar. El limite queda definido por DICT_4x4_LIMIT
     * \param sizeImg Tamanio en pixeles del lado del marcador ArUco generado.
     * \param borderBits Dimension del borde de la imagen del marcador en bits (unidad ArUco). Debe ser al menos 1.
     * \return Retorna 1 si la operacion fue satisfactoria.
     *
    */

    // Obtiene el diccionario predefinido de ArUco (Diccionario de imagenes de 4x4 bits, 50 marcadores diferentes)
    aruco::Dictionary dictionary = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);

    // Genera la imagen del marcador ArUco
    aruco::generateImageMarker(dictionary, id, sizeImg, markerImage, borderBits);
    imshow("Marcador ArUco 4x4_27", markerImage);
    imwrite("./imagenes/Marcador_ArUco_4x4_27.png", markerImage);
}

void detectMarker(Mat& inputImage)
{
    /**
     * \brief Detecta marcadores ArUco en una imagen de entrada y muestra los resultados en una nueva imagen.
     *
     * \param inputImage Referencia a un objeto Mat que contiene la imagen de entrada donde se buscaran los marcadores ArUco.
     *
     */

    // Vectores para almacenar IDs y esquinas de los marcadores detectados
    vector<int> markerIds;
    vector<vector<Point2f>> markerCorners, rejectedCandidates;

    // Parametros del detector de ArUco
    aruco::DetectorParameters detectorParams = aruco::DetectorParameters();

    // Diccionario de marcadores ArUco predefinido (4x4, 50 marcadores diferentes)
    aruco::Dictionary dictionary = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);

    // Detector de marcadores ArUco
    aruco::ArucoDetector detector(dictionary, detectorParams);

    // Detecta marcadores ArUco en la imagen de entrada
    detector.detectMarkers(inputImage, markerCorners, markerIds, rejectedCandidates);

    // Representacion del marcador detectado
    Mat outputImage = inputImage.clone();
    aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);
    imshow("Marcador detectado", outputImage);
}
