#include "MenuProcesos.h"
#include "usuarios.h"
#include <iostream>
#include "pedidos.h"
#include "inventario.h"
#include "envios.h"
#include "facturacion.h"
#include "reportes.h"
#include "globals.h"
#include "clientes.h"
#include "producto.h"
#include "Almacen.h"

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

using namespace std;

// Declaración externa del usuario registrado actual
extern usuarios usuarioRegistrado;

// Muestra el menú principal de procesos y redirige según la opción elegida
void MenuProcesos::mostrar(const std::vector<Clientes>& clientes,
                          const std::vector<Producto>& productos,
                          const std::vector<Almacen>& almacenes) {
    int choice;
    do {
        // Limpiar pantalla antes de mostrar el menú
        system("cls");

        // Mostrar encabezado del menú y nombre del usuario actual
        cout << "\t\t========================================\n"
             << "\t\t|          MENÚ DE PROCESOS            |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << "\n"
             << "\t\t========================================\n"
             << "\t\t 1. Gestión de Pedidos\n"
             << "\t\t 2. Control de Inventario\n"
             << "\t\t 3. Envíos y Transportes\n"
             << "\t\t 4. Facturación\n"
             << "\t\t 5. Reportes\n"
             << "\t\t 6. Volver\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opción: ";

        // Captura la opción del usuario
        cin >> choice;

        // Ejecuta la opción seleccionada
        switch(choice) {
            case 1:
                // Acceder a la funcionalidad de gestión de pedidos
                {
                    Pedidos gestorPedidos;
                    gestorPedidos.gestionPedidos(clientes, productos, almacenes);
                }
                break;

            case 2:
                // Acceder a la funcionalidad de control de inventario
                gestorInventario.controlInventario();
                break;

            case 3:
                // Acceder a la funcionalidad de gestión de envíos y transportes
                gestorEnvios.gestionEnvios();
                break;

            case 4:
                // Funcionalidad de facturación (a implementar)
                break;

            case 5:
                // Generar reportes disponibles en el sistema
                gestorReportes.generarReportes();
                break;

            case 6:
                // Salir del menú de procesos
                return;

            default:
                // Manejar opción inválida
                cout << "\n\t\tOpción inválida...";
        }

        // Esperar una tecla antes de volver a mostrar el menú
        cin.ignore(); // Limpiar buffer
        cin.get();    // Esperar entrada del usuario
    } while(choice != 6); // Repetir hasta que se seleccione salir
}
