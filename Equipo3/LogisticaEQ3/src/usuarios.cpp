//Karina Alejandra Arriaza Ortiz
#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;

extern bitacora auditoria;

// Constructor
usuarios::usuarios() {
    id = "";
    nombre = "";
    contrasena = "";
}

// Destructor
usuarios::~usuarios() {}

// Login de usuarios
bool usuarios::loginUsuarios() {
    string user, pass;
    int intentos = 0;
    bool acceso = false;

    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| AUTENTICACION DE USUARIOS - LOGISTICA |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tUsuario: ";
        cin >> user;
        cout << "\t\tContrasena: ";

        // Ocultar contraseña con *
        char ch;
        pass = "";
        while ((ch = _getch()) != 13) { // 13 = Enter
            if (ch == 8 && !pass.empty()) { // 8 = Backspace
                pass.pop_back();
                cout << "\b \b";
            } else if (ch != 8) {
                pass.push_back(ch);
                cout << '*';
            }
        }

        if (buscarUsuario(user, pass)) {
            acceso = true;
            nombre = user;
            auditoria.insertar(nombre, "000", "LOGIN");
            cout << "\n\t\tAutenticacion exitosa. Bienvenido!";
            system("pause");
            break;
        } else {
            intentos++;
            auditoria.insertar(user, "000", "LOGIN-FAIL");
            cout << "\n\t\tUsuario o contrasena incorrectos. Intentos restantes: " << 3 - intentos;
            system("pause");
        }
    } while (intentos < 3);

    return acceso;
}

// Buscar usuario en archivo
bool usuarios::buscarUsuario(const string& user, const string& pass) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de usuarios!";
        return false;
    }

    string idArchivo, nombreArchivo, passArchivo;
    while (archivo >> idArchivo >> nombreArchivo >> passArchivo) {
        if (nombreArchivo == user && passArchivo == pass) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

// Menú de administración de usuarios
void usuarios::menuUsuarios() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| ADMINISTRACION DE USUARIOS - LOGISTICA|" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t1. Registrar nuevo usuario" << endl;
        cout << "\t\t2. Consultar usuarios" << endl;
        cout << "\t\t3. Modificar usuario" << endl;
        cout << "\t\t4. Eliminar usuario" << endl;
        cout << "\t\t5. Volver al menu principal" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarUsuario(); break;
            case 2: consultarUsuarios(); break;
            case 3: modificarUsuario(); break;
            case 4: eliminarUsuario(); break;
            case 5: break;
            default: cout << "\n\t\tOpcion invalida!"; system("pause");
        }
    } while (opcion != 5);
}

// Registrar nuevo usuario
void usuarios::registrarUsuario() {
    system("cls");
    ofstream archivo("usuarios.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de usuarios!";
        return;
    }

    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRO DE NUEVO USUARIO            |" << endl;
    cout << "\t\t========================================" << endl;
    cout << "\t\tID: ";
    cin >> id;
    cout << "\t\tNombre: ";
    cin >> nombre;
    cout << "\t\tContrasena: ";

    char ch;
    contrasena = "";
    while ((ch = _getch()) != 13) {
        if (ch == 8 && !contrasena.empty()) {
            contrasena.pop_back();
            cout << "\b \b";
        } else if (ch != 8) {
            contrasena.push_back(ch);
            cout << '*';
        }
    }

    archivo << id << " " << nombre << " " << contrasena << endl;
    archivo.close();
    auditoria.insertar(nombre, "000", "REG-USER");
    cout << "\n\t\tUsuario registrado con exito!";
    system("pause");
}

// Consultar usuarios
void usuarios::consultarUsuarios() {
    system("cls");
    ifstream archivo("usuarios.txt");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| LISTADO DE USUARIOS - LOGISTICA      |" << endl;
    cout << "\t\t========================================" << endl;

    if (!archivo.is_open()) {
        cout << "\t\tNo hay usuarios registrados." << endl;
    } else {
        string id, nombre, pass;
        cout << "\t\t" << left << setw(10) << "ID" << setw(20) << "NOMBRE" << endl;
        while (archivo >> id >> nombre >> pass) {
            cout << "\t\t" << setw(10) << id << setw(20) << nombre << endl;
        }
        archivo.close();
    }
    cout << "\t\t========================================" << endl;
    auditoria.insertar(this->nombre, "000", "CONS-USER");
    system("pause");
}

// Getters y setters
string usuarios::getNombre() {
    return nombre;
}

void usuarios::setNombre(const string& nombre) {
    this->nombre = nombre;
}

// Modificar usuario
void usuarios::modificarUsuario() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| MODIFICAR USUARIO                    |" << endl;
    cout << "\t\t========================================" << endl;

    string usuarioBuscado, nuevaContrasena;
    cout << "\t\tNombre del usuario a modificar: ";
    cin >> usuarioBuscado;

    ifstream archivoIn("usuarios.txt");
    ofstream archivoTemp("temp.txt");
    bool encontrado = false;

    if (!archivoIn.is_open() || !archivoTemp.is_open()) {
        cerr << "\n\t\tError al abrir archivos!" << endl;
        return;
    }

    string idArchivo, nombreArchivo, passArchivo;
    while (archivoIn >> idArchivo >> nombreArchivo >> passArchivo) {
        if (nombreArchivo == usuarioBuscado) {
            encontrado = true;
            cout << "\t\tNueva contraseña: ";
            char ch;
            nuevaContrasena = "";
            while ((ch = _getch()) != 13) {
                if (ch == 8 && !nuevaContrasena.empty()) {
                    nuevaContrasena.pop_back();
                    cout << "\b \b";
                } else if (ch != 8) {
                    nuevaContrasena.push_back(ch);
                    cout << '*';
                }
            }
            archivoTemp << idArchivo << " " << nombreArchivo << " " << nuevaContrasena << endl;
        } else {
            archivoTemp << idArchivo << " " << nombreArchivo << " " << passArchivo << endl;
        }
    }

    archivoIn.close();
    archivoTemp.close();

    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");

    if (encontrado) {
        auditoria.insertar(usuarioBuscado, "000", "MOD-USER");
        cout << "\n\t\tUsuario modificado con éxito!" << endl;
    } else {
        cout << "\n\t\tUsuario no encontrado." << endl;
    }

    system("pause");
}

// Eliminar usuario
void usuarios::eliminarUsuario() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| ELIMINAR USUARIO                     |" << endl;
    cout << "\t\t========================================" << endl;

    string usuarioBuscado;
    cout << "\t\tNombre del usuario a eliminar: ";
    cin >> usuarioBuscado;

    ifstream archivoIn("usuarios.txt");
    ofstream archivoTemp("temp.txt");
    bool eliminado = false;

    if (!archivoIn.is_open() || !archivoTemp.is_open()) {
        cerr << "\n\t\tError al abrir archivos!" << endl;
        return;
    }

    string idArchivo, nombreArchivo, passArchivo;
    while (archivoIn >> idArchivo >> nombreArchivo >> passArchivo) {
        if (nombreArchivo != usuarioBuscado) {
            archivoTemp << idArchivo << " " << nombreArchivo << " " << passArchivo << endl;
        } else {
            eliminado = true;
        }
    }

    archivoIn.close();
    archivoTemp.close();

    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");

    if (eliminado) {
        auditoria.insertar(usuarioBuscado, "000", "DEL-USER");
        cout << "\n\t\tUsuario eliminado correctamente." << endl;
    } else {
        cout << "\n\t\tUsuario no encontrado." << endl;
    }

    system("pause");
}
