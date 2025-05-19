//Karla Patricia Ruiz ordo�ez 9959-24-6859
#include "Cuentas.h"         // Incluye el encabezado de la clase Cuentas
#include <iostream>          // Incluye la biblioteca de entrada/salida est�ndar

// Inicializa la instancia est�tica de la bit�cora para la clase Cuentas
Bitacora Cuentas::bitacoraCuentas;

using namespace std;        // Usa el espacio de nombres est�ndar

// Constructor de la clase Cuentas
Cuentas::Cuentas() {
    tipoCuentaSeleccionada = "No configurada"; // Inicializa tipoCuentaSeleccionada con un valor por defecto
}

// Muestra el men� para seleccionar el tipo de cuenta
void Cuentas::menuTipoCuenta(const std::string& bancoNombre) {
    int opcion; // Variable para almacenar la opci�n seleccionada
    do {
        // Muestra el encabezado del men�
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n"; // Muestra el nombre del banco
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Corriente"; // Opci�n para seleccionar cuenta corriente
        cout << "\n2. Cuenta de Ahorro";  // Opci�n para seleccionar cuenta de ahorro
        cout << "\nSeleccione una opci�n: "; // Pide al usuario que seleccione una opci�n
        cin >> opcion; // Lee la opci�n seleccionada
        cin.ignore();  // Limpia el buffer de entrada

        // Controla el flujo seg�n la opci�n seleccionada
        switch (opcion) {
            case 1: // Si se selecciona cuenta corriente
                tipoCuentaSeleccionada = "Corriente"; // Actualiza el tipo de cuenta seleccionada
                // Registro en la bit�cora
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Cuenta Corriente seleccionada");
                return; // Sale del men�
            case 2: // Si se selecciona cuenta de ahorro
                tipoCuentaSeleccionada = "Ahorro"; // Actualiza el tipo de cuenta seleccionada
                // Registro en la bit�cora
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Cuenta de Ahorro seleccionada");
                return; // Sale del men�
            default: // Si la opci�n no es v�lida
                cout << "Opci�n inv�lida.\n"; // Muestra un mensaje de error
                break; // Contin�a el bucle
        }
    } while (true); // Repite indefinidamente hasta que se seleccione una opci�n v�lida
}

// Devuelve el tipo de cuenta seleccionada
std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada; // Devuelve el valor de tipoCuentaSeleccionada
}
