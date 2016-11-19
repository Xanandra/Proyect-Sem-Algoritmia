#include "Destinos.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // WIN32

void Destinos::Agregar()
{
    codigo=1;
    char auxiliar[15];
    int unsigned cont=0, band=0, band2=0, i=1;
    int a,b,c, ax, bx, cx, codigoaux;

    ax=strlen(destino);
    bx=1;
    cx=1;

    cin.ignore();
    do
    {
        band = 0;
        cont = 0;
        cout<<"Ingrese el destino: ";
        cin.getline(destino, 15, '\n');
        destino[strlen(destino)] = '\0';
        while(cont < strlen(destino) && band == 0)
        {
            if(!isalpha(destino[cont]) && destino[cont]!=' ')
            {
                band = 1;
            }
            cont++;
        }
    }while(band == 1);

    do
    {
    cout<<"Ingrese el tipo (salida=s, entrada=e): ";
    cin>>tipo;
    }while(tipo !='s' && tipo != 'S' && tipo != 'e' && tipo != 'E');

    do
    {
    cout<<"Ingrese la disponibilidad (disponible=1, no disponible=0): ";
    cin>>disponibilidad;
    }while(disponibilidad != '1' && disponibilidad != '0');

    ifstream Leer("Destinos.txt");
    if(Leer.good())
    {
            Leer.read((char*)&codigoaux,sizeof(int));
            if(codigoaux==0)
            {
                band2=1;
            }
            else
            {
            while(!Leer.eof())
            {
                Leer.read((char*)&ax, sizeof(int));
                Leer.read((char*)&auxiliar, ax);
                auxiliar[ax]='\0';

                Leer.read((char*)&bx, sizeof(int));
                Leer.read((char*)&auxiliar, bx);


                Leer.read((char*)&cx, sizeof(int));
                Leer.read((char*)&auxiliar, cx);

                codigo = codigoaux;
                if(Leer.eof())
                {
                    break;
                }
                i++;
                Leer.read((char*)&codigoaux,sizeof(int));
            }
            }
            if(band2==0)
            {
                codigo++;
            }
    }
    Leer.close();

    a=strlen(destino);
    b=1;
    c=1;

        ofstream A("Destinos.txt", ios::app);
        A.write((char*)&codigo, sizeof(int));
        A.write((char*)&a, sizeof(int));
        A.write((char*)&destino, a);
        A.write((char*)&b, sizeof(int));
        A.write((char*)&disponibilidad, b);
        A.write((char*)&c, sizeof(int));
        A.write((char*)&tipo, c);
        A.close();
        string conex;
        ifstream Esc("Matriz.txt", ios::in);
        ofstream aux("auxiliar.txt", ios::out);
        if(Esc.good())
        {
            for(unsigned int x=1; x<=i; x++)
            {
                for(unsigned int y=1; y<=i; y++)
                {
                    getline(Esc, conex, '|');
                    if(x==i || y==i)
                    {
                        aux << "0|";
                    }
                    else
                    {
                        aux << conex << "|";
                    }
                }
            }
        }
        Esc.close();
        aux.close();
        remove("Matriz.txt");
        rename("auxiliar.txt", "Matriz.txt");
}

void Destinos::Imprimir()
{
    int a, b, c;
    a=strlen(destino);
    b=1;
    c=1;

    ifstream A("Destinos.txt");
    if (!A.good())
    {
        cout<<"No existe el archivo"<<endl;
    }
    else
    {
        while(!A.eof())
        {
            A.read((char*)&codigo,sizeof(int));

            A.read((char*)&a, sizeof(int));
            A.read((char*)&destino, a);
            destino[a]='\0';

            A.read((char*)&b, sizeof(int));
            A.read((char*)&disponibilidad, b);

            A.read((char*)&c, sizeof(int));
            A.read((char*)&tipo, c);

            if(A.eof())
            {
                break;
            }

            cout<<"Destino: "<<destino<<endl;
            cout<<"Codigo: "<<codigo<<endl;
            cout<<"Tipo: ";
            if (tipo=='s')
            {
                cout<<"salida"<<endl;
            }
            else
            {
                cout<<"entrada"<<endl;
            }
            cout<<"Disponible: ";
            if(disponibilidad=='1')
            {
                cout<<"si"<<endl;
            }
            else
            {
                cout<<"no"<<endl;
            }
            cout<<endl;
        }
    }
    A.close();
}

void Destinos::Modificar()
{
    int unsigned band=0, band2=0, cont=0;
    int a, b, c, ax, bx, cx, codigoaux;
    char destinoaux[15], tipoaux, disponibilidadaux, validardigito;
    ofstream aux("auxiliar.txt", ios::out);
    ifstream leer("Destinos.txt", ios::in);

    a=strlen(destino);
    b=1;
    c=1;

    if(aux.good() && leer.good())
    {
        cout<<"Ingresa el codigo del destino que deseas modificar: ";
        cin>>validardigito;
        if(isdigit(validardigito))
        {
            codigoaux=validardigito-48;
            leer.read((char*)&codigo,sizeof(int));
            while(!leer.eof())
            {
                leer.read((char*)&a, sizeof(int));
                leer.read((char*)&destino, a);
                destino[a]='\0';

                leer.read((char*)&b, sizeof(int));
                leer.read((char*)&disponibilidad, b);

                leer.read((char*)&c, sizeof(int));
                leer.read((char*)&tipo, c);

                if(codigo==codigoaux)
                {
                    band=1;
                    cout<<"Ingrese el nuevo destino: ";
                    cin.getline(destinoaux, 15);
                    cin.getline(destinoaux, 15);
                    while(cont<strlen(destinoaux) && band2==0)
                    {
                        if(!isalpha(destinoaux[cont]))
                        {
                            band2=1;
                        }
                        cont++;
                    }

                    cout<<"Ingrese el tipo (salida=s, entrada=e): ";
                    cin>>tipoaux;
                    if (tipoaux!='s' && tipoaux!='e')
                    {
                        band2=1;
                    }

                    cout<<"Ingrese la disponibilidad (disponible=1, no disponible=0): ";
                    cin>>disponibilidadaux;
                    if (disponibilidadaux!='1' && disponibilidadaux!='0')
                    {
                        band2=1;
                    }
                    if(band2==0)
                    {
                        ax=strlen(destinoaux);
                        bx=1;
                        cx=1;

                        aux.write((char*)&codigoaux,sizeof(int));

                        aux.write((char*)&ax, sizeof(int));
                        aux.write((char*)&destinoaux, ax);

                        aux.write((char*)&bx, sizeof(int));
                        aux.write((char*)&disponibilidadaux, bx);

                        aux.write((char*)&cx, sizeof(int));
                        aux.write((char*)&tipoaux, cx);

                        cout<<"Destino modificado"<<endl;
                    }
                    else
                    {
                        cout<<"Datos erroneos, por favor intentelo de nuevo"<<endl;
                    }
                }
                else
                {
                    aux.write((char*)&codigo,sizeof(int));

                    aux.write((char*)&a, sizeof(int));
                    aux.write((char*)&destino, a);

                    aux.write((char*)&b, sizeof(int));
                    aux.write((char*)&disponibilidad, b);

                    aux.write((char*)&c, sizeof(int));
                    aux.write((char*)&tipo, c);
                }
                leer.read((char*)&codigo,sizeof(int));
            }
            if(band==0)
            {
                cout<<"Ese codigo no existe"<<endl;
            }
            aux.close();
            leer.close();
            remove("Destinos.txt");
            rename("auxiliar.txt", "Destinos.txt");
        }
        else
        {
            cout<<"codigo invalido, por favor intente de nuevo"<<endl;
        }
    }
    else
    {
        cout<<"Error: archivo no encontrado"<<endl;
    }
    if(leer.good() && aux.good())
    {
        aux.close();
        leer.close();
    }
}

void Destinos::Eliminar()
{
    int band=0, i=0, num;
    int a, b, c, codigoaux;
    char validardigito;
    string preciosaux;
    ofstream aux("auxiliar.txt", ios::out);
    ifstream leer("Destinos.txt", ios::in);

    a=strlen(destino);
    b=1;
    c=1;

    if(aux.good() && leer.good())
    {
        cout<<"Ingresa el codigo del destino que deseas Eliminar: ";
        cin>>validardigito;
        if(isdigit(validardigito))
        {
            codigoaux=validardigito-48;
            leer.read((char*)&codigo,sizeof(int));
            while(!leer.eof())
            {
                leer.read((char*)&a, sizeof(int));
                leer.read((char*)&destino, a);
                destino[a]='\0';

                leer.read((char*)&b, sizeof(int));
                leer.read((char*)&disponibilidad, b);

                leer.read((char*)&c, sizeof(int));
                leer.read((char*)&tipo, c);

                if(leer.eof())
                {
                    break;
                }
                if(codigo==codigoaux)
                {
                    band=1;
                    num=i;
                    cout<<"Destino eliminado"<<endl;
                }
                else
                {
                    aux.write((char*)&codigo,sizeof(int));

                    aux.write((char*)&a, sizeof(int));
                    aux.write((char*)&destino, a);

                    aux.write((char*)&b, sizeof(int));
                    aux.write((char*)&disponibilidad, b);

                    aux.write((char*)&c, sizeof(int));
                    aux.write((char*)&tipo, c);
                }
                leer.read((char*)&codigo,sizeof(int));
                i++;
            }
            if(band==0)
            {
                cout<<"Ese codigo no existe"<<endl;
            }
            else
            {
                ifstream Leer("Matriz.txt", ios::in);
                ofstream Temp("Temporal.txt", ios::out);
                if(Leer.good() && Temp.good())
                {
                    for(int x=0; x<i; x++)
                    {
                        for(int y=0; y<i; y++)
                        {
                            getline(Leer, preciosaux, '|');
                            if(leer.eof())
                            {
                                break;
                            }
                            if(x!=num && y!=num)
                            {
                                Temp << preciosaux << "|";
                            }
                        }
                    }
                }
                else
                {
                    cout<<"Error al eliminar conexiones"<<endl;
                }
                Leer.close();
                Temp.close();
                remove("Matriz.txt");
                rename("Temporal.txt", "Matriz.txt");
            }
            aux.close();
            leer.close();
            remove("Destinos.txt");
            rename("auxiliar.txt", "Destinos.txt");

        }
        else
        {
            cout<<"codigo invalido, por favor intente de nuevo"<<endl;
        }
    }
    else
    {
        cout<<"Error: archivo no encontrado"<<endl;
    }
    if(leer.good() && aux.good())
    {
        aux.close();
        leer.close();
    }
}

void Destinos::Cancelar()
{
    int band=0;
    int a, b, c, codigoaux;
    char validardigito;
    ofstream aux("auxiliar.txt", ios::out);
    ifstream leer("Destinos.txt", ios::in);

    a=strlen(destino);
    b=1;
    c=1;

    if(aux.good() && leer.good())
    {
        cout<<"Ingresa el codigo del destino que deseas cancelar: ";
        cin>>validardigito;
        if(isdigit(validardigito))
        {
            codigoaux=validardigito-48;
            leer.read((char*)&codigo,sizeof(int));
            while(!leer.eof())
            {
                leer.read((char*)&a, sizeof(int));
                leer.read((char*)&destino, a);
                destino[a]='\0';

                leer.read((char*)&b, sizeof(int));
                leer.read((char*)&disponibilidad, b);

                leer.read((char*)&c, sizeof(int));
                leer.read((char*)&tipo, c);

                if(codigo==codigoaux)
                {
                    band=1;
                    if(disponibilidad=='1')
                    {
                    disponibilidad='0';
                    cout<<"Destino cancelado"<<endl;
                    }
                    else
                    {
                        cout<<"Ese destino ya estaba cancelado"<<endl;
                    }
                    aux.write((char*)&codigo,sizeof(int));

                    aux.write((char*)&a, sizeof(int));
                    aux.write((char*)&destino, a);

                    aux.write((char*)&b, sizeof(int));
                    aux.write((char*)&disponibilidad, b);

                    aux.write((char*)&c, sizeof(int));
                    aux.write((char*)&tipo, c);
                }
                else
                {
                    aux.write((char*)&codigo,sizeof(int));

                    aux.write((char*)&a, sizeof(int));
                    aux.write((char*)&destino, a);

                    aux.write((char*)&b, sizeof(int));
                    aux.write((char*)&disponibilidad, b);

                    aux.write((char*)&c, sizeof(int));
                    aux.write((char*)&tipo, c);
                }
                leer.read((char*)&codigo,sizeof(int));
            }
            if(band==0)
            {
                cout<<"Ese codigo no existe"<<endl;
            }
            aux.close();
            leer.close();
            remove("Destinos.txt");
            rename("auxiliar.txt", "Destinos.txt");
        }
        else
        {
            cout<<"codigo invalido, por favor intente de nuevo"<<endl;
        }
    }
    else
    {
        cout<<"Error: archivo no encontrado"<<endl;
    }
    if(leer.good() && aux.good())
    {
        aux.close();
        leer.close();
    }
}

void Destinos::Buscar()
{
    int codigoaux, band=0, band2=0, a, b, c;
    int unsigned cont=0;
    char destinoaux[15], tipoaux, validarcodigo, opc;
    ifstream leer("Destinos.txt", ios::out|ios::in);

    a=strlen(destino);
    b=1;
    c=1;

    if(leer.good())
    {
        cout<<"1. Buscar por codigo"<<endl;
        cout<<"2. Buscar por destino"<<endl;
        cout<<"3. Buscar por tipo"<<endl;
        cout<<"Elija una opcion: ";
        cin>>opc;
        switch(opc)
        {
            case '1':
            {
                system(CLEAR);
                cout<<"Inserta el codigo que deseas buscar: ";
                cin>>validarcodigo;
                codigoaux=validarcodigo-48;
                if(isdigit(validarcodigo))
                {
                cout<<endl;
                leer.read((char*)&codigo, sizeof(int));
                while(!leer.eof())
                {
                    leer.read((char*)&a, sizeof(int));
                    leer.read((char*)&destino, a);
                    destino[a]='\0';

                    leer.read((char*)&b, sizeof(int));
                    leer.read((char*)&disponibilidad, b);

                    leer.read((char*)&c, sizeof(int));
                    leer.read((char*)&tipo, c);

                    if(codigo==codigoaux)
                    {
                        band=1;
                        cout<<"Destino: "<<destino<<endl;
                        cout<<"Codigo: "<<codigo<<endl;
                        cout<<"Tipo: ";
                        if(tipo=='s')
                        {
                            cout<<"salida"<<endl;
                        }
                        else
                        {
                            cout<<"entrada"<<endl;
                        }
                        cout<<"Disponible: ";
                        if (disponibilidad=='1')
                        {
                            cout<<"si"<<endl;
                        }
                        else
                        {
                            cout<<"no"<<endl;
                        }
                    }
                    leer.read((char*)&codigo, sizeof(int));
                }
                if(band==0)
                {
                    cout<<"No existe ese codigo"<<endl;
                }
                }
                else
                {
                    cout<<"Codigo no valido, por favor intente de nuevo"<<endl;
                }
                break;
            }
            case '2':
            {
                system(CLEAR);
                cout<<"Inserta el destino que deseas buscar: ";
                cin>>destinoaux;
                while(cont<strlen(destinoaux) && band2==0)
                {
                    if(!isalpha(destinoaux[cont]))
                    {
                        band2=1;
                    }
                    cont++;
                }
                if(band2==0)
                {
                cout<<endl;
                leer.read((char*)&codigo, sizeof(int));
                while(!leer.eof())
                {
                    leer.read((char*)&a, sizeof(int));
                    leer.read((char*)&destino, a);
                    destino[a]='\0';

                    leer.read((char*)&b, sizeof(int));
                    leer.read((char*)&disponibilidad, b);

                    leer.read((char*)&c, sizeof(int));
                    leer.read((char*)&tipo, c);

                    if(strcmp(destino, destinoaux)==0)
                    {
                        band=1;
                        cout<<"Destino: "<<destino<<endl;
                        cout<<"Codigo: "<<codigo<<endl;
                        cout<<"Tipo: ";
                        if(tipo=='s')
                        {
                            cout<<"salida"<<endl;
                        }
                        else
                        {
                            cout<<"entrada"<<endl;
                        }
                        cout<<"Disponible: ";
                        if (disponibilidad=='1')
                        {
                            cout<<"si"<<endl;
                        }
                        else
                        {
                            cout<<"no"<<endl;
                        }
                    }
                    leer.read((char*)&codigo, sizeof(int));
                }
                if(band==0)
                {
                    cout<<"No existe ese destino"<<endl;
                }
                }
                else
                {
                    cout<<"Datos no validos, por favor intente de nuevo"<<endl;
                }
                break;
            }
            case '3':
            {
                system(CLEAR);
                cout<<"Inserta el tipo que deseas buscar (salida = s, entrada = e): ";
                cin>>tipoaux;
                if(tipoaux!='s' && tipoaux!='e')
                {
                    cout<<"Datos no validos, por favor intente de nuevo"<<endl;
                }
                else
                {
                cout<<endl;
                leer.read((char*)&codigo, sizeof(int));
                while(!leer.eof())
                {
                    leer.read((char*)&a, sizeof(int));
                    leer.read((char*)&destino, a);
                    destino[a]='\0';

                    leer.read((char*)&b, sizeof(int));
                    leer.read((char*)&disponibilidad, b);

                    leer.read((char*)&c, sizeof(int));
                    leer.read((char*)&tipo, c);

                    if(tipo==tipoaux)
                    {
                        band=1;
                        cout<<"Destino: "<<destino<<endl;
                        cout<<"Codigo: "<<codigo<<endl;
                        cout<<"Tipo: ";
                        if(tipo=='s')
                        {
                            cout<<"salida"<<endl;
                        }
                        else
                        {
                            cout<<"entrada"<<endl;
                        }
                        cout<<"Disponible: ";
                        if (disponibilidad=='1')
                        {
                            cout<<"si"<<endl;
                        }
                        else
                        {
                            cout<<"no"<<endl;
                        }
                        cout<<endl;
                    }
                    leer.read((char*)&codigo, sizeof(int));
                }
                if(band==0)
                {
                    cout<<"No existe ese codigo"<<endl;
                }
                }
                break;
            }
        }
    }
    else
    {
        cout<<"No se pudo abrir el archivo"<<endl;
    }
    leer.close();
}

void Destinos::Menu()
{
    char opc2;
    do
    {
        system(CLEAR);
        cout<<"1. Agregar destino"<<endl;
        cout<<"2. Imprimir destinos"<<endl;
        cout<<"3. Modificar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Buscar"<<endl;
        cout<<"6. Cancelar"<<endl;
        cout<<"7. Regresar al menu principal"<<endl;
        cout<<"Elija una opcion: ";
        cin>>opc2;
        switch(opc2)
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
            Buscar();
            cin.get();
            cin.get();
            break;
        }
        case '6':
        {
            system(CLEAR);
            Cancelar();
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
            cout<<endl<<"Por favor ingrese solo el numero de la opcion"<<endl;
            cin.get();
            cin.get();
            break;
        }
        }
    }
    while(opc2!='7');
}
