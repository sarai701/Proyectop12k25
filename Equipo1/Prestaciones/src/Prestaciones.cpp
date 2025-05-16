//incluimos biblioteca y el archivo .h
#include <iostream>
#include "Prestaciones.h"
using namespace std;

//Aqui encontramos el constructor de la clase y lo inicializamos con el nombre y salario del empleado
Prestaciones::Prestaciones(string nombreEmpleado, double salarioBaseEmpleado) {
    nombre = nombreEmpleado;
    salarioBase = salarioBaseEmpleado;
}
//este es un metodo para obtener el nombre del empleado
string Prestaciones::getNombre(){
    //pendiente el calculo
}
//aqui tenemos otro metodo para obtener el calculo del salario base
double Prestaciones::getSalarioBase(){
    //pendiente el calculo
}
//metodo para obtener el calculo del salario bruto
double Prestaciones::calcularSalarioBruto(){
    //pendiente el calculo
}
//metodo para obtener el calculo del salario neto
double Prestaciones::calcularSalarioNeto(){
   //pendiente el calculo
}
//metodo para calculo de bonificacion incentiva
double Prestaciones::calcularBonificacionIncentivo(){
    //pendiente el calculo
}
//aqui el metodo para obtener el calculo de vacaciones
double Prestaciones::calcularVacaciones(){
    //pendiente el calculo
}
//metodo para calculo de aguinaldo
double Prestaciones::calcularAguinaldo(){
    //pendiente el calculo
}
//metodo para calculo de bono 14
double Prestaciones::calcularBonoCatorce(){
    //pendiente el calculo
}
//metodo del calculo de igss
double Prestaciones::calcularIgss(){
   //pendiente el calculo
}
//este ultimo metodo es para calcular el irtra
double Prestaciones::calcularIrtra(){
    //pendiente el calculo
}
//Aqui el metodo para calculo de la indemnizacion del empleado
double Prestaciones::calcularIndemnizacion(){
    //pendiente el calculo
}
