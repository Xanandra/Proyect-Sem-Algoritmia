#include "Conexiones.h"
#include "Destinos.h"
#include "ListaSimbolos.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>

ListaSimbolos LS;

using namespace std;

void Conexiones::LlenarMatriz()
{
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            precios[i][j]=0;
        }
    }
}

void Conexiones::Agregar()
{
    char auxiliar[15];
    int MAX;
    int a, codigoaux, i=0, x, y;
    MAX=0;
    ifstream Leer("Destinos.txt");
    if(Leer.good())
    {
        Leer.read((char*)&codigoaux,sizeof(int));
        while(!Leer.eof())
        {
            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, a);
            auxiliar[a]='\0';
            destinos[i]=auxiliar;
            cout<<i+1<<". "<<destinos[i]<<endl;
            i++;

            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, 1);
            auxiliar[1]='\0';

            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, 1);
            auxiliar[1]='\0';

            if(Leer.eof())
            {
                break;
            }
            MAX++;
            Leer.read((char*)&codigoaux,sizeof(int));
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    Leer.close();
    cout<<endl<<"Inserte el pais de origen: ";
    cin>>x;
    cout<<"Inserte el origen de destino : ";
    cin>>y;
    cout<<"Inserte el precio: ";
    cin>>precios[x-1][y-1];
    precios[y-1][x-1]=precios[x-1][y-1];

    ofstream Escribir("Matriz.txt", ios::out);
    for(int i=0; i<MAX; i++)
    {
        for(int j=0; j<MAX; j++)
        {
            Escribir << precios[i][j] << "|";
        }
    }
    Escribir.close();
    ofstream Esc("MAX.txt", ios::out);
    Esc<<MAX;
    Esc.close();
}

void Conexiones::Imprimir()
{
    int i=0, j=0, MAX=0, a, b, c, codigoaux;
    string preciosaux, maxaux;
    char disponibilidadaux, tipoaux, destinosaux[15];

    ifstream Leer("Destinos.txt");
    if(Leer.good())
    {
        while(!Leer.eof())
        {

            Leer.read((char*)&codigoaux,sizeof(int));
            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&destinosaux, a);
            destinosaux[a]='\0';

            Leer.read((char*)&b, sizeof(int));
            Leer.read((char*)&disponibilidadaux, 1);

            Leer.read((char*)&c, sizeof(int));
            Leer.read((char*)&tipoaux, 1);

            if(Leer.eof())
            {
                break;
            }
            destinos[i]=destinosaux;
            i++;
            MAX++;
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    Leer.close();
    ifstream leer("Matriz.txt");
    if(leer.good())
    {
        i=0;
        while(!leer.eof() && i<MAX)
        {
            for(j=0; j<MAX; j++)
            {
                getline(leer, preciosaux, '|');
                if(leer.eof())
                {
                    break;
                }
                precios[i][j]=atoi(preciosaux.c_str());
            }
            i++;
        }
        for(int i=0; i<MAX; i++)
        {
            cout<<i+1<<". "<<destinos[i]<<endl;
        }
        cout<<endl<<endl;
        for(i=1; i<=MAX; i++)
        {
            cout<<"\t"<<i;
        }
        cout<<endl<<endl;
        for(i=0; i<MAX; i++)
        {
            cout<<i+1;
            for(j=0; j<MAX; j++)
            {
                cout<<"\t"<<precios[i][j];
            }
            cout<<endl;
        }
    }
    else
    {
        for(int i=0; i<MAX; i++)
        {
            cout<<i+1<<". "<<destinos[i]<<endl;
        }
        cout<<endl<<endl;
        for(i=1; i<=MAX; i++)
        {
            cout<<"\t"<<i;
        }
        cout<<endl<<endl;
        for(i=0; i<MAX; i++)
        {
            cout<<i+1;
            for(j=0; j<MAX; j++)
            {
                cout<<"\t"<<precios[i][j];
            }
            cout<<endl;
        }
    }
    leer.close();
}

void Conexiones::Modificar()
{
    int x, y, precaux, codigoaux, a, i=0, j=0, MAX=0, band=0;
    char conexaux, auxiliar[15];
    string preciosaux;

    ifstream Leer("Destinos.txt");
    if(Leer.good())
    {
        Leer.read((char*)&codigoaux,sizeof(int));
        while(!Leer.eof())
        {
            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, a);
            auxiliar[a]='\0';
            destinos[i]=auxiliar;
            cout<<i+1<<". "<<destinos[i]<<endl;
            i++;

            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, 1);
            auxiliar[1]='\0';

            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, 1);
            auxiliar[1]='\0';

            if(Leer.eof())
            {
                break;
            }
            MAX++;
            Leer.read((char*)&codigoaux,sizeof(int));
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    Leer.close();

    ofstream aux("auxiliar.txt", ios::out);
    ifstream leer("Matriz.txt", ios::in);
    if(aux.good() && leer.good())
    {
        cout<<"Conexion que desea modificar"<<endl;
        cout<<"Inserte el numero del pais de origen: ";
        cin>>x;
        cout<<"Inserte el numero del pais de destino: ";
        cin>>y;
        for(i=0; i<MAX; i++)
        {
            for(j=0; j<MAX; j++)
            {
                getline(leer, preciosaux, '|');
                precios[i][j]=atoi(preciosaux.c_str());
                if((i==x-1 && j==y-1) || (i==y-1 && j==x-1))
                {
                    if(band==0)
                    {
                        cout<<"Son adyacentes? si=V, no=F: ";
                        cin>>conexaux;

                        if(conexaux=='V' || conexaux=='v')
                        {
                            cout<<"Inserte el nuevo precio: ";
                            cin>>precaux;
                        }
                        else
                        {
                            precaux=0;
                        }
                        band=1;
                    }
                    aux << precaux << "|";
                }
                else
                {
                    aux << precios[i][j] << "|";
                }
                if(leer.eof())
                {
                    break;
                }
            }
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    aux.close();
    leer.close();
    remove ("Matriz.txt");
    rename ("auxiliar.txt", "Matriz.txt");
}

void Conexiones::Eliminar()
{
    int n, codigoaux, i=0, j=0, MAX=0, a, b, c;
    char auxiliar[15], destinosaux[15], disponibilidadaux, tipoaux;
    string preciosaux;

    ifstream Leer("Destinos.txt");
    if(Leer.good())
    {
        Leer.read((char*)&codigoaux,sizeof(int));
        while(!Leer.eof())
        {
            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, a);
            auxiliar[a]='\0';
            destinos[i]=auxiliar;
            cout<<i+1<<". "<<destinos[i]<<endl;
            i++;

            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, 1);
            auxiliar[1]='\0';

            Leer.read((char*)&a, sizeof(int));
            Leer.read((char*)&auxiliar, 1);
            auxiliar[1]='\0';

            if(Leer.eof())
            {
                break;
            }
            MAX++;
            Leer.read((char*)&codigoaux,sizeof(int));
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    Leer.close();

    ifstream lee("Destinos.txt", ios::in);
    ofstream tmp("temporal.txt", ios::out);
    ofstream aux("auxiliar.txt", ios::out);
    ifstream leer("Matriz.txt", ios::in);
    if(aux.good() && leer.good())
    {
        cout<<"Inserte el numero de pais que desea eliminar: ";
        cin>>n;
        for(i=0; i<MAX; i++)
        {
            for(j=0; j<MAX; j++)
            {
                getline(leer, preciosaux, '|');
                precios[i][j]=atoi(preciosaux.c_str());
                if(i==n-1 || j==n-1)
                {

                }
                else
                {
                    aux << precios[i][j] << "|";
                }
                if(leer.eof())
                {
                    break;
                }
            }
            lee.read((char*)&codigoaux,sizeof(int));
            lee.read((char*)&a, sizeof(int));
            lee.read((char*)&destinosaux, a);
            destinosaux[a]='\0';

            lee.read((char*)&b, sizeof(int));
            lee.read((char*)&disponibilidadaux, 1);

            lee.read((char*)&c, sizeof(int));
            lee.read((char*)&tipoaux, 1);

            if(i==n-1)
            {

            }
            else
            {
                a=strlen(destinosaux);
                b=1;
                c=1;
                tmp.write((char*)&codigoaux, sizeof(int));
                tmp.write((char*)&a, sizeof(int));
                tmp.write((char*)&destinosaux, a);
                tmp.write((char*)&b, sizeof(int));
                tmp.write((char*)&disponibilidadaux, b);
                tmp.write((char*)&c, sizeof(int));
                tmp.write((char*)&tipoaux, c);
            }
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    lee.close();
    aux.close();
    leer.close();
    remove ("Matriz.txt");
    rename ("auxiliar.txt", "Matriz.txt");
    remove("Destinos.txt");
    rename("temporal.txt", "Destinos.txt");
}

void Conexiones::Encriptar()
{
int frec;
string contenido;

ifstream Con("Matriz.txt");
if(Con.good())
{
    getline(Con, contenido);
}
else
{
    cout<<"Error"<<endl;
}
Con.close();

cout<<"Texto: "<<endl;
cout<<contenido<<endl<<endl;

for(unsigned int i=0; i<contenido.length()-1; i++)
{
    frec = 1;
    for(unsigned int j=i+1; j<contenido.length(); j++)
    {
        if(contenido.at(i) == contenido.at(j))
        {
            frec++;
        }
    }
    if(!LS.Existe(contenido.at(i)))
    {
        LS.Inserta(contenido.at(i), frec);
    }
}

cout<<"Lista de caracteres ordenados: "<<endl;
LS.Ordenar();
LS.MostrarTodo();

cout<<endl<<"Arbol: "<<endl;
LS.Arbolear();

cout<<endl<<"Diccionario: "<<endl;
LS.MostrarDiccionario();
LS.GuardarDiccionario();

cout<<endl<<"Texto binarisado: "<<endl;
LS.BinarisarTexto(contenido);
}

void Conexiones::Descomprimir()
{
    string compreso, TextoBinario;
     int decimal, dividendo, t;

     LS.CargarDiccionario();

    ifstream Com("Compreso.txt");
    if(Com.good())
    {
        Com.read((char*)&t, sizeof(int));
        char aux[t];
        Com.read((char*)&aux, t);
        aux[t]='\0';
        compreso = aux;
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    Com.close();

    int tama;
    string tam;
    ifstream Tam("TamanoOriginal.txt");
    if(Tam.good())
    {
        getline(Tam, tam, '|');
        tama = atoi(tam.c_str());
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    Tam.close();
    unsigned char letra;
    char aux[compreso.length()];
    string TextoBinarisado;
    strcpy(aux, compreso.c_str());
    int i=compreso.length()-1;
    while(i>=0)
    {
        letra = aux[i];
        decimal = letra;
        dividendo = decimal;
        TextoBinario = "";
        while(dividendo >= 2)
        {
            if(dividendo%2 == 0)
            {
                TextoBinario = "0" + TextoBinario;
            }
            else
            {
                TextoBinario = "1" + TextoBinario;
            }
            dividendo = dividendo/2;
        }
        if(dividendo == 0)
        {
            TextoBinario = "0" + TextoBinario;
        }
        else
        {
            TextoBinario = "1" + TextoBinario;
        }
        while(TextoBinario.length() < 8)
        {
            TextoBinario = "0" + TextoBinario;
        }
        TextoBinarisado = TextoBinario + TextoBinarisado;
        i--;
    }
    cout<<"Texto compreso: "<<endl;
    cout<<compreso<<endl;
    cout<<endl<<"texto binarisado: "<<endl;
    cout<<TextoBinarisado<<endl;

    string descompresa, cadena="";
    char let;
    for(int i=0; i<tama; i++)
    {
        cadena = cadena + TextoBinarisado.at(i);
        let = LS.letra(cadena);
        if(let != 'n')
        {
            descompresa = descompresa + let;
            cadena = "";
        }
    }

    cout<<endl<<"Cadena descompresa: "<<endl;
    cout<<descompresa<<endl;

}

void Conexiones::Menu()
{
    LlenarMatriz();
    LS.Inicializa();
    char opc3;
    do
    {
        system(CLEAR);
        cout<<"1. Agregar"<<endl;
        cout<<"2. Imprimir"<<endl;
        cout<<"3. Modificar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Comprimir"<<endl;
        cout<<"6. Decomprimir"<<endl;
        cout<<"7. Regresar al menu principal"<<endl;
        cout<<"Elija una opcion: ";
        cin>>opc3;
        switch(opc3)
        {
        case '1':
        {
            system(CLEAR);
            Agregar();
            cin.get();
            cin.get();
            break;
        }
        case '2':
        {
            system(CLEAR);
            Imprimir();
            cin.get();
            cin.get();
            break;
        }
        case '3':
        {
            system(CLEAR);
            Modificar();
            cin.get();
            cin.get();
            break;
        }
        case '4':
        {
            system(CLEAR);
            Eliminar();
            cin.get();
            cin.get();
            break;
        }
        case '5':
        {
            system(CLEAR);
            LS.Anular();
            Encriptar();
            cin.get();
            cin.get();
            break;
        }
        case '6':
        {
            system(CLEAR);
            Descomprimir();
            cin.get();
            cin.get();
            break;
        }
        case '7':
        {
            break;
        }
        default:
        {
            cout<<"Inserte solo una de las opciones mencionadas, por favor"<<endl;
            cin.get();
            cin.get();
            break;
        }
        }
    }
    while(opc3!='7');
}
