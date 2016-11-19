#include "Hoteles.h"
#include "TDA_Hoteles.h"
#include "TDA_Secundario.h"

IndiceH I;
Hoteles H;
Paises P;
TDA_Hoteles TDA;
TDA_Secundario TDAS;

void Hoteles::SetCod_Pais(int cod_paisx)
{
    cod_pais = cod_paisx;
}

int Hoteles::GetCod_Pais()
{
    return cod_pais;
}

void IndiceH::SetLlave(int llavex)
{
    llave = llavex;
}

int IndiceH::GetLlave()
{
    return llave;
}

void IndiceH::SetPosicion(long int posicionx)
{
    posicion = posicionx;
}

long int IndiceH::GetPosicion()
{
    return posicion;
}

void Paises::SetCodigo(int codigox)
{
    codigo = codigox;
}

int Paises::GetCodigo()
{
    return codigo;
}

void Paises::SetPosicion(int posicionx)
{
    posicion = posicionx;
}

int Paises::GetPosicion()
{
    return posicion;
}

int Hoteles::CodigoH()
{
    ifstream B("IndiceH.txt");
    if(B.good())
    {
        while(!B.eof())
        {
            B.read((char*)&I, sizeof(I));
            if(B.eof())
            {
                break;
            }
        }
    }
    B.close();
    return I.GetLlave();
}

int Hoteles::Codigo_pais(int cod)
{
    int a, b, c, cod_pais, band=0;
    char auxiliar[15];
    ifstream D("Destinos.txt");
    if(D.good())
    {
        while(!D.eof())
        {
            D.read((char*)&cod_pais, sizeof(int));
            D.read((char*)&a, sizeof(int));
            D.read((char*)&auxiliar, a);
            auxiliar[a]='\0';
            D.read((char*)&b, sizeof(int));
            D.read((char*)&auxiliar, b);
            D.read((char*)&c, sizeof(int));
            D.read((char*)&auxiliar, c);
            if(D.eof())
            {
                break;
            }
            if(cod_pais == cod)
            {
                band = 1;
                break;
            }
        }
    }
    D.close();
    return band;
}

int Paises::cod_paises(int cod)
{
    ifstream Pais("Paises.txt");
    if(Pais.good())
    {
        while(!Pais.eof())
        {
            Pais.read((char*)&P, sizeof(P));
            if(Pais.eof())
            {
                break;
            }
            if(cod == P.GetCodigo())
            {
                return P.GetPosicion();
            }
        }
    }
    Pais.close();
    return -1;
}

string Hoteles::Pais(int codigo)
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

void Hoteles::Capturar()
{
    int band, band2;
    cout<<"Inserte el nombre del hotel: ";
    cin.ignore();
    cin.getline(H.nombre, 30, '\n');
    cout<<"Inserte el costo: ";
    cin>>H.costo;
    cout<<"Inserte la categoria: ";
    cin.ignore();
    cin.getline(H.categoria, 20, '\n');
    do
    {
        cout<<"Inserte el codigo del pais: ";
        cin>>H.cod_pais;
        band = H.Codigo_pais(H.cod_pais);
    }while(band == 0);

    H.codigo = H.CodigoH();
    H.codigo++;
    I.SetLlave(H.codigo);
    band2 = P.cod_paises(H.cod_pais);
    P.SetPosicion(H.codigo);
    P.SetCodigo(H.cod_pais);

    if(band2 == -1)
    {
        ofstream Pais("Paises.txt", ios::app);
        Pais.write((char*)&P, sizeof(P));
        Pais.close();

        TDAS.Insertar(H.codigo, 0);
    }
    else
    {
        TDAS.Insertar(H.codigo, band2);
    }


    ofstream A("Hoteles.txt", ios::app);
    ofstream B("IndiceH.txt", ios::app);
    A.write((char*)&H, sizeof(H));
    A.seekp(0, A.end);
    I.SetPosicion(A.tellp());
    I.SetPosicion(I.GetPosicion() - sizeof(H));
    B.write((char*)&I, sizeof(I));
    A.close();
    B.close();
}

void Hoteles::Mostrar()
{
    ifstream B("IndiceH.txt");
    if(B.good())
    {
        ifstream A("Hoteles.txt");
        while(!B.eof())
        {
            B.read((char*)&I, sizeof(I));
            if(B.eof())
            {
                break;
            }
            A.seekg(I.GetPosicion());
            A.read((char*)&H, sizeof(H));
            cout<<"Codigo: "<<H.codigo<<endl;
            cout<<"Nombre: "<<H.nombre<<endl;
            cout<<"Costo: "<<H.costo<<endl;
            cout<<"Categoria: "<<H.categoria<<endl;
            cout<<"Pais: "<<H.cod_pais<<". "<<Pais(H.cod_pais)<<endl<<endl;
        }
        A.close();
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    B.close();
}

void Hoteles::Modificar()
{
    int cod, band, band2 = 0, pos;
    fstream B("IndiceH.txt", ios::out | ios::in);
    if(B.good())
    {
        cout<<"Ingrese el codigo del hotel que desea modificar: ";
        cin>>cod;
        fstream A("Hoteles.txt", ios::out | ios::in);
        while(!B.eof())
        {
            B.read((char*)&I, sizeof(I));
            if(B.eof())
            {
                break;
            }
            if(I.GetLlave() == cod)
            {
                band2=1;
                A.seekg(I.GetPosicion());
                A.read((char*)&H, sizeof(H));
                cout<<"Inserte el nuevo nombre del hotel: ";
                cin.ignore();
                cin.getline(H.nombre, 30, '\n');
                cout<<"Inserte el costo: ";
                cin>>H.costo;
                cout<<"Inserte la categoria: ";
                cin.ignore();
                cin.getline(H.categoria, 20, '\n');
                do
                {
                    cout<<"Inserte el codigo del pais: ";
                    cin>>H.cod_pais;
                    band = H.Codigo_pais(H.cod_pais);
                }while(band == 0);
                if(cod != H.cod_pais)
                {
                    pos = P.cod_paises(H.cod_pais);
                    if(pos == -1)
                    {
                        TDAS.Modificar(I.GetLlave(), 0);
                    }
                    else
                    {
                        TDAS.Modificar(I.GetLlave(), pos);
                    }
                }
                A.seekg(I.GetPosicion());
                A.write((char*)&H, sizeof(H));
                cout<<endl<<"Hotel modificado"<<endl;
            }
        }
        if(band2 == 0)
        {
            cout<<"no existe ese codigo"<<endl;
        }
        A.close();
    }
    else
    {
        cout<<"Error al abrir los archivos"<<endl;
    }
    B.close();
}

void Hoteles::Eliminar()
{
    int cod, band=0;
    long int pos;
    ifstream B("IndiceH.txt", ios::in);
    ofstream Temp("Temporal.txt", ios::out);
    if(B.good())
    {
        cout<<"Inserte el codigo del hotel que desea eliminar: ";
        cin>>cod;
        ifstream A("Hoteles.txt", ios::in);
        ofstream Aux("Auxiliar.txt", ios::out);
        while(!B.eof())
        {
            B.read((char*)&I, sizeof(I));
            A.read((char*)&H, sizeof(H));
            if(B.eof())
            {
                break;
            }
            if(I.GetLlave() == cod)
            {
                band=1;
                cout<<endl<<"Hotel eliminado"<<endl;
                TDAS.Eliminar(I.GetLlave());
            }
            else
            {
                Aux.write((char*)&H, sizeof(H));
                Temp.seekp(0, Temp.end);
                pos = Aux.tellp();
                I.SetPosicion(pos - sizeof(H));
                Temp.write((char*)&I, sizeof(I));
            }
        }
        if(band == 0)
        {
            cout<<"No existe ese codigo"<<endl;
        }
        A.close();
        remove("Hoteles.txt");
        rename("Auxiliar.txt", "Hoteles.txt");
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    B.close();
    remove("IndiceH.txt");
    rename("Temporal.txt", "IndiceH.txt");
}

void Hoteles::Buscar()
{
    int cod, band=0;
    ifstream B("IndiceH.txt");
    if(B.good())
    {
        cout<<"Inserte el codigo del hotel que desea buscar: ";
        cin>>cod;
        ifstream A("Hoteles.txt");
        while(!B.eof())
        {
            B.read((char*)&I, sizeof(I));
            if(B.eof())
            {
                break;
            }
            if(I.GetLlave() == cod)
            {
                band=1;
                A.seekg(I.GetPosicion());
                A.read((char*)&H, sizeof(H));
                cout<<endl<<"Codigo: "<<H.codigo<<endl;
                cout<<"Nombre: "<<H.nombre<<endl;
                cout<<"Costo: "<<H.costo<<endl;
                cout<<"Categoria: "<<H.categoria<<endl;
                cout<<"Codigo de pais: "<<H.cod_pais<<endl<<endl;
            }
        }
        if(band == 0)
        {
            cout<<endl<<"Ese codigo no existe"<<endl;
        }
        A.close();
    }
    else
    {
        cout<<"Error al abrir el archivo"<<endl;
    }
    B.close();
}

void Hoteles::Like()
{
    char patron[15];
    char *like;
    int band = 0;
    ifstream A("Hoteles.txt");
    if(A.good())
    {
        cout<<"Ingrese el patron a buscar: ";
        cin.ignore();
        cin.getline(patron, 15, '\n');
        while(!A.eof())
        {
            A.read((char*)&H, sizeof(H));
            if(A.eof())
            {
                break;
            }
            like = strstr(H.nombre, patron);
            if(like != '\0')
            {
                band = 1;
                cout<<"Codigo: "<<H.codigo<<endl;
                cout<<"Nombre: "<<H.nombre<<endl;
                cout<<"Costo: "<<H.costo<<endl;
                cout<<"Categoria: "<<H.categoria<<endl;
                cout<<"Codigo de pais: "<<H.cod_pais<<endl<<endl;
            }
        }
        if(band == 0)
        {
            cout<<endl<<"No existen hoteles con ese patron de busqueda"<<endl;
        }
    }
    else
    {
        cout<<endl<<"Error al abrir el archivo"<<endl;
    }
    A.close();
}

void Hoteles::BuscarPais()
{
    Paises PaisAux;
    int pos, cod, band = 0;
    long int posicion;
    cout<<"Inserte el codigo del pais: ";
    cin>>cod;
    cout<<endl;
    ifstream Pa("Paises.txt");
    if(Pa.good())
    {
        while(!Pa.eof())
        {
            Pa.read((char*)&P, sizeof(P));
            if(Pa.eof())
            {
                break;
            }
            if(P.GetCodigo() == cod)
            {
                band = 1;
                pos = P.GetPosicion();
            }
        }
    }
    Pa.close();

    if(band == 0)
    {
        cout<<endl<<"Ese codigo no existe"<<endl;
    }
    else
    {
    PaisAux = TDAS.BuscarPos(pos);

    ifstream Hot("Hoteles.txt");
    if(Hot.good())
    {
        while(PaisAux.GetPosicion() != -1)
        {
        posicion = TDA.Buscar(PaisAux.GetCodigo());
        Hot.seekg(posicion);
        Hot.read((char*)&H, sizeof(H));
        cout<<"Codigo: "<<H.codigo<<endl;
        cout<<"Nombre: "<<H.nombre<<endl;
        cout<<"Costo: "<<H.costo<<endl;
        cout<<"Categoria: "<<H.categoria<<endl;
        cout<<"Codigo de pais: "<<H.cod_pais<<endl<<endl;
        PaisAux = TDAS.BuscarPos(PaisAux.GetPosicion());
        }
        if(PaisAux.GetPosicion() == -1)
        {
            posicion = TDA.Buscar(PaisAux.GetCodigo());
            Hot.seekg(posicion);
            Hot.read((char*)&H, sizeof(H));
            cout<<"Codigo: "<<H.codigo<<endl;
            cout<<"Nombre: "<<H.nombre<<endl;
            cout<<"Costo: "<<H.costo<<endl;
            cout<<"Categoria: "<<H.categoria<<endl;
            cout<<"Codigo de pais: "<<H.cod_pais<<endl<<endl;
        }
    }
    Hot.close();
    }
}

int Hoteles::codigo_del_pais(int cod)
{
        long int posicion;
        posicion = TDA.Buscar(cod);
        ifstream Hot("Hoteles.txt");
        Hot.seekg(posicion);
        Hot.read((char*)&H, sizeof(H));
        Hot.close();
        return H.GetCod_Pais();
}

void Hoteles::Menu()
{
    TDA.Inicializar();
    TDAS.Inicializa();
    TDAS.Anular();
    TDAS.Cargar();
    char opc;
    do
    {
        TDA.Anular();
        TDA.Cargar();
        system(CLEAR);
        cout<<"1. Capturar"<<endl;
        cout<<"2. Mostrar todos los hoteles"<<endl;
        cout<<"3. Modificar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Buscar"<<endl;
        cout<<"6. Like"<<endl;
        cout<<"7. Indices secundarios"<<endl;
        cout<<"8. Mostrar hoteles por pais"<<endl;
        cout<<"9. Ordenar"<<endl;
        cout<<"0. Regresar al menu principal"<<endl;
        cout<<endl<<"Elija una opcion: ";
        cin>>opc;
        switch(opc)
        {
        case '1':
        {
            system(CLEAR);
            H.Capturar();
            cin.get();
            cin.get();
            break;
        }
        case '2':
        {
            system(CLEAR);
            H.Mostrar();
            cin.get();
            cin.get();
            break;
        }
        case '3':
        {
            system(CLEAR);
            H.Modificar();
            cin.get();
            cin.get();
            break;
        }
        case '4':
        {
            system(CLEAR);
            H.Eliminar();
            cin.get();
            cin.get();
            break;
        }
        case '5':
        {
            system(CLEAR);
            H.Buscar();
            cin.get();
            cin.get();
            break;
        }
        case '6':
        {
            system(CLEAR);
            H.Like();
            cin.get();
            cin.get();
            break;
        }
        case '7':
        {
            system(CLEAR);
            TDAS.MostrarIndicesSecundarios();
            cin.get();
            cin.get();
            break;
        }
        case '8':
        {
            system(CLEAR);
            H.BuscarPais();
            cin.get();
            cin.get();
            break;
        }
        case '9':
        {
            char opc2;
            system(CLEAR);
            cout<<"1. Ordenar ascendentemente"<<endl;
            cout<<"2. Ordenar descendentemente"<<endl;
            cout<<endl<<"Elija una opcion: ";
            cin>>opc2;
            TDA.Ordenar(opc2);
            cout<<endl<<"Elementos ordenados"<<endl;
            cin.get();
            cin.get();
            break;
        }
        case '0':
        {
            TDAS.Guardar();
            break;
        }
        default:
        {
            cout<<"elija una opcion valida"<<endl;
        }
        }
    }
    while(opc!='0');
}
