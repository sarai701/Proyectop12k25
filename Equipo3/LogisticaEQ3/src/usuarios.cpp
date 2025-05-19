//Karina Alejandra Arriaza Ortiz
#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <conio.h> // Para getch()
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
        cout << "\t\t1. Iniciar sesion" << endl;
        cout << "\t\t2. Registrarse (nuevo usuario)" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion: ";
        int opcion;
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            cout << "\t\tUsuario: ";
            getline(cin, user);
            cout << "\t\tContrasena: ";

            char ch;
            pass = "";
            while ((ch = _getch()) != 13) {
                if (ch == 8 && !pass.empty()) {
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
        } else if (opcion == 2) {
            registrarUsuario(); // Llama al registro directamente
            cout << "\n\t\tAhora puede iniciar sesion con sus nuevas credenciales";
            system("pause");
        }
    } while (intentos < 3);

    return acceso;
}

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

    cout << "\t\tID (ej: 1001): ";
    getline(cin, id);
    cout << "\t\tNombre de usuario: ";
    getline(cin, nombre);
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
    cout << "\n\n\t\tUsuario registrado con exito!";
    system("pause");
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

// Men� de administraci�n de usuarios
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
            //case 3:  modificarUsuario();  break;
            //case 4:  eliminarUsuario();  break;
            case 5: break;
            default: cout << "\n\t\tOpcion invalida!"; system("pause");
        }
    } while (opcion != 5);
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
