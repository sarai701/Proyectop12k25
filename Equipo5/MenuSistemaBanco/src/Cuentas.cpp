#include "Cuentas.h"
#include <iostream>

Bitacora Cuentas::bitacoraCuentas;

using namespace std;

Cuentas::Cuentas() {
    tipoCuentaSeleccionada = "No configurada";
}

void Cuentas::menuTipoCuenta(const std::string& bancoNombre) {
    int opcion;
    do {
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n";
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Corriente";
        cout << "\n2. Cuenta de Ahorro";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                tipoCuentaSeleccionada = "Corriente";
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Cuenta Corriente seleccionada");
                return;
            case 2:
                tipoCuentaSeleccionada = "Ahorro";
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Cuenta de Ahorro seleccionada");
                return;
            default:
                cout << "Opción inválida.\n";
                break;
        }
    } while (true);
}

std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada;
}
