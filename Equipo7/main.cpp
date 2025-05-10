#include <iostream>
#include "SistemaVentas.h"
#include "Login.h"
#include "bitacora.h"

using namespace std;


string usuarioActual; // Para guardar el nombre del usuario bitacora

void mostrarMenuPrincipal();

int main() {
    int opcion;
    bool accesoPermitido = false;

    do {

        system ("cls");
        cout << "\n--- Bienvenido al Sistema ---\n";
        cout << "1. Iniciar Sesion\n";
        cout << "2. Registrarse\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Para evitar errores con getline

        switch (opcion) {
            case 1:
                accesoPermitido = iniciarSesion(usuarioActual);
                break;
            case 2:
                registrarUsuario();
                break;
            case 3:
                cout << "\n\nSaliendo del sistema...\n";
                return 0;
            default:
                cout << "Opción invalida.\n";
        }
    } while (!accesoPermitido);

    mostrarMenuPrincipal();
     registrarEvento(usuarioActual, "Cerró sesión desde menú principal");
    return 0;
}




void mostrarMenuPrincipal() {
    SistemaVentas sistema;
    int opcion;
    do {
        system ("cls");
        cout << "\n--- Menu General ---\n";
        cout << "1. Archivo\n";
        cout << "2. Catalogos\n";
        cout << "3. Procesos\n";
        cout << "4. Informes\n";
        cout << "5. Salir del sistema\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarEvento(usuarioActual, "Entró a la opción Archivo");
                cout << "Archivo (sin funciones aun).\n";
                break;
            case 2:
                registrarEvento(usuarioActual, "Entró a la opción Catálogos");
                sistema.mostrarMenu();
                break;
            case 3:
                registrarEvento(usuarioActual, "Entró a la opción Procesos");
                sistema.realizarVenta();
                break;
            case 4:
                registrarEvento(usuarioActual, "Entró a la opción Informes");
                sistema.mostrarVentas();
                break;
            case 5:
                registrarEvento(usuarioActual, "Salió del menú general");
                cout << "Cerrando sesion...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}
