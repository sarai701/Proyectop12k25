//Programado por Priscila Sarai Guzmán Calgua 9959-23-450
//Boris de León 9959-24-6203
#include "Bitacora.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;
//Registra una acción realizada por un usuario en la bitacora
void Bitacora::insertar(const string& usuario, int codigo, const std::string& aplicacion, const std::string& accion) {
    ofstream archivo("bitacora.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de bitácora.\n";
        return;
    }

    time_t now = time(nullptr);//obtenr fecha y hora
    char* fechaHora = ctime(&now);//convierte el tiempo en cadena
    fechaHora[strcspn(fechaHora, "\n")] = '\0';  // eliminar salto de línea

    archivo << left << setw(15) << usuario
            << setw(10) << codigo
            << setw(20) << aplicacion
            << setw(30) << accion
            << setw(25) << fechaHora << '\n';

    archivo.close();
}
//Mostarar todos los registros almacenados en bitácora
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
        cout << "\n--- MENÚ DE BITÁCORA ---\n";
        cout << "1. Desplegar bitácora\n";
        cout << "2. Regresar al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                mostrar();
                break;
            case 2:
                cout << "Regresando al menú principal...\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while (opcion != 2);
}

