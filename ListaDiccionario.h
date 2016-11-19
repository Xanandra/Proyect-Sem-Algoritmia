#ifndef LISTADICCIONARIO_H
#define LISTADICCIONARIO_H
#include <iostream>
#include <fstream>

using namespace std;

class nodod
{
    char letra;
    string codigo;
    nodod *sig;
    nodod *ant;
    friend class ListaDiccionario;
};

class ListaDiccionario
{
    nodod *h;
    nodod *t;
    public:
        void Inicializa();
        void Inserta(char let, string cod);
        void MostrarTodo();
        void Anular();
        void GuardarDiccionario();
        void CargarDiccionario();
        string Buscar(char let);
        char BuscarCodigo(string cod);
        bool Vacia();
        bool Existe(char let);
};

#endif // LISTADICCIONARIO_H
