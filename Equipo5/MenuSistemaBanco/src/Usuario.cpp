//Programado por Priscila Sarai Guzmán Calgua 9959-23-450
#include "Usuario.h"
#include <iostream>
#include <fstream> //Librería para archivos de lectura o escritura
#include <conio.h>// Se usa _getch() para ocultar la contraseña mientras se escribe
#include <cstdlib>
//Objeto global de tipo Botacora para registrar inicio de sesión
Bitacora bitacoralog2;
using namespace std;

//Definición de la constante que representa el archivo de login
const string Usuario::ARCHIVO_LOGIN = "login.txt";
//Constructor por defecto
Usuario::Usuario() : nombreUsuario(""), contrasena("") {} //Inicializa las variables de nombre de usuario y contraseña como vacías
//Inicializa el nombre usuario y contraseña
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

//Método para obtener el nombre del usuario
string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}
//Método para obtener la contraseña
string Usuario::getContrasena() const {
    return contrasena;
}
//Método para crear un nuevo usuario
void Usuario::setNombreUsuario(const string& usuario) {
    nombreUsuario = usuario;
}
//para crear una nueva contraseña
void Usuario::setContrasena(const string& contrasena) {
    this->contrasena = contrasena;
}

void Usuario::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función para leer la contraeña de forma oculta
string leerContrasenaOculta() {
    string contrasena;//Variable que almacena la contraeña
    char tecla;//Variable para almacenar cada tecla
    while (true) {
        tecla = _getch();//Leee la tecla sin mostrarla
        if (tecla == 13) break;//Si da enter se termina la lectura
        else if (tecla == 8 && !contrasena.empty()) { //si la contraseña no esta vacía y si es retroceso
            contrasena.pop_back();//Elimina el ultimo caracter de la contraseña
            cout << "\b \b";//Borra el caracter en pantalla (retroceso)
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*';
        }
    }
    cout << endl;
    return contrasena;//Devuelve la contraseña oculta
}
// Método para autenticar al usuario comparando el nombre de usuario y la contraseña ingresada
bool Usuario::autenticar(const string& usuario, const string& contrasena) const {
    return (this->nombreUsuario == usuario && this->contrasena == contrasena);
}
// Método para autenticar al usuario desde un archivo de texto (login.txt)
bool Usuario::autenticarDesdeArchivo(string& usuarioAutenticado) {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;
 // Bucle que se ejecuta mientras haya intentos disponibles
    while (intentos > 0) {
        cout << "\n========== INICIO DE SESION ==========";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contraseña: ";
        contrasenaIngresada = leerContrasenaOculta();

        ifstream archivo("login.txt");//Abre el archivo de login.txt para leer los usuarios registrados
        if (!archivo.is_open()) {
            cout << "\nError al abrir el archivo login.txt\n";
            return false;
        }

        string user, pass;
// Bucle que recorre todos los usuarios y contraseñas del archivo
        while (archivo >> user >> pass) {
            Usuario usuario(user, pass); // Crea un objeto Usuario con los datos del archivo
            if (usuario.autenticar(usuarioIngresado, contrasenaIngresada)) { // Si coinciden
                usuarioAutenticado = usuarioIngresado; // Guarda el nombre del usuario autenticado
                cout << "\nInicio de sesión exitoso.\n";
                archivo.close(); // Cierra el archivo
                cout << "\nPresione una tecla para continuar";
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
//Método para registrar un nuevo usuario en el archivo de login.txt
bool Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n========== REGISTRO DE NUEVO USUARIO ==========";
    cout << "\nIngrese nombre de usuario: ";
    cin >> nuevoUsuario;
    cout << "Ingrese contraseña: ";
    nuevaContrasena = leerContrasenaOculta();

    ofstream archivo("login.txt", ios::app); // Abre el archivo login.txt en modo "append" para agregar un nuevo usuario
    if (!archivo.is_open()) {
        cout << "\nError al abrir el archivo login.txt para escribir.\n";
        return false;
    }

    // Escribe el nuevo usuario y su contraseña en el archivo
    archivo << nuevoUsuario << " " << nuevaContrasena << endl;
    archivo.close();
    cout << "\nUsuario registrado con éxito.\n";
    cout << "\nPresione Enter para continuar";
    cin.ignore();
    cin.get();
    limpiarPantalla();
    return true;
}

// Menú de autenticación que permite al usuario elegir entre iniciar sesión, registrarse o salir
bool Usuario::menuAutenticacion(string& usuarioAutenticado) {
    int opcion; // Variable para almacenar la opción seleccionada por el usuario
    do {
        limpiarPantalla();
        cout << "\n===== SISTEMA DE ACCESO =====";
        cout << "\n1. Iniciar sesión";
        cout << "\n2. Registrar nuevo usuario";
        cout << "\n3. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (autenticarDesdeArchivo(usuarioAutenticado)) {
                    return true;
                }
                break;

            case 2:
                registrarUsuario(); // Llama al método para registrar un nuevo usuario
                break;

            case 3:
                cout << "\nSaliendo...\n";
                return false;
                break;

            default:
                cout << "\nOpción no válida.\n";
                break;
        }
    } while (true);

    return false;
}
