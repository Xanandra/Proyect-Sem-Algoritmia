#ifndef CONEXIONES_H
#define CONEXIONES_H
#include <iostream>
#ifdef WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <stdlib.h>
#define CLEAR "clear"
#endif // WIN32

using namespace std;

class Conexiones
{
    int precios[20][20];
    string destinos[20];

    public:
        void LlenarMatriz();
        void Agregar();
        void Imprimir();
        void Modificar();
        void Eliminar();
        void Encriptar();
        void Descomprimir();
        void Menu();
};


#endif // CONEXIONES_H
