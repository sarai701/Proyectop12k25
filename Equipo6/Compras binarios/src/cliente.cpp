#include "cliente.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

// Función XOR para encriptar/desencriptar
string xorEncryptDecrypt(const string& texto, char clave = 'K') {
    string resultado = texto;
    for (char& c : resultado) {
        c ^= clave;
    }
    return resultado;
}

// Constructor por defecto
Cliente::Cliente() : id(""), nombre(""), telefono(""), email("") {}

// Constructor con parámetros
Cliente::Cliente(const string& _id, const string& _nombre, const string& _telefono, const string& _email)
    : id(_id), nombre(_nombre), telefono(_telefono), email(_email) {}

// Setters
void Cliente::setId(const string& _id) { id = _id; }
void Cliente::setNombre(const string& _nombre) { nombre = _nombre; }
void Cliente::setTelefono(const string& _telefono) { telefono = _telefono; }
void Cliente::setEmail(const string& _email) { email = _email; }

// Getters
string Cliente::getId() const { return id; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getEmail() const { return email; }

// Mostrar datos
void Cliente::mostrar() const {
    cout << "ID: " << id << "\n"
         << "Nombre: " << nombre << "\n"
         << "Teléfono: " << telefono << "\n"
         << "Email: " << email << "\n";
}

// Generador de ID
string generarIdCliente() {
    static int counter = 0;
    stringstream ss;
    ss << "CLI-" << setw(4) << setfill('0') << ++counter;
    return ss.str();
}

// Guardar en archivo binario con cifrado
void guardarClientes(const vector<Cliente>& clientes) {
    ofstream archivo("clientes.dat", ios::binary);
    if (archivo.is_open()) {
        for (const auto& cliente : clientes) {
            string linea = cliente.getId() + "|" + cliente.getNombre() + "|" + cliente.getTelefono() + "|" + cliente.getEmail();
            string cifrado = xorEncryptDecrypt(linea);
            size_t longitud = cifrado.size();
            archivo.write(reinterpret_cast<const char*>(&longitud), sizeof(longitud));
            archivo.write(cifrado.c_str(), longitud);
        }
        archivo.close();
    } else {
        cerr << "❌ No se pudo abrir el archivo para guardar.\n";
    }
}

// Cargar desde archivo binario y desencriptar
vector<Cliente> cargarClientes() {
    vector<Cliente> clientes;
    ifstream archivo("clientes.dat", ios::binary);
    if (!archivo.is_open()) return clientes;

    while (!archivo.eof()) {
        size_t longitud;
        archivo.read(reinterpret_cast<char*>(&longitud), sizeof(longitud));
        if (archivo.eof()) break;

        string cifrado(longitud, '\0');
        archivo.read(&cifrado[0], longitud);

        string linea = xorEncryptDecrypt(cifrado);
        stringstream ss(linea);

        string id, nombre, telefono, email;
        getline(ss, id, '|');
        getline(ss, nombre, '|');
        getline(ss, telefono, '|');
        getline(ss, email);

        clientes.emplace_back(id, nombre, telefono, email);
    }

    archivo.close();
    return clientes;
}

// Registrar nuevo cliente
void ingresarCliente() {
    Cliente nuevo;
    nuevo.setId(generarIdCliente());

    cout << "\n--- REGISTRAR CLIENTE ---\n";
    cout << "ID: " << nuevo.getId() << endl;

    string input;
    cout << "Nombre: ";
    getline(cin, input);
    nuevo.setNombre(input);

    cout << "Teléfono: ";
    getline(cin, input);
    nuevo.setTelefono(input);

    cout << "Email: ";
    getline(cin, input);
    nuevo.setEmail(input);

    vector<Cliente> clientes = cargarClientes();
    clientes.push_back(nuevo);
    guardarClientes(clientes);

    cout << "Cliente registrado\n";
}

// Consultar clientes
void consultarClientes() {
    vector<Cliente> clientes = cargarClientes();

    cout << "\n--- LISTA DE CLIENTES ---\n";
    if (clientes.empty()) {
        cout << "No hay clientes registrados\n";
        return;
    }

    for (const auto& cliente : clientes) {
        cliente.mostrar();
        cout << "\n";
    }
}

// Modificar cliente
void modificarCliente() {
    consultarClientes();
    vector<Cliente> clientes = cargarClientes();

    if (clientes.empty()) return;

    string id;
    cout << "Ingrese ID del cliente a modificar: ";
    getline(cin, id);

    auto it = find_if(clientes.begin(), clientes.end(),
        [&id](const Cliente& c) { return c.getId() == id; });

    if (it == clientes.end()) {
        cerr << "Cliente no encontrado\n";
        return;
    }

    string input;
    cout << "Nuevo nombre [" << it->getNombre() << "]: ";
    getline(cin, input);
    if (!input.empty()) it->setNombre(input);

    cout << "Nuevo teléfono [" << it->getTelefono() << "]: ";
    getline(cin, input);
    if (!input.empty()) it->setTelefono(input);

    cout << "Nuevo email [" << it->getEmail() << "]: ";
    getline(cin, input);
    if (!input.empty()) it->setEmail(input);

    guardarClientes(clientes);
    cout << "Cliente actualizado\n";
}

// Borrar cliente
void borrarCliente() {
    consultarClientes();
    vector<Cliente> clientes = cargarClientes();

    if (clientes.empty()) return;

    string id;
    cout << "Ingrese ID del cliente a eliminar: ";
    getline(cin, id);

    size_t before = clientes.size();
    clientes.erase(remove_if(clientes.begin(), clientes.end(),
        [&id](const Cliente& c) { return c.getId() == id; }), clientes.end());

    if (clientes.size() == before) {
        cout << "No se encontró un cliente con ese ID\n";
    } else {
        guardarClientes(clientes);
        cout << "Cliente eliminado\n";
    }
}
