//Programaddo por Priscila Sarai Guzm�n Calgua 9959-23-450
#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <conio.h> // Para leer contrase�as ocultas con '*'
#include <cstdlib>

using namespace std;

// Constructor por defecto
Usuario::Usuario() : nombreUsuario(""), contrasena("") {}

// Constructor con par�metros
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

// Devuelve el nombre de usuario
string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}

// Devuelve la contrase�a
string Usuario::getContrasena() const {
    return contrasena;
}

// Asigna un nuevo nombre de usuario
void Usuario::setNombreUsuario(const string& usuario) {
    nombreUsuario = usuario;
}

// Asigna una nueva contrase�a
void Usuario::setContrasena(const string& contrasena) {
    this->contrasena = contrasena;
}

// Funci�n para limpiar pantalla (compatible con Windows y Unix)
void Usuario::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar();  // Declaraci�n si viene de otro archivo

// Verifica si el nombre de usuario y la contrase�a coinciden con los almacenados
bool Usuario::autenticar(const string& usuario, const string& contrasena) const {
    return (this->nombreUsuario == usuario && this->contrasena == contrasena);
}

// Funci�n auxiliar que lee la contrase�a sin mostrarla en pantalla
string leerContrasenaOculta() {
    string contrasena;
    char tecla;
    while (true) {
        tecla = _getch();
        if (tecla == 13) break; // Enter
        else if (tecla == 8 && !contrasena.empty()) {
            contrasena.pop_back();
            cout << "\b \b";
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*';
        }
    }
    cout << endl;
    return contrasena;
}

// M�todo est�tico para iniciar sesi�n desde archivo
// Definici�n de la funci�n autenticarDesdeArchivo
bool Usuario::autenticarDesdeArchivo() {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n========== INICIO DE SESION ==========";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contrase�a: ";
        contrasenaIngresada = leerContrasenaOculta();

        ifstream archivo("login.txt");
        if (!archivo.is_open()) {
            cout << "\nError al abrir el archivo login.txt\n";
            return false;
        }

        string user, pass;
        while (archivo >> user >> pass) {
            Usuario usuario(user, pass);
            if (usuario.autenticar(usuarioIngresado, contrasenaIngresada)) {
                cout << "\nInicio de sesi�n exitoso.\n";
                archivo.close();
                cout <<"\nPresione una tecla para continuar";
                cin.ignore();
                cin.get();
                limpiarPantalla();
                return true;
            }
        }
        archivo.close();

        intentos--;
        cout << "\nUsuario o contrase�a incorrectos. Intentos restantes: " << intentos << endl;
    }

    cout << "\nDemasiados intentos fallidos. Acceso denegado.\n";
    return false;
}


// M�todo est�tico para registrar un nuevo usuario en el archivo login.txt
bool Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n========== REGISTRO DE NUEVO USUARIO ==========";
    cout << "\nIngrese nombre de usuario: ";
    cin >> nuevoUsuario;
    cout << "Ingrese contrase�a: ";
    nuevaContrasena = leerContrasenaOculta();

    ofstream archivo("login.txt", ios::app);
    if (!archivo.is_open()) {
        cout << "\nError al abrir el archivo login.txt para escribir.\n";
        return false;
    }

    archivo << nuevoUsuario << " " << nuevaContrasena << endl;
    archivo.close();

    cout << "\nUsuario registrado con �xito.\n";
    cout <<"\nPresione Enter para continuar";
    cin.ignore();
    cin.get();
    limpiarPantalla();
    return true;
}

bool Usuario::menuAutenticacion() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n===== SISTEMA DE ACCESO =====";
        cout << "\n1. Iniciar sesi�n";
        cout << "\n2. Registrar nuevo usuario";
        cout << "\n3. Salir";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Llamamos a la funci�n que maneja el inicio de sesi�n
                if (autenticarDesdeArchivo()) {
                    return true;  // Si el usuario se autentica correctamente, retorna true
                }
                break;

            case 2:
                // Permite registrar un nuevo usuario
                registrarUsuario();
                break;

            case 3:
                cout << "\nSaliendo...\n";
                return false;  // Si el usuario decide salir, retorna false

            default:
                cout << "\nOpci�n inv�lida.\n";

        }
    } while (true);

    return false;  // En caso de que el ciclo termine sin �xito
}
const string Usuario::ARCHIVO_LOGIN = "login.txt"; // Definici�n de archivo
