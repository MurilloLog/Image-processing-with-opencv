# Instalación de OpenCV: Entorno Windows-CodeBlocks

Este documento es una adaptación de la guía escrita por Zahid Hasan sobre "[Cómo instalar OpenCV en Windows (64 bits) usando MinGW (64) y CodeBlocks](https://zahidhasan.github.io/2017/03/25/How-to-install-OpenCV-3.2-in-windows-10-using-MinGW-(64)-and-Codeblocks.html)".
La descripción paso a paso se ha extraído de allí, con algunas sugerencias añadidas para reducir los posibles errores que pueden generar problemas durante su instalación.

Aunque puede parecer trivial la instalación de OpenCV, los guiaré paso a paso durante este proceso con las configuraciones realizadas de mi parte para ejecutar sin inconveniente el conjunto de aplicaciones presentes en este repositorio.

Es importante mencionar que, para esta configuración, se hará uso de las siguientes herramientas:

-  OpenCV 4.10.0
-  CMake 3.30.0
-  Compilador TDM-GCC
-  Codeblocks 20.03

## 1. Descarga de OpenCV

El primer paso es descargar el código fuente de OpenCV desde su página oficial [opencv.org](https://opencv.org/releases/).
Aunque no hay ningún inconveniente en descargar una versión diferente, es importante verificar que la versión por descargar satisfaga sus necesidades y que sea explicitamente el código fuente, no las versiones precompiladas de OpenCV.

La principal diferencia entre la versión precompilada y el código fuente es que al compilar OpenCV en la máquina donde se va a utilizar, la instalación queda personalizada para los recursos de hardware que tiene el dispositivo, explotando al máximo los recursos en tiempo de ejecución.

Por el contrario, descargar la versión precompilada facilitará la instalación, pero no será garantía de que se exprima el hardware del equipo.

Una vez descargado, se descomprimen los archivos en un directorio raíz para facilitar su instalación, por ejemplo, en C:\opencv. Para efectos de esta guía, el nombre de este directorio será source, aunque pueden darle el nombre que ustedes prefieran.

Dentro de esta carpeta, se deberá crear un directorio adicional: build. De tal forma que la ruta C:\opencv tendrá dos subdirectorios: el directorio build y el directorio source (resultado de la descompresión del código fuente de OpenCV). 

Cada una de estas carpetas cumple un rol específico:

- build: Aquí instalaremos los binarios y dependencias de OpenCV necesarias para nuestros programas.
- source: Aquí se almacenan los archivos que descomprimimos de OpenCV. El nombre puede variar, basta con identificar que en este directorio se encuentra el código fuente.
