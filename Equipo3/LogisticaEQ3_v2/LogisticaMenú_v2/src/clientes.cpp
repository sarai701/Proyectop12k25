//LUIS ANGEL MENDEZ FUENTES
//9959-24-6845
#include "clientes.h"
#include <iostream>
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
        std::cerr << "\n\t\tError: No hay codigos disponibles para nuevos clientes (rango lleno)\n";
        system("pause");
        return;
    }

    std::cout << "\n-------------------------- AGREGAR CLIENTE --------------------------\n";
    std::cout << std::left << std::setw(25) << "ID Asignado:" << nuevo.id << "\n";
    std::cout << "---------------------------------------------------------------------\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\t\tNombre completo: ";
    std::getline(std::cin, nuevo.nombre);

    std::cout << "\t\tDireccion: ";
    std::getline(std::cin, nuevo.direccion);

    std::cout << "\t\tTelefono: ";
    std::getline(std::cin, nuevo.telefono);

    std::cout << "\t\tNIT: ";
    std::getline(std::cin, nuevo.nit);

    lista.push_back(nuevo); // Agrega el cliente a la lista
    guardarEnArchivo(lista); // Guarda la lista actualizada de clientes

    // Registra la acción en la bitácora
    bitacora::registrar(usuarioActual, "CLIENTES", "Cliente agregado - ID: " + nuevo.id);

    // Mostrar reporte visual de un solo cliente
    std::cout << "\n-------------------------- Cliente Registrado --------------------------\n";
    std::cout << std::left << std::setw(15) << "ID"
              << std::setw(25) << "Nombre"
              << std::setw(20) << "NIT"
              << std::setw(20) << "Telefono"
              << std::setw(30) << "Direccion" << "\n";
    std::cout << "---------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << nuevo.id
              << std::setw(25) << nuevo.nombre
              << std::setw(20) << nuevo.nit
              << std::setw(20) << nuevo.telefono
              << std::setw(30) << nuevo.direccion << "\n";
    std::cout << "---------------------------------------------------------------------------\n";

    // Opcional: Guardar también en un archivo de reportes
    std::ofstream reporteFile("clientes.txt", std::ios::app);
    if (reporteFile.is_open()) {
        reporteFile << "-------------------------- NUEVO CLIENTE --------------------------\n";
        reporteFile << std::left << std::setw(15) << "ID"
                    << std::setw(25) << "Nombre"
                    << std::setw(20) << "NIT"
                    << std::setw(20) << "Telefono"
                    << std::setw(30) << "Direccion" << "\n";
        reporteFile << "-------------------------------------------------------------------\n";
        reporteFile << std::left << std::setw(15) << nuevo.id
                    << std::setw(25) << nuevo.nombre
                    << std::setw(20) << nuevo.nit
                    << std::setw(20) << nuevo.telefono
                    << std::setw(30) << nuevo.direccion << "\n";
        reporteFile << "-------------------------------------------------------------------\n\n";
        reporteFile.close();
    }

    std::cout << "\n\t\tCliente registrado exitosamente con ID: " << nuevo.id << "\n";

    // Limpiar buffer antes del system("pause") para evitar doble pausa
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    system("pause");
}

/**
 * Muestra todos los clientes actualmente almacenados en la lista.
 * Si la lista está vacía, muestra un mensaje apropiado.
 * @param lista Lista de clientes a mostrar.
 */
void Clientes::mostrar(const std::vector<Clientes>& lista) {
    if (lista.empty()) {
        std::cout << "\n----------------------------- CLIENTES -----------------------------\n";
        std::cout << "\tNo hay clientes registrados.\n";
        std::cout << "\tEl archivo puede estar vacío o no se cargo correctamente.\n";
        std::cout << "--------------------------------------------------------------------\n";
    } else {
        std::cout << "\n----------------------------- LISTADO DE CLIENTES -----------------------------\n";
        std::cout << std::left
                  << std::setw(10) << "ID"
                  << std::setw(30) << "Nombre completo"
                  << std::setw(25) << "Direccion"
                  << std::setw(15) << "Teléfono"
                  << std::setw(20) << "NIT" << "\n";
        std::cout << std::string(100, '-') << "\n";

        for (const auto& cliente : lista) {
            std::cout << std::left
                      << std::setw(10) << cliente.id
                      << std::setw(30) << cliente.nombre
                      << std::setw(25) << cliente.direccion
                      << std::setw(15) << cliente.telefono
                      << std::setw(20) << cliente.nit << "\n";
        }

        std::cout << std::string(100, '-') << "\n";
    }

    // Limpiar buffer antes del system("pause") para evitar doble pausa
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    system("pause");
}

/**
 * Modifica los datos de un cliente existente según su ID.
 * Guarda los cambios en el archivo y registra en la bitácora.
 * @param lista Lista de clientes (modificable).
 * @param usuarioActual Usuario que realiza la modificación.
 * @param id ID del cliente a modificar.
 */
void Clientes::modificar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& idCliente) {
    // Buscar cliente con el idCliente recibido
    auto it = std::find_if(lista.begin(), lista.end(),
        [&idCliente](const Clientes& c) { return c.id == idCliente; });

    if (it == lista.end()) {
        std::cout << "Cliente con ID '" << idCliente << "' no encontrado.\n";
        system("pause");
        return;
    }

    std::cout << "\n-------------------------- MODIFICAR CLIENTE --------------------------\n";
    std::cout << std::left << std::setw(25) << "ID del cliente:" << idCliente << "\n";
    std::cout << "------------------------------------------------------------------------\n";

    // Mostrar datos actuales
    std::cout << std::left << std::setw(15) << "Nombre actual:" << it->nombre << "\n";
    std::cout << std::left << std::setw(15) << "Direccion actual:" << it->direccion << "\n";
    std::cout << std::left << std::setw(15) << "Telefono actual:" << it->telefono << "\n";
    std::cout << std::left << std::setw(15) << "NIT actual:" << it->nit << "\n";
    std::cout << "------------------------------------------------------------------------\n";

    // Pedir nuevos datos
    std::cout << "Nuevo nombre: ";
    std::getline(std::cin, it->nombre);

    std::cout << "Nueva direccion: ";
    std::getline(std::cin, it->direccion);

    std::cout << "Nuevo telefono: ";
    std::getline(std::cin, it->telefono);

    std::cout << "Nuevo NIT: ";
    std::getline(std::cin, it->nit);

    // Guardar cambios y registrar en bitácora
    guardarEnArchivo(lista);
    bitacora::registrar(usuarioActual, "CLIENTES", "Cliente modificado - ID: " + idCliente);

    std::cout << "\n-----------------------------\n";
    std::cout << "¡Cliente modificado exitosamente!\n";
    std::cout << "-----------------------------\n";

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
    auto it = std::find_if(lista.begin(), lista.end(),
        [&id](const Clientes& c) { return c.id == id; });

    std::cout << "\n--------------------------- ELIMINAR CLIENTE ---------------------------\n";
    std::cout << std::left << std::setw(25) << "ID a eliminar:" << id << "\n";
    std::cout << "------------------------------------------------------------------------\n";

    if (it != lista.end()) {
        lista.erase(it); // Elimina el cliente de la lista
        guardarEnArchivo(lista); // Guarda la lista actualizada
        bitacora::registrar(usuarioActual, "CLIENTES", "Cliente eliminado - ID: " + id);

        std::cout << "\n-----------------------------\n";
        std::cout << "¡Cliente eliminado exitosamente!\n";
        std::cout << "-----------------------------\n";
    } else {
        std::cout << "\n-----------------------------\n";
        std::cout << "Cliente con ID '" << id << "' no encontrado.\n";
        std::cout << "-----------------------------\n";
    }

    // Limpiar buffer antes de la pausa para evitar doble mensaje
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    system("pause");
}

/**
 * Guarda la lista completa de clientes en un archivo binario.
 * @param lista Lista actual de clientes.
 */
void Clientes::guardarEnArchivo(const std::vector<Clientes>& lista) {
    std::ofstream archivo("clientes.bin", std::ios::binary | std::ios::trunc);
    if (!archivo) {
        std::cerr << "Error al abrir clientes.dat para escritura.\n";
        return;
    }

    for (const auto& cliente : lista) {
        // Guardar ID
        size_t size = cliente.id.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(cliente.id.c_str(), size);

        // Guardar Nombre
        size = cliente.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(cliente.nombre.c_str(), size);

        // Guardar Dirección
        size = cliente.direccion.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(cliente.direccion.c_str(), size);

        // Guardar Teléfono
        size = cliente.telefono.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(cliente.telefono.c_str(), size);

        // Guardar NIT
        size = cliente.nit.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(cliente.nit.c_str(), size);
    }
    archivo.close();
    std::cout << "\tDatos guardados correctamente.\n";
}

/**
 * Carga la lista de clientes desde el archivo binario "clientes.dat".
 * Si el archivo no existe o está vacío, la lista queda vacía.
 * @param lista Lista donde se cargarán los clientes.
 */
void Clientes::cargarDesdeArchivo(std::vector<Clientes>& lista) {
    lista.clear();

    std::ifstream archivo("clientes.bin", std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al abrir clientes.dat para lectura.\n";
        return;
    }

    while (archivo.peek() != EOF) {
        Clientes cliente;
        size_t size;

        // Leer ID
        if (!archivo.read(reinterpret_cast<char*>(&size), sizeof(size))) break;
        cliente.id.resize(size);
        archivo.read(&cliente.id[0], size);

        // Leer Nombre
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        cliente.nombre.resize(size);
        archivo.read(&cliente.nombre[0], size);

        // Leer Dirección
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        cliente.direccion.resize(size);
        archivo.read(&cliente.direccion[0], size);

        // Leer Teléfono
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        cliente.telefono.resize(size);
        archivo.read(&cliente.telefono[0], size);

        // Leer NIT
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        cliente.nit.resize(size);
        archivo.read(&cliente.nit[0], size);

        lista.push_back(cliente);
    }
    archivo.close();
    std::cout << "\tDatos cargados correctamente.\n";
}
