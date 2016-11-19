#include "Empleados.h"
#include <iostream>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <stdlib.h>
#define CLEAR "clear"
#endif // WIN32

using namespace std;

Empleados Em;

int Empleados::CodigoE()
{
    int cod;
    ifstream E("Empleados.txt");
    if(E.good())
    {
        while(!E.eof())
        {
            E.read((char*)&Em, sizeof(Em));
            if(E.eof())
            {
                cod = Em.codigo + 1;
                break;
            }
        }
    }
    else
    {
        cod = 1;
    }
    E.close();
    return cod;
}

void Empleados::Capturar()
{
    Em.codigo = Em.CodigoE();

    cout<<"Inserte el nombre del empleado: ";
    cin.ignore();
    cin.getline(Em.nombre, 30, '\n');
    cout<<"Inserte el nombre de usuario: ";
    cin.getline(Em.usuario, 30, '\n');
    cout<<"Inserte el password: ";
    cin.getline(Em.password, 30, '\n');
    cout<<"Inserte el RFC: ";
    cin.getline(Em.RFC, 12, '\n');
    cout<<"Inserte el tipo: ";
    cin>>Em.tipo;

    ofstream E("Empleados.txt", ios::app);
    E.write((char*)&Em, sizeof(Em));
    E.close();
}

void Empleados::Mostrar()
{
    ifstream E("Empleados.txt", ios::in);
    if(E.good())
    {
        while(!E.eof())
        {
            E.read((char*)&Em, sizeof(Em));
            if(E.eof())
            {
                break;
            }
            cout<<"Codigo: "<<Em.codigo<<endl;
            cout<<"Nombre: "<<Em.nombre<<endl;
            cout<<"Usuario: "<<Em.usuario<<endl;
            cout<<"Password: "<<Em.password<<endl;
            cout<<"RFC: "<<Em.RFC<<endl;
            cout<<"Tipo: "<<Em.tipo<<endl<<endl;
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;

    }
    E.close();
}

void Empleados::Modificar()
{
    int cod, band=0;
    long int pos;
    fstream E("Empleados.txt", ios::in | ios::out);
    if(E.good())
    {
        cout<<"Inserte el codigo del empelado que desea modificar: ";
        cin>>cod;
        while(!E.eof() && band==0)
        {
            E.read((char*)&Em, sizeof(Em));
            if(E.eof())
            {
                break;
            }
            if(cod == Em.codigo)
            {
                band=1;
                pos = E.tellg();
                E.seekg(pos - sizeof(Em), ios::beg);
                cout<<endl<<"Nuevos datos"<<endl;
                cout<<"Inserte el nombre del empleado: ";
                cin.ignore();
                cin.getline(Em.nombre, 30, '\n');
                cout<<"Inserte el nombre de usuario: ";
                cin.getline(Em.usuario, 30, '\n');
                cout<<"Inserte el password: ";
                cin.getline(Em.password, 30, '\n');
                cout<<"Inserte el RFC: ";
                cin.getline(Em.RFC, 12, '\n');
                cout<<"Inserte el tipo: ";
                cin>>Em.tipo;
                E.write((char*)&Em, sizeof(Em));
                cout<<endl<<"Cliente modificado"<<endl;
            }
        }
        if(band==0)
        {
            cout<<"No existe ese codigo"<<endl;
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    E.close();
}

void Empleados::Eliminar()
{
    int cod, band=0;
    ifstream E("Empleados.txt", ios::in);
    ofstream Aux("Auxiliar.txt", ios::out);
    if(E.good())
    {
        cout<<"Inserte el codigo del empleado que desea eliminar: ";
        cin>>cod;
        while(!E.eof())
        {
            E.read((char*)&Em, sizeof(Em));
            if(E.eof())
            {
                break;
            }
            if(cod == Em.codigo)
            {
                band=1;
                cout<<endl<<"Empleado eliminado"<<endl;
            }
            else
            {
                Aux.write((char*)&Em, sizeof(Em));
            }
        }
        if(band==0)
        {
            cout<<"No existe ese codigo"<<endl;
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    Aux.close();
    E.close();
    remove("Empleados.txt");
    rename("Auxiliar.txt", "Empleados.txt");
}

void Empleados::Buscar()
{
    int cod, band=0;
    ifstream E("Empleados.txt");
    if(E.good())
    {
        cout<<"Inserte el codigo del empleado que desea buscar: ";
        cin>>cod;
        cout<<endl;
        while(!E.eof())
        {
            E.read((char*)&Em, sizeof(Em));
            if(E.eof())
            {
                break;
            }
            if(cod == Em.codigo)
            {
                band=1;
                cout<<"Codigo: "<<Em.codigo<<endl;
                cout<<"Nombre: "<<Em.nombre<<endl;
                cout<<"Usuario: "<<Em.usuario<<endl;
                cout<<"Password: "<<Em.password<<endl;
                cout<<"RFC: "<<Em.RFC<<endl;
                cout<<"Tipo: "<<Em.tipo<<endl<<endl;
            }
        }
        if(band==0)
        {
            cout<<"No existe ese codigo"<<endl;
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    E.close();
}

void Empleados::Menu()
{
    char opc;
    do
    {
        system(CLEAR);
        cout<<"1. Agregar"<<endl;
        cout<<"2. Imprimir"<<endl;
        cout<<"3. Modificar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Buscar"<<endl;
        cout<<"6. Regresar al menu principal"<<endl;
        cout<<"Elija una opcion: ";
        cin>>opc;
        switch(opc)
        {
        case '1':
        {
            system(CLEAR);
            Em.Capturar();
            cin.get();
            cin.get();
            break;
        }
        case '2':
        {
            system(CLEAR);
            Em.Mostrar();
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
            Buscar();
            cin.get();
            cin.get();
        }
        case '6':
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
    while(opc!='6');
}
