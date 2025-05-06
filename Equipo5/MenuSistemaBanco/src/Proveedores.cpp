//Programaddo por Boris Ivan de Leon Santos 9959-24-6203
#include "Proveedores.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

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

// Carga los proveedores desde el archivo proveedores.txt
void Proveedor::cargarProveedores() {
    proveedores.clear();  // Vaciar lista actual
    ifstream archivo("proveedores.txt");
    Proveedor p;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = 0;
        int campo = 0;
        string datos[4];
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[3] = linea; // Dirección

        p.codigo = datos[0];
        p.nombre = datos[1];
        p.telefono = datos[2];
        p.direccion = datos[3];

        proveedores.push_back(p);
    }

    archivo.close();
    ordenarProveedores();
}

// Guarda todos los proveedores en el archivo proveedores.txt
void Proveedor::guardarProveedores() {
    ofstream archivo("proveedores.txt");
    for (const auto& p : proveedores) {
        archivo << p.codigo << "," << p.nombre << "," << p.telefono << "," << p.direccion << "\n";
    }
    archivo.close();
}

// Ordena los proveedores alfabéticamente por nombre
void Proveedor::ordenarProveedores() {
    sort(proveedores.begin(), proveedores.end(), [](const Proveedor& a, const Proveedor& b) {
        return a.nombre < b.nombre;
    });
}

// Muestra el menú principal de proveedores
void Proveedor::menuProveedor() {
    int opcion;
    do {
        cargarProveedores(); // Cargar al entrar o después de cada operación
        limpiarPantalla();
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

// Agrega un nuevo proveedor
void Proveedor::crearProveedor() {
    limpiarPantalla();
    Proveedor p;

    cout << "\n=== Crear Proveedor ===";
    cout << "\nCódigo: "; getline(cin, p.codigo);
    cout << "Nombre: "; getline(cin, p.nombre);
    cout << "Teléfono: "; getline(cin, p.telefono);
    cout << "Dirección: "; getline(cin, p.direccion);

    proveedores.push_back(p);
    ordenarProveedores();
    guardarProveedores();

    cout << "\nProveedor agregado correctamente.";
    pausar();
}

// Borra un proveedor por código
void Proveedor::borrarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Borrar Proveedor ===";
    cout << "\nCódigo: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Proveedor> nuevaLista;

    for (const auto& p : proveedores) {
        if (p.codigo != codigo) {
            nuevaLista.push_back(p);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        proveedores = nuevaLista;
        guardarProveedores();
        cout << "\nProveedor eliminado correctamente.";
    } else {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Busca un proveedor por código
void Proveedor::buscarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Buscar Proveedor ===";
    cout << "\nCódigo: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& p : proveedores) {
        if (p.codigo == codigo) {
            cout << "\nProveedor encontrado:";
            cout << "\nCódigo    : " << p.codigo;
            cout << "\nNombre    : " << p.nombre;
            cout << "\nTeléfono  : " << p.telefono;
            cout << "\nDirección : " << p.direccion;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Modifica los datos de un proveedor
void Proveedor::modificarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Modificar Proveedor ===";
    cout << "\nCódigo: "; getline(cin, codigo);

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
        ordenarProveedores();
        guardarProveedores();
        cout << "\nProveedor modificado exitosamente.";
    } else {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Muestra todos los proveedores
void Proveedor::desplegarProveedores() {
    limpiarPantalla();
    cout << "\n=== Proveedores Registrados ===\n";

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
    }

    pausar();
}


