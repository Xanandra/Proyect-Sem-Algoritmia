#ifndef EMPLEADOS_H
#define EMPLEADOS_H

class Empleados
{
    int codigo, tipo;
    char nombre[30], password[30], usuario[30], RFC[12];
    public:
        void Capturar();
        void Mostrar();
        void Modificar();
        void Eliminar();
        void Buscar();
        void Menu();
        int CodigoE();
};

#endif // EMPLEADOS_H
