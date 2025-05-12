#include "menu_compra.h"
#include "compras.h"
#include <iostream>
#include <iomanip>

using namespace std;

void mostrarMenuCompra() {
    vector<Producto> listaCompras;
    int opcion;

    do {
        cout << "\n=== MENÚ DE COMPRAS ==="
             << "\n1. Registrar nueva compra"
             << "\n2. Ver historial de compras"
             << "\n3. Buscar por proveedor"
             << "\n4. Ver total gastado"
             << "\n5. Volver al menú principal"
             << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
                registrarCompra(listaCompras);
                break;
            case 2:
                mostrarHistorial(listaCompras);
                break;
            case 3:
                buscarPorProveedor(listaCompras);
                break;
            case 4:
                cout << "\n💰 Total gastado: $" << fixed << setprecision(2)
                     << calcularTotalGastado(listaCompras) << endl;
                break;
            case 5:
                cout << "Volviendo...\n";
                break;
            default:
                cerr << "Opción inválida\n";
        }
    } while(opcion != 5);
}
