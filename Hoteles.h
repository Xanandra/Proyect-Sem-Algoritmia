#ifndef HOTELES_H
#define HOTELES_H
#include <iostream>
#include <fstream>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <stdlib.h>
#define CLEAR "clear"
#endif // WIN32

using namespace std;

class IndiceH
{
    int llave;
    long int posicion;
    public:
        void SetLlave(int llavex);
        int GetLlave();
        void SetPosicion(long int posicionx);
        long int GetPosicion();
};

class Hoteles
{
    int codigo, costo, cod_pais;
    char nombre[30], categoria[20];
    public:
        void SetCod_Pais(int cod_paisx);
        int GetCod_Pais();
        void Capturar();
        void Mostrar();
        void Modificar();
        void Eliminar();
        void Buscar();
        void Like();
        void Menu();
        int CodigoH();
        int Codigo_pais(int cod);
        void BuscarPais();
        int codigo_del_pais(int cod);
        string Pais(int cod);
};

class Paises
{
    int codigo, posicion;
    public:
        void SetCodigo(int codigox);
        int GetCodigo();
        void SetPosicion(int posicionx);
        int GetPosicion();
        int cod_paises(int cod);
};

#endif // HOTELES_H
