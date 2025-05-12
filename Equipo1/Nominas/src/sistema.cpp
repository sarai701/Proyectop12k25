#include "sistema.h"
#include "Opciones.h"
#include <conio.h>
Opciones opcion;
sistema::sistema()
{
    //ctor
}
sistema::~sistema()
{
    //dtor
}
void sistema::registrarUsuario() {
    system("cls");
    string nombre, contrasenia;
    cout << "Ingrese nombre de usuario: ";
    cin >> nombre;
    cout << "Ingrese contrasenia: ";
    char caracter;
    while ((caracter = _getch()) != '\r') {
        if (caracter == '\b') {
            if (!contrasenia.empty()) {
                cout << "\b \b";
                contrasenia.pop_back();
            }
        } else {
            contrasenia += caracter;
            cout << "*";
        }
    }
    cout << endl;
    ofstream archivo(archivoUsuarios, ios::app);
    if (archivo.is_open()) {
        archivo << nombre << "," << contrasenia << endl;
        archivo.close();
        cout << "Usuario registrado con exito." << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void sistema::ingresarUsuario() {
    system("cls");
    string nombre, contrasenia;
    cout << "Ingrese nombre de usuario: ";
    cin >> nombre;
    cout << "Ingrese contrasenia: ";
    char caracter;
    while ((caracter = _getch()) != '\r') {
        if (caracter == '\b') {
            if (!contrasenia.empty()) {
                cout << "\b \b";
                contrasenia.pop_back();
            }
        } else {
            contrasenia += caracter;
            cout << "*";
        }
    }
    cout << endl;
    ifstream archivo(archivoUsuarios);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            size_t coma = linea.find(",");
            string usuario = linea.substr(0, coma);
            string contraseniaArchivo = linea.substr(coma + 1);
            if (usuario == nombre && contraseniaArchivo == contrasenia) {
                cout << "Ingreso exitoso." << endl;
                archivo.close();
                opcion.menu();
                return;
            }
        }
        archivo.close();
        cout << "Nombre de usuario o contrasena incorrecta." << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void sistema::mostrarUsuarios() {
    system("cls");
    ifstream archivo(archivoUsuarios);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            size_t coma = linea.find(",");
            string usuario = linea.substr(0, coma);
            string contrasenia = linea.substr(coma + 1);
            string asteriscos(contrasenia.length(), '*');
            cout << "Nombre de usuario: " << usuario << endl;
            cout << "Contraseña: " << asteriscos << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

