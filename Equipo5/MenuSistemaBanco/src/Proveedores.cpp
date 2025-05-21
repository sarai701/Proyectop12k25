// Boris de León 9959-24-6203
#include "Proveedores.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Bitacora.h"

using namespace std;
Bitacora bitacoralogProveedores;

// Limpia la pantalla según el sistema operativo
void Proveedor::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa el programa hasta que el usuario presione ENTER
void Proveedor::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Carga los proveedores desde el archivo binario "proveedores.dat"
vector<Proveedor> Proveedor::cargarProveedores() {
    vector<Proveedor> proveedores;
    ifstream archivo("proveedores.dat", ios::binary);
    if (!archivo) {
        // Si no existe archivo, retornar vector vacío
        return proveedores;
    }

    // Leer hasta el final del archivo
    while (true) {
        Proveedor p;
        size_t size;

        // Leer tamaño y contenido del campo codigo
        if (!archivo.read(reinterpret_cast<char*>(&size), sizeof(size))) break;
        p.codigo.resize(size);
        archivo.read(&p.codigo[0], size);

        // Leer tamaño y contenido del campo nombre
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        p.nombre.resize(size);
        archivo.read(&p.nombre[0], size);

        // Leer tamaño y contenido del campo telefono
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        p.telefono.resize(size);
        archivo.read(&p.telefono[0], size);

        // Leer tamaño y contenido del campo direccion
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        p.direccion.resize(size);
        archivo.read(&p.direccion[0], size);

        proveedores.push_back(p);
    }
    archivo.close();
    ordenarProveedores(proveedores);
    return proveedores;
}

// Guarda todos los proveedores en el archivo binario "proveedores.dat"
void Proveedor::guardarProveedores(const vector<Proveedor>& proveedores) {
    ofstream archivo("proveedores.dat", ios::binary | ios::trunc);
    for (const auto& p : proveedores) {
        size_t size;

        // Guardar codigo con tamaño y datos
        size = p.codigo.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.codigo.c_str(), size);

        // Guardar nombre con tamaño y datos
        size = p.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.nombre.c_str(), size);

        // Guardar telefono con tamaño y datos
        size = p.telefono.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.telefono.c_str(), size);

        // Guardar direccion con tamaño y datos
        size = p.direccion.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(p.direccion.c_str(), size);
    }
    archivo.close();
}

// Ordena el vector de proveedores alfabéticamente por nombre
void Proveedor::ordenarProveedores(vector<Proveedor>& proveedores) {
    sort(proveedores.begin(), proveedores.end(), [](const Proveedor& a, const Proveedor& b) {
        return a.nombre < b.nombre;
    });
}

void Proveedor::setUsuario(const string& u) {
    usuario = u;
}

// Muestra el menú principal para la gestión de proveedores
void Proveedor::menuProveedor() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MENÚ DE PROVEEDORES =====";
        cout << "\n1. Crear Proveedor";
        cout << "\n2. Borrar Proveedor";
        cout << "\n3. Buscar Proveedor";
        cout << "\n4. Modificar Proveedor";
        cout << "\n5. Despliegue de Proveedores";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearProveedor(); break;
            case 2: borrarProveedor(); break;
            case 3: buscarProveedor(); break;
            case 4: modificarProveedor(); break;
            case 5: desplegarProveedores(); break;
            case 6:
                limpiarPantalla();
                return;
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// Crea un nuevo proveedor solicitando datos al usuario y lo guarda
void Proveedor::crearProveedor() {
    limpiarPantalla();
    Proveedor p;
    vector<Proveedor> proveedores = cargarProveedores();

    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Crear Proveedor ===";
    cout << "\nCódigo: "; getline(cin, p.codigo);
    cout << "Nombre: "; getline(cin, p.nombre);
    cout << "Teléfono: "; getline(cin, p.telefono);
    cout << "Dirección: "; getline(cin, p.direccion);

    proveedores.push_back(p);
    ordenarProveedores(proveedores);
    guardarProveedores(proveedores);
    bitacoralogProveedores.insertar(usuario, 4011, "Proveedores", "Crear Proveedor");
    cout << "\nProveedor agregado correctamente.";
    pausar();
}

// Borra un proveedor buscándolo por código
void Proveedor::borrarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Borrar Proveedor ===";
    cout << "\nCódigo: "; getline(cin, codigo);

    vector<Proveedor> proveedores = cargarProveedores();
    size_t inicial = proveedores.size();

    proveedores.erase(
        remove_if(proveedores.begin(), proveedores.end(), [&](const Proveedor& p) {
            return p.codigo == codigo;
        }),
        proveedores.end()
    );

    if (proveedores.size() < inicial) {
        guardarProveedores(proveedores);
        bitacoralogProveedores.insertar(usuario, 4012, "Proveedores", "Borrar Proveedor");
        cout << "\nProveedor eliminado correctamente.";
    } else {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Busca un proveedor por código y muestra su información
void Proveedor::buscarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Buscar Proveedor ===";
    cout << "\nCódigo: "; getline(cin, codigo);

    vector<Proveedor> proveedores = cargarProveedores();
    bool encontrado = false;

    for (const auto& p : proveedores) {
        if (p.codigo == codigo) {
            cout << "\nUsuario: " << usuario << endl;
            cout << "\nProveedor encontrado:";
            cout << "\nCódigo    : " << p.codigo;
            cout << "\nNombre    : " << p.nombre;
            cout << "\nTeléfono  : " << p.telefono;
            cout << "\nDirección : " << p.direccion;
            encontrado = true;
            bitacoralogProveedores.insertar(usuario, 4013, "Proveedores", "Buscar Proveedor");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Modifica un proveedor existente buscando por código y pidiendo nuevos datos
void Proveedor::modificarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Modificar Proveedor ===";
    cout << "\nCódigo: "; getline(cin, codigo);

    vector<Proveedor> proveedores = cargarProveedores();
    bool modificado = false;

    for (auto& p : proveedores) {
        if (p.codigo == codigo) {
            cout << "\nIngrese nueva información:";
            cout << "\nNuevo Nombre: "; getline(cin, p.nombre);
            cout << "Nuevo Teléfono: "; getline(cin, p.telefono);
            cout << "Nueva Dirección: "; getline(cin, p.direccion);
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarProveedores(proveedores);
        guardarProveedores(proveedores);
        bitacoralogProveedores.insertar(usuario, 4014, "Proveedores", "Modificar Proveedor");
        cout << "\nProveedor modificado exitosamente.";
    } else {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Muestra todos los proveedores registrados
void Proveedor::desplegarProveedores() {
    limpiarPantalla();
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Proveedores Registrados ===\n";

    vector<Proveedor> proveedores = cargarProveedores();
    if (proveedores.empty()) {
        cout << "\nNo hay proveedores registrados.";
    } else {
        for (const auto& p : proveedores) {
            cout << "\n-----------------------------";
            cout << "\nCódigo    : " << p.codigo;
            cout << "\nNombre    : " << p.nombre;
            cout << "\nTeléfono  : " << p.telefono;
            cout << "\nDirección : " << p.direccion;
        }
        cout << "\n-----------------------------";
        bitacoralogProveedores.insertar(usuario, 4015, "Proveedores", "Desplegar Proveedores");
    }

    pausar();
}
