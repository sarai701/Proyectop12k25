//incluimos biblioteca y el archivo .h
#include <iostream>
#include "Prestaciones.h"
using namespace std;

//Aqui encontramos el constructor de la clase y lo inicializamos con el nombre y salario del empleado
Prestaciones::Prestaciones()
{

}
Prestaciones::~Prestaciones()
{

}
void Prestaciones::MostrarMenu(){
    do{
    system ("cls");
    cout << "\n -----MENU DE PRESTACIONES LABORALES -----\n";
    cout << "\n -----------------------------------------\n";
    cout << "1. Mostrar tu salario base\n";
    cout << "2. Mostrar salario bruto\n";
    cout << "3. Calcular salario neto\n";
    cout << "4. Calcular bonificacion incentivo\n";
    cout << "5. Calcular vacaciones\n";
    cout << "6. Calcular aguinaldo\n";
    cout << "7. Calcular bono 14\n";
    cout << "8. Calcular iGSS\n";
    cout << "9. Calcular irtra\n";
    cout << "10. Calcular Indemnizacion\n";
    cout << "11. Salir del sistema\n";
    cout << "Seleccione una opcion: ";
    cout << "\n -----------------------------------------\n";
    cout << "\n -----------------NOMIREG-----------------\n";
    cin >> opcion;
    }while (opcion!=11);
}
//este es un metodo para obtener el nombre del empleado
//metodo para obtener el calculo del salario bruto
double Prestaciones::calcularSalarioBruto(){
    return salarioBruto;
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
