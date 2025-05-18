//Karla Patricia Ruiz Ordoñez
#include "Cuentas.h"
#include <iostream>

using namespace std;

// Aquí se crea una instancia estática de la clase Bitacora, que va a servir para guardar los registros
Bitacora Cuentas::bitacoraCuentas;

// Constructor de la clase Cuentas
Cuentas::Cuentas() {
    // Cuando se crea un objeto de tipo Cuentas, este empieza sin ningún tipo de cuenta asignada
    tipoCuentaSeleccionada = "No configurada";
}

// Función que muestra el menú para seleccionar el tipo de cuenta
void Cuentas::menuTipoCuenta(const std::string& bancoNombre) {
    int opcion;
    do {
        system("cls"); // Limpia la pantalla (esto es más visual, no afecta la lógica)
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n";
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Monetaria";
        cout << "\n2. Cuenta de Ahorro";
        cout << "\n3. Volver al menú anterior";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Para evitar que se salte la siguiente entrada

        switch (opcion) {
            case 1:
                // Si elige 1, se guarda que la cuenta es Monetaria
                tipoCuentaSeleccionada = "Monetaria";
                // Se registra en la bitácora que se eligió cuenta corriente (otro nombre para monetaria)
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Tipo de cuenta: Corriente");
                return;
            case 2:
                // Si elige 2, se guarda que la cuenta es de Ahorro
                tipoCuentaSeleccionada = "Ahorro";
                // También se guarda en la bitácora
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Tipo de cuenta: Ahorro");
                return;
            case 3:
                // Si elige salir, simplemente se regresa sin hacer cambios
                return;
            default:
                // Por si el usuario se equivoca y pone algo que no está en el menú
                cout << "Opción inválida. Intente de nuevo.\n";
                system("pause"); // Espera que el usuario presione una tecla
        }
    } while (true); // Repite hasta que elija una opción válida
}

// Esta función solo devuelve el tipo de cuenta que fue seleccionado antes
std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada;
}

