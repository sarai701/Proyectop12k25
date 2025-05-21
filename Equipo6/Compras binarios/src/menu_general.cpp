#include "menu_general.h"
#include "usuario.h"
#include "menu_producto.h"
#include <iostream>
#include <string>

using namespace std;

void MenuGeneral::mostrar() {
    string usuario, contrasena;
    int opcion;

    cout << "=== SISTEMA DE GESTIÓN ===\n";

    // Login o registro simple
    do {
        cout << "1. Iniciar sesión\n2. Registrar usuario\nSeleccione opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            cout << "Usuario: ";
            getline(cin, usuario);
            cout << "Contraseña: ";
            getline(cin, contrasena);

            if (Usuario::iniciarSesion(usuario, contrasena)) {
                cout << "Sesión iniciada correctamente.\n";
                break;
            } else {
                cout << "Usuario o contraseña incorrectos.\n";
            }
        } else if (opcion == 2) {
            cout << "Nuevo usuario: ";
            getline(cin, usuario);
            cout << "Nueva contraseña: ";
            getline(cin, contrasena);
            Usuario::registrarUsuario(usuario, contrasena);
        } else {
            cout << "Opción inválida.\n";
        }
    } while (true);

    // Menú principal
    do {
        cout << "\n=== MENÚ PRINCIPAL ===\n"
             << "1. Gestión de productos\n"
             << "2. Salir\n"
             << "Seleccione opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                MenuProducto::mostrarMenuProducto();
                break;
            case 2:
                cout << "Saliendo del sistema...\n";
                return;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (true);
}
