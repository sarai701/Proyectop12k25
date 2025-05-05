#include "sistema.h"
#include "Opciones.h"
Opciones opcion;
sistema::sistema()
{
    //ctor
}
sistema::~sistema()
{
    //dtor
}
void sistema::registrarUsuario() //Metodo para registrar usuario nuevo
{
    string nombre, contrasenia;
    cout << "Ingrese nombre de usuario: ";
    cin >> nombre;
    cout << "Ingrese contrasenia: ";
    cin >> contrasenia;

    ofstream archivo(archivoUsuarios, ios::app);
    if (archivo.is_open()) {
        archivo << nombre << "," << contrasenia << endl;
        archivo.close();
        cout << "Usuario registrado con exito." << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void sistema::ingresarUsuario() //Metodo para ingresar
{
    string nombre, contrasenia;
    cout << "Ingrese nombre de usuario: ";
    cin >> nombre;
    cout << "Ingrese contrasenia: ";
    cin >> contrasenia;

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

void sistema::mostrarUsuarios() //Metodo para mostrar la lista de los usuarios-ANGEL ROQUEL
{
    ifstream archivo(archivoUsuarios);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            size_t coma = linea.find(",");
            string usuario = linea.substr(0, coma);
            cout << "Nombre de usuario: " << usuario << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    }

