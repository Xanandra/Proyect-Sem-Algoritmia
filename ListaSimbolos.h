#ifndef LISTASIMBOLOS_H
#define LISTASIMBOLOS_H
#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

class nodos
{
    char letra;
    int frecuencia;
    nodos *sig;
    nodos *ant;
    nodos *izq;
    nodos *der;
    friend class ListaSimbolos;
};

class ListaSimbolos
{
    nodos *h;
    nodos *t;
    public:
        void Inicializa();
        void Inserta(char let, int frec);
        void MostrarTodo();
        void Ordenar();
        void Arbolear();
        void Anular();
        void Recorrido_Preorden(nodos *raiz, int band, string cod);
        void MostrarDiccionario();
        void BinarisarTexto(string texto);
        void GuardarDiccionario();
        void CargarDiccionario();
        char letra(string cadena);
        int Tamano();
        bool Vacia();
        bool Existe(char let);
};

#endif // LISTASIMBOLOS_H
