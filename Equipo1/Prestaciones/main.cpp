// Se incluye el archivo "Prestaciones.h"
#include <iostream>
#include "Prestaciones.h"
using namespace std;

//Aqui encontramos una funcion que muestra el menu de calculos de prestaciones de nuestro sistema NomiReg
void mostrarMenu() {
    cout << "\n -----MENU DE PRESTACIONES LABORALES -----\n";
    cout << "\n -----------------------------------------\n";
    cout << "1. Mostrar tu salario base\n";
    cout << "2. Mostrar salario bruto\n";
    cout << "3. Calcular salario neto\n";
    cout << "4. Calcular bonificación incentivo\n";
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
}

int main() {
    //Aqui se colocaron variables para el nombre del empleado, salario y opciónes del menú
    string nombre;
    double salarioBase;
    int opcion;

    //Aqui nos pide que ingresemos el nombre del empleado
    cout << "Ingrese el nombre del empleado: ";
    //aqui le coloque getline para que lea la linea completa y lo coloque en nombre
    getline(cin, nombre);
    //Aqui nos pide que ingresemos el salariio del empleado
    cout << "Ingrese el salario que recibe mensualmente Q: ";
    cin >> salarioBase;

    //Creamos un objeto de la clase prestaciones y usamos el nombre y el salario del empleado
    Prestaciones prestaciones(nombre, salarioBase);

    //aqui iniciamos un bucle para que muestre el menú hasta que el usuario elija salir
    do {
        //nos muestra el menu de opciones de arriba
        mostrarMenu();
        //lee la opcion que se selecciono del menu
        cin >> opcion;

        //se creo un switch para que ejecute las opciones seleccionadas del menu
        switch (opcion) {
            case 1:
                cout << "Salario Base de " << prestaciones.getNombre() << ": Q"
                     << prestaciones.getSalarioBase() << endl;
                break;
            case 2:
                cout << "Salario Bruto: Q" << prestaciones.calcularSalarioBruto() << endl;
                break;
            case 3:
                cout << "Salario Neto: Q" << prestaciones.calcularSalarioNeto() << endl;
                break;
            case 4:
                cout << "Bonificacion Incentiva: Q" << prestaciones.calcularBonificacionIncentivo() << endl;
                break;
            case 5:
                cout << "Vacaciones(15 dias): Q" << prestaciones.calcularVacaciones() << endl;
                break;
            case 6:
                cout << "Aguinaldo: Q" << prestaciones.calcularAguinaldo() << endl;
                break;
            case 7:
                cout << "Bono 14: Q" << prestaciones.calcularBonoCatorce() << endl;
                break;
            case 8:
                cout << "IGSS: Q" << prestaciones.calcularIgss() <<endl;
                break;
            case 9:
                cout << "IRTRA: Q" << prestaciones.calcularIrtra() <<endl;
                break;
            case 10:
                cout << "Indemnizacion: Q" << prestaciones.calcularIndemnizacion() <<endl;
                break;
            case 11:
                cout << "Saliendo del programa. ¡Gracias por visitar NomiReg!\n";
                break;
            default:
                cout << "Error, opcion incorrecta.\n";
        }
    //aqui se repite hasta que el usuario seleccione la opcion salir
    } while (opcion != 11);

    return 0;
}
