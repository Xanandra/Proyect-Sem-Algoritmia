#ifndef TDA_SECUNDARIO_H
#define TDA_SECUNDARIO_H
#include "Hoteles.h"

class nodos
{
    Paises data;
    nodos *sig;
    friend class TDA_Secundario;
};

class TDA_Secundario
{
    nodos *h;
    public:
        void Inicializa();
        bool Vacia();
        void Anular();
        void Insertar(int llave, int posicion);
        int Tamano();
        void MostrarPorPais(int pos);
        void MostrarIndicesSecundarios();
        nodos* Buscar(int posicion);
        Paises BuscarPos(int pos);
        void Cargar();
        void Guardar();
        void InsertarSimple(Paises Pais);
        void Eliminar(int llave);
        int BuscarPorLlave(int llave);
        void Modificar(int llave, int posicion);
        string Pais(int codigo);
};

#endif // TDA_SECUNDARIO_H
