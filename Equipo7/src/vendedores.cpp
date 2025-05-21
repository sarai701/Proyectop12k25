//STEVEN ANDRE VASQUEZ CHAVEZ 9959 24 11528

#include "Vendedores.h"
#include <iostream>
#include <iomanip>  // Para formato de impresión (setw, etc.)
#include <cstdlib>  // Para system("cls")
#include "encabezado.h"

using namespace std;

// Inicialización de la variable estática 'vendedores' para almacenar los vendedores registrados.
vector<Vendedores> Vendedores::vendedores;

// Inicialización del contador de vendedores para generar códigos de forma automática, comenzando desde 100.
int Vendedores::contadorVendedores = 100;

// Constructor por defecto de la clase Vendedores (no realiza ninguna acción).
Vendedores::Vendedores() {}

// Constructor parametrizado para crear un nuevo vendedor con su nombre, teléfono y código.
Vendedores::Vendedores(string n, string t, string cod)
    : nombre(n), telefono(t), codigo(cod) {}

// Método estático para obtener la lista de vendedores registrados.
std::vector<Vendedores>& Vendedores::obtenerVendedores() {
    return vendedores;
}

// Menú principal para interactuar con los vendedores, permite agregar, modificar, eliminar y salir.
void Vendedores::MenuVendedores() {
    int opcion;
    do {
        system("cls"); // Limpia la pantalla en cada ciclo
        // Muestra el menú de opciones
        cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
        cout << "\t\t\t |---------------------------|\n";
        cout << "\t\t\t |   SISTEMA DE VENDEDORES   |\n";
        cout << "\t\t\t |---------------------------|\n";
        cout << "\t\t\t | 1. AGREGAR VENDEDOR       |\n";
        cout << "\t\t\t | 2. MODIFICAR VENDEDOR     |\n";
        cout << "\t\t\t | 3. ELIMINAR VENDEDOR      |\n";
        cout << "\t\t\t | 4. SALIR                  |\n";
        cout << "\t\t\t |---------------------------|\n";
        cout << "\t\t\tIngresa tu opcion: ";
        cin >> opcion;

        // Ejecuta la opción seleccionada
        switch (opcion) {
            case 1:
                AgregarVendedor();  // Agregar un nuevo vendedor
                break;
            case 2:
                ModificarVendedor();  // Modificar la información de un vendedor
                break;
            case 3:
                EliminarVendedor();  // Eliminar un vendedor
                break;
            case 4:
                return;  // Salir del menú
            default:
                cout << "\n\t\t\t Opcion invalida... Por favor intenta otra vez...\n";
                cin.ignore(); // Ignora los caracteres de nueva línea
                cin.get();    // Espera una entrada para continuar
        }
    } while (opcion != 5);  // Bucle que se repite hasta que se seleccione la opción de salir
}

// Método para agregar un nuevo vendedor al sistema.
void Vendedores::AgregarVendedor() {
    system("cls"); // Limpia la pantalla
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
    cout << "\t\t\t---------------------\n";
    cout << "\t\t\t |   NUEVO VENDEDOR  |\n";
    cout << "\t\t\t----------------------\n";

    string nombre, telefono;
    // Genera automáticamente un código único para el nuevo vendedor.
    string codigo = to_string(contadorVendedores++);

    // Solicita los datos del nuevo vendedor
    cout << "\t\t\tIngrese el nombre del vendedor: ";
    cin.ignore(); // Ignora el salto de línea anterior
    getline(cin, nombre); // Lee el nombre completo del vendedor
    cout << "\t\t\tIngrese el numero telefonico del vendedor: ";
    cin >> telefono; // Lee el teléfono del vendedor

    // Agrega el nuevo vendedor al vector de vendedores
    vendedores.push_back(Vendedores(nombre, telefono, codigo));
    cout << "\t\t\tVendedor agregado exitosamente.\n";

    cout << "\t\t\t Presione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Método para modificar la información de un vendedor existente.
void Vendedores::ModificarVendedor() {
    system("cls"); // Limpia la pantalla
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
    cout << "\t\t\t------------------------\n";
    cout << "\t\t\t |   MODIFICAR VENDEDOR |\n";
    cout << "\t\t\t------------------------\n";

    string codigoBuscado;
    // Solicita el código del vendedor a modificar
    cout << "\t\t\tIngrese el codigo del vendedor a modificar: ";
    cin >> codigoBuscado;

    // Busca el vendedor por código y permite modificar su información
    for (auto& vendedor : vendedores) {
        if (vendedor.codigo == codigoBuscado) {
            cout << "\t\t\tVendedor encontrado:\n";
            cout << "\t\t\tNombre: " << vendedor.nombre << "\n";
            cout << "\t\t\tTelefono: " << vendedor.telefono << "\n";

            // Permite modificar el nombre o teléfono del vendedor
            cout << "\n\t\t\tQue desea modificar?\n";
            cout << "\t\t\t1. Nombre\n";
            cout << "\t\t\t2. Telefono\n";
            int opcion;
            cin >> opcion;

            if (opcion == 1) {
                cout << "\t\t\tIngrese nuevo nombre: ";
                cin.ignore(); // Limpia el buffer de entrada
                getline(cin, vendedor.nombre); // Modifica el nombre
            } else if (opcion == 2) {
                cout << "\t\t\tIngrese nuevo telefono: ";
                cin >> vendedor.telefono; // Modifica el teléfono
            } else {
                cout << "\t\t\tOpcion invalida.\n";
            }

            cout << "\t\t\tVendedor modificado exitosamente.\n";
            break;
        }
    }

    cout << "\t\t\t Presione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Método para eliminar un vendedor del sistema.
void Vendedores::EliminarVendedor() {
    system("cls"); // Limpia la pantalla
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
    cout << "\t\t\t---------------------\n";
    cout << "\t\t\t |   ELIMINAR VENDEDOR |\n";
    cout << "\t\t\t----------------------\n";

    string codigoBuscado;
    // Solicita el código del vendedor a eliminar
    cout << "\t\t\tIngrese el codigo del vendedor a eliminar: ";
    cin >> codigoBuscado;

    // Busca y elimina el vendedor por código
    for (auto it = vendedores.begin(); it != vendedores.end(); ++it) {
        if (it->codigo == codigoBuscado) {
            vendedores.erase(it); // Elimina el vendedor
            cout << "\t\t\tVendedor eliminado exitosamente.\n";
            break;
        }
    }

    cout << "\nPresione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Método para mostrar todos los vendedores registrados en el sistema.
void Vendedores::MostrarVendedores() {
    system("cls"); // Limpia la pantalla
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
    cout << "\t\t\t------------------------------\n";
    cout << "\t\t\t|   REGISTRO DE VENDEDORES   |\n";
    cout << "\t\t\t------------------------------\n";

    // Verifica si hay vendedores registrados
    if (vendedores.empty()) {
        cout << "\t\t\tNo hay vendedores registrados.\n";
    } else {
        // Muestra la información de cada vendedor en formato de tabla
        cout << left << setw(10) << "Codigo" << setw(20) << "Nombre" << setw(15) << "Telefono" << "\n";
        cout << "--------------------------------------------------\n";

        for (const auto& vendedor : vendedores) {
            cout << left << setw(10) << vendedor.codigo << setw(20) << vendedor.nombre << setw(15) << vendedor.telefono << "\n";
        }
    }

    cout << "\t\t\tPresione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}
