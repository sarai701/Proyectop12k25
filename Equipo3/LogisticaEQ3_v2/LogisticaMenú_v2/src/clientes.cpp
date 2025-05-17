#include "clientes.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "bitacora.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Rango de códigos para clientes
const int CODIGO_INICIAL = 3107;
const int CODIGO_FINAL = 3157;

/**
 * Genera un ID único dentro del rango permitido (3107–3157) para un nuevo cliente.
 * @param lista Lista actual de clientes.
 * @return ID disponible como string, o cadena vacía si el rango está lleno.
 */
std::string Clientes::generarIdUnico(const std::vector<Clientes>& lista) {
    // Itera dentro del rango permitido para generar un ID único
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        std::string id = std::to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

/**
 * Verifica si un ID está disponible (no repetido) en la lista de clientes.
 * @param lista Lista de clientes.
 * @param id ID a verificar.
 * @return true si el ID no está en uso, false si ya está ocupado.
 */
bool Clientes::idDisponible(const std::vector<Clientes>& lista, const std::string& id) {
    // Verifica si el ID ya existe en la lista de clientes
    return std::none_of(lista.begin(), lista.end(),
        [&id](const Clientes& c) { return c.id == id; });
}

/**
 * Valida si un ID es un número dentro del rango permitido.
 * @param id ID a validar.
 * @return true si es válido, false si no.
 */
bool Clientes::esIdValido(const std::string& id) {
    try {
        int num = std::stoi(id);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

/**
 * Agrega un nuevo cliente a la lista, solicitando los datos desde la entrada estándar.
 * Asigna automáticamente un ID único, guarda en archivo y registra en bitácora.
 * @param lista Lista de clientes (modificable).
 * @param usuarioActual Nombre del usuario activo (para bitácora).
 */
void Clientes::agregar(std::vector<Clientes>& lista, const std::string& usuarioActual) {
    Clientes nuevo;

    // Genera un ID único para el nuevo cliente
    nuevo.id = generarIdUnico(lista);
    if (nuevo.id.empty()) {
        std::cerr << "\n\t\tError: No hay códigos disponibles para nuevos clientes (rango lleno)\n";
        system("pause");
        return;
    }

    std::cout << "\n\t\t=== AGREGAR CLIENTE (ID Auto-Asignado: " << nuevo.id << ") ===\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\t\tNombre completo: ";
    std::getline(std::cin, nuevo.nombre);

    std::cout << "\t\tDirección: ";
    std::getline(std::cin, nuevo.direccion);

    std::cout << "\t\tTeléfono: ";
    std::getline(std::cin, nuevo.telefono);

    std::cout << "\t\tNIT: ";
    std::getline(std::cin, nuevo.nit);

    lista.push_back(nuevo); // Agrega el cliente a la lista
    guardarEnArchivo(lista); // Guarda la lista actualizada de clientes

    // Registra la acción en la bitácora
    bitacora::registrar(usuarioActual, "CLIENTES", "Cliente agregado - ID: " + nuevo.id);
    std::cout << "\n\t\tCliente registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}

/**
 * Muestra todos los clientes actualmente almacenados en la lista.
 * Si la lista está vacía, muestra un mensaje apropiado.
 * @param lista Lista de clientes a mostrar.
 */
void Clientes::mostrar(const std::vector<Clientes>& lista) {
    if (lista.empty()) {
        cout << "\n\t--- NO HAY CLIENTES REGISTRADOS ---\n";
        cout << "\tEl archivo puede estar vacío o no se cargó correctamente.\n";
    } else {
        cout << "\n\t" << string(100, '-') << "\n";
        cout << "\t" << left
             << setw(10) << "| ID |"
             << setw(30) << " NOMBRE COMPLETO |"
             << setw(25) << " DIRECCIÓN |"
             << setw(15) << " TELÉFONO |"
             << setw(15) << " NIT |" << "\n";
        cout << "\t" << string(100, '-') << "\n";

        for (const auto& cliente : lista) {
            cout << "\t" << left
                 << "| " << setw(6) << cliente.id << "| "
                 << setw(28) << cliente.nombre << "| "
                 << setw(23) << cliente.direccion << "| "
                 << setw(13) << cliente.telefono << "| "
                 << setw(13) << cliente.nit << "|" << "\n";
        }
        cout << "\t" << string(100, '-') << "\n";
    }
    system("pause");
}

/**
 * Modifica los datos de un cliente existente según su ID.
 * Guarda los cambios en el archivo y registra en la bitácora.
 * @param lista Lista de clientes (modificable).
 * @param usuarioActual Usuario que realiza la modificación.
 * @param id ID del cliente a modificar.
 */
void Clientes::modificar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Clientes& c) { return c.id == id; });

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR CLIENTE (ID: " << id << ") ---\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "Nueva dirección (" << it->direccion << "): ";
        getline(cin, it->direccion);

        cout << "Nuevo teléfono (" << it->telefono << "): ";
        getline(cin, it->telefono);

        cout << "Nuevo NIT (" << it->nit << "): ";
        getline(cin, it->nit);

        guardarEnArchivo(lista); // Guarda los cambios en el archivo
        bitacora::registrar(usuarioActual, "CLIENTES", "Cliente modificado - ID: " + id);
        cout << "Cliente modificado!\n";
    } else {
        cout << "Cliente no encontrado.\n";
    }
    system("pause");
}

/**
 * Elimina un cliente de la lista dado su ID.
 * Guarda los cambios y registra la acción en bitácora.
 * @param lista Lista de clientes (modificable).
 * @param usuarioActual Usuario que realiza la eliminación.
 * @param id ID del cliente a eliminar.
 */
void Clientes::eliminar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Clientes& c) { return c.id == id; });

    if (it != lista.end()) {
        lista.erase(it); // Elimina el cliente de la lista
        guardarEnArchivo(lista); // Guarda la lista actualizada
        bitacora::registrar(usuarioActual, "CLIENTES", "Cliente eliminado - ID: " + id);
        cout << "Cliente eliminado!\n";
    } else {
        cout << "Cliente no encontrado.\n";
    }
    system("pause");
}

/**
 * Guarda la lista completa de clientes en un archivo binario.
 * @param lista Lista actual de clientes.
 */
void Clientes::guardarEnArchivo(const std::vector<Clientes>& lista) {
    std::ofstream archivo("clientes.txt");
    if (!archivo) {
        std::cerr << "Error al abrir clientes.txt para escritura.\n";
        return;
    }

    for (const auto& cliente : lista) {
        archivo << cliente.getId() << '\t'
                << cliente.getNombre() << '\t'
                << cliente.getDireccion() << '\t'
                << cliente.getTelefono() << '\t'
                << cliente.getNit() << '\n';
    }

    archivo.close();
    std::cout << "\tDatos guardados correctamente en clientes.txt.\n";
}

/**
 * Carga la lista de clientes desde el archivo binario "clientes.dat".
 * Si el archivo no existe o está vacío, la lista queda vacía.
 * @param lista Lista donde se cargarán los clientes.
 */
void Clientes::cargarDesdeArchivo(std::vector<Clientes>& lista) {
    lista.clear();

    std::ifstream archivo("clientes.txt");
    if (!archivo) {
        std::cerr << "Error al abrir clientes.txt para lectura.\n";
        return;
    }

    Clientes cliente;
    std::string id, nombre, direccion, telefono, nit;

    while (std::getline(archivo, id, '\t') &&
           std::getline(archivo, nombre, '\t') &&
           std::getline(archivo, direccion, '\t') &&
           std::getline(archivo, telefono, '\t') &&
           std::getline(archivo, nit)) {

        cliente = Clientes(); // Crear uno nuevo
        // Asignar valores usando setters o constructor (si tienes uno)
        cliente.id = id;
        cliente.nombre = nombre;
        cliente.direccion = direccion;
        cliente.telefono = telefono;
        cliente.nit = nit;
        lista.push_back(cliente);
    }

    archivo.close();
    std::cout << "\tDatos cargados correctamente desde clientes.txt.\n";
}
