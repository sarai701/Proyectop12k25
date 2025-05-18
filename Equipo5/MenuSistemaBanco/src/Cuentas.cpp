#include "Cuentas.h"
#include <iostream>

using namespace std;

Bitacora Cuentas::bitacoraCuentas;

Cuentas::Cuentas() {
    tipoCuentaSeleccionada = "No configurada";
}

void Cuentas::menuTipoCuenta(const std::string& bancoNombre) {
    int opcion;
    do {
        system("cls"); // o "clear" si estás en Linux/Mac
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n";
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Monetaria";
        cout << "\n2. Cuenta de Ahorro";
        cout << "\n3. Volver al menú anterior";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                tipoCuentaSeleccionada = "Monetaria";
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Tipo de cuenta: Corriente");
                return;
            case 2:
                tipoCuentaSeleccionada = "Ahorro";
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Tipo de cuenta: Ahorro");
                return;
            case 3:
                return;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
                system("pause");
        }
    } while (true);
}

std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada;
}
