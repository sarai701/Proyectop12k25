//Karina Alejandra Arriaza Ortiz
#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "globals.h"

using namespace std;

extern bitacora auditoria;

// Constructor
usuarios::usuarios() : id(""), nombre(""), contrasena(""), nivelAcceso(1) {}

// Destructor
usuarios::~usuarios() {}

// Funciones auxiliares privadas
bool usuarios::esNumero(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

bool usuarios::usuarioExiste(const string& nombreUsuario) {
    ifstream archivo("usuarios.txt");
    string linea;

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string idArchivo, nombreArchivo, passArchivo;
        int nivelArchivo;

        if (ss >> idArchivo >> nombreArchivo >> passArchivo >> nivelArchivo) {
            if (nombreArchivo == nombreUsuario) {
                archivo.close();
                return true;
            }
        }
    }
    archivo.close();
    return false;
}

string usuarios::leerPasswordSegura() {
    string pass;
    char ch;
    while ((ch = _getch()) != 13) { // 13 es Enter
        if (ch == 8 && !pass.empty()) { // 8 es Backspace
            pass.pop_back();
            cout << "\b \b";
        } else if (ch != 8) {
            pass.push_back(ch);
            cout << '*';
        }
    }
    return pass;
}

// Funciones públicas
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
            pass = leerPasswordSegura();

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
            registrarUsuario();
        }
    } while (intentos < 3);

    return acceso;
}

void usuarios::registrarUsuario() {
    system("cls");
    ofstream archivo("usuarios.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de usuarios!\n";
        return;
    }

    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRO DE NUEVO USUARIO            |" << endl;
    cout << "\t\t========================================" << endl;

    // Validación de ID
    do {
        cout << "\t\tID (ej: 1001): ";
        getline(cin, id);
        if (!esNumero(id)) {
            cout << "\t\tID invalido! Debe ser numerico.\n";
        }
    } while (!esNumero(id));

    // Validación de nombre de usuario
    do {
        cout << "\t\tNombre de usuario (sin espacios): ";
        getline(cin, nombre);
        if (nombre.find(' ') != string::npos) {
            cout << "\t\tEl nombre no puede contener espacios!\n";
        } else if (usuarioExiste(nombre)) {
            cout << "\t\tEste nombre de usuario ya existe!\n";
        }
    } while (nombre.empty() || nombre.find(' ') != string::npos || usuarioExiste(nombre));

    // Entrada de contraseña
    cout << "\t\tContrasena (minimo 8 caracteres): ";
    contrasena = leerPasswordSegura();
    while (contrasena.length() < 8) {
        cout << "\n\t\tLa contrasena debe tener al menos 8 caracteres!\n";
        cout << "\t\tContrasena: ";
        contrasena = leerPasswordSegura();
    }

    // Validación de nivel de acceso
    do {
        cout << "\n\t\tNivel de acceso (1-3): ";
        cin >> nivelAcceso;
        cin.ignore();
        if (nivelAcceso < 1 || nivelAcceso > 3) {
            cout << "\t\tNivel de acceso invalido!\n";
        }
    } while (nivelAcceso < 1 || nivelAcceso > 3);

    // Escribir en el archivo
    archivo << id << " " << nombre << " " << contrasena << " " << nivelAcceso << "\n";
    archivo.close();

    auditoria.insertar(nombre, "000", "REG-USER");
    cout << "\n\n\t\tUsuario registrado con exito!\n";
    system("pause");
}

bool usuarios::buscarUsuario(const string& user, const string& pass) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de usuarios!\n";
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string idArchivo, nombreArchivo, passArchivo;
        int nivelArchivo;

        if (ss >> idArchivo >> nombreArchivo >> passArchivo >> nivelArchivo) {
            if (nombreArchivo == user && passArchivo == pass) {
                id = idArchivo;
                nombre = nombreArchivo;
                contrasena = passArchivo;
                nivelAcceso = nivelArchivo;
                archivo.close();
                return true;
            }
        }
    }
    archivo.close();
    return false;
}

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
        cin.ignore();

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

void usuarios::consultarUsuarios() {
    system("cls");
    ifstream archivo("usuarios.txt");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| LISTADO DE USUARIOS - LOGISTICA      |" << endl;
    cout << "\t\t========================================" << endl;
    cout << "\t\t" << left << setw(10) << "ID" << setw(20) << "NOMBRE"
         << setw(15) << "NIVEL" << endl;

    if (!archivo.is_open()) {
        cout << "\t\tNo hay usuarios registrados." << endl;
    } else {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string idArchivo, nombreArchivo, passArchivo;
            int nivelArchivo;

            if (ss >> idArchivo >> nombreArchivo >> passArchivo >> nivelArchivo) {
                cout << "\t\t" << setw(10) << idArchivo
                     << setw(20) << nombreArchivo
                     << setw(15) << nivelArchivo << endl;
            }
        }
        archivo.close();
    }
    cout << "\t\t========================================" << endl;
    auditoria.insertar(this->nombre, "000", "CONS-USER");
    system("pause");
}

void usuarios::modificarUsuario() {
    system("cls");
    string idBuscar;
    cout << "\t\tIngrese ID del usuario a modificar: ";
    getline(cin, idBuscar);

    ifstream archivoEntrada("usuarios.txt");
    ofstream archivoTemp("temp.txt");

    if (!archivoEntrada.is_open() || !archivoTemp.is_open()) {
        cerr << "\t\tError al abrir archivos!\n";
        return;
    }

    string linea;
    bool encontrado = false;
    usuarios usuarioModificar;

    while (getline(archivoEntrada, linea)) {
        istringstream ss(linea);
        string idArchivo, nombreArchivo, passArchivo;
        int nivelArchivo;

        if (ss >> idArchivo >> nombreArchivo >> passArchivo >> nivelArchivo) {
            if (idArchivo == idBuscar) {
                encontrado = true;
                usuarioModificar.id = idArchivo;
                usuarioModificar.nombre = nombreArchivo;
                usuarioModificar.contrasena = passArchivo;
                usuarioModificar.nivelAcceso = nivelArchivo;

                // Mostrar datos actuales
                cout << "\n\t\tDatos actuales del usuario:\n";
                cout << "\t\tID: " << usuarioModificar.id << endl;
                cout << "\t\tNombre: " << usuarioModificar.nombre << endl;
                cout << "\t\tNivel acceso: " << usuarioModificar.nivelAcceso << endl;

                // Solicitar nuevos datos
                cout << "\n\t\tIngrese nuevos datos (deje en blanco para no modificar):\n";

                string nuevoNombre;
                cout << "\t\tNuevo nombre: ";
                getline(cin, nuevoNombre);
                if (!nuevoNombre.empty()) usuarioModificar.nombre = nuevoNombre;

                cout << "\t\tNueva contraseña: ";
                string nuevaPass = leerPasswordSegura();
                if (!nuevaPass.empty()) usuarioModificar.contrasena = nuevaPass;

                string nuevoNivel;
                cout << "\t\tNuevo nivel (1-3): ";
                getline(cin, nuevoNivel);
                if (!nuevoNivel.empty()) {
                    usuarioModificar.nivelAcceso = stoi(nuevoNivel);
                }

                // Escribir usuario modificado
                archivoTemp << usuarioModificar.id << " " << usuarioModificar.nombre << " "
                           << usuarioModificar.contrasena << " " << usuarioModificar.nivelAcceso << endl;
                continue;
            }
        }
        // Escribir línea original si no es el usuario a modificar
        archivoTemp << linea << endl;
    }

    archivoEntrada.close();
    archivoTemp.close();

    if (encontrado) {
        remove("usuarios.txt");
        rename("temp.txt", "usuarios.txt");
        auditoria.insertar(this->nombre, idBuscar, "MOD-USER");
        cout << "\t\tUsuario modificado con exito!\n";
    } else {
        remove("temp.txt");
        cout << "\t\tUsuario no encontrado!\n";
    }
    system("pause");
}

void usuarios::eliminarUsuario() {
    system("cls");
    string idEliminar;
    cout << "\t\tIngrese ID del usuario a eliminar: ";
    getline(cin, idEliminar);

    ifstream archivoEntrada("usuarios.txt");
    ofstream archivoTemp("temp.txt");

    if (!archivoEntrada.is_open() || !archivoTemp.is_open()) {
        cerr << "\t\tError al abrir archivos!\n";
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        istringstream ss(linea);
        string idArchivo, nombreArchivo, passArchivo;
        int nivelArchivo;

        if (ss >> idArchivo >> nombreArchivo >> passArchivo >> nivelArchivo) {
            if (idArchivo == idEliminar) {
                encontrado = true;
                continue; // No escribimos este registro
            }
        }
        // Escribir línea original si no es el usuario a eliminar
        archivoTemp << linea << endl;
    }

    archivoEntrada.close();
    archivoTemp.close();

    if (encontrado) {
        remove("usuarios.txt");
        rename("temp.txt", "usuarios.txt");
        auditoria.insertar(this->nombre, idEliminar, "DEL-USER");
        cout << "\t\tUsuario eliminado con exito!\n";
    } else {
        remove("temp.txt");
        cout << "\t\tUsuario no encontrado!\n";
    }
    system("pause");
}

// Getters
string usuarios::getNombre() const { return nombre; }
string usuarios::getId() const { return id; }
int usuarios::getNivelAcceso() const { return nivelAcceso; }

// Setters
void usuarios::setNivelAcceso(int nivel) { nivelAcceso = nivel; }
