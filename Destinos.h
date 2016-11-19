#ifndef DESTINOS_H
#define DESTINOS_H
#include <iostream>

using namespace std;

class Destinos
{
    char destino[15], disponibilidad, tipo;
    int codigo;
public:
    void Agregar();
    void Imprimir();
    void Eliminar();
    void Modificar();
    void Buscar();
    void Cancelar();
    void LlenarGrafo();
    void Menu();
};

#endif // DESTINOS_H
