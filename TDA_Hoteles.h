#ifndef TDA_HOTELES_H
#define TDA_HOTELES_H
#include "Hoteles.h"


class nodo
{
    IndiceH IH;
    nodo *sig;
    friend class TDA_Hoteles;
};

class TDA_Hoteles
{
    nodo *h;
    public:
        void Cargar();
        void Inicializar();
        bool Vacia();
        void Insertar(int llave, long int posicion);
        void Mostrar();
        void Anular();
        long int Buscar(int llave);
        void Ordenar(int opc2);
};

#endif // TDA_HOTELES_H
