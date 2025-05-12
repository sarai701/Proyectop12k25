#include "MenuProductos.h"
#include "Producto.h"
#include <iostream>
#include <limits>

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025
using namespace std;

// Muestra el menú de productos y permite al usuario realizar operaciones sobre el inventario
void MenuProductos::mostrar(vector<Producto>& listaProductos, usuarios& usuarioActual) {
    int opcion;
    string input;

    // Cargar productos desde archivo al iniciar el menú
    Producto::cargarDesdeArchivo(listaProductos);

    do {
        system("cls"); // Limpiar pantalla
        cout << "\t\t=== MENÚ PRODUCTOS ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar producto\n"
             << "\t\t2. Mostrar productos\n"
             << "\t\t3. Modificar producto\n"
             << "\t\t4. Eliminar producto\n"
             << "\t\t5. Volver al menú principal\n"
             << "\t\t======================\n"
             << "\t\tSeleccione una opción: ";

        // Validación de entrada numérica
        while (!(cin >> opcion)) {
            cin.clear(); // Limpiar estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
            cout << "\t\tEntrada inválida. Por favor ingrese un número: ";
        }
        cin.ignore(); // Limpiar salto de línea pendiente

        switch(opcion) {
            case 1:
                // Agregar un nuevo producto al inventario
                Producto::agregar(listaProductos, usuarioActual.getNombre());
                break;

            case 2:
                // Mostrar todos los productos disponibles
                Producto::mostrar(listaProductos);
                break;

            case 3: {
                // Mostrar productos antes de solicitar código a modificar
                Producto::mostrar(listaProductos);
                if (!listaProductos.empty()) {
                    cout << "\n\t\tIngrese Código del producto a modificar: ";
                    getline(cin, input);

                    // Validar que el código esté dentro del rango permitido
                    if (Producto::esCodigoValido(input)) {
                        Producto::modificar(listaProductos, usuarioActual.getNombre(), input);
                    } else {
                        // Mostrar mensaje si el código no es válido
                        cout << "\t\tCódigo no válido. Debe estar entre " << 3209
                             << " y " << 3259 << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 4: {
                // Mostrar productos antes de solicitar código a eliminar
                Producto::mostrar(listaProductos);
                if (!listaProductos.empty()) {
                    cout << "\n\t\tIngrese Código del producto a eliminar: ";
                    getline(cin, input);

                    // Validar que el código esté dentro del rango permitido
                    if (Producto::esCodigoValido(input)) {
                        Producto::eliminar(listaProductos, usuarioActual.getNombre(), input);
                    } else {
                        // Mostrar mensaje si el código no es válido
                        cout << "\t\tCódigo no válido. Debe estar entre " << 3209
                             << " y " << 3259 << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                // Guardar productos antes de salir del menú
                Producto::guardarEnArchivo(listaProductos);
                return;

            default:
                // Manejar opción no válida
                cout << "\t\tOpción no válida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true); // Repetir menú hasta que el usuario decida salir
}
