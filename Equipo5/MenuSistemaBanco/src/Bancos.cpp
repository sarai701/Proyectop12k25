//Jonathan Samuel Gonzalez
//Modificaciones 11/05/25
#include "Bancos.h"             // Incluye la definición de la clase Bancos
#include "Moneda.h"
#include "Cuentas.h"
#include <iostream>             // Librería para entrada y salida estándar

// Inicializa el objeto bitácora para registrar acciones

using namespace std;            // Permite usar std:: sin anteponer el prefijo
Bitacora bitacoralogBancos;
// Constructor de la clase Bancos
Bancos::Bancos() {
    bancoSeleccionado = "No configurado";             // Valor por defecto para el banco
    tipoCuentaSeleccionada = "No configurada";         // Valor por defecto para el tipo de cuenta
    monedaSeleccionada = "GTQ";                        // Valor por defecto para la moneda
}

// Muestra el menú completo de configuración
void Bancos::menuConfiguracion() {
    menuSeleccionBanco();       // Primero selecciona el banco
    menuTipoCuenta();           // Luego el tipo de cuenta
    menuTipoMoneda();           // Finalmente la moneda
}

// Muestra la configuración actual seleccionada
void Bancos::mostrarConfiguracion() {
    limpiarPantalla();          // Limpia la pantalla
    cout << "\n===== CONFIGURACIÓN ACTUAL =====";
    cout << "\nBanco: " << bancoSeleccionado;             // Muestra el banco actual
    cout << "\nTipo de cuenta: " << tipoCuentaSeleccionada; // Muestra el tipo de cuenta actual
    cout << "\nMoneda: " << monedaSeleccionada << " (" << Moneda::getSimbolo() << ")"; // Muestra moneda y su símbolo
    pausar();                   // Pausa para que el usuario vea la información
}

void Bancos::setUsuario(const string& u) {
    usuario = u;
}

// Menú para seleccionar el banco
void Bancos::menuSeleccionBanco() {
    int opcion;
    do {
        limpiarPantalla();      // Limpia pantalla antes de mostrar opciones
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== SELECCIONE SU BANCO =====";
        cout << "\n1. Banco Industrial";
        cout << "\n2. Banco GyT Continental";
        cout << "\n3. Banco Banrural";
        cout << "\n4. Bac Credomatic";
        cout << "\n5. Bantrab";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();           // Limpia buffer de entrada

        switch (opcion) {
            case 1:
                bancoSeleccionado = "Banco Industrial"; // Asigna banco
                bitacoralogBancos.insertar(usuario, 4604, "Bancos", "Banco seleccionado: Industrial"); // Registra en bitácora
                break;
            case 2:
                bancoSeleccionado = "Banco GyT Continental";
                bitacoralogBancos.insertar(usuario, 4605, "Bancos", "Banco seleccionado: GyT");
                break;
            case 3:
                bancoSeleccionado = "Banco Banrural";
                bitacoralogBancos.insertar(usuario, 4606, "Bancos", "Banco seleccionado: Banrural");
                break;
            case 4:
                bancoSeleccionado = "Bac Credomatic";
                bitacoralogBancos.insertar(usuario, 4607, "Bancos", "Banco seleccionado: Bac Credomatic");
                break;
            case 5:
                bancoSeleccionado = "Bantrab";
                bitacoralogBancos.insertar(usuario, 4608, "Bancos", "Banco seleccionado: Bantrab");
                break;
            default:
                cout << "Opción inválida."; // Manejo de opción inválida
                pausar();
                continue;
        }
        break; // Sale del bucle después de una opción válida
    } while (true);
}

// Menú para seleccionar el tipo de cuenta
void Bancos::menuTipoCuenta() {
    limpiarPantalla();
    Cuentas cuentas;                      // Crea instancia de Cuentas
    cuentas.setUsuario(usuario);         // Asigna el usuario para la bitácora
    cuentas.menuTipoCuenta(bancoSeleccionado); // Muestra el menú, pasando el banco seleccionado
    tipoCuentaSeleccionada = cuentas.getTipoCuenta(); // Guarda la cuenta seleccionada en Bancos
}


// Menú para seleccionar el tipo de moneda
void Bancos::menuTipoMoneda() {
    int opcion;
    do {
        limpiarPantalla(); // Limpia pantalla
        cout << "\nUsuario: " << usuario << endl;
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
                monedaSeleccionada = "GTQ";            // Asigna GTQ como moneda
                Moneda::moneda = "GTQ";                // Asigna en clase Moneda también
                bitacoralogBancos.insertar(usuario, 4601, "Bancos", "Moneda cambiada a GTQ");
                limpiarPantalla();
                return;
            case 2:
                monedaSeleccionada = "USD";
                Moneda::moneda = "USD";
                bitacoralogBancos.insertar(usuario, 4602, "Bancos", "Moneda cambiada a USD");
                limpiarPantalla();
                return;
            case 3:
                monedaSeleccionada = "EUR";
                Moneda::moneda = "EUR";
                bitacoralogBancos.insertar(usuario, 4603, "Bancos", "Moneda cambiada a EUR");
                limpiarPantalla();
                return;
            case 4:
                menuTipoCuenta(); // Regresa al menú anterior
                continue;
            default:
                cout << "Opción inválida.";
                pausar();
                continue;
        }
    } while (true);
}

// Limpia la pantalla según el sistema operativo
void Bancos::limpiarPantalla() {
#ifdef _WIN32
    system("cls"); // Comando para Windows
#else
    system("clear"); // Comando para Linux/Mac
#endif
}

// Pausa el programa hasta que el usuario presione ENTER
void Bancos::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(); // Limpia buffer
    cin.get();    // Espera ENTER
}

// Devuelve el banco seleccionado
std::string Bancos::getBanco() const { return bancoSeleccionado; }

// Devuelve el tipo de cuenta seleccionado
std::string Bancos::getCuenta() const { return tipoCuentaSeleccionada; }

// Devuelve la moneda seleccionada
std::string Bancos::getMoneda() const { return monedaSeleccionada; }
