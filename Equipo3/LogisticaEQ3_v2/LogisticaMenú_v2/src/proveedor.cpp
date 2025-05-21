// Angoly Araujo Mayo 2025 9959-24-17623
#include "proveedor.h"
#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>

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
    return reg;
}

Proveedor Proveedor::fromRegistro(const ProveedorRegistro& reg) {
    Proveedor p;
    p.id = std::string(reg.id);
    p.nombre = std::string(reg.nombre);
    p.telefono = std::string(reg.telefono);
    return p;
}

string Proveedor::generarIdUnico(const vector<Proveedor>& lista) {
    for (int i = CODIGO_INICIAL_PROV; i <= CODIGO_FINAL_PROV; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

bool Proveedor::idDisponible(const vector<Proveedor>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.id == id; });
}

bool Proveedor::esIdValido(const string& id) {
    try {
        int num = stoi(id);
        return (num >= CODIGO_INICIAL_PROV && num <= CODIGO_FINAL_PROV);
    } catch (...) {
        return false;
    }
}

void Proveedor::agregar(vector<Proveedor>& lista, const string& usuarioActual) {
    Proveedor nuevo;
    nuevo.id = generarIdUnico(lista);

    if (nuevo.id.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles para nuevos proveedores.\n";
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
        cout << "\t\tTeléfono: ";
        getline(cin, nuevo.telefono);
    } while (nuevo.telefono.empty());

    lista.push_back(nuevo);

    guardarEnArchivoBinario(lista);

    bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor agregado - ID: " + nuevo.id);
    cout << "\n\t\tProveedor registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}

void Proveedor::mostrar(const vector<Proveedor>& lista) {
    cout << "\n--- LISTA DE PROVEEDORES ---\n";
    for (const auto& p : lista) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Teléfono: " << p.telefono << "\n";
    }
    system("pause");
}

void Proveedor::modificar(vector<Proveedor>& lista, const string& usuarioActual, const string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR PROVEEDOR (ID: " << id << ") ---\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "Nuevo teléfono (" << it->telefono << "): ";
        getline(cin, it->telefono);

        guardarEnArchivoBinario(lista);

        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor modificado - ID: " + id);
        cout << "Proveedor modificado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

void Proveedor::eliminar(vector<Proveedor>& lista, const string& usuarioActual, const string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivoBinario(lista);
        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor eliminado - ID: " + id);
        cout << "Proveedor eliminado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

void Proveedor::guardarEnArchivoBinario(const vector<Proveedor>& lista) {
    ofstream archivo("Proveedores.bin", ios::binary | ios::out | ios::trunc);
    if (!archivo) {
        cerr << "\n\t\tError crítico: No se pudo abrir Proveedores.bin para escribir\n";
        return;
    }

    for (const auto& p : lista) {
        ProveedorRegistro reg = toRegistro(p);
        codificar(reg.id, sizeof(reg.id));
        codificar(reg.nombre, sizeof(reg.nombre));
        codificar(reg.telefono, sizeof(reg.telefono));
        archivo.write(reinterpret_cast<const char*>(&reg), sizeof(reg));
    }

    archivo.close();
    cout << "\n\t\tArchivo Proveedores.bin guardado correctamente (cifrado).\n";
}

void Proveedor::cargarDesdeArchivoBinario(vector<Proveedor>& lista) {
    lista.clear();
    ifstream archivo("Proveedores.bin", ios::binary);

    if (!archivo) {
        cerr << "\n\t\tArchivo Proveedores.bin no encontrado. Se creará al guardar.\n";
        return;
    }

    ProveedorRegistro reg;
    while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
        decodificar(reg.id, sizeof(reg.id));
        decodificar(reg.nombre, sizeof(reg.nombre));
        decodificar(reg.telefono, sizeof(reg.telefono));

        Proveedor p = fromRegistro(reg);

        if (!esIdValido(p.id)) continue;
        if (!idDisponible(lista, p.id)) continue;

        lista.push_back(p);
    }
}

// Wrappers para compatibilidad con main.cpp
void Proveedor::guardarEnArchivo(vector<Proveedor>& lista) {
    guardarEnArchivoBinario(lista);
}

void Proveedor::cargarDesdeArchivo(vector<Proveedor>& lista) {
    cargarDesdeArchivoBinario(lista);
}


