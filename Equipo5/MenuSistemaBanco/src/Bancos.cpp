//Jonathan Samuel Gonzalez
//Modificaciones 11/05/25
#include "Bancos.h"
#include "Moneda.h"
#include <iostream>
#include "Bitacora.h"

Bitacora bitacoralog6;
Bitacora Bancos::bitacoraBancos;

using namespace std;

Bancos::Bancos() {
    bancoSeleccionado = "No configurado";
    tipoCuentaSeleccionada = "No configurada";
    monedaSeleccionada = "GTQ";
}

// Menú principal de configuración bancaria
void Bancos::menuConfiguracion() {
    menuSeleccionBanco();
    menuTipoCuenta();
    menuTipoMoneda();
}

// Muestra la configuración actual
void Bancos::mostrarConfiguracion() {
    limpiarPantalla();
    cout << "\n===== CONFIGURACIÓN ACTUAL =====";
    cout << "\nBanco: " << bancoSeleccionado;
    cout << "\nTipo de cuenta: " << tipoCuentaSeleccionada;
    cout << "\nMoneda: " << monedaSeleccionada << " (" << Moneda::getSimbolo() << ")";
    pausar();
}

// --- Menús internos ---
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
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: bancoSeleccionado = "Banco Industrial";
            bitacoraBancos.insertar("Admin", 4604, "Bancos", "Banco seleccionado: Industrial");
            break;
            case 2: bancoSeleccionado = "Banco GyT Continental";
            bitacoraBancos.insertar("Admin", 4605, "Bancos", "Banco seleccionado: GyT");
            break;
            case 3: bancoSeleccionado = "Banco Banrural";
            bitacoraBancos.insertar("Admin", 4606, "Bancos", "Banco seleccionado: Banrural");
            break;
            case 4: bancoSeleccionado = "Bac Credomatic";
            bitacoraBancos.insertar("Admin", 4607, "Bancos", "Banco seleccionado: Bac Credomatic");
            break;
            case 5: bancoSeleccionado = "Bantrab";
            bitacoraBancos.insertar("Admin", 4608, "Bancos", "Banco seleccionado: Bantrab");
            break;
            default: cout << "Opción inválida."; pausar();
        }

        if (opcion >= 1 && opcion <= 5) return;
    } while (true);
}


void Bancos::menuTipoCuenta() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoSeleccionado << "\n";
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Corriente";
        cout << "\n2. Cuenta de Ahorro";
        cout << "\n3. Volver al menú anterior";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: tipoCuentaSeleccionada = "Corriente";
            bitacoraBancos.insertar("Admin", 4610, "Bancos", "Tipo de cuenta seleccionado: Cuenta Corriente");
            break;
            case 2: tipoCuentaSeleccionada = "Ahorro";
            bitacoraBancos.insertar("Admin", 4611, "Bancos", "Tipo de cuenta seleccionado: Cuenta de Ahorro");
            break;
            case 3: menuSeleccionBanco(); // Vuelve al menú de bancos
            default: cout << "Opción inválida."; pausar();
        }

        if (opcion >= 1 && opcion <= 3) return;
    } while (true);
}

void Bancos::menuTipoMoneda() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== TIPO DE MONEDA =====\n";
        cout << "-------------------------------------------\n";
        cout << " Banco:    " << bancoSeleccionado << "\n";
        cout << " Cuenta:   " << tipoCuentaSeleccionada << "\n";
        cout << "-------------------------------------------\n";
        cout << "\n1. Quetzales (GTQ)";
        cout << "\n2. Dólares (USD)";
        cout << "\n3. Euros (EUR)";
        cout << "\n4. Volver al menú anterior";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                monedaSeleccionada = "GTQ";
                Moneda::moneda = "GTQ";
                bitacoraBancos.insertar("Admin", 4601, "Bancos", "Moneda cambiada a GTQ");
                limpiarPantalla(); // Limpia pantalla antes de salir
                return;
            case 2:
                monedaSeleccionada = "USD";
                Moneda::moneda = "USD";
                bitacoraBancos.insertar("Admin", 4602, "Bancos", "Moneda cambiada a USD");
                limpiarPantalla(); // Limpia pantalla antes de salir
                return;
            case 3:
                monedaSeleccionada = "EUR";
                Moneda::moneda = "EUR";
                bitacoraBancos.insertar("Admin", 4603, "Bancos", "Moneda cambiada a EUR");
                limpiarPantalla(); // Limpia pantalla antes de salir
                return;
            case 4: menuTipoCuenta(); break;
            default: cout << "Opción inválida."; pausar();
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
