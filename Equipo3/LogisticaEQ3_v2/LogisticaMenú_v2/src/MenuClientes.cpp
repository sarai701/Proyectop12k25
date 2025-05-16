// Inclusión de encabezados propios
#include "MenuClientes.h"
#include "Clientes.h"

// Inclusión de librerías estándar
#include <iostream>
#include <vector>
#include <string>
#include <limits> // Para manejar entradas inválidas y limpiar el buffer de entrada

using namespace std;

// Definición de rangos válidos para los ID de clientes
const int CODIGO_INICIAL = 3107;
const int CODIGO_FINAL = 3157;

/**
 * Muestra el menú de gestión de clientes.
 * Permite agregar, mostrar, modificar o eliminar clientes.
 * @param listaClientes Vector que contiene la lista de todos los clientes registrados.
 * @param usuarioActual Objeto que representa al usuario que está utilizando el sistema.
 */
void MenuClientes::mostrar(vector<Clientes>& listaClientes, usuarios& usuarioActual) {
    int opcion;
    string input;

    do {
        // Limpiar pantalla y mostrar encabezado del menú
        system("cls");
        cout << "\t\t=== MENÚ CLIENTES ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar cliente\n"
             << "\t\t2. Mostrar clientes\n"
             << "\t\t3. Modificar cliente\n"
             << "\t\t4. Eliminar cliente\n"
             << "\t\t5. Volver al menú principal\n"
             << "\t\t=====================\n"
             << "\t\tSeleccione una opción: ";

        // Validación de entrada: solo se aceptan números
        while (!(cin >> opcion)) {
            cin.clear(); // Limpiar estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada inválida
            cout << "\t\tEntrada inválida. Por favor ingrese un número: ";
        }
        cin.ignore(); // Limpiar el buffer restante

        // Ejecutar la opción seleccionada por el usuario
        switch(opcion) {
            case 1:
                // Llamar a la función estática para agregar un cliente
                Clientes::agregar(listaClientes, usuarioActual.getNombre());
                break;

            case 2:
                // Mostrar la lista de clientes
                Clientes::mostrar(listaClientes);
                break;

            case 3: {
                // Mostrar la lista antes de modificar
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n\t\tIngrese ID del cliente a modificar: ";
                    getline(cin, input);

                    // Verificar si el ID ingresado es válido antes de modificar
                    if (Clientes::esIdValido(input)) {
                        Clientes::modificar(listaClientes, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 4: {
                // Mostrar la lista antes de eliminar
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n\t\tIngrese ID del cliente a eliminar: ";
                    getline(cin, input);

                    // Verificar si el ID ingresado es válido antes de eliminar
                    if (Clientes::esIdValido(input)) {
                        Clientes::eliminar(listaClientes, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no válido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                // Guardar datos en archivo antes de volver al menú principal
                Clientes::guardarEnArchivo(listaClientes);
                return; // Salir del menú de clientes

            default:
                // Opción inválida
                cout << "\t\tOpción no válida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true); // Bucle infinito hasta que el usuario elija salir
}
