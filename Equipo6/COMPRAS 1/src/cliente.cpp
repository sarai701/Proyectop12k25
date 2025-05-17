#include "cliente.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

string generarIdCliente() {
    static int counter = 0;
    stringstream ss;
    ss << "CLI-" << setw(4) << setfill('0') << ++counter;
    return ss.str();
}

void guardarClientes(const vector<Cliente>& clientes) {
    ofstream archivo("clientes.txt");
    if (archivo.is_open()) {
        for (const auto& cliente : clientes) {
            archivo << cliente.id << "|"
                    << cliente.nombre << "|"
                    << cliente.telefono << "|"
                    << cliente.email << "\n";
        }
        archivo.close();
    }
}

vector<Cliente> cargarClientes() {
    vector<Cliente> clientes;
    ifstream archivo("clientes.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Cliente cliente;

        getline(ss, cliente.id, '|');
        getline(ss, cliente.nombre, '|');
        getline(ss, cliente.telefono, '|');
        getline(ss, cliente.email);

        clientes.push_back(cliente);
    }

    return clientes;
}

void ingresarCliente() {
    Cliente nuevo;
    nuevo.id = generarIdCliente();

    cout << "\n--- REGISTRAR CLIENTE ---\n";
    cout << "ID: " << nuevo.id << endl;
    cout << "Nombre: ";
    getline(cin, nuevo.nombre);
    cout << "Teléfono: ";
    getline(cin, nuevo.telefono);
    cout << "Email: ";
    getline(cin, nuevo.email);

    vector<Cliente> clientes = cargarClientes();
    clientes.push_back(nuevo);
    guardarClientes(clientes);

    cout << "✔ Cliente registrado\n";
}

void consultarClientes() {
    vector<Cliente> clientes = cargarClientes();

    cout << "\n--- LISTA DE CLIENTES ---\n";
    if (clientes.empty()) {
        cout << "No hay clientes registrados\n";
        return;
    }

    for (const auto& cliente : clientes) {
        cout << "ID: " << cliente.id << "\n"
             << "Nombre: " << cliente.nombre << "\n"
             << "Teléfono: " << cliente.telefono << "\n"
             << "Email: " << cliente.email << "\n\n";
    }
}

void modificarCliente() {
    consultarClientes();
    vector<Cliente> clientes = cargarClientes();

    if (clientes.empty()) return;

    string id;
    cout << "Ingrese ID del cliente a modificar: ";
    getline(cin, id);

    auto it = find_if(clientes.begin(), clientes.end(),
        [&id](const Cliente& c) { return c.id == id; });

    if (it == clientes.end()) {
        cerr << "❌ Cliente no encontrado\n";
        return;
    }

    cout << "Nuevo nombre [" << it->nombre << "]: ";
    getline(cin, it->nombre);
    cout << "Nuevo teléfono [" << it->telefono << "]: ";
    getline(cin, it->telefono);
    cout << "Nuevo email [" << it->email << "]: ";
    getline(cin, it->email);

    guardarClientes(clientes);
    cout << "✔ Cliente actualizado\n";
}

void borrarCliente() {
    consultarClientes();
    vector<Cliente> clientes = cargarClientes();

    if (clientes.empty()) return;

    string id;
    cout << "Ingrese ID del cliente a eliminar: ";
    getline(cin, id);

    clientes.erase(remove_if(clientes.begin(), clientes.end(),
        [&id](const Cliente& c) { return c.id == id; }), clientes.end());

    guardarClientes(clientes);
    cout << "✔ Cliente eliminado\n";
}
