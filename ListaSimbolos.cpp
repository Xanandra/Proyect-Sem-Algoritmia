#include "ListaSimbolos.h"
#include "ListaDiccionario.h"

ListaDiccionario LD;

void ListaSimbolos::Inicializa()
{
    h = NULL;
    t = NULL;
}

bool ListaSimbolos::Vacia()
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

int ListaSimbolos::Tamano()
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

void ListaSimbolos::Inserta(char let, int frec)
{
    nodos *tmp = new nodos;
    tmp->sig = NULL;
    tmp->ant = NULL;
    tmp->izq = NULL;
    tmp->der = NULL;
    tmp->letra = let;
    tmp->frecuencia = frec;

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

void ListaSimbolos::MostrarTodo()
{
    nodos *aux;
    aux = h;
    while(aux != NULL)
    {
        cout<<aux->letra<<": "<<aux->frecuencia<<endl;
        aux = aux->sig;
    }
}

bool ListaSimbolos::Existe(char let)
{
    nodos *aux;
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

void ListaSimbolos::Anular()
{
    nodos *aux;
    while(h != NULL)
    {
        aux = h;
        h = h->sig;
        delete(aux);
    }
    h = NULL;
    t = NULL;
}

void ListaSimbolos::Ordenar()
{
    char letaux;
    int frecaux;
    nodos *aux;
    nodos *tmp;
    aux = h;
    while(aux->sig != NULL)
    {
        tmp = aux->sig;
        while(tmp != NULL)
        {
            if(aux->frecuencia > tmp->frecuencia)
            {
                letaux = aux->letra;
                frecaux = aux->frecuencia;
                aux->letra = tmp->letra;
                aux->frecuencia = tmp->frecuencia;
                tmp->letra = letaux;
                tmp->frecuencia = frecaux;
            }
            tmp = tmp->sig;
        }
        aux = aux->sig;
    }

    aux = h;
    while(aux->sig != NULL)
    {
        tmp = aux->sig;
        while(aux->frecuencia == tmp->frecuencia)
        {
            if(aux->letra > tmp->letra)
            {
                letaux = aux->letra;
                frecaux = aux->frecuencia;
                aux->letra = tmp->letra;
                aux->frecuencia = tmp->frecuencia;
                tmp->letra = letaux;
                tmp->frecuencia = frecaux;
            }
            tmp = tmp->sig;
        }
        aux = aux->sig;
    }
}

void ListaSimbolos::Recorrido_Preorden(nodos *raiz, int band, string cod)
{
    if(raiz != NULL)
    {
        if(band == 0)
        {
            cod = cod + "0";
        }
        else if(band == 1)
        {
            cod = cod + "1";
        }
        if(raiz->izq == NULL && raiz->der == NULL && !LD.Existe(raiz->letra))
        {
            LD.Inserta(raiz->letra, cod);
        }
        Recorrido_Preorden(raiz->izq, 0, cod);
        Recorrido_Preorden(raiz->der, 1, cod);
    }
}

void ListaSimbolos::Arbolear()
{
    nodos *aux;
    nodos *aux2;
    while(Tamano() != 1)
    {
        nodos *tmp = new nodos;
        tmp->sig = NULL;
        tmp->ant = NULL;
        tmp->izq = NULL;
        tmp->der = NULL;
        tmp->letra = '\0';
        tmp->frecuencia = h->frecuencia + h->sig->frecuencia;

        aux = h->sig->sig;
        if(aux != NULL)
        {
            while(tmp->frecuencia >= aux->frecuencia && aux->sig != NULL)
            {
                aux = aux->sig;
            }
        }

        cout<<tmp->frecuencia<<endl;

        if(aux == NULL)
        {
            t->sig = tmp;
            tmp->ant = t;
            t = tmp;
        }
        else if(aux->sig == NULL && tmp->frecuencia > aux->frecuencia)
        {
            aux->sig = tmp;
            tmp->ant = aux;
            t = tmp;
        }
        else
        {
            tmp->sig = aux;
            tmp->ant = aux->ant;
            aux->ant->sig = tmp;
            aux->ant = tmp;
        }

        aux2 = h;
        h = h->sig->sig;

        tmp->izq = aux2;
        tmp->der = aux2->sig;
        cout<<aux2->letra<<": "<<aux2->frecuencia<<" - "<<aux2->sig->letra<<": "<<aux2->sig->frecuencia<<endl;
        aux2->sig->sig->ant = NULL;
        aux2->sig->sig = NULL;
        aux2->sig->ant = NULL;
        aux2->sig = NULL;
    }
    Recorrido_Preorden(h, 5, "");
}

void ListaSimbolos::MostrarDiccionario()
{
    LD.MostrarTodo();
}

void ListaSimbolos::BinarisarTexto(string texto)
{
    string TextoBinarisado;
    int tama, t;
    for(unsigned int i=0; i<texto.length(); i++)
    {
        TextoBinarisado = TextoBinarisado + LD.Buscar(texto.at(i));
    }
    cout<<TextoBinarisado<<endl;
    tama = TextoBinarisado.length();

    ofstream Original("TamanoOriginal.txt", ios::out);
    Original<<tama<<"|";
    Original.close();
    if(TextoBinarisado.length()%8 != 0)
    {
        while(TextoBinarisado.length()%8 != 0)
        {
            TextoBinarisado = TextoBinarisado + "0";
        }
    }
    cout<<endl<<"Texto modificado: "<<endl;
    cout<<TextoBinarisado<<endl;

    char ascii;
    int decimal, suma = 0, tam;
    string dec, decaux, compreso, ascaux;
    tam = TextoBinarisado.length();
    for(int j=1; j<=tam; j++)
    {
        if(TextoBinarisado.at(j-1) == '1')
        {
            if(j%8 == 0)
            {
                decimal = 1;
            }
            else
            {
                decimal = pow(2, 8-j%8);
            }

            suma = suma + decimal;
        }
        if(j%8 == 0)
        {
            ascii = suma;
            compreso = compreso + ascii;
            suma = 0;
        }
    }
    ofstream Com("Compreso.txt",ios::out);
    t = compreso.length();
    char aux[t];
    strcpy(aux, compreso.c_str());
    Com.write((char*)&t, sizeof(int));
    Com.write((char*)&aux, t);
    Com.close();
    cout<<endl<<"Texto compreso: "<<endl;
    cout<<compreso<<endl;
}

void ListaSimbolos::GuardarDiccionario()
{
    LD.GuardarDiccionario();
}

char ListaSimbolos::letra(string cadena)
{
    char let;
    let = LD.BuscarCodigo(cadena);
    return let;
}

void ListaSimbolos::CargarDiccionario()
{
    LD.CargarDiccionario();
}
