#include "menu_producto.h"
#include "producto.h"
#include <iostream>

using namespace std;

void mostrarMenuProducto() {
    int opcion;
    do {
        cout << "\n=== GESTIÓN DE PRODUCTOS ==="
             << "\n1. Registrar nuevo producto"
             << "\n2. Listar productos"
             << "\n3. Modificar producto"
             << "\n4. Eliminar producto"
             << "\n5. Volver al menú principal"
             << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: ingresarProducto(); break;
            case 2: consultarProductos(); break;
            case 3: modificarProducto(); break;
            case 4: borrarProducto(); break;
            case 5: cout << "Volviendo...\n"; break;
            default: cerr << "Opción inválida\n";
        }
    } while(opcion != 5);
}
