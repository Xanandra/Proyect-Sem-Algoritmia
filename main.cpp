/*
Ernesto Emmanuel Lopez Gonzalez
214520082
Seminario de solucion de problemas de estructuras de datos II
D09
Hassem Ruben Macias Brambila
Code::Blocks
*/

#include <iostream>
#include <fstream>
#include "Destinos.h"
#include "Conexiones.h"
#include "Empleados.h"
#include "Hoteles.h"
#include "Clientes.h"
#ifdef WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <stdlib.h>
#define CLEAR "clear"
#endif // WIN32


using namespace std;

int main()
{
    Conexiones X;
    Empleados Em;
    Destinos D;
    Hoteles H;
    Clientes Cl;
    char opc1;
    int band = 0;

    ifstream A("Clientes.txt");
    if(!A.good())
    {
        band = 1;
    }
    A.close();

    if(band == 1)
    {
        Cl.Genera();
    }

    do
    {
        system(CLEAR);
        cout<<"1. Destinos"<<endl;
        cout<<"2. Conexiones"<<endl;
        cout<<"3. Empleados"<<endl;
        cout<<"4. Hoteles"<<endl;
        cout<<"5. Clientes"<<endl;
        cout<<"6. Salir"<<endl;
        cout<<endl<<"Elija una opcion: ";
        cin>>opc1;
        switch(opc1)
        {
            case '1':
            {
                system(CLEAR);
                D.Menu();
                cin.get();
                cin.get();
                break;
            }
            case '2':
            {
                system(CLEAR);
                X.Menu();
                cin.get();
                break;
            }
            case '3':
            {
                system(CLEAR);
                Em.Menu();
                cin.get();
                break;
            }
            case '4':
            {
                system(CLEAR);
                H.Menu();
                cin.get();
                break;
            }
            case '5':
            {
                system(CLEAR);
                Cl.Menu();
                cin.get();
                break;
            }
            case '6':
            {
                break;
            }
            default:
            {
                cout<<"Elija una opcion valida"<<endl;
                break;
            }
        }
    }while(opc1!='6');
    return 0;
}
