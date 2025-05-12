//Jonathan Samuel Gonzalez
#include "Bancos.h"
#include "Moneda.h"
#include <iostream>
#include "Bitacora.h"

using namespace std;

Bancos::Bancos() {
    bancoSeleccionado = "No configurado";
    tipoCuentaSeleccionada = "No configurada";
    monedaSeleccionada = "GTQ";
}

// Men� principal de configuraci�n bancaria
void Bancos::menuConfiguracion() {
    menuSeleccionBanco();
    menuTipoMoneda();
}

// Muestra la configuraci�n actual
void Bancos::mostrarConfiguracion() {
    limpiarPantalla();
    cout << "\n===== CONFIGURACI�N ACTUAL =====";
    cout << "\nBanco: " << bancoSeleccionado;
    cout << "\nTipo de cuenta: " << tipoCuentaSeleccionada;
    cout << "\nMoneda: " << monedaSeleccionada << " (" << Moneda::getSimbolo() << ")";
    pausar();
}

// --- Men�s internos ---
void Bancos::menuSeleccionBanco() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== SELECCIONE SU BANCO =====";
        cout << "\n1. Banco Industrial";
        cout << "\n2. Banco GyT Continental";
        cout << "\n3. Banco Banrural";
        cout << "\n4. Bac Credomatic";
        cout << "\n5. Bantrab";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: bancoSeleccionado = "Banco Industrial"; break;
            case 2: bancoSeleccionado = "Banco GyT Continental"; break;
            case 3: bancoSeleccionado = "Banco Banrural"; break;
            case 4: bancoSeleccionado = "Bac Credomatic"; break;
            case 5: bancoSeleccionado = "Bantrab"; break;
            default: cout << "Opci�n inv�lida."; pausar();
        }

        if (opcion >= 1 && opcion <= 5) return;
    } while (true);
}


void Bancos::menuTipoMoneda() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== TIPO DE MONEDA =====";
        cout << "\nBanco: " << bancoSeleccionado;
        cout << "\nCuenta: " << tipoCuentaSeleccionada;
        cout << "\n1. Quetzales (GTQ)";
        cout << "\n2. D�lares (USD)";
        cout << "\n3. Euros (EUR)";
        cout << "\n4. Volver al men� anterior";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                monedaSeleccionada = "GTQ";
                Moneda::moneda = "GTQ";
                limpiarPantalla(); // Limpia pantalla antes de salir
                return;
            case 2:
                monedaSeleccionada = "USD";
                Moneda::moneda = "USD";
                limpiarPantalla(); // Limpia pantalla antes de salir
                return;
            case 3:
                monedaSeleccionada = "EUR";
                Moneda::moneda = "EUR";
                limpiarPantalla(); // Limpia pantalla antes de salir
                return;
            case 4: menuSeleccionBanco(); break;
            default: cout << "Opci�n inv�lida."; pausar();
        }
    } while (true);
}
// --- Funciones auxiliares ---
void Bancos::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Bancos::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// --- Getters ---
std::string Bancos::getBanco() const { return bancoSeleccionado; }
std::string Bancos::getCuenta() const { return tipoCuentaSeleccionada; }
std::string Bancos::getMoneda() const { return monedaSeleccionada; }
