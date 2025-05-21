//funcionamiento del menú (kevin)
//funcionamiento del menú (Luis)
//Actualizacion (Anthony)
#include "Menu.h"
#include "Bitacora.h"

Menu::Menu() {}


void Menu::mostrarOpciones(Inventario& inventario, Facturacion& factura, const string& nombreUsuario) {
    int opcion;
    bitacora auditoria;
    do {
        system("cls"); // Usa "clear" y mejora en lo visual por Anthony Suc
        cout << "=====================================\n";
        cout << "         SISTEMA DE INVENTARIO       \n";
        cout << "=====================================\n";
        cout << " 1. Agregar Producto\n";
        cout << " 2. Ver Inventario\n";
        cout << " 3. Facturar\n";
        cout << " 4. Salir\n";
        cout << "-------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                system("cls");
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
                system("cls");
                int subopcion;
                do {
                    cout << "\n=====================================\n";
                    cout << "      --- SUBMENU INVENTARIO ---\n";
                    cout << "=====================================\n";
                    cout << "1. Kardex\n";
                    cout << "2. Reporte ventas\n";
                    cout << "3. Reporte existencias\n";
                    cout << "4. Reporte compras\n";
                    cout << "5. Regresar al menu principal\n";
                    cout << "-------------------------------------\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;

                    switch (subopcion) {
                        case 1:
                            auditoria.insertar(nombreUsuario, 2001, "Ver Inventario General", "Visualización del inventario");
                            inventario.mostrarInventarioGeneral();
                            break;
                        case 2:
                            auditoria.insertar(nombreUsuario, 2002, "Ver Inventario Ventas", "Visualización de inventario de ventas");
                            inventario.mostrarInventarioPorTipo("ventas");
                            break;
                        case 3:
                            auditoria.insertar(nombreUsuario, 2003, "Ver Inventario Stock", "Visualización de inventario de stock");
                            inventario.mostrarInventarioPorTipo("stock");
                            break;
                        case 4:
                            auditoria.insertar(nombreUsuario, 2004, "Ver Inventario Compras", "Visualización de inventario de compras");
                            inventario.mostrarInventarioPorTipo("compras");
                            break;
                        case 5:
                            cout << "Regresando al menú principal...\n";
                            break;
                        default:
                            cout << "Opción no válida, intente de nuevo.\n";
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

