#include "Proveedores.h"
#include "Bitacora.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Bitacora bitacoralog1;  // Instancia global para registrar eventos
using namespace std;

// Limpia la pantalla seg�n el sistema operativo
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
        datos[3] = linea; // Direcci�n

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

// Ordena los proveedores alfab�ticamente por nombre
void Proveedor::ordenarProveedores() {
    sort(proveedores.begin(), proveedores.end(), [](const Proveedor& a, const Proveedor& b) {
        return a.nombre < b.nombre;
    });
}

// Muestra el men� principal de proveedores
void Proveedor::menuProveedor() {
    int opcion;
    do {
        cargarProveedores(); // Cargar al entrar o despu�s de cada operaci�n
        limpiarPantalla();
        cout << "\n===== MEN� DE PROVEEDORES =====";
        cout << "\n1. Crear Proveedor";
        cout << "\n2. Borrar Proveedor";
        cout << "\n3. Buscar Proveedor";
        cout << "\n4. Modificar Proveedor";
        cout << "\n5. Despliegue de Proveedores";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opci�n: ";
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
                cout << "\nOpci�n inv�lida.";
                pausar();
        }
    } while (true);
}

// Agrega un nuevo proveedor
void Proveedor::crearProveedor() {
    limpiarPantalla();
    Proveedor p;

    cout << "\n=== Crear Proveedor ===";
    cout << "\nC�digo: "; getline(cin, p.codigo);
    cout << "Nombre: "; getline(cin, p.nombre);
    cout << "Tel�fono: "; getline(cin, p.telefono);
    cout << "Direcci�n: "; getline(cin, p.direccion);

    proveedores.push_back(p);
    ordenarProveedores();
    guardarProveedores();

    cout << "\nProveedor agregado correctamente.";
    bitacoralog1.insertar("Admin", 4201, "Proveedores", "Crear Proveedor");
    pausar();
}

// Borra un proveedor por c�digo
void Proveedor::borrarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Borrar Proveedor ===";
    cout << "\nC�digo: "; getline(cin, codigo);

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
        bitacoralog1.insertar("Admin", 4204, "Proveedores", "Borrar Proveedor");
        cout << "\nProveedor eliminado correctamente.";
    } else {
        cout << "\nProveedor no encontrado.";
    }

    pausar();
}

// Busca un proveedor por c�digo
void Proveedor::buscarProveedor() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Buscar Proveedor ===";
    cout << "\nC�digo: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& p : proveedores) {
        if (p.codigo == codigo) {
            cout << "\nProveedor encontrado:";
            cout << "\nC�digo    : " << p.codigo;
            cout << "\nNombre    : " << p.nombre;
            cout << "\nTel�fono  : " << p.telefono;
            cout << "\nDirecci�n : " << p.direccion;
            encontrado = true;
            break;
            bitacoralog1.insertar("Admin", 4202, "Proveedores", "Busqueda de Proveedor");
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
    cout << "\nC�digo: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& p : proveedores) {
        if (p.codigo == codigo) {
            cout << "\nIngrese nueva informaci�n:";
            cout << "\nNuevo Nombre: "; getline(cin, p.nombre);
            cout << "Nuevo Tel�fono: "; getline(cin, p.telefono);
            cout << "Nueva Direcci�n: "; getline(cin, p.direccion);
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarProveedores();
        guardarProveedores();
        bitacoralog1.insertar("Admin", 4203, "Proveedores", "Modificacion de Proveedor");
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
            cout << "\nC�digo    : " << p.codigo;
            cout << "\nNombre    : " << p.nombre;
            cout << "\nTel�fono  : " << p.telefono;
            cout << "\nDirecci�n : " << p.direccion;
        }
        cout << "\n-----------------------------";
    }

    pausar();
}


