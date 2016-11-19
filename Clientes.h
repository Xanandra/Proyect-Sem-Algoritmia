#ifndef CLIENTES_H
#define CLIENTES_H
#include <iostream>
#include <string.h>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <stdlib.h>
#define CLEAR "clear"
#endif // WIN32

using namespace std;

class Clientes
{
    int codigo, tel;
    char nombre[30], correo[30];
    public:
        void Dispersa();
        void Genera();
        void Capturar(int band);
        void Mostrar();
        void Modificar();
        int Eliminar();
        void Buscar();
        void Menu();
        int GeneraCodigo();
        int GeneraMaximo();
        void Encriptacion();
        void MostrarContenido();
};

#endif // CLIENTES_H
