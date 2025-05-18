//Karla Patricia Ruiz Ordo�ez
#include "Cuentas.h"
#include <iostream>

using namespace std;

// Aqu� se crea una instancia est�tica de la clase Bitacora, que va a servir para guardar los registros
Bitacora Cuentas::bitacoraCuentas;

// Constructor de la clase Cuentas
Cuentas::Cuentas() {
    // Cuando se crea un objeto de tipo Cuentas, este empieza sin ning�n tipo de cuenta asignada
    tipoCuentaSeleccionada = "No configurada";
}

// Funci�n que muestra el men� para seleccionar el tipo de cuenta
void Cuentas::menuTipoCuenta(const std::string& bancoNombre) {
    int opcion;
    do {
        system("cls"); // Limpia la pantalla (esto es m�s visual, no afecta la l�gica)
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n";
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Monetaria";
        cout << "\n2. Cuenta de Ahorro";
        cout << "\n3. Volver al men� anterior";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore(); // Para evitar que se salte la siguiente entrada

        switch (opcion) {
            case 1:
                // Si elige 1, se guarda que la cuenta es Monetaria
                tipoCuentaSeleccionada = "Monetaria";
                // Se registra en la bit�cora que se eligi� cuenta corriente (otro nombre para monetaria)
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Tipo de cuenta: Corriente");
                return;
            case 2:
                // Si elige 2, se guarda que la cuenta es de Ahorro
                tipoCuentaSeleccionada = "Ahorro";
                // Tambi�n se guarda en la bit�cora
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Tipo de cuenta: Ahorro");
                return;
            case 3:
                // Si elige salir, simplemente se regresa sin hacer cambios
                return;
            default:
                // Por si el usuario se equivoca y pone algo que no est� en el men�
                cout << "Opci�n inv�lida. Intente de nuevo.\n";
                system("pause"); // Espera que el usuario presione una tecla
        }
    } while (true); // Repite hasta que elija una opci�n v�lida
}

// Esta funci�n solo devuelve el tipo de cuenta que fue seleccionado antes
std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada;
}

