#include "MenuArchivo.h"
#include "usuarios.h"
#include <iostream>
#include "globals.h"

using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

void MenuArchivo::mostrar() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================\n"
             << "\t\t|          MENU ARCHIVO                |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << "\n"
             << "\t\t========================================\n"
             << "\t\t 1. Cerrar sesion\n"
             << "\t\t 2. Backup\n"
             << "\t\t 3. Volver al menu principal\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cerrarSesion();
                return;
            case 2: /* ... */ break;
            case 3:
                return;
            default:
                cout << "\n\t\tOpcion invalida...";
                system("pause");
        }
    } while(true);
}

void MenuArchivo::cerrarSesion() {
    char confirmacion;
    cout << "\n\t\t¿Esta seguro que desea cerrar sesion y salir del programa? (S/N): ";
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S') {
        // Registrar en bitácora
        auditoria.insertar(usuarioRegistrado.getNombre(), "000", "LOGOUT");

        cout << "\n\t\tSesion cerrada correctamente. Saliendo del programa...\n";
        system("pause");

        // Terminar el programa completamente
        exit(0);
    } else {
        cout << "\n\t\tOperacion cancelada.\n";
        system("pause");
    }
}
