#include "TDA_Secundario.h"
#include "TDA_Hoteles.h"
#include "Hoteles.h"

TDA_Hoteles TDAH;
Hoteles Hote;

void TDA_Secundario::Inicializa()
{
    h = NULL;
}

bool TDA_Secundario::Vacia()
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

nodos* TDA_Secundario::Buscar(int posicion)
{
    int cont = 1;
    nodos *aux;
    aux = h;
    while(cont != posicion)
    {
        aux = aux->sig;
        cont++;
    }
    return aux;
}

Paises TDA_Secundario::BuscarPos(int pos)
{
    int cont=1;
    nodos *aux;
    aux = h;
    while(cont != pos)
    {
        aux = aux->sig;
        cont++;
    }
    return aux->data;
}

int TDA_Secundario::Tamano()
{
    int cont = 1;
    nodos *aux;

    aux = h;
    while(aux->sig != NULL)
    {
        aux = aux->sig;
        cont++;
    }
    return cont;
}

void TDA_Secundario::Insertar(int llave, int posicion)
{
    int cont = 1;
    nodos *tmp = new nodos;
    tmp->sig = NULL;
    tmp->data.SetCodigo(llave);
    tmp->data.SetPosicion(-1);
    nodos *aux;
    nodos *aux2;

    if(Vacia())
    {
        h = tmp;
    }
    else
    {
        aux2 = h;
        if(posicion != 0)
        {
            while(cont != posicion)
            {
                aux2 = aux2->sig;
                cont++;
            }

            while(aux2->data.GetPosicion() != -1)
            {
                aux2 = Buscar(aux2->data.GetPosicion());
            }
            aux2->data.SetPosicion(Tamano() + 1);
        }

        aux = h;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = tmp;
    }
}

string TDA_Secundario::Pais(int codigo)
{
    char destino[15], auxiliar;
    int a, codigoaux;
    string dest;
    ifstream A("Destinos.txt");
    if(A.good())
    {
        while(!A.eof())
        {
            A.read((char*)&codigoaux,sizeof(int));

            A.read((char*)&a, sizeof(int));
            A.read((char*)&destino, a);
            destino[a]='\0';
            dest = destino;

            A.read((char*)&a, sizeof(int));
            A.read((char*)&auxiliar, a);

            A.read((char*)&a, sizeof(int));
            A.read((char*)&auxiliar, a);

            if(A.eof())
            {
                break;
            }
            if(codigoaux == codigo)
            {
                return dest;
            }
        }
    }
    A.close();
    return "";
}

void TDA_Secundario::MostrarIndicesSecundarios()
{
    int cont = 1;
    nodos *aux;
    aux = h;
    while(aux != NULL)
    {
        cout<<"Llave: "<<aux->data.GetCodigo()<<endl;
        cout<<"Posicion: "<<cont<<endl;
        cout<<"Pais: "<<Hote.codigo_del_pais(aux->data.GetCodigo())<<". "<<Pais(Hote.codigo_del_pais(aux->data.GetCodigo()))<<endl;
        cout<<"Posicion del siguiente nodo: "<<aux->data.GetPosicion()<<endl<<endl;
        aux = aux->sig;
        cont++;
    }

}

void TDA_Secundario::Anular()
{
    nodos *aux;
    while(h != NULL)
    {
        aux = h;
        h = h->sig;
        delete(aux);
    }
}

void TDA_Secundario::Guardar()
{
    nodos *aux;
    aux = h;
    remove("TDA_Secundario.txt");
    ofstream TDASEC("TDA_Secundario.txt", ios::app);
    while(aux != NULL)
    {
        TDASEC.write((char*)&aux->data, sizeof(aux->data));
        aux = aux->sig;
    }
    TDASEC.close();
}

void TDA_Secundario::InsertarSimple(Paises Pais)
{
    nodos *tmp = new nodos;
    tmp->data = Pais;
    tmp->sig = NULL;
    nodos *aux;
    if(Vacia())
    {
        h = tmp;
    }
    else
    {
        aux = h;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = tmp;
    }
}

void TDA_Secundario::Cargar()
{
    Paises Pai;
    ifstream TDASEC("TDA_Secundario.txt");
    if(TDASEC.good())
    {
        while(!TDASEC.eof())
        {
            TDASEC.read((char*)&Pai, sizeof(Pai));
            if(TDASEC.eof())
            {
                break;
            }
            InsertarSimple(Pai);
        }
    }
    TDASEC.close();
}

int TDA_Secundario::BuscarPorLlave(int llave)
{
    int cont = 1;
    nodos *aux;
    aux = h;
    while(aux->data.GetCodigo() != llave)
    {
        cont++;
        aux = aux->sig;
    }
    return cont;
}

void TDA_Secundario::Eliminar(int llave)
{
    int pos, band = 0;
    nodos *aux;
    nodos *aux2;
    nodos *tmp;

    if(h->data.GetCodigo() == llave)
    {
        aux = h;
        h = h->sig;
        delete(aux);

        aux = h;
        while(aux != NULL)
        {
            if(aux->data.GetPosicion() != -1)
            {
                aux->data.SetPosicion(aux->data.GetPosicion() - 1);
            }
            aux = aux->sig;
        }
    }
    else
    {
        aux = h;
        pos = BuscarPorLlave(llave);

        while(aux->data.GetCodigo() != llave)
        {
            if(aux->data.GetPosicion() == pos)
            {
                tmp = aux;
                band = 1;
            }
            aux2 = aux;
            aux = aux->sig;
        }
        if(band == 1)
        {
            tmp->data.SetPosicion(aux->data.GetPosicion());
        }
        aux2->sig = aux->sig;
        delete(aux);

        aux = h;
        while(aux != NULL)
        {
            if(aux->data.GetPosicion() != -1 && aux->data.GetPosicion() > pos)
            {
                aux->data.SetPosicion(aux->data.GetPosicion() - 1);
            }

            aux = aux->sig;
        }
    }
}

void TDA_Secundario::Modificar(int llave, int posicion)
{
    Insertar(llave, posicion);
    Eliminar(llave);
}
