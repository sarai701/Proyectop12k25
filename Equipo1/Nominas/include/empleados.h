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
#include "bitacora.h"

using namespace std;

class Empleados
{
  public:
        //Metosoa
        Empleados();
        void menuEmpleados();
        void registroEmpleados();
        void listaEmpleados();
        void cambioEmpleados();
        void borrarEmpleados();
        void buscarEmpleado();
        //metodos para el proceso de nomina
        void mostrarMenuNomina();
        void calcularNominaAnual();
        void calcularNominaMensual();
    private:
        double salarioSinISR, salarioSinIGSS, salarioConBI;
        double salarioNeto;
        double IGSS=0.0483;
        double ISR=0.05;
        int bonoIncentivo=250;
        int opcion;
        double salarioBruto;
        string tipoEmpleado, Nombre;
        float sueldo = 0.0;

};

#endif // EMPLEADOS_H
