//LUIS ANGEL MENDEZ FUENTES
//9959-24-6845
// Inclusión de encabezados propios
/**
 * @file MenuClientes.cpp
 * @brief Implementación del menú interactivo para la gestión de clientes.
 *
 * Este módulo permite al usuario realizar operaciones básicas sobre clientes
 * tales como agregar, mostrar, modificar, eliminar y guardar cambios.
 * Cada acción limpia la pantalla antes de mostrarse y pausa para que el usuario
 * pueda leer mensajes importantes.
 */

// Inclusión de encabezados propios
#include "MenuClientes.h"
#include "Clientes.h"

// Inclusión de librerías estándar
#include <iostream>
#include <vector>
#include <string>
#include <limits> // Para manejo de entradas inválidas y limpieza de buffer

using namespace std;

// Constantes para validar ID de clientes
const int CODIGO_INICIAL = 3107; /**< ID mínimo válido para clientes */
const int CODIGO_FINAL = 3157;   /**< ID máximo válido para clientes */

/**
 * @brief Muestra y controla el menú de gestión de clientes.
 *
 * Esta función presenta al usuario las opciones disponibles para manejar clientes.
 * Al seleccionar una opción, la pantalla se limpia y se ejecuta la función correspondiente.
 * Al finalizar la acción, se pausa la ejecución para que el usuario pueda leer mensajes.
 *
 * @param listaClientes Vector con la lista actual de clientes.
 * @param usuarioActual Objeto que representa al usuario que utiliza el sistema.
 */
void MenuClientes::mostrar(vector<Clientes>& listaClientes, usuarios& usuarioActual) {
    int opcion;       /**< Opción seleccionada por el usuario */
    string input;     /**< Entrada para IDs u otros textos */

    do {
        system("cls"); // Limpia pantalla antes de mostrar el menú principal
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "                        SISTEMA DE GESTION DE CLIENTES                          \n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "   Usuario actual: " << usuarioActual.getNombre() << "\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "   [1] Agregar cliente\n";
        cout << "   [2] Mostrar clientes\n";
        cout << "   [3] Modificar cliente\n";
        cout << "   [4] Eliminar cliente\n";
        cout << "   [5] Volver al menu principal\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "                     Seleccione una opcion: ";

        // Validación para asegurar que la entrada sea un número válido
        while (!(cin >> opcion)) {
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora entrada inválida
            cout << "\n   Entrada invalida. Ingrese un numero valido: ";
        }
        cin.ignore(); // Limpia el salto de línea residual del buffer

        switch (opcion) {
            case 1:
                system("cls"); // Limpia antes de ejecutar la acción
                Clientes::agregar(listaClientes, usuarioActual.getNombre());
                // NO system("pause"); porque 'agregar' ya pausa
                break;

            case 2:
                system("cls");
                Clientes::mostrar(listaClientes);
                // NO system("pause"); porque 'mostrar' ya pausa
                break;

            case 3: {
                system("cls");
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n   Ingrese ID del cliente a modificar: ";
                    getline(cin, input);

                    if (Clientes::esIdValido(input)) {
                        Clientes::modificar(listaClientes, usuarioActual.getNombre(), input);
                        // modificar ya pausa internamente
                    } else {
                        cout << "   ID no valido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause"); // Pausa solo aquí en caso de ID inválido
                    }
                }
                // NO system("pause"); adicional acá
                break;
            }

            case 4: {
                system("cls");
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n   Ingrese ID del cliente a eliminar: ";
                    getline(cin, input);

                    if (Clientes::esIdValido(input)) {
                        Clientes::eliminar(listaClientes, usuarioActual.getNombre(), input);
                        // eliminar ya pausa internamente
                    } else {
                        cout << "   ID no valido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause"); // Pausa solo aquí en caso de ID inválido
                    }
                }
                // NO system("pause"); adicional acá
                break;
            }

            case 5:
                Clientes::guardarEnArchivo(listaClientes);
                cout << "\n   Regresando al menu principal...\n";
                system("pause"); // Pausa para que el usuario vea mensaje de salida
                break;

            default:
                cout << "\n   Opcion invalida.\n";
                system("pause"); // Pausa para informar opción inválida
                break;
        }

    } while (opcion != 5);
}
