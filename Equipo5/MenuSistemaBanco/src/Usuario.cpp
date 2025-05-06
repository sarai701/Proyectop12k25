//Programaddo por Priscila Sarai Guzmán Calgua 9959-23-450
#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <conio.h> // Para leer contraseñas ocultas con '*'
#include <cstdlib>

using namespace std;

// Constructor por defecto
Usuario::Usuario() : nombreUsuario(""), contrasena("") {}

// Constructor con parámetros
Usuario::Usuario(const std::string& usuario, const std::string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

// Devuelve el nombre de usuario
std::string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}

// Devuelve la contraseña
std::string Usuario::getContrasena() const {
    return contrasena;
}

// Asigna un nuevo nombre de usuario
void Usuario::setNombreUsuario(const std::string& usuario) {
    nombreUsuario = usuario;
}

// Asigna una nueva contraseña
void Usuario::setContrasena(const std::string& contrasena) {
    this->contrasena = contrasena;
}

// Función para limpiar pantalla (compatible con Windows y Unix)
void Usuario::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar();  // Declaración si viene de otro archivo

// Verifica si el nombre de usuario y la contraseña coinciden con los almacenados
bool Usuario::autenticar(const std::string& usuario, const std::string& contrasena) const {
    return (this->nombreUsuario == usuario && this->contrasena == contrasena);
}

// Función auxiliar que lee la contraseña sin mostrarla en pantalla
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

// Método estático para iniciar sesión desde archivo
// Definición de la función autenticarDesdeArchivo
bool Usuario::autenticarDesdeArchivo() {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n========== INICIO DE SESION ==========";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contraseña: ";
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
                cout << "\nInicio de sesión exitoso.\n";
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
        cout << "\nUsuario o contraseña incorrectos. Intentos restantes: " << intentos << endl;
    }

    cout << "\nDemasiados intentos fallidos. Acceso denegado.\n";
    return false;
}


// Método estático para registrar un nuevo usuario en el archivo login.txt
bool Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n========== REGISTRO DE NUEVO USUARIO ==========";
    cout << "\nIngrese nombre de usuario: ";
    cin >> nuevoUsuario;
    cout << "Ingrese contraseña: ";
    nuevaContrasena = leerContrasenaOculta();

    ofstream archivo("login.txt", ios::app);
    if (!archivo.is_open()) {
        cout << "\nError al abrir el archivo login.txt para escribir.\n";
        return false;
    }

    archivo << nuevoUsuario << " " << nuevaContrasena << endl;
    archivo.close();

    cout << "\nUsuario registrado con éxito.\n";
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
        std::cout << "\n===== SISTEMA DE ACCESO =====";
        std::cout << "\n1. Iniciar sesión";
        std::cout << "\n2. Registrar nuevo usuario";
        std::cout << "\n3. Salir";
        std::cout << "\nSeleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                // Llamamos a la función que maneja el inicio de sesión
                if (autenticarDesdeArchivo()) {
                    return true;  // Si el usuario se autentica correctamente, retorna true
                }
                break;

            case 2:
                // Permite registrar un nuevo usuario
                registrarUsuario();
                break;

            case 3:
                std::cout << "\nSaliendo...\n";
                return false;  // Si el usuario decide salir, retorna false

            default:
                std::cout << "\nOpción inválida.\n";

        }
    } while (true);

    return false;  // En caso de que el ciclo termine sin éxito
}
const std::string Usuario::ARCHIVO_LOGIN = "login.txt"; // Definición de archivo
