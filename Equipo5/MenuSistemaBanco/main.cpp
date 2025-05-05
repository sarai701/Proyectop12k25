#include <iostream>
#include <fstream>
#include <string>
#include "Empleados.h"
#include "Cliente.h"
#include "Proveedores.h"
#include "Contabilidad.h"
#include "Auditoria.h"
#include "Usuario.h"
#include <conio.h> //para la funci�n getch() que permite capturar teclas sin mostrarlas
#include "Nominas.h"

using namespace std;



// Pausar el programa esperando ENTER
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Mostrar el men� principal
void mostrarMenu() {
    //se crean objetos de cada clase para poder usar sus funciones
    Empleado empleado;
    Cliente cliente;
    Proveedor proveedor;
    Contabilidad contabilidad;
    Auditoria auditoria;
    Nominas nominas;

    int opcion;
    do {
        cout << "\n------------------------------------";
        cout << "\n        SISTEMA BANCARIO";
        cout << "\n------------------------------------";
        cout << "\n 1. Nominas";
        cout << "\n 2. Cliente";
        cout << "\n 3. Empleados";
        cout << "\n 4. Contabilidad";
        cout << "\n 5. Auditoria";
        cout << "\n 6. Proveedores";
        cout << "\n 7. Salir";
        cout << "\n------------------------------------";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        // Validar entrada incorrecta
        if (cin.fail()) {
            cin.clear(); // limpiar error
            cin.ignore(10000, '\n'); // descartar entrada
            opcion = 0;
        }

        switch (opcion) {
            case 1: nominas.menuNominas(); break;
            case 2: cliente.menuCliente(); break;
            case 3: empleado.gestionarEmpleados(); break;
            case 4: contabilidad.menuContabilidad(); break;
            case 5: auditoria.menuAuditoria(); break;
            case 6: proveedor.menuProveedor(); break; // Llamada a men� de proveedor
            case 7: cout << "\nSaliendo del sistema... Gracias!\n"; break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n";
                pausar();
        }

    } while (opcion != 7);
}

// Funci�n principal
int main() {
    while (true) {
        // Mostrar el men� de autenticaci�n
        if (Usuario::menuAutenticacion()) {
            // Si inicia sesi�n con �xito, mostrar men� bancario
            mostrarMenu();

            // Despu�s de salir del men� bancario:
            pausar();
            Usuario::limpiarPantalla();  // si la hiciste p�blica o moviste la funci�n
        } else {
            cout << "\nAutenticaci�n fallida o el usuario decidi� salir.\n";
            break; // salir completamente del programa
        }
    }

    return 0;
}



