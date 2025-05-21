//Karina Alejandra Arriaza Ortiz 9959-24-14190
#include "transportistas.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <vector>
#include "globals.h"
#include <fstream>
#include <sstream>

using namespace std;

const int CODIGO_INICIAL = 3311;
const int CODIGO_FINAL = 3361;

std::string Transportistas::generarIdUnico(const std::vector<Transportistas>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        std::string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

bool Transportistas::idDisponible(const std::vector<Transportistas>& lista, const std::string& id) {
    return none_of(lista.begin(), lista.end(),
        [&id](const Transportistas& t) { return t.id == id; });
}

bool Transportistas::esIdValido(const std::string& id) {
    try {
        int num = stoi(id);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

void Transportistas::agregar(std::vector<Transportistas>& lista, const std::string& usuarioActual) {
    Transportistas nuevo;
    nuevo.id = generarIdUnico(lista);

    if (nuevo.id.empty()) {
        cerr << "\n\t\tError: No hay c�digos disponibles para nuevos transportistas\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR TRANSPORTISTA (ID: " << nuevo.id << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tNombre: ";
    getline(cin, nuevo.nombre);

    cout << "\t\tTel�fono: ";
    getline(cin, nuevo.telefono);

    cout << "\t\tVeh�culo: ";
    getline(cin, nuevo.vehiculo);

    cout << "\t\tDisponibilidad (Diurna/Nocturna/24-7): ";
    getline(cin, nuevo.disponibilidad);

    lista.push_back(nuevo);
    guardarEnArchivo(lista);
    cout << "\n\t\tTransportista registrado exitosamente!\n";
    system("pause");
}

void Transportistas::mostrar(const std::vector<Transportistas>& lista) {
    cout << "\n--- LISTA DE TRANSPORTISTAS ---\n";
    for (const auto& t : lista) {
        cout << "ID: " << t.id
             << " | Nombre: " << t.nombre
             << " | Tel: " << t.telefono
             << " | Veh�culo: " << t.vehiculo
             << " | Disponibilidad: " << t.disponibilidad << "\n";
    }
    system("pause");
}

void Transportistas::modificar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Transportistas& t) { return t.id == id; });

    if (it != lista.end()) {
        cout << "\n--- MODIFICAR TRANSPORTISTA (ID: " << id << ") ---\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "Nuevo tel�fono (" << it->telefono << "): ";
        getline(cin, it->telefono);

        cout << "Nuevo veh�culo (" << it->vehiculo << "): ";
        getline(cin, it->vehiculo);

        cout << "Nueva disponibilidad (" << it->disponibilidad << "): ";
        getline(cin, it->disponibilidad);

        guardarEnArchivo(lista);
        cout << "Transportista modificado!\n";
    } else {
        cout << "Transportista no encontrado.\n";
    }
    system("pause");
}

void Transportistas::eliminar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Transportistas& t) { return t.id == id; });

    if (it != lista.end()) {
        char confirmar;
        cout << "�Eliminar transportista " << it->nombre << "? (s/n): ";
        cin >> confirmar;

        if (tolower(confirmar) == 's') {
            lista.erase(it);
            guardarEnArchivo(lista);
            cout << "Transportista eliminado!\n";
        } else {
            cout << "Operaci�n cancelada.\n";
        }
    } else {
        cout << "Transportista no encontrado.\n";
    }
    system("pause");
}

void Transportistas::cargarDesdeArchivo(std::vector<Transportistas>& lista) {
    lista.clear();
    std::ifstream archivo("transportistas.txt");

    if (!archivo.is_open()) {
        std::ofstream nuevoArchivo("transportistas.txt");
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        Transportistas transp;


        if (std::getline(ss, transp.id, ',') &&
            std::getline(ss, transp.nombre, ',') &&
            std::getline(ss, transp.telefono, ',') &&
            std::getline(ss, transp.vehiculo, ',') &&
            std::getline(ss, transp.disponibilidad)) {
            lista.push_back(transp);
        }
    }
}

void Transportistas::guardarEnArchivo(const std::vector<Transportistas>& lista) {
    std::ofstream archivo("transportistas.txt");

    for (const auto& transp : lista) {
        archivo << transp.id << ","
                << transp.nombre << ","
                << transp.telefono << ","
                << transp.vehiculo << ","
                << transp.disponibilidad << "\n";
    }
}

std::vector<Transportistas> Transportistas::getTransportistasDisponibles() {
    std::vector<Transportistas> transportistas;
    cargarDesdeArchivo(transportistas);

    // Filtrar solo los disponibles
    transportistas.erase(
        std::remove_if(transportistas.begin(), transportistas.end(),
            [](const Transportistas& t) { return t.disponibilidad != "disponible"; }),
        transportistas.end());

    return transportistas;
}
