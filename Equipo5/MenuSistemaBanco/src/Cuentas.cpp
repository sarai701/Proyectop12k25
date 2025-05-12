#include "Cuentas.h"
#include <iostream>

#ifdef _WIN32
#include <cstdlib>
#endif

using namespace std;

Cuentas::Cuentas() : tipoCuentaSeleccionada(0) {}

void Cuentas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Cuentas::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void Cuentas::menuTipoCuenta() {
    limpiarPantalla();
    cout << "=======================================" << endl;
    cout << "   SELECCIONE EL TIPO DE CUENTA" << endl;
    cout << "=======================================" << endl;
    cout << "1. Cuenta monetaria" << endl;
    cout << "2. Cuenta de ahorro" << endl;
    cout << "Opción: ";
    cin >> tipoCuentaSeleccionada;
    cin.ignore(); // Para limpiar buffer

    if (tipoCuentaSeleccionada != 1 && tipoCuentaSeleccionada != 2) {
        cout << "Opción inválida. Se seleccionará cuenta monetaria por defecto." << endl;
        tipoCuentaSeleccionada = 1;
    }

    pausar();
}

int Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada;
}
