#include <iostream>
#include "SistemaVentas.h"
#include "Login.h"

using namespace std;

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

        switch (opcion) {
            case 1:
                accesoPermitido = iniciarSesion();
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
                cout << "Archivo (sin funciones aun).\n";
                break;
            case 2:
                sistema.mostrarMenu(); // reutilizamos temporalmente
                break;
            case 3:
                sistema.realizarVenta();
                break;
            case 4:
                sistema.mostrarVentas();
                break;
            case 5:
                cout << "Cerrando sesion...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}
