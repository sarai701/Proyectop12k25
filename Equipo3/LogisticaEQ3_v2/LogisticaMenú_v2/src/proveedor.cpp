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

const int CODIGO_INICIAL_PROV = 3158;  // Rango inicial válido para IDs de proveedores
const int CODIGO_FINAL_PROV = 3208;    // Rango final válido para IDs de proveedores

// Método para codificar datos mediante XOR con clave XOR_KEY
void Proveedor::codificar(char* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[i] ^= XOR_KEY;  // Aplica XOR con clave para cada byte
    }
}

// Método para decodificar datos (igual que codificar porque XOR es reversible)
void Proveedor::decodificar(char* data, size_t len) {
    codificar(data, len);  // Decodificar es aplicar XOR de nuevo
}

// Convierte un objeto Proveedor a un registro ProveedorRegistro para almacenamiento
ProveedorRegistro Proveedor::toRegistro(const Proveedor& p) {
    ProveedorRegistro reg = {};
    strncpy(reg.id, p.id.c_str(), sizeof(reg.id) - 1);            // Copia id
    strncpy(reg.nombre, p.nombre.c_str(), sizeof(reg.nombre) - 1);// Copia nombre
    strncpy(reg.telefono, p.telefono.c_str(), sizeof(reg.telefono) - 1);// Copia teléfono
    return reg;
}

// Convierte un registro ProveedorRegistro a un objeto Proveedor
Proveedor Proveedor::fromRegistro(const ProveedorRegistro& reg) {
    Proveedor p;
    p.id = std::string(reg.id);
    p.nombre = std::string(reg.nombre);
    p.telefono = std::string(reg.telefono);
    return p;
}

// Genera un ID único dentro del rango definido, que no exista en la lista actual
string Proveedor::generarIdUnico(const vector<Proveedor>& lista) {
    for (int i = CODIGO_INICIAL_PROV; i <= CODIGO_FINAL_PROV; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) {  // Verifica si el ID está disponible
            return id;
        }
    }
    return "";  // No hay IDs disponibles en el rango
}

// Verifica si un ID está disponible (no existe en la lista)
bool Proveedor::idDisponible(const vector<Proveedor>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.id == id; });
}

// Valida que un ID esté dentro del rango permitido
bool Proveedor::esIdValido(const string& id) {
    try {
        int num = stoi(id);
        return (num >= CODIGO_INICIAL_PROV && num <= CODIGO_FINAL_PROV);
    } catch (...) {
        return false;  // No es un número válido
    }
}

// Agrega un nuevo proveedor a la lista, pidiendo datos al usuario
void Proveedor::agregar(vector<Proveedor>& lista, const string& usuarioActual) {
    Proveedor nuevo;
    nuevo.id = generarIdUnico(lista);  // Asigna ID único automáticamente

    if (nuevo.id.empty()) {  // Si no hay IDs disponibles, muestra error
        cerr << "\n\t\tError: No hay códigos disponibles para nuevos proveedores.\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR PROVEEDOR (ID Auto-Asignado: " << nuevo.id << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia buffer de entrada

    do {
        cout << "\t\tNombre completo: ";
        getline(cin, nuevo.nombre);  // Solicita nombre hasta que no esté vacío
    } while (nuevo.nombre.empty());

    do {
        cout << "\t\tTeléfono: ";
        getline(cin, nuevo.telefono);  // Solicita teléfono hasta que no esté vacío
    } while (nuevo.telefono.empty());

    lista.push_back(nuevo);  // Agrega nuevo proveedor a la lista

    guardarEnArchivoBinario(lista);  // Guarda la lista cifrada en archivo

    bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor agregado - ID: " + nuevo.id);
    cout << "\n\t\tProveedor registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}

// Muestra la lista completa de proveedores con sus datos
void Proveedor::mostrar(const vector<Proveedor>& lista) {
    cout << "\n--- LISTA DE PROVEEDORES ---\n";
    for (const auto& p : lista) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Teléfono: " << p.telefono << "\n";
    }
    system("pause");
}

// Modifica los datos de un proveedor dado su ID
void Proveedor::modificar(vector<Proveedor>& lista, const string& usuarioActual, const string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });  // Busca proveedor por ID

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR PROVEEDOR (ID: " << id << ") ---\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia buffer

        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);  // Pide nuevo nombre (puede quedar igual)

        cout << "Nuevo teléfono (" << it->telefono << "): ";
        getline(cin, it->telefono);  // Pide nuevo teléfono (puede quedar igual)

        guardarEnArchivoBinario(lista);  // Guarda cambios en archivo

        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor modificado - ID: " + id);
        cout << "Proveedor modificado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

// Elimina un proveedor de la lista dado su ID
void Proveedor::eliminar(vector<Proveedor>& lista, const string& usuarioActual, const string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });  // Busca proveedor

    if (it != lista.end()) {
        lista.erase(it);  // Borra proveedor de la lista
        guardarEnArchivoBinario(lista);  // Guarda lista actualizada

        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor eliminado - ID: " + id);
        cout << "Proveedor eliminado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

// Guarda la lista de proveedores en un archivo binario cifrado
void Proveedor::guardarEnArchivoBinario(const vector<Proveedor>& lista) {
    ofstream archivo("Proveedores.bin", ios::binary | ios::out | ios::trunc);
    if (!archivo) {
        cerr << "\n\t\tError crítico: No se pudo abrir Proveedores.bin para escribir\n";
        return;
    }

    for (const auto& p : lista) {
        ProveedorRegistro reg = toRegistro(p);   // Convierte objeto a registro
        codificar(reg.id, sizeof(reg.id));       // Codifica campos para cifrado
        codificar(reg.nombre, sizeof(reg.nombre));
        codificar(reg.telefono, sizeof(reg.telefono));
        archivo.write(reinterpret_cast<const char*>(&reg), sizeof(reg));  // Escribe registro
    }

    archivo.close();
    cout << "\n\t\tArchivo Proveedores.bin guardado correctamente (cifrado).\n";
}

// Carga la lista de proveedores desde un archivo binario cifrado
void Proveedor::cargarDesdeArchivoBinario(vector<Proveedor>& lista) {
    lista.clear();  // Limpia lista antes de cargar
    ifstream archivo("Proveedores.bin", ios::binary);

    if (!archivo) {
        cerr << "\n\t\tArchivo Proveedores.bin no encontrado. Se creará al guardar.\n";
        return;
    }

    ProveedorRegistro reg;
    while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
        decodificar(reg.id, sizeof(reg.id));           // Decodifica campos
        decodificar(reg.nombre, sizeof(reg.nombre));
        decodificar(reg.telefono, sizeof(reg.telefono));

        Proveedor p = fromRegistro(reg);  // Convierte registro a objeto

        if (!esIdValido(p.id)) continue;          // Descarta IDs fuera de rango
        if (!idDisponible(lista, p.id)) continue; // Descarta IDs repetidos

        lista.push_back(p);  // Agrega proveedor válido a la lista
    }
}

// Wrappers para compatibilidad con main.cpp (solo llaman a las funciones binarios)
void Proveedor::guardarEnArchivo(vector<Proveedor>& lista) {
    guardarEnArchivoBinario(lista);
}

void Proveedor::cargarDesdeArchivo(vector<Proveedor>& lista) {
    cargarDesdeArchivoBinario(lista);
}
