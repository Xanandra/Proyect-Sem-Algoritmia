#include "ListaDiccionario.h"

void ListaDiccionario::Inicializa()
{
    h = NULL;
    t = NULL;
}

bool ListaDiccionario::Vacia()
{
    if(h == NULL && t == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ListaDiccionario::Inserta(char let, string cod)
{
    nodod *tmp = new nodod;
    tmp->sig = NULL;
    tmp->ant = NULL;
    tmp->letra = let;
    tmp->codigo = cod;

    if(Vacia())
    {
        h = tmp;
        t = tmp;
    }
    else
    {
        t->sig = tmp;
        tmp->ant = t;
        t = tmp;
    }
}

void ListaDiccionario::MostrarTodo()
{
    nodod *aux;
    aux = h;
    while(aux != NULL)
    {
        cout<<aux->letra<<": "<<aux->codigo<<endl;
        aux = aux->sig;
    }
}

string ListaDiccionario::Buscar(char let)
{
    nodod *aux;
    aux = h;
    while(aux != NULL)
    {
        if(aux->letra == let)
        {
            return aux->codigo;
        }
        aux = aux->sig;
    }
    return "";
}

void ListaDiccionario::Anular()
{
    nodod *aux;
    while(h != NULL)
    {
        aux = h;
        h = h->sig;
        delete(aux);
    }
    h = NULL;
    t = NULL;
}

bool ListaDiccionario::Existe(char let)
{
    nodod *aux;
    aux = h;
    while(aux != NULL)
    {
        if(aux->letra == let)
        {
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

void ListaDiccionario::GuardarDiccionario()
{
    nodod *aux;
    aux = h;
    ifstream D("Diccionario.txt");
    if(!D.good())
    {
        ofstream Dic("Diccionario.txt", ios::app);
        while(aux != NULL)
        {
            Dic<<aux->letra<<'@'<<aux->codigo<<'@';
            aux = aux->sig;
        }
        Dic.close();
    }
    D.close();
}

char ListaDiccionario::BuscarCodigo(string cadena)
{
    nodod *aux;
    aux = h;
    while(aux != NULL)
    {
        if(cadena == aux->codigo)
        {
            return aux->letra;
        }
        aux = aux->sig;
    }
    return 'n';
}

void ListaDiccionario::CargarDiccionario()
{
    string cod, letrilla;
    ifstream Dic("Diccionario.txt");
    if(Dic.good())
    {
        while(!Dic.eof())
        {
            getline(Dic, letrilla, '@');
            getline(Dic, cod, '@');
            if(Dic.eof())
            {
                break;
            }
            if(!Existe(letrilla.at(0)))
            {
                Inserta(letrilla.at(0), cod);
            }
        }
    }
    Dic.close();
}
