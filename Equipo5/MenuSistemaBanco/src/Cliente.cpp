//Programaddo por Boris Ivan de Leon Santos 9959-24-6203
#include "Cliente.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Limpia la pantalla según el sistema operativo
void Cliente::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa el programa hasta que el usuario presione ENTER
void Cliente::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Carga los clientes desde el archivo clientes.txt
void Cliente::cargarClientes() {
    clientes.clear();  // Vaciar lista actual
    ifstream archivo("clientes.txt");
    Cliente c;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = 0;
        int campo = 0;
        string datos[4];  // Solo 4 campos ahora (sin saldo)
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[3] = linea; // Dirección

        c.codigo = datos[0];
        c.nombre = datos[1];
        c.telefono = datos[2];
        c.direccion = datos[3];

        clientes.push_back(c);
    }

    archivo.close();
    ordenarClientes();
}

// Guarda todos los clientes en el archivo clientes.txt
void Cliente::guardarClientes() {
    ofstream archivo("clientes.txt");
    for (const auto& c : clientes) {
        archivo << c.codigo << "," << c.nombre << "," << c.telefono << "," << c.direccion << "\n";
    }
    archivo.close();
}

// Ordena los clientes alfabéticamente por nombre
void Cliente::ordenarClientes() {
    sort(clientes.begin(), clientes.end(), [](const Cliente& a, const Cliente& b) {
        return a.nombre < b.nombre;
    });
}

// Muestra el menú principal
void Cliente::menuCliente() {
    int opcion;
    do {
        cargarClientes(); // Cargar al entrar o después de cada operación
        limpiarPantalla();
        cout << "\n===== MENÚ DE CLIENTES =====";
        cout << "\n1. Crear Cliente";
        cout << "\n2. Borrar Cliente";
        cout << "\n3. Buscar Cliente";
        cout << "\n4. Modificar Cliente";
        cout << "\n5. Despliegue de Clientes";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearCliente(); break;
            case 2: borrarCliente(); break;
            case 3: buscarCliente(); break;
            case 4: modificarCliente(); break;
            case 5: desplegarClientes(); break;
            case 6:
                limpiarPantalla();
                return;
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// Agrega un nuevo cliente
void Cliente::crearCliente() {
    limpiarPantalla();
    Cliente c;

    cout << "\n=== Crear Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, c.codigo);  // Colocado primero
    cout << "Nombre: "; getline(cin, c.nombre);
    cout << "Teléfono: "; getline(cin, c.telefono);
    cout << "Dirección: "; getline(cin, c.direccion);

    clientes.push_back(c);
    ordenarClientes();
    guardarClientes();

    cout << "\nCliente agregado correctamente.";
    pausar();
}

// Borra un cliente por código
void Cliente::borrarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Borrar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Cliente> nuevaLista;

    for (const auto& c : clientes) {
        if (c.codigo != codigo) {
            nuevaLista.push_back(c);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        clientes = nuevaLista;
        guardarClientes();
        cout << "\nCliente eliminado correctamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Busca un cliente por código
void Cliente::buscarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Buscar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nCliente encontrado:";
            cout << "\nCódigo    : " << c.codigo;
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTeléfono  : " << c.telefono;
            cout << "\nDirección : " << c.direccion;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Modifica los datos de un cliente
void Cliente::modificarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Modificar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nIngrese nueva información:";
            cout << "\nNuevo Código: "; getline(cin, c.codigo);
            cout << "Nuevo Nombre: "; getline(cin, c.nombre);
            cout << "Nuevo Teléfono: "; getline(cin, c.telefono);
            cout << "Nueva Dirección: "; getline(cin, c.direccion);
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarClientes();
        guardarClientes();
        cout << "\nCliente modificado exitosamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Muestra todos los clientes
void Cliente::desplegarClientes() {
    limpiarPantalla();
    cout << "\n=== Clientes Registrados ===\n";

    if (clientes.empty()) {
        cout << "\nNo hay clientes registrados.";
    } else {
        for (const auto& c : clientes) {
            cout << "\n-----------------------------";
            cout << "\nCódigo    : " << c.codigo;  // Muestra primero el código
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTeléfono  : " << c.telefono;
            cout << "\nDirección : " << c.direccion;
        }
        cout << "\n-----------------------------";
    }

    pausar();
}

