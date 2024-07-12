# Last Stand

## Descripción

Last Stand es un emocionante juego desarrollado en C++ utilizando la biblioteca SFML. En este juego, te enfrentarás a hordas de enemigos mientras intentas sobrevivir el mayor tiempo posible. ¡Demuestra tu habilidad y estrategia para mantenerte en pie!

## Requisitos
Para compilar y ejecutar este juego, necesitas tener instalados los siguientes componentes:

C++ Compiler (GCC, Clang, MSVC, etc.)
SFML Library (versión 2.5.1 o superior)
Instalación
Sigue estos pasos para instalar y configurar el entorno necesario para ejecutar "Last Stand":

Instalar un compilador de C++:

En Windows, puedes instalar MinGW o utilizar el compilador incluido en Visual Studio.
En macOS, puedes instalar el compilador a través de Homebrew con brew install gcc.
En Linux, puedes instalar GCC utilizando tu gestor de paquetes favorito (por ejemplo, sudo apt-get install g++ en Ubuntu).
Instalar SFML:

Windows:
Descarga la última versión de SFML desde la página oficial.
Sigue las instrucciones de instalación proporcionadas en la documentación de SFML.
macOS:
Puedes instalar SFML utilizando Homebrew con el comando brew install sfml.
Linux:
Instala SFML utilizando tu gestor de paquetes (por ejemplo, sudo apt-get install libsfml-dev en Ubuntu).
Compilación
Una vez que tengas todo instalado, sigue estos pasos para compilar el juego:

Clona este repositorio en tu máquina local:

bash
Copiar código
git clone https://github.com/Diego-Benitez/LAST-STAND.git
cd last-stand
Compila el código fuente utilizando el compilador de C++ y enlazando la biblioteca SFML. A continuación se muestra un ejemplo de cómo hacerlo con g++:

bash

g++ -c main.cpp -o main.o
g++ main.o -o last-stand -lsfml-graphics -lsfml-window -lsfml-system
Asegúrate de ajustar el comando según la estructura de tu proyecto y los archivos fuente que tengas.

## Ejecución
Después de compilar el juego, puedes ejecutarlo con el siguiente comando:

bash
./last-stand

## Contacto
Si tienes alguna pregunta, sugerencia o
 problema, no dudes en abrir un issue en el repositorio o contactarme directamente a través de mi correo electrónico: criptograma12@gmail.com o lucas.e.saucedo@outlook.com.







