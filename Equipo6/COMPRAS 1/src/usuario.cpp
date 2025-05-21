#include "usuario.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const string Usuario::ARCHIVO_USUARIOS = "usuarios.txt";

bool Usuario::usuarioExiste(const string& usuario) {
    ifstream archivo(ARCHIVO_USUARIOS);
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('|');
        if (pos != string::npos && linea.substr(0, pos) == usuario) {
            return true;
        }
    }
    return false;
}

bool Usuario::registrarUsuario(const string& usuario, const string& contrasena) {
    if (usuarioExiste(usuario)) {
        cerr << "❌ El usuario ya existe\n";
        return false;
    }

    ofstream archivo(ARCHIVO_USUARIOS, ios::app);
    if (archivo.is_open()) {
        archivo << usuario << "|" << contrasena << "\n";
        cout << "✔ Usuario registrado exitosamente\n";
        return true;
    }
    return false;
}

bool Usuario::iniciarSesion(const string& usuario, const string& contrasena) {
    ifstream archivo(ARCHIVO_USUARIOS);
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('|');
        if (pos != string::npos &&
            linea.substr(0, pos) == usuario &&
            linea.substr(pos + 1) == contrasena) {
            return true;
        }
    }
    return false;
}
