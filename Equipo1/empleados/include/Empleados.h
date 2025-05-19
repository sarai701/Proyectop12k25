#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>

using namespace std;

class Empleados
{
    public:
        Empleados();
        void menu();
        void registro();
        void lista();
        void cambio();
        void borrar();

    private:
        string tipoEmpleado,Nombre;
        float sueldo = 0.0;
};

#endif // EMPLEADOS_H
