// Programado por Priscila Sarai Guzmán Calgua 9959-23-450

#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <conio.h> // Para _getch()
#include <cstring> // Para strcpy, strcmp
#include <cstdlib> // Para system()

using namespace std;

// Objeto global de bitácora para registrar actividades de login
Bitacora bitacoralogUsuario;

// Definición del archivo binario de login
const string Usuario::ARCHIVO_LOGIN = "login.dat";

// Constructor por defecto
Usuario::Usuario() : nombreUsuario(""), contrasena("") {}

// Constructor con parámetros
Usuario::Usuario(const string& usuario, const string& contrasena)
    : nombreUsuario(usuario), contrasena(contrasena) {}

// Devuelve el nombre de usuario
string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}

// Devuelve la contraseña
string Usuario::getContrasena() const {
    return contrasena;
}

// Establece el nombre de usuario
void Usuario::setNombreUsuario(const string& usuario) {
    nombreUsuario = usuario;
}

// Establece la contraseña
void Usuario::setContrasena(const string& contrasena) {
    this->contrasena = contrasena;
}

// Establece el nombre del usuario autenticado (para bitácora)
void Usuario::setUsuario(const string& u) {
    usuario = u;
}

// Limpia la pantalla según el sistema operativo
void Usuario::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función para ocultar la contraseña mientras se escribe
string leerContrasenaOculta() {
    string contrasena;
    char tecla;
    while (true) {
        tecla = _getch();
        if (tecla == 13) break; // Enter
        else if (tecla == 8 && !contrasena.empty()) {
            contrasena.pop_back();
            cout << "\b \b"; // Borrar carácter en pantalla
        } else if (tecla != 8 && tecla != 13) {
            contrasena += tecla;
            cout << '*';
        }
    }
    cout << endl;
    return contrasena;
}

// Autenticación directa (comparación interna)
bool Usuario::autenticar(const string& usuario, const string& contrasena) const {
    return (this->nombreUsuario == usuario && this->contrasena == contrasena);
}

// Verifica usuario/contraseña desde el archivo binario login.dat
bool Usuario::autenticarDesdeArchivo(string& usuarioAutenticado) {
    limpiarPantalla();
    string usuarioIngresado, contrasenaIngresada;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n========== INICIO DE SESION ==========";
        cout << "\nUsuario: ";
        cin >> usuarioIngresado;
        cout << "Contraseña: ";
        contrasenaIngresada = leerContrasenaOculta();

        ifstream archivo(ARCHIVO_LOGIN, ios::binary);
        if (!archivo.is_open()) {
            cout << "\nError al abrir el archivo " << ARCHIVO_LOGIN << "\n";
            return false;
        }

        RegistroUsuario reg;
        // Recorre todos los registros del archivo
        while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(RegistroUsuario))) {
            if (usuarioIngresado == reg.nombreUsuario && contrasenaIngresada == reg.contrasena) {
                usuarioAutenticado = usuarioIngresado;
                cout << "\nInicio de sesión exitoso.\n";
                archivo.close();
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

// Registra un nuevo usuario en el archivo binario login.dat
string Usuario::registrarUsuario() {
    limpiarPantalla();
    string nuevoUsuario, nuevaContrasena;

    cout << "\n========== REGISTRO DE NUEVO USUARIO ==========";
    cout << "\nIngrese nombre de usuario: ";
    cin >> nuevoUsuario;
    cout << "Ingrese contraseña: ";
    nuevaContrasena = leerContrasenaOculta();

    // Crear estructura con datos de longitud fija
    RegistroUsuario reg;
    strncpy(reg.nombreUsuario, nuevoUsuario.c_str(), sizeof(reg.nombreUsuario));
    reg.nombreUsuario[sizeof(reg.nombreUsuario) - 1] = '\0'; // Seguridad
    strncpy(reg.contrasena, nuevaContrasena.c_str(), sizeof(reg.contrasena));
    reg.contrasena[sizeof(reg.contrasena) - 1] = '\0';

    ofstream archivo(ARCHIVO_LOGIN, ios::binary | ios::app);
    if (!archivo.is_open()) {
        cout << "\nError al abrir el archivo " << ARCHIVO_LOGIN << " para escritura.\n";
        return "";
    }

    archivo.write(reinterpret_cast<const char*>(&reg), sizeof(RegistroUsuario));
    archivo.close();

    cout << "\nUsuario registrado con éxito.\n";
    cout << "\nPresione Enter para continuar";
    cin.ignore();
    cin.get();
    limpiarPantalla();

    return nuevoUsuario;
}

// Pausa para permitir que el usuario lea un mensaje antes de continuar
void Usuario::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Muestra menú de autenticación (inicio de sesión o registro)
bool Usuario::menuAutenticacion(string& usuarioAutenticado) {
    int opcion;
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
                    bitacoralogUsuario.insertar(usuarioAutenticado, 1000, "Usuario", "Inicio de sesión exitoso");
                    return true;
                }
                bitacoralogUsuario.insertar("Desconocido", 4902, "Usuario", "Intento de inicio de sesión fallido");
                break;

            case 2: {
                string nuevoUsuario = registrarUsuario();
                if (!nuevoUsuario.empty()) {
                    bitacoralogUsuario.insertar(nuevoUsuario, 1001, "Usuario", "Registro de nuevo usuario");
                }
                break;
            }

            case 3:
                cout << "\nSaliendo...\n";
                return false;

            default:
                cout << "\nOpción no válida.\n";
                break;
        }
    } while (true);

    return false;
}
