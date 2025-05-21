#include "sistema.h"
#include "Opciones.h"
#include <conio.h>
#include <limits>
//Realizado por ANGEL ROQUEL
Opciones opcion; // Se crea un objeto global de la clase Opciones

sistema::sistema()
{

}

sistema::~sistema()
{

}

// Función para registrar un nuevo usuario
void sistema::registrarUsuario() {
    system("cls");       // Limpia la pantalla

    string nombre, contrasenia;  // Variables para guardar el nombre y la contraseña del usuario
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese nombre de usuario: ";
    getline(cin,nombre);  // Captura el nombre del usuario Corregido por Isaias Cedillo para obtener nombre completo del usuario

    cout << "Ingrese contrasenia: ";
    char caracter;       // Variable para leer carácter por carácter la contraseña

    // Captura la contraseña con ocultamiento visual (solo muestra '*')
    while ((caracter = _getch()) != '\r') { // Mientras no se presione Enter
        if (caracter == '\b') {             // Si se presiona retroceso
            if (!contrasenia.empty()) {     // Si la contraseña no está vacía
                cout << "\b \b";            // Borra un asterisco en pantalla
                contrasenia.pop_back();     // Elimina el último carácter de la contraseña
            }
        } else {
            contrasenia += caracter;        // Agrega el carácter a la contraseña
            cout << "*";                    // Muestra un asterisco
        }
    }
    cout << endl;  // Salto de línea al final de la contraseña

    ofstream archivo(archivoUsuarios, ios::app);  // Abre archivo para agregar usuarios
    if (archivo.is_open()) {
        archivo << nombre << "," << contrasenia << endl;  // Guarda el usuario y contraseña
        archivo.close();                                  // Cierra el archivo
        cout << "Usuario registrado con exito." << endl;  // Mensaje de éxito
    } else {
        cout << "No se pudo abrir el archivo." << endl;   // Error al abrir archivo
    }
}

// Función para ingresar (iniciar sesión) un usuario existente
void sistema::ingresarUsuario() {
    system("cls");       // Limpia la pantalla

    string nombre, contrasenia;  // Variables para ingresar datos del usuario

    cout << "Ingrese nombre de usuario: ";
    cin >> nombre;       // Captura el nombre

    cout << "Ingrese contrasenia: ";
    char caracter;

    // Captura oculta de contraseña
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

    ifstream archivo(archivoUsuarios);  // Abre el archivo de usuarios en modo lectura
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {      // Lee cada línea del archivo
            size_t coma = linea.find(",");     // Encuentra la posición de la coma
            string usuario = linea.substr(0, coma);             // Extrae el nombre de usuario
            string contraseniaArchivo = linea.substr(coma + 1); // Extrae la contraseña

            // Compara los datos ingresados con los del archivo
            if (usuario == nombre && contraseniaArchivo == contrasenia) {
                usuarioActual = nombre;
                cout << "Ingreso exitoso." << endl;
                archivo.close();      // Cierra el archivo
                opcion.menu(usuario);        // Llama al menú principal del sistema
                return;               // Sale de la función
            }
        }
        archivo.close();  // Cierra el archivo si no se encontró coincidencia
        cout << "Nombre de usuario o contrasena incorrecta." << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// Función para mostrar todos los usuarios registrados
void sistema::mostrarUsuarios() {
    system("cls");  // Limpia la pantalla

    ifstream archivo(archivoUsuarios);  // Abre el archivo en modo lectura
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {     // Lee línea por línea
            size_t coma = linea.find(",");    // Encuentra la coma
            string usuario = linea.substr(0, coma);            // Extrae el nombre de usuario
            string contrasenia = linea.substr(coma + 1);       // Extrae la contraseña

            string asteriscos(contrasenia.length(), '*');      // Crea una cadena de asteriscos del mismo largo

            // Muestra el usuario y su contraseña oculta
            cout << "Nombre de usuario: " << usuario << endl;
            cout << "Contrasenia: " << asteriscos << endl;
            cout << "===============================" << endl << endl;
        }
        archivo.close();  // Cierra el archivo después de leer
    } else {
        cout << "No se pudo abrir el archivo." << endl;  // Mensaje si el archivo no se puede abrir
    }
}
