//Boris de León 9959-24-6203
//Priscila Guzmán 9959-23-450
#include "Bitacora.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

// Estructura para almacenar un registro de bitácora en formato binario
struct RegistroBitacora {
    char usuario[30];
    int codigo;
    char aplicacion[30];
    char accion[50];
    char fechaHora[30];
};

// Inserta un registro en el archivo binario "bitacora.dat"
void Bitacora::insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion) {
    ofstream archivo("bitacora.dat", ios::binary | ios::app);  // abrir archivo para agregar al final en modo binario
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de bitácora.\n";
        return;
    }

    RegistroBitacora registro;
    strncpy(registro.usuario, usuario.c_str(), sizeof(registro.usuario) - 1); // copiar usuario a registro
    registro.usuario[sizeof(registro.usuario) - 1] = '\0'; // asegurar terminación nula

    registro.codigo = codigo; // asignar código

    strncpy(registro.aplicacion, aplicacion.c_str(), sizeof(registro.aplicacion) - 1); // copiar aplicación
    registro.aplicacion[sizeof(registro.aplicacion) - 1] = '\0';

    strncpy(registro.accion, accion.c_str(), sizeof(registro.accion) - 1); // copiar acción
    registro.accion[sizeof(registro.accion) - 1] = '\0';

    time_t now = time(nullptr); // obtener tiempo actual
    char* fecha = ctime(&now); // convertir tiempo a cadena
    fecha[strcspn(fecha, "\n")] = '\0'; // quitar salto de línea
    strncpy(registro.fechaHora, fecha, sizeof(registro.fechaHora) - 1); // copiar fecha y hora
    registro.fechaHora[sizeof(registro.fechaHora) - 1] = '\0';

    archivo.write(reinterpret_cast<char*>(&registro), sizeof(registro)); // escribir registro en archivo
    archivo.close();
}

// Muestra todos los registros almacenados en "bitacora.dat"
void Bitacora::mostrar() {
    ifstream archivo("bitacora.dat", ios::binary); // abrir archivo para lectura binaria
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de bitácora.\n";
        return;
    }

    RegistroBitacora registro;
    cout << "\n--- BITÁCORA DE USUARIO ---\n";
    while (archivo.read(reinterpret_cast<char*>(&registro), sizeof(registro))) { // leer registro a registro
        cout << "Usuario: " << registro.usuario << "\n"
             << "Código: " << registro.codigo << "\n"
             << "Aplicación: " << registro.aplicacion << "\n"
             << "Acción: " << registro.accion << "\n"
             << "Fecha y Hora: " << registro.fechaHora << "\n"
             << "-----------------------------\n";
    }

    archivo.close();
}

// Menú simple para interactuar con la bitácora
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
            opcion = 0; // para repetir en caso de entrada inválida
        }

        switch (opcion) {
            case 1:
                mostrar(); // mostrar registros
                break;
            case 2:
                cout << "Regresando al menú principal...\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 2);
}
