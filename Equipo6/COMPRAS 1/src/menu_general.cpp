 #include "menu_general.h"
#include "menu_cliente.h"
#include "menu_producto.h"
#include "menu_compra.h"
#include "menu_archivo.h"
#include <iostream>

using namespace std;

void mostrarMenuGeneral() {
    int opcion;
    do {
        cout << "\n=== MENÚ PRINCIPAL ==="
             << "\n1. Gestión de Clientes"
             << "\n2. Gestión de Productos"
             << "\n3. Gestión de Compras"
             << "\n4. Herramientas de Archivo"
             << "\n5. Cerrar sesión"
             << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: mostrarMenuCliente(); break;
            case 2: mostrarMenuProducto(); break;
            case 3: mostrarMenuCompra(); break;
            case 4: menuArchivo(); break;
            case 5: cout << "Cerrando sesión...\n"; break;
            default: cerr << "Opción inválida\n";
        }
    } while(opcion != 5);
}
