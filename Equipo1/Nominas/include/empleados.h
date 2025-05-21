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
//CODIGO REALIZADO POR-Isaias Cedillo (9959-24-1672) "IsaC8-bit"
using namespace std;

class Empleados
{

public:
     Empleados();
    // Métodos con parametros para el usuario
    void menuEmpleados(const string& usuarioRegistrante);
    void registroEmpleados(const string& usuarioRegistrante);
    void listaEmpleados(const string& usuarioRegistrante);
    void cambioEmpleados(const string& usuarioRegistrante);
    void borrarEmpleados(const string& usuarioRegistrante);
    void buscarEmpleado(const string& usuarioRegistrante);

    //Nominas XANDER REYES
    void mostrarMenuNomina(const string& usuarioRegistrante);
    void calcularNominaAnual();
    void calcularNominaMensual();

private:
    // Variables para cálculos de nómina XANDER REYES
    double salarioSinISR, salarioSinIGSS, salarioSinIRTRA, salarioConBI;
    double salarioNeto;
    double IGSS = 0.0483;
    double IRTRA = 0.01;
    double ISR = 0.05;
    double bono14;
    double aguinaldo;
    int bonoIncentivo = 250;
    int opcion;
    double salarioBruto;
    string tipoEmpleado, Nombre;
    float sueldo = 0.0;


};

#endif // EMPLEADOS_H
