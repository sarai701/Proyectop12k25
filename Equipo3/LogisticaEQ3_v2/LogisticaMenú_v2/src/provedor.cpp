//Angoly Araujo Mayo 2025 9959-24-17623
#include "proveedor.h"
#include "bitacora.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Rango de códigos válidos para IDs de proveedores
const int CODIGO_INICIAL_PROV = 3158;
const int CODIGO_FINAL_PROV = 3208;

// Genera un ID único dentro del rango permitido para nuevos proveedores
std::string Proveedor::generarIdUnico(const std::vector<Proveedor>& lista) {
    for (int i = CODIGO_INICIAL_PROV; i <= CODIGO_FINAL_PROV; ++i) {
        std::string id = std::to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return ""; // Si no hay IDs disponibles
}

// Verifica si el ID dado no está en uso
bool Proveedor::idDisponible(const std::vector<Proveedor>& lista, const std::string& id) {
    return std::none_of(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });
}

// Verifica que el ID esté dentro del rango permitido
bool Proveedor::esIdValido(const std::string& id) {
    try {
        int num = std::stoi(id);
        return (num >= CODIGO_INICIAL_PROV && num <= CODIGO_FINAL_PROV);
    } catch (...) {
        return false;
    }
}

// Agrega un nuevo proveedor al vector y guarda el cambio
void Proveedor::agregar(std::vector<Proveedor>& lista, const std::string& usuarioActual) {
    Proveedor nuevo;
    nuevo.id = generarIdUnico(lista); // ID autoasignado

    if (nuevo.id.empty()) {
        std::cerr << "\n\t\tError: No hay códigos disponibles para nuevos proveedores.\n";
        system("pause");
        return;
    }

    std::cout << "\n\t\t=== AGREGAR PROVEEDOR (ID Auto-Asignado: " << nuevo.id << ") ===\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Solicita nombre y teléfono del proveedor
    std::cout << "\t\tNombre completo: ";
    std::getline(std::cin, nuevo.nombre);

    std::cout << "\t\tTeléfono: ";
    std::getline(std::cin, nuevo.telefono);

    lista.push_back(nuevo); // Agrega a la lista
    guardarEnArchivo(lista); // Guarda cambios

    // Registra acción en la bitácora
    bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor agregado - ID: " + nuevo.id);
    std::cout << "\n\t\tProveedor registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}

// Muestra todos los proveedores existentes
void Proveedor::mostrar(const std::vector<Proveedor>& lista) {
    cout << "\n--- LISTA DE PROVEEDORES ---\n";
    for (const auto& p : lista) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Teléfono: " << p.telefono << "\n";
    }
    system("pause");
}

// Modifica los datos de un proveedor existente
void Proveedor::modificar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR PROVEEDOR (ID: " << id << ") ---\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Solicita nuevos datos
        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "Nuevo teléfono (" << it->telefono << "): ";
        getline(cin, it->telefono);

        guardarEnArchivo(lista); // Guarda cambios
        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor modificado - ID: " + id);
        cout << "Proveedor modificado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

// Elimina un proveedor por ID
void Proveedor::eliminar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Proveedor& p) { return p.id == id; });

    if (it != lista.end()) {
        lista.erase(it); // Elimina de la lista
        guardarEnArchivo(lista); // Guarda cambios

        bitacora::registrar(usuarioActual, "PROVEEDORES", "Proveedor eliminado - ID: " + id);
        cout << "Proveedor eliminado!\n";
    } else {
        cout << "Proveedor no encontrado.\n";
    }
    system("pause");
}

// Guarda la lista de proveedores en un archivo temporal y renombra al archivo definitivo
void Proveedor::guardarEnArchivo(const std::vector<Proveedor>& lista) {
    ofstream archivo("Proveedores.tmp", ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo crear archivo temporal!\n";
        return;
    }

    bool errorEscritura = false;

    // Escribe cada proveedor en el archivo
    for (const auto& p : lista) {
        if (!(archivo << p.id << "," << p.nombre << "," << p.telefono << "\n")) {
            cerr << "\n\t\tError al escribir proveedor ID: " << p.id << "\n";
            errorEscritura = true;
        }
    }

    archivo.flush(); // Fuerza escritura al disco

    if (!archivo || errorEscritura) {
        cerr << "\n\t\tError: No se pudieron guardar todos los datos!\n";
        archivo.close();
        remove("Proveedores.tmp"); // Elimina archivo corrupto
        return;
    }

    archivo.close();

    // Elimina archivo anterior y renombra el temporal
    if (remove("Proveedores.txt") != 0 && errno != ENOENT) {
        cerr << "\n\t\tAdvertencia: No se pudo eliminar archivo anterior\n";
    }
    if (rename("Proveedores.tmp", "Proveedores.txt") != 0) {
        cerr << "\n\t\tError crítico: Falló el guardado final!\n";
    }
}

// Carga los proveedores desde archivo a la lista en memoria
void Proveedor::cargarDesdeArchivo(std::vector<Proveedor>& lista) {
    lista.clear();

    ifstream archivo("Proveedores.txt");
    if (!archivo) {
        // Crea archivo si no existe
        ofstream nuevoArchivo("Proveedores.txt");
        if (!nuevoArchivo) {
            cerr << "\n\t\tError crítico: No se pudo crear archivo de proveedores!\n";
        }
        return;
    }

    int cargados = 0, omitidos = 0;
    string linea;

    while (getline(archivo, linea)) {
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;

        istringstream ss(linea);
        Proveedor temp;
        string campo;

        try {
            // Extrae campos
            if (!getline(ss, temp.id, ',') ||
                !getline(ss, temp.nombre, ',') ||
                !getline(ss, temp.telefono)) {
                throw runtime_error("Formato inválido");
            }

            // Validaciones de ID
            if (!esIdValido(temp.id)) {
                throw runtime_error("ID fuera de rango");
            }

            if (!idDisponible(lista, temp.id)) {
                throw runtime_error("ID duplicado");
            }

            lista.push_back(temp); // Agrega a la lista
            cargados++;
        } catch (const exception& e) {
            cerr << "\n\t\tAdvertencia: Proveedor omitido (" << e.what() << "): " << linea << "\n";
            omitidos++;
        }
    }

    if (archivo.bad()) {
        cerr << "\n\t\tError: Fallo durante la lectura del archivo!\n";
    }

    cout << "\n\t\tCarga completada. " << cargados << " proveedores cargados, "
         << omitidos << " omitidos.\n";
}

