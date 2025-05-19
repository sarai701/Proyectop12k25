// Angoly Araujo Mayo 2025 9959-24-17623
#include "proveedor.h"
#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>
#include <ctime>

using namespace std;

const int CODIGO_INICIAL_PROV = 3158;
const int CODIGO_FINAL_PROV = 3208;

void Proveedor::codificar(char* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[i] ^= XOR_KEY;
    }
}

void Proveedor::decodificar(char* data, size_t len) {
    codificar(data, len);
}

ProveedorRegistro Proveedor::toRegistro(const Proveedor& p) {
    ProveedorRegistro reg = {};
    strncpy(reg.id, p.id.c_str(), sizeof(reg.id) - 1);
    strncpy(reg.nombre, p.nombre.c_str(), sizeof(reg.nombre) - 1);
    strncpy(reg.telefono, p.telefono.c_str(), sizeof(reg.telefono) - 1);
    codificar(reg.id, sizeof(reg.id));
    codificar(reg.nombre, sizeof(reg.nombre));
    codificar(reg.telefono, sizeof(reg.telefono));
    return reg;
}

Proveedor Proveedor::fromRegistro(const ProveedorRegistro& regCodificado) {
    ProveedorRegistro reg = regCodificado;
    decodificar(reg.id, sizeof(reg.id));
    decodificar(reg.nombre, sizeof(reg.nombre));
    decodificar(reg.telefono, sizeof(reg.telefono));
    Proveedor p;
    p.id = reg.id;
    p.nombre = reg.nombre;
    p.telefono = reg.telefono;
    return p;
}

string Proveedor::generarIdUnico(const vector<Proveedor>& lista) {
    for (int i = CODIGO_INICIAL_PROV; i <= CODIGO_FINAL_PROV; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) return id;
    }
    return "";
}

bool Proveedor::idDisponible(const vector<Proveedor>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.id == id; });
}

bool Proveedor::esIdValido(const string& id) {
    try {
        int valor = stoi(id);
        return valor >= CODIGO_INICIAL_PROV && valor <= CODIGO_FINAL_PROV;
    } catch (...) {
        return false;
    }
}

void Proveedor::guardarEnBitacora(const string& usuario, const string& operacion, const Proveedor& proveedor) {
    bitacora::registrar(usuario, "PROVEEDORES", operacion + " - ID: " + proveedor.getId());
}

void Proveedor::agregar(vector<Proveedor>& lista, const string& usuarioActual) {
    int opcion;
    cout << "\n\t\tDesea volver al menu principal? (1: Si / 0: No): ";
    cin >> opcion;
    if (opcion == 1) return;

    Proveedor nuevo;
    nuevo.id = generarIdUnico(lista);

    if (nuevo.id.empty()) {
        cerr << "\n\t\tError: No hay codigos disponibles para nuevos proveedores.\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR PROVEEDOR (ID Auto-Asignado: " << nuevo.id << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "\t\tNombre completo: ";
        getline(cin, nuevo.nombre);
    } while (nuevo.nombre.empty());

    do {
        cout << "\t\tTelefono: ";
        getline(cin, nuevo.telefono);
    } while (nuevo.telefono.empty());

    lista.push_back(nuevo);
    guardarEnArchivoBinario(lista);
    guardarEnBitacora(usuarioActual, "Proveedor agregado", nuevo);
    cout << "\n\t\tProveedor registrado exitosamente.\n";
    system("pause");
}

void Proveedor::mostrar(const vector<Proveedor>& lista) {
    cout << "\n\t\t--- LISTA DE PROVEEDORES ---\n";
    for (const auto& p : lista) {
        cout << "\t\tID: " << p.getId()
             << " | Nombre: " << p.getNombre()
             << " | Telefono: " << p.getTelefono() << '\n';
    }
    system("pause");
}

void Proveedor::modificar(vector<Proveedor>& lista, const string& usuarioActual, const string& /*idDummy*/) {
    int opcion;
    cout << "\n\t\tDesea volver al menu principal? (1: Si / 0: No): ";
    cin >> opcion;
    if (opcion == 1) return;

    mostrar(lista);
    string id;
    cout << "\n\t\tIngrese el ID del proveedor a modificar: ";
    cin >> id;

    auto it = find_if(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.getId() == id; });

    if (it != lista.end()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\t\t--- MODIFICAR PROVEEDOR (ID: " << id << ") ---\n";

        string nuevoNombre, nuevoTelefono;

        cout << "\t\tNuevo nombre (" << it->getNombre() << "): ";
        getline(cin, nuevoNombre);
        if (!nuevoNombre.empty()) it->setNombre(nuevoNombre);

        cout << "\t\tNuevo telefono (" << it->getTelefono() << "): ";
        getline(cin, nuevoTelefono);
        if (!nuevoTelefono.empty()) it->setTelefono(nuevoTelefono);

        guardarEnArchivoBinario(lista);
        guardarEnBitacora(usuarioActual, "Proveedor modificado", *it);
        cout << "\n\t\tProveedor modificado correctamente.\n";
    } else {
        cout << "\n\t\tProveedor no encontrado.\n";
    }
    system("pause");
}

void Proveedor::eliminar(vector<Proveedor>& lista, const string& usuarioActual, const string& /*idDummy*/) {
    int opcion;
    cout << "\n\t\tDesea volver al menu principal? (1: Si / 0: No): ";
    cin >> opcion;
    if (opcion == 1) return;

    mostrar(lista);
    string id;
    cout << "\n\t\tIngrese el ID del proveedor a eliminar: ";
    cin >> id;

    auto it = find_if(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.getId() == id; });

    if (it != lista.end()) {
        guardarEnBitacora(usuarioActual, "Proveedor eliminado", *it);
        lista.erase(it);
        guardarEnArchivoBinario(lista);
        cout << "\n\t\tProveedor eliminado correctamente.\n";
    } else {
        cout << "\n\t\tProveedor no encontrado.\n";
    }
    system("pause");
}

void Proveedor::guardarEnArchivoBinario(const vector<Proveedor>& lista) {
    ofstream archivo("Proveedores.bin", ios::binary | ios::trunc);
    if (!archivo) {
        cerr << "\n\t\tError: No se pudo abrir Proveedores.bin para escritura.\n";
        return;
    }

    for (const auto& p : lista) {
        ProveedorRegistro reg = toRegistro(p);
        archivo.write(reinterpret_cast<const char*>(&reg), sizeof(reg));
    }

    archivo.close();
}

void Proveedor::cargarDesdeArchivoBinario(vector<Proveedor>& lista) {
    lista.clear();
    ifstream archivo("Proveedores.bin", ios::binary);
    if (!archivo) return;

    ProveedorRegistro reg;
    while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
        lista.push_back(fromRegistro(reg));
    }

    archivo.close();
}

// Wrappers para main.cpp
void Proveedor::guardarEnArchivo(vector<Proveedor>& lista) {
    guardarEnArchivoBinario(lista);
}
void Proveedor::cargarDesdeArchivo(vector<Proveedor>& lista) {
    cargarDesdeArchivoBinario(lista);
}
