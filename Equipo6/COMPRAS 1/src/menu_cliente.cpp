#include "menu_cliente.h"
#include "cliente.h"
#include <iostream>

using namespace std;

void mostrarMenuCliente() {
    int opcion;
    do {
        cout << "\n=== GESTIÓN DE CLIENTES ==="
             << "\n1. Registrar nuevo cliente"
             << "\n2. Listar clientes"
             << "\n3. Modificar cliente"
             << "\n4. Eliminar cliente"
             << "\n5. Volver al menú principal"
             << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: ingresarCliente(); break;
            case 2: consultarClientes(); break;
            case 3: modificarCliente(); break;
            case 4: borrarCliente(); break;
            case 5: cout << "Volviendo...\n"; break;
            default: cerr << "Opción inválida\n";
        }
    } while(opcion != 5);
}
