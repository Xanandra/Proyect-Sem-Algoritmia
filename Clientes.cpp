#include "Clientes.h"

Clientes Cl;
char llave[30];
long int d_base, pos;
int cont = 0, bandera;

void Clientes::Dispersa()
{
    unsigned int j = 0;
    d_base = 0;
    while(j < strlen(llave))
    {
        d_base = d_base + (100 * llave[j]) + (llave[j+1]%84645);
        j = j+2;
    }
    d_base = d_base%100;
}

void Clientes::Genera()
{
    int i, j, maximo = 4;
    ofstream A("Clientes.txt", ios::app);
    for(i=0; i<100; i++)
    {
        A.write((char*)&cont, sizeof(int));
        for(j=0; j<4; j++)
        {
            A.write((char*)&Cl, sizeof(Cl));
        }
    }
    A.close();
    ofstream M("maximo.txt", ios::out);
    M.write((char*)&maximo, sizeof(int));
    M.close();
}


int Clientes::GeneraCodigo()
{
    int maximo, maxi;
    maximo = GeneraMaximo();
    int i;
    pos = 0;
    ifstream A("Clientes.txt");
    if(A.good())
    {
        while(!A.eof())
        {
            A.seekg(pos, ios::beg);
            A.read((char*)&cont, sizeof(int));
            if(cont == 0)
            {
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
            else
            {
                for(i=0; i<cont; i++)
                {
                    A.read((char*)&Cl, sizeof(Cl));
                    if(Cl.codigo > maxi)
                    {
                        maxi = Cl.codigo;
                    }
                }
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
        }
    }
    A.close();
    maxi++;
    return maxi;
}

int Clientes::GeneraMaximo()
{
    int maximo;
    ifstream M("maximo.txt");
    if(M.good())
    {
        M.read((char*)&maximo, sizeof(int));
    }
    M.close();
    return maximo;
}

void Clientes::Capturar(int band)
{
    long int aux, aux2;
    int maximo, codaux, telaux;
    char nombreaux[30], correoaux[30];
    if(band == 0)
    {
        Cl.codigo = Cl.GeneraCodigo();
    }
    else
    {
        Cl.codigo = band;
    }

    cout<<"Inserte el nombre: ";
    cin.ignore();
    cin.getline(Cl.nombre, 30, '\n');
    cout<<"Inserte el telefono: ";
    cin>>Cl.tel;
    cout<<"Inserte el correo electronico: ";
    cin.ignore();
    cin.getline(Cl.correo, 30, '\n');
    strcpy(llave, Cl.nombre);
    Dispersa();
    aux = d_base;

    maximo = GeneraMaximo();

    fstream B("Clientes.txt", ios::out | ios::in);
    d_base = d_base * ((sizeof(Cl) * maximo) + sizeof(int));
    B.seekg(d_base, ios::beg);
    B.read((char*)&cont, sizeof(int));
    cout<<endl<<"Contador: "<<cont<<endl;
    if(cont == maximo)
    {
        strcpy(nombreaux, Cl.nombre);
        codaux = Cl.codigo;
        strcpy(correoaux, Cl.correo);
        telaux = Cl.tel;

        cout<<"No quedan mas espacios, expandiendo..."<<endl<<endl;
        ofstream Aux("Auxiliar.txt", ios::app);
        B.seekp(0, ios::beg);
        while(!B.eof())
        {
            B.read((char*)&cont, sizeof(int));
            if(B.eof())
            {
                break;
            }
            Aux.write((char*)&cont, sizeof(cont));
            for(int i=0; i<maximo; i++)
            {
                B.read((char*)&Cl, sizeof(Cl));
                Aux.write((char*)&Cl, sizeof(Cl));
            }
            Aux.write((char*)&Cl, sizeof(Cl));
        }
        B.close();
        Aux.close();

        ofstream M("maximo.txt", ios::out);
        maximo++;
        M.seekp(0, ios::beg);
        M.write((char*)&maximo, sizeof(int));
        M.close();

        remove("Clientes.txt");
        rename("Auxiliar.txt", "Clientes.txt");

        strcpy(Cl.nombre, nombreaux);
        Cl.codigo = codaux;
        strcpy(Cl.correo, correoaux);
        Cl.tel = telaux;

        fstream Cli("Clientes.txt", ios::out | ios::in);
        strcpy(llave, Cl.nombre);
        Dispersa();
        aux = d_base;
        d_base = d_base * ((sizeof(Cl) * maximo) + sizeof(int));
        Cli.seekg(d_base, ios::beg);
        Cli.read((char*)&cont, sizeof(int));
        pos = d_base + (cont * sizeof(Cl)) + sizeof(int);
        aux2 = pos;
        Cli.seekp(pos, ios::beg);
        Cli.write((char*)&Cl, sizeof(Cl));
        cont++;
        pos = d_base;
        Cli.seekp(pos, ios::beg);
        Cli.write((char*)&cont, sizeof(int));
        cout<<"Contador: "<<cont<<" de la llave y la direccion es: "<<aux2<<" su distancia base fue: "<<aux<<endl;
        Cli.close();
    }
    else
    {
        pos = d_base + (cont * sizeof(Cl)) + sizeof(int);
        aux2 = pos;
        B.seekp(pos, ios::beg);
        B.write((char*)&Cl, sizeof(Cl));
        cont++;
        pos = d_base;
        B.seekp(pos, ios::beg);
        B.write((char*)&cont, sizeof(int));
        cout<<"Contador: "<<cont<<" de la llave y la direccion es: "<<aux2<<" su distancia base fue: "<<aux<<endl;
        B.close();
    }
}

void Clientes::Mostrar()
{
    int i, maximo;
    pos = 0;
    maximo = GeneraMaximo();
    ifstream A("Clientes.txt");
    if(A.good())
    {
        while(!A.eof())
        {
            A.seekg(pos, ios::beg);
            A.read((char*)&cont, sizeof(int));
            if(cont == 0)
            {
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
            else
            {
                for(i=0; i<cont; i++)
                {
                    A.read((char*)&Cl, sizeof(Cl));
                    if(A.eof())
                    {
                        break;
                    }
                    cout<<"Codigo: "<<Cl.codigo<<endl;
                    cout<<"Nombre: "<<Cl.nombre<<endl;
                    cout<<"Telefono: "<<Cl.tel<<endl;
                    cout<<"Correo: "<<Cl.correo<<endl<<endl;
                }
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    A.close();
}

int Clientes::Eliminar()
{
    int codaux, i, maximo;
    pos = 0;
    bandera = 0;
    maximo = GeneraMaximo();
    fstream A("Clientes.txt", ios::out | ios::in);
    if(A.good())
    {
        cout<<"Codigo del cliente: ";
        cin>>codaux;
        while(!A.eof())
        {
            A.seekg(pos, ios::beg);
            A.read((char*)&cont, sizeof(int));
            if(cont == 0)
            {
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
            else
            {
                for(i=0; i<cont; i++)
                {
                    A.read((char*)&Cl, sizeof(Cl));
                    if(Cl.codigo == codaux)
                    {
                        bandera = 1;
                        int j=0;
                        while(j < cont-i-1)
                        {
                            A.read((char*)&Cl, sizeof(Cl));
                            pos = A.tellg();
                            pos = pos - 2 * sizeof(Cl);
                            A.seekg(pos, ios::beg);
                            A.write((char*)&Cl, sizeof(Cl));
                            pos = A.tellg();
                            pos = pos + sizeof(Cl);
                            A.seekg(pos, ios::beg);
                            j++;
                        }
                        pos = A.tellg();
                        pos = pos - cont * sizeof(Cl) - sizeof(int);
                        A.seekg(pos, ios::beg);
                        A.read((char*)&cont, sizeof(cont));
                        cont--;
                        A.seekg(pos, ios::beg);
                        A.write((char*)&cont, sizeof(int));
                        return codaux;
                    }
                }
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
        }
        if(bandera == 0)
        {
            cout<<"No existe ese codigo"<<endl;
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    A.close();
    return -1;
}

void Clientes::Modificar()
{
    int band;
    band = Eliminar();
    if(band != -1)
    {
        cout<<endl<<"Nuevos datos"<<endl;
        Capturar(band);
    }
}

void Clientes::Buscar()
{
    int i, cod, band = 0, maximo;
    pos = 0;
    maximo = GeneraMaximo();
    ifstream A("Clientes.txt");
    if(A.good())
    {
        cout<<"Inserte el codigo del cliente a buscar: ";
        cin>>cod;
        while(!A.eof())
        {
            A.seekg(pos, ios::beg);
            A.read((char*)&cont, sizeof(int));
            if(cont == 0)
            {
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
            else
            {
                for(i=0; i<cont; i++)
                {
                    A.read((char*)&Cl, sizeof(Cl));
                    if(A.eof())
                    {
                        break;
                    }
                    if(Cl.codigo == cod)
                    {
                        band = 1;
                        cout<<endl<<"Codigo: "<<Cl.codigo<<endl;
                        cout<<"Nombre: "<<Cl.nombre<<endl;
                        cout<<"Telefono: "<<Cl.tel<<endl;
                        cout<<"Correo: "<<Cl.correo<<endl;
                    }
                }
                pos = pos + (maximo * sizeof(Cl)) + sizeof(int);
            }
        }
        if(band == 0)
        {
            cout<<endl<<"No existe ese codigo"<<endl;
        }
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    A.close();
}

void Clientes::Menu()
{
    char opc;
    do
    {
        system(CLEAR);
        cout<<"1. Capturar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Modificar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Buscar"<<endl;
        cout<<"6. Regresar al menu principal"<<endl;
        cout<<endl<<"Elija una opcion: ";
        cin>>opc;
        switch(opc)
        {
        case '1':
        {
            system(CLEAR);
            Cl.Capturar(0);
            cin.get();
            cin.get();
            break;
        }
        case '2':
        {
            system(CLEAR);
            Cl.Mostrar();
            cin.get();
            cin.get();
            break;
        }
        case '3':
        {
            system(CLEAR);
            Cl.Modificar();
            cin.get();
            cin.get();
            break;
        }
        case '4':
        {
            system(CLEAR);
            Cl.Eliminar();
            cin.get();
            cin.get();
            break;
        }
        case '5':
        {
            system(CLEAR);
            Cl.Buscar();
            cin.get();
            cin.get();
            break;
        }
        case '6':
        {
            break;
        }
        default:
        {
            cout<<"Inserte una opcion valida"<<endl;
        }
        }
    }
    while(opc != '6');
}
