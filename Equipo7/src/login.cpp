//Marlon De León 5001
#include "Login.h"
#include <iostream>
#include <fstream>
#include <string>
#include "encabezado.h"

using namespace std;

// Verifica si el usuario ya está registrado
bool usuarioExiste(const string& username) {
    ifstream file("usuarios.txt");
    string user, pass;
    while (file >> user >> pass) {
        if (user == username) {
            return true;
        }
    }
    return false;
}

// Registra un nuevo usuario en el archivo
bool registrarUsuario() {
    system("cls");
    string username, password;
    cout << "\n--- Registro de Usuario ---\n";
    cout << "Ingrese nombre de usuario: ";
    cin >> username;

    if (usuarioExiste(username)) {
        cout << "El usuario ya existe.\n";
        return false;
    }

    cout << "Ingrese contraseña: ";
    cin >> password;

    ofstream file("usuarios.txt", ios::app);
    file << username << " " << password << "\n";
    file.close();

    cout << "Usuario registrado exitosamente.\n";
    return true;
}

// Iniciar sesión con referencia a usuarioActual para guardar su nombre
bool iniciarSesion(string& usuarioActual) {
    system("cls");
    string username, password;
    cout << "\n--- Inicio de Sesion ---\n";
    cout << "Usuario: ";
    cin >> username;
    cout << "Contraseña: ";
    cin >> password;

    ifstream file("usuarios.txt");
    string user, pass;
    while (file >> user >> pass) {
        if (user == username && pass == password) {
            usuarioActual = username; // ← Guarda el nombre del usuario para bitácora
            cout << "Inicio de sesión exitoso. Bienvenido, " << username << ".\n";
            return true;
        }
    }

    cout << "Credenciales incorrectas.\n";
    return false;
}
