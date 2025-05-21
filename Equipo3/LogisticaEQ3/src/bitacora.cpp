// LUIS ANGEL MENDEZ FUENTES 9959-24-6845
#include "bitacora.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Inserta un nuevo registro en el archivo "bitacora.txt"
void bitacora::insertar(string usuario, string codigo, string accion) {
    ofstream file("bitacora.txt", ios::app); // Abre el archivo en modo agregar
    if (file.is_open()) {
        // Escribe los datos con formato alineado
        file << left << setw(20) << usuario
             << setw(10) << codigo
             << setw(15) << accion << endl;
        file.close();
    } else {
        cerr << "\n\t\tError al abrir la bitácora!";
    }
}

// Muestra en pantalla los registros de la bitácora
void bitacora::desplegar() {
    system("cls"); // Limpia la consola
    ifstream file("bitacora.txt");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRO DE BITACORA - LOGISTICA     |" << endl;
    cout << "\t\t========================================" << endl;

    if (file.is_open()) {
        string linea;
        // Muestra línea por línea el contenido del archivo
        while (getline(file, linea)) {
            cout << "\t\t" << linea << endl;
        }
        file.close();
    } else {
        cout << "\t\tNo hay registros en la bitácora." << endl;
    }

    cout << "\t\t========================================" << endl;
    system("pause"); // Pausa para que el usuario lea la información
}

// Menú interactivo para acceder a funciones de la bitácora
void bitacora::menuBitacora() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| ADMINISTRACION DE BITACORA           |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Ver registros" << endl;
        cout << "\t\t 2. Exportar a archivo" << endl;
        cout << "\t\t 3. Volver" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                desplegar();
                break;
            case 2:
                cout << "\n\t\t[Exportando bitácora...]" << endl;
                system("pause"); // Simulación de exportación
                break;
            case 3:
                break; // Salir del menú
            default:
                cout << "\n\t\tOpcion invalida!";
                cin.get();
        }
    } while(opcion != 3);
}
