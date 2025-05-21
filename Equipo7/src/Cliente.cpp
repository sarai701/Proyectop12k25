//Maria Celeste Mayen Ibarra  9959-23-3775
#include "Cliente.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "encabezado.h" //Marlon De Leon 5001

using namespace std;

// Inicialización de variables estáticas
vector<Cliente> Cliente::clientes; // Vector que almacena los clientes
int Cliente::contadorClientes = 200;  // Código inicial modificado para los clientes

// Constructor por defecto
Cliente::Cliente() {}

// Constructor con parámetros para inicializar un cliente
Cliente::Cliente(string n, string t, string nit, string cod)
    : nombre(n), telefono(t), nit(nit), codigo(cod) {}

// Método para obtener la lista de clientes
std::vector<Cliente>& Cliente::obtenerClientes() {
    return clientes;
}

// Método que muestra el menú de opciones para gestionar clientes
void Cliente::MenuClientes() {
    int opcion;
    do {
        system("cls"); // Limpia la pantalla
        cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
        cout << "\n\t\t\t---------------------------\n";
        cout << "\t\t\t |   SISTEMA DE CLIENTES  |\n";
        cout << "\t\t\t---------------------------\n";
        cout << "\t\t\t 1. NUEVO CLIENTE\n";
        cout << "\t\t\t 2. MODIFICAR CLIENTE\n";
        cout << "\t\t\t 3. ELIMINAR CLIENTE\n";
        cout << "\t\t\t 4. SALIR\n";
        cout << "\t\t\t-------------------------------\n";
        cout << "\t\t\tIngresa tu opcion: ";
        cin >> opcion;

        // Manejo de opciones del menú
        switch (opcion) {
            case 1:
                AgregarCliente(); // Agregar un nuevo cliente
                break;
            case 2:
                ModificarCliente(); // Modificar un cliente existente
                break;
            case 3:
                EliminarCliente(); // Eliminar un cliente
                break;
            case 4:
                return; // Salir del menú
            default:
                cout << "\n\t\t\t Opción inválida...Intente otra vez...\n";
                cin.ignore();
                cin.get();
        }
    } while (opcion != 4); // Repite hasta que se elija salir
}

// Método para agregar un nuevo cliente
void Cliente::AgregarCliente() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t---------------------\n";
    cout << "\t\t\t |   NUEVO CLIENTE   |\n";
    cout << "\t\t\t----------------------\n";

    // Verifica si se ha alcanzado el límite de clientes
    if (contadorClientes > 300) {
        cout << "\t\t\tLímite de clientes alcanzado.\n";
        return;
    }

    string nombre, telefono, nit;
    string codigo = to_string(contadorClientes++); // Genera un nuevo código para el cliente

    // Solicita información del cliente
    cout << "\t\t\tIngrese el nombre del cliente: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\t\t\tIngrese el número telefonico del cliente: ";
    cin >> telefono;
    cout << "\t\t\tIngrese el numero de NIT del cliente: ";
    cin >> nit;

    // Agrega el nuevo cliente al vector
    clientes.push_back(Cliente(nombre, telefono, nit, codigo));
    GuardarClientes(); // Guarda la lista de clientes en un archivo
    cout << "\t\t\tCliente agregado exitosamente.\n";

    cout << "\nPresione ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

// Método para modificar un cliente existente
void Cliente::ModificarCliente() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t--------------------------\n";
    cout << "\t\t\t |   MODIFICAR CLIENTE   |\n";
    cout << "\t\t\t--------------------------\n";

    string codigoBuscado;
    cout << "\t\t\tIngrese el código del cliente a modificar: ";
    cin >> codigoBuscado;

    // Busca el cliente por su código
    for (auto& cliente : clientes) {
        if (cliente.codigo == codigoBuscado) {
            // Muestra la información del cliente encontrado
            cout << "\t\t\tCliente encontrado:\n";
            cout << "\t\t\tNombre: " << cliente.nombre << "\n";
            cout << "\t\t\tTelefono: " << cliente.telefono << "\n";
            cout << "\t\t\tNIT: " << cliente.nit << "\n";

            // Solicita qué información desea modificar
            cout << "\t\t\t¿Que desea modificar?\n";
            cout << "\t\t\t1. Telefono\n";
            cout << "\t\t\t2. NIT\n";
            int opcion;
            cin >> opcion;

            // Modifica la información según la opción elegida
            if (opcion == 1) {
                cout << "\t\t\tIngrese nuevo número telefonico: ";
                cin >> cliente.telefono;
            } else if (opcion == 2) {
                cout << "\t\t\tIngrese nuevo NIT: ";
                cin >> cliente.nit;
            } else {
                cout << "\t\t\tOpcion inválida.\n";
            }

            GuardarClientes(); // Guarda los cambios en el archivo
            cout << "\t\t\tCliente modificado exitosamente.\n";
            break;
        }
    }

    cout << "\t\t\tPresione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Método para eliminar un cliente
void Cliente::EliminarCliente() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\t\t\t-------------------------\n";
    cout << "\t\t\t |   ELIMINAR CLIENTE   |\n";
    cout << "\t\t\t-------------------------\n";

    string codigoBuscado;
    cout << "\t\t\tIngrese el codigo del cliente a eliminar: ";
    cin >> codigoBuscado;

    // Busca el cliente por su código y lo elimina
    for (auto it = clientes.begin(); it != clientes.end(); ++it) {
        if (it->codigo == codigoBuscado) {
            clientes.erase(it); // Elimina el cliente del vector
            GuardarClientes(); // Guarda los cambios en el archivo
            cout << "\t\t\tCliente eliminado exitosamente.\n";
            break;
        }
    }

    cout << "\t\t\tPresione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Método para mostrar todos los clientes registrados
void Cliente::MostrarClientes() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t----------------------------\n";
    cout << "\t\t\t |   REGISTRO DE CLIENTE   |\n";
    cout << "\t\t\t----------------------------\n";

    // Verifica si hay clientes registrados
    if (clientes.empty()) {
        cout << "\t\t\tNo hay clientes registrados.\n";
    } else {
        // Muestra la lista de clientes en formato tabular
        cout << left << setw(10) << "Codigo" << setw(20) << "Nombre"
             << setw(15) << "Telefono" << setw(15) << "NIT" << "\n";
        cout << "-------------------------------------------------------------\n";

        for (const auto& cliente : clientes) {
            cout << left << setw(10) << cliente.codigo
                 << setw(20) << cliente.nombre
                 << setw(15) << cliente.telefono
                 << setw(15) << cliente.nit << "\n";
        }
    }

    cout << "\t\t\tPresione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Método para guardar la lista de clientes en un archivo
void Cliente::GuardarClientes() {
    ofstream archivo("clientes.dat", ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }
    // Escribe cada cliente en el archivo
    for (const auto& cliente : clientes) {
        archivo.write(reinterpret_cast<const char*>(&cliente), sizeof(Cliente));
    }
    archivo.close(); // Cierra el archivo
}

// Método para cargar la lista de clientes desde un archivo
void Cliente::CargarClientes() {
    ifstream archivo("clientes.dat", ios::binary);
    if (!archivo) return; // Si no se puede abrir el archivo, retorna

    Cliente cliente;
    // Lee cada cliente del archivo y lo agrega al vector
    while (archivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        clientes.push_back(cliente);
    }
    archivo.close(); // Cierra el archivo
}
