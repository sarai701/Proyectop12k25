#include "Bitacora.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

void Bitacora::insertar(const std::string& usuario, int codigo, const std::string& aplicacion, const std::string& accion) {
    ofstream archivo("bitacora.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de bitácora.\n";
        return;
    }

    time_t now = time(nullptr);
    char* fechaHora = ctime(&now);
    fechaHora[strcspn(fechaHora, "\n")] = '\0';  // eliminar salto de línea

    archivo << left << setw(15) << usuario
            << setw(10) << codigo
            << setw(20) << aplicacion
            << setw(30) << accion
            << setw(25) << fechaHora << '\n';

    archivo.close();
}

void Bitacora::mostrar() {
    ifstream archivo("bitacora.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de bitácora.\n";
        return;
    }

    string usuario, aplicacion, accion, fechaHora;
    int codigo;

    cout << "\n--- BITÁCORA DE USUARIO ---\n";
    while (archivo >> usuario >> codigo >> aplicacion >> accion) {
        getline(archivo, fechaHora);
        cout << "Usuario: " << usuario << "\n"
             << "Código: " << codigo << "\n"
             << "Aplicación: " << aplicacion << "\n"
             << "Acción: " << accion << "\n"
             << "Fecha y Hora:" << fechaHora << "\n"
             << "-----------------------------\n";
    }

    archivo.close();
}

void Bitacora::menuBitacora() {
    int opcion;

    do {
        std::cout << "\n--- MENÚ DE BITÁCORA ---\n";
        std::cout << "1. Desplegar bitácora\n";
        std::cout << "2. Regresar al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                mostrar();
                break;
            case 2:
                std::cout << "Regresando al menú principal...\n";
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while (opcion != 2);
}

