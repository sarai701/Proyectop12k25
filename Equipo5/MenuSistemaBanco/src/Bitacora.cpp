//Primera version por Boris de Leon 9959-24-6203
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
