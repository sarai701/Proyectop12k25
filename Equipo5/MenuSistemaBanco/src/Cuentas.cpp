//Karla Patricia Ruiz ordoñez 9959-24-6859
#include "Cuentas.h"         // Incluye el encabezado de la clase Cuentas
#include <iostream>          // Incluye la biblioteca de entrada/salida estándar

// Inicializa la instancia estática de la bitácora para la clase Cuentas
Bitacora Cuentas::bitacoraCuentas;

using namespace std;        // Usa el espacio de nombres estándar

// Constructor de la clase Cuentas
Cuentas::Cuentas() {
    tipoCuentaSeleccionada = "No configurada"; // Inicializa tipoCuentaSeleccionada con un valor por defecto
}

// Muestra el menú para seleccionar el tipo de cuenta
void Cuentas::menuTipoCuenta(const std::string& bancoNombre) {
    int opcion; // Variable para almacenar la opción seleccionada
    do {
        // Muestra el encabezado del menú
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n"; // Muestra el nombre del banco
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Corriente"; // Opción para seleccionar cuenta corriente
        cout << "\n2. Cuenta de Ahorro";  // Opción para seleccionar cuenta de ahorro
        cout << "\nSeleccione una opción: "; // Pide al usuario que seleccione una opción
        cin >> opcion; // Lee la opción seleccionada
        cin.ignore();  // Limpia el buffer de entrada

        // Controla el flujo según la opción seleccionada
        switch (opcion) {
            case 1: // Si se selecciona cuenta corriente
                tipoCuentaSeleccionada = "Corriente"; // Actualiza el tipo de cuenta seleccionada
                // Registro en la bitácora
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Cuenta Corriente seleccionada");
                return; // Sale del menú
            case 2: // Si se selecciona cuenta de ahorro
                tipoCuentaSeleccionada = "Ahorro"; // Actualiza el tipo de cuenta seleccionada
                // Registro en la bitácora
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Cuenta de Ahorro seleccionada");
                return; // Sale del menú
            default: // Si la opción no es válida
                cout << "Opción inválida.\n"; // Muestra un mensaje de error
                break; // Continúa el bucle
        }
    } while (true); // Repite indefinidamente hasta que se seleccione una opción válida
}

// Devuelve el tipo de cuenta seleccionada
std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada; // Devuelve el valor de tipoCuentaSeleccionada
}
