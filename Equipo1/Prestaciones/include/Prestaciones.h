#ifndef PRESTACIONES_H
#define PRESTACIONES_H
#include <string>
using namespace std;

//declaracion de la clase
class Prestaciones {
private:
    //aqui encontramos los atributos de la clase de prestaciones
    string nombre;
    double salarioBase;
    double salarioBruto;

public:
    //aqui el constructor que inicializamos con el nombre y salario del empleado
    Prestaciones(string nombreEmpleado, double salarioBaseEmpleado);

    //aqui obtenemos el nombre del empleado
    string getNombre();
    //aqui obtenemos el salario del empleado
    double getSalarioBase();
    //metodos para calculo de las prestaciones
    double calcularSalarioBruto();
    double calcularSalarioNeto();
    double calcularVacaciones();
    double calcularAguinaldo();
    double calcularBonificacionIncentivo();
    double calcularBonoCatorce();
    double calcularIndemnizacion();
    double calcularIgss();
    double calcularIrtra();
};

#endif // PRESTACIONES_H
