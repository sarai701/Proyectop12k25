#include "Cliente.h"
#include "Bitacora.h" // Agrega la bitacora
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

Bitacora log; // Instancia global para registrar eventos
using namespace std;

// Limpia la pantalla seg�n el sistema operativo
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
        datos[3] = linea; // Direcci�n

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

// Ordena los clientes alfab�ticamente por nombre
void Cliente::ordenarClientes() {
    sort(clientes.begin(), clientes.end(), [](const Cliente& a, const Cliente& b) {
        return a.nombre < b.nombre;
    });
}

// Muestra el men� principal
void Cliente::menuCliente() {
    int opcion;
    do {
        cargarClientes(); // Cargar al entrar o despu�s de cada operaci�n
        limpiarPantalla();
        cout << "\n===== MEN� DE CLIENTES =====";
        cout << "\n1. Crear Cliente";
        cout << "\n2. Borrar Cliente";
        cout << "\n3. Buscar Cliente";
        cout << "\n4. Modificar Cliente";
        cout << "\n5. Despliegue de Clientes";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opci�n: ";
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
                cout << "\nOpci�n inv�lida.";
                pausar();
        }
    } while (true);
}

// Agrega un nuevo cliente
void Cliente::crearCliente() {
    limpiarPantalla();
    Cliente c;

    cout << "\n=== Crear Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, c.codigo);  // Colocado primero
    cout << "Nombre: "; getline(cin, c.nombre);
    cout << "Tel�fono: "; getline(cin, c.telefono);
    cout << "Direcci�n: "; getline(cin, c.direccion);

    clientes.push_back(c);
    ordenarClientes();
    guardarClientes();

    cout << "\nCliente agregado correctamente.";
    log.insertar("Admin", 4101, "Clientes", "Crear Cliente");

    pausar();
}

// Borra un cliente por c�digo
void Cliente::borrarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Borrar Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, codigo);

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
        log.insertar("Admin", 4104, "Clientes", "Borrar Cliente");

        cout << "\nCliente eliminado correctamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Busca un cliente por c�digo
void Cliente::buscarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Buscar Cliente ===";
    cout << "\nC�digo de Cliente: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nCliente encontrado:";
            cout << "\nC�digo    : " << c.codigo;
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTel�fono  : " << c.telefono;
            cout << "\nDirecci�n : " << c.direccion;
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
    cout << "\nC�digo de Cliente: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nIngrese nueva informaci�n:";
            cout << "\nNuevo C�digo: "; getline(cin, c.codigo);
            cout << "Nuevo Nombre: "; getline(cin, c.nombre);
            cout << "Nuevo Tel�fono: "; getline(cin, c.telefono);
            cout << "Nueva Direcci�n: "; getline(cin, c.direccion);
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarClientes();
        guardarClientes();
        log.insertar("Admin", 4103, "Clientes", "Modificar Cliente");

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
            cout << "\nC�digo    : " << c.codigo;  // Muestra primero el c�digo
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTel�fono  : " << c.telefono;
            cout << "\nDirecci�n : " << c.direccion;
        }
        cout << "\n-----------------------------";
    }

    pausar();
}

