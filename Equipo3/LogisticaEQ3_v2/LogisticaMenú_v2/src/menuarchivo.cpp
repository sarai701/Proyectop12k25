#include "MenuArchivo.h"
#include "usuarios.h"
#include <iostream>
using namespace std;

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

//ESTE MENÚ AUN DEBE SER CORREGIDO Y AÑADIR NUEVAS FUNCIONES.

extern usuarios usuarioRegistrado;

void MenuArchivo::mostrar() {
    int opcion;
    do {
        system("cls");
        std::cout << "\t\t========================================\n"
                  << "\t\t|          MENÚ ARCHIVO                |\n"
                  << "\t\t========================================\n"
                  << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << "\n"  // Nombre aquí
                  << "\t\t========================================\n"
                  << "\t\t 1. Cerrar sesión\n"
                  << "\t\t 2. Backup\n"
                  << "\t\t 3. Volver\n"
                  << "\t\t========================================\n"
                  << "\t\tIngresa tu opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: usuarioRegistrado.~usuarios(); return;  // Cierra sesión
            case 2: /* ... */ break;
            case 3: return;
            default: std::cout << "\n\t\tOpción inválida...";
        }
    } while(true);
}
