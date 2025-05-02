//funcionamiento del menú (kevin)
//funcionamiento del menú (Luis)
#include "Menu.h"

Menu::Menu() {}

void Menu::mostrarOpciones(Inventario& inventario, Facturacion& factura) {
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Agregar Producto\n";
        cout << "2. Ver Inventario\n";
        cout << "3. Facturar\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int codigo, stock;
                float precio;
                string nombre, tipo;
                cout << "Codigo: "; cin >> codigo;
                cout << "Nombre: "; cin >> nombre;
                cout << "Precio: "; cin >> precio;
                cout << "Stock: "; cin >> stock;
                cout << "Tipo (ventas, stock, compras): "; cin >> tipo;
                inventario.agregarProducto(codigo, nombre, precio, stock, tipo);
                break;
            }

            case 2: {
                int subopcion;
                do {
                    cout << "\n--- SUBMENU INVENTARIO ---\n";
                    cout << "1. Inventario General\n";
                    cout << "2. Inventario para Ventas\n";
                    cout << "3. Inventario para Stock\n";
                    cout << "4. Inventario para Compras\n";
                    cout << "5. Regresar al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;

                    switch (subopcion) {
                        case 1:
                            inventario.mostrarInventarioGeneral();
                            break;
                        case 2:
                            inventario.mostrarInventarioPorTipo("ventas");
                            break;
                        case 3:
                            inventario.mostrarInventarioPorTipo("stock");
                            break;
                        case 4:
                            inventario.mostrarInventarioPorTipo("compras");
                            break;
                        case 5:
                            cout << "Regresando al menu principal...\n";
                            break;
                        default:
                            cout << "Opción no valida, intente de nuevo.\n";
                    }
                } while (subopcion != 5);
                break;
            }

            case 3:
                factura.generarFactura(inventario);
                break;

            case 4:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida, intente de nuevo.\n";
        }
    } while (opcion != 4);
}

Menu::~Menu() {}

