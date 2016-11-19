#include "TDA_Hoteles.h"

Hoteles Ho;

void TDA_Hoteles::Inicializar()
{
    h = NULL;
}

bool TDA_Hoteles::Vacia()
{
    if(h == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void TDA_Hoteles::Insertar(int llave, long int posicion)
{
    nodo *tmp = new nodo;
    tmp->IH.SetLlave(llave);
    tmp->IH.SetPosicion(posicion);
    tmp->sig = NULL;

    if(Vacia())
    {
        h = tmp;
    }
    else
    {
        nodo *aux;
        aux = h;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig=tmp;
    }
}

void TDA_Hoteles::Mostrar()
{
    nodo *aux;
    aux = h;
    while(aux != NULL)
    {
        cout<<"Llave: "<<aux->IH.GetLlave()<<endl;
        cout<<"Posicion: "<<aux->IH.GetPosicion()<<endl;
        cout<<"Direccion: "<<aux<<endl<<endl;
        aux = aux->sig;
    }
}

void TDA_Hoteles::Cargar()
{
    IndiceH IHAUX;
    ifstream I("IndiceH.txt");
    if(I.good())
    {
        while(!I.eof())
        {
            I.read((char*)&IHAUX, sizeof(IHAUX));
            if(I.eof())
            {
                break;
            }
            Insertar(IHAUX.GetLlave(), IHAUX.GetPosicion());
        }
    }
    I.close();
}

void TDA_Hoteles::Anular()
{
    nodo *aux;
    while(h != NULL)
    {
        aux = h;
        delete(aux);
        h = h->sig;
    }
}

long int TDA_Hoteles::Buscar(int llave)
{
    long int posicion;
    nodo *aux;
    aux = h;
    while(aux != NULL)
    {
        if(aux->IH.GetLlave() == llave)
        {
            posicion = aux->IH.GetPosicion();
        }
        aux = aux->sig;
    }
    return posicion;
}

void TDA_Hoteles::Ordenar(int opc2)
{
    nodo *aux;
    nodo *tmp;
    IndiceH I;
    aux = h;
    tmp = h->sig;
    while(aux->sig != NULL)
    {
        tmp = aux->sig;
        while(tmp != NULL)
        {
            if(opc2 == '1')
            {
                if(aux->IH.GetLlave() > tmp->IH.GetLlave())
            {
                I = aux->IH;
                aux->IH = tmp->IH;
                tmp->IH = I;
            }
            }
            else if(opc2 == '2')
            {
            if(aux->IH.GetLlave() < tmp->IH.GetLlave())
            {
                I = aux->IH;
                aux->IH = tmp->IH;
                tmp->IH = I;
            }
            }
            tmp = tmp->sig;
        }
        aux = aux->sig;
    }
    aux = h;
    ofstream A("IndiceH.txt", ios::out);
    while(aux != NULL)
    {
        A.write((char*)&aux->IH, sizeof(aux->IH));
        aux = aux->sig;
    }
    A.close();
}
