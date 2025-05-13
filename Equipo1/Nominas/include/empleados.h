#ifndef EMPLEADOS_H
#define EMPLEADOS_H
//Bibliotecas
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include<limits> // Añadido para usar numeric_limits

using namespace std;

class Empleados
{
    public:
        //Metosoa
        Empleados();
        void menuEmpleados();
        void registroEmpleados ();
        void listaEmpleados();
        void cambioEmpleados();
        void borrarEmpleados();

    private:
        string tipoEmpleado, Nombre;
        float sueldo = 0.0;
};

#endif // EMPLEADOS_H
