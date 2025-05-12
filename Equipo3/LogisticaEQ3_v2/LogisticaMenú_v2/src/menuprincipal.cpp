// Inclusión de encabezados necesarios para los menús y entidades
#include "menuprincipal.h"
#include "menuarchivo.h"
#include "menucatalogos.h"
#include "menuprocesos.h"
#include "usuarios.h"
#include <vector>
#include <iostream>
using namespace std;

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

// Función que muestra el menú principal del sistema de gestión logística
void MenuPrincipal::mostrar(std::vector<Clientes>& clientes,
                          std::vector<Proveedor>& proveedores,
                          std::vector<Producto>& productos,
                          std::vector<Almacen>& almacenes,
                          std::vector<Administracion>& administradores,
                          std::vector<Transportistas>& transportistas,
                          usuarios& usuarioActual) {
    int choice;
    do {
        // Limpia la pantalla antes de mostrar el menú
        system("cls");

        // Encabezado del sistema con nombre del usuario
        cout << "\t\t========================================\n"
             << "\t\t|     SISTEMA DE GESTIÓN LOGÍSTICA     |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t================================================\n"
             << "\t\t 1. Archivo\n"
             << "\t\t 2. Catálogos\n"
             << "\t\t 3. Procesos\n"
             << "\t\t 4. Informes\n"
             << "\t\t 5. Salir\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opción: ";

        // Captura la opción ingresada por el usuario
        cin >> choice;

        // Ejecuta la acción correspondiente según la opción seleccionada
        switch(choice) {
            case 1:
                // Llama al menú de opciones de archivo (como guardar o cargar datos)
                MenuArchivo::mostrar();
                break;

            case 2:
                // Llama al menú de catálogos, pasando todas las listas y el usuario actual
                MenuCatalogos::mostrar(clientes, proveedores, productos,
                                       almacenes, administradores,
                                       transportistas, usuarioActual);
                break;

            case 3:
                // Llama al menú de procesos operativos
                MenuProcesos::mostrar();
                break;

            case 4:
                // Funcionalidad de informes aún no implementada
                break;

            case 5:
                // Opción para salir del menú principal
                return;

            default:
                // Mensaje si el usuario ingresa una opción inválida
                cout << "\n\t\tOpción inválida... Intenta de nuevo...";
        }
    } while(choice != 5); // Se repite hasta que el usuario seleccione salir
}
