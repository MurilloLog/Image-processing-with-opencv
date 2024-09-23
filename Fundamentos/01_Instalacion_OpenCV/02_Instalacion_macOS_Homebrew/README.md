# Instalación de OpenCV: Entorno macOS-Homebrew

Este repositorio proporciona una guía básica para instalar OpenCV en macOS y compilar programas en C++ que utilicen la biblioteca de OpenCV a través de Homebrew.

## Requisitos previos

Antes de comenzar, asegúrate de tener los siguientes elementos instalados:

- **Xcode Command Line Tools** (incluye `g++` y otros comandos esenciales de desarrollo).
  Puedes instalarlos ejecutando el siguiente comando en la terminal:
  
  ```bash
  xcode-select --install

## 1. Instalación de Homebrew

Homebrew es un gestor de paquetes para macOS que facilita la instalación de OpenCV y otras dependencias. Si no tienes Homebrew instalado, puedes instalarlo ejecutando este comando en la terminal:

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

## 2. OpenCV

Utiliza Homebrew para instalar OpenCV ejecutando el siguiente comando en la terminal:

    ```bash
    brew install opencv
    brew install pkg-config
    brew info opencv
    pkg-config --cflags --libs opencv4

## Compilación 
Una vez que OpenCV esté instalado, puedes compilar programas en C++ que utilicen OpenCV y sus respectivas librerías con la siguiente instrucción:

g++ -std=c++11 -o mi_programa_ejecutable codigo_fuente.cpp `pkg-config --cflags --libs opencv4`

Si todo funciona correctamente, se generará el ejecutable de nombre __mi_programa_ejecutable__ que podrás iniciar con la instrucción:

./mi_programa_ejecutable