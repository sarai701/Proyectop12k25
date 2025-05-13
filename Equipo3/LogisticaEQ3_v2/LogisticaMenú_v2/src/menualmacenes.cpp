//9959 24 11603 GE
#include "MenuAlmacenes.h"
#include <iostream>
#include <limits>

// Función que muestra el menú de gestión de almacenes
void MenuAlmacenes::mostrar(std::vector<Almacen>& lista, usuarios& usuarioActual) {
    int opcion;          // Variable para almacenar la opción ingresada por el usuario
    std::string input;   // Para capturar IDs u otros textos desde el teclado

    do {
        system("cls"); // Limpia la pantalla (solo en sistemas Windows)

        // Muestra el menú principal con el nombre del usuario actual
        std::cout << "=== MENÚ ALMACENES ===\n"
                  << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
                  << "1. Agregar Almacen\n"
                  << "2. Mostrar Almacenes\n"
                  << "3. Modificar Almacen\n"
                  << "4. Eliminar Almacen\n"
                  << "5. Volver al menú principal\n"
                  << "\t\t=====================\n"
                  << "\t\tSeleccione una opción: ";

        // Validación de entrada para asegurarse de que se ingrese un número
        while (!(std::cin >> opcion)) {
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta entrada inválida
            std::cout << "Entrada inválida. Ingrese un número: ";
        }

        std::cin.ignore(); // Limpia el salto de línea tras ingresar número

        // Lógica del menú según la opción seleccionada
        switch (opcion) {
            case 1:
                // Agrega un nuevo almacén
                Almacen::agregar(lista, usuarioActual.getNombre());
                break;
            case 2:
                // Muestra todos los almacenes registrados
                Almacen::mostrar(lista);
                system("pause"); // Pausa para que el usuario pueda ver los datos
                break;
            case 3: {
                // Solicita y modifica un almacén existente
                Almacen::mostrar(lista); // Primero muestra los almacenes
                std::cout << "ID a modificar: ";
                std::getline(std::cin, input);
                Almacen::modificar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 4: {
                // Solicita y elimina un almacén existente
                Almacen::mostrar(lista); // Primero muestra los almacenes
                std::cout << "ID a eliminar: ";
                std::getline(std::cin, input);
                Almacen::eliminar(lista, usuarioActual.getNombre(), input);
                break;
            }
            case 5:
                // Sale del menú de almacenes y vuelve al menú principal
                return;
            default:
                // Opción no válida
                std::cout << "Opción inválida\n";
                system("pause"); // Pausa para mostrar el mensaje
        }
    } while (true); // Bucle infinito hasta que se seleccione la opción de salir
}
