#include "MenuProcesos.h"
#include "usuarios.h"
#include <iostream>  // Faltaba en varios archivos
#include "pedidos.h"
#include "inventario.h"
#include "envios.h"
#include "facturacion.h"
#include "reportes.h"
#include "globals.h"

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

using namespace std;


extern usuarios usuarioRegistrado;

void MenuProcesos::mostrar() {
    int choice;
    do {
        system("cls");
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
        cin >> choice;

        switch(choice) {
            case 1: gestorPedidos.gestionPedidos(); break;
            case 2: gestorInventario.controlInventario(); break;
            case 3: gestorEnvios.gestionEnvios(); break;
            case 4: gestorFacturacion.gestionFacturacion(); break;
            case 5: gestorReportes.generarReportes(); break;
            case 6: return;
            default: cout << "\n\t\tOpción inválida...";
        }
        cin.ignore();
        cin.get();
    } while(choice != 6);
}
