#include "usuario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void Usuario::registrarUsuario(const string& nombre, const string& contrasena) {
    ofstream archivo("usuarios.txt", ios::app);  // Abre el archivo para agregar al final
    if (archivo.is_open()) {
        archivo << nombre << "," << contrasena << endl;  // Guarda el usuario y contraseña
        archivo.close();
        cout << "✅ Usuario registrado exitosamente." << endl;
    } else {
        cout << "❌ No se pudo abrir el archivo para registrar el usuario." << endl;
    }
}

bool Usuario::iniciarSesion(const string& nombre, const string& contrasena) {
    ifstream archivo("usuarios.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombreGuardado, contrasenaGuardada;
        getline(ss, nombreGuardado, ',');
        getline(ss, contrasenaGuardada);

        if (nombreGuardado == nombre && contrasenaGuardada == contrasena) {
            return true;  // Inicio de sesión exitoso
        }
    }

    return false;  // Usuario o contraseña incorrectos
}
