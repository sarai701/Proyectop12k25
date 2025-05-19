// Archivo: utilidades.cpp
// Implementación de funciones auxiliares para validación y utilidades comunes
// Autora: Dulce Reyes - Mayo 2025

#include "utilidades.h"
#include "factura.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausarPantalla() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void pausar() {
    system("pause");
}

void limpiarPantalla() {
    system("cls");
}

string aMayusculas(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::toupper);
    return texto;
}

bool esNumeroEntero(const string& str) {
    if (str.empty()) return false;
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool esNumeroDecimal(const string& str) {
    bool punto = false;
    for (char c : str) {
        if (c == '.') {
            if (punto) return false;
            punto = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

bool obtenerDatosClientePorID(const string& idBuscar, string& nombre, string& nit) {
    ifstream archivo("cliente.txt");
    if (!archivo) return false;

    string id, telefono;
    while (archivo >> id >> nombre >> telefono >> nit) {
        if (id == idBuscar) {
            return true;
        }
    }
    return false;
}

// En utilidades.cpp

bool obtenerDatosProveedorPorID(const string& idBuscar, string& nombre, string& nit) {
    ifstream archivo("proveedor.txt");
    if (!archivo) return false;

    string id, telefono, banco, numCuenta;

    // Leer línea por línea
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);

        // Leer cada campo considerando el ancho fijo (15 caracteres)
        ss >> setw(15) >> id >> setw(15) >> nombre >> setw(15) >> nit
           >> setw(15) >> telefono >> setw(15) >> banco >> setw(15) >> numCuenta;

        // Eliminar espacios en blanco sobrantes
        id = id.substr(0, id.find_first_of(' '));
        if (id == idBuscar) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

bool obtenerDatosAcreedorPorID(const string& idBuscar, string& nombre, string& nit) {
    ifstream archivo("acreedor.txt");
    if (!archivo) return false;

    string id, telefono, banco, numCuenta;

    // Leer línea por línea
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);

        // Leer cada campo considerando el ancho fijo (15 caracteres)
        ss >> setw(15) >> id >> setw(15) >> nombre >> setw(15) >> nit
           >> setw(15) >> telefono >> setw(15) >> numCuenta >> setw(15) >> banco;

        // Eliminar espacios en blanco sobrantes
        id = id.substr(0, id.find_first_of(' '));
        if (id == idBuscar) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}
