#include "Nominas.h"
#include <iostream>
#include <limits>

using namespace std;

void Nominas::menuNominas() {
    int opcion;
    do {
        cout << "\n===== MENU NOMINAS =====";
        cout << "\n1. Crear Empleado";
        cout << "\n2. Borrar Empleado";
        cout << "\n3. Buscar Empleado";
        cout << "\n4. Modificar Empleado";
        cout << "\n5. Salir";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearEmpleado(); break;
            case 2: borrarEmpleado(); break;
            case 3: buscarEmpleado(); break;
            case 4: modificarEmpleado(); break;
            case 5: cout << "Saliendo a menu principal...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 5);
}

void Nominas::crearEmpleado() {
    DatosEmpleado nuevo;
    cout << "\n--- Crear Empleado ---\n";
    cout << "Nombre: ";
    getline(cin, nuevo.nombre);
    cout << "Telefono: ";
    getline(cin, nuevo.telefono);
    cout << "Codigo: ";
    getline(cin, nuevo.codigo);
    cout << "Direccion: ";
    getline(cin, nuevo.direccion);
    cout << "Salario: ";
    cin >> nuevo.salario;
    cin.ignore();

    empleados.push_back(nuevo);
    cout << "Empleado agregado correctamente.\n";
}

void Nominas::borrarEmpleado() {
    string nombre, codigo;
    cout << "\n--- Borrar Empleado ---\n";
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Codigo: ";
    getline(cin, codigo);

    for (auto it = empleados.begin(); it != empleados.end(); ++it) {
        if (it->nombre == nombre && it->codigo == codigo) {
            empleados.erase(it);
            cout << "Empleado eliminado exitosamente.\n";
            return;
        }
    }
    cout << "Empleado no encontrado.\n";
}

void Nominas::buscarEmpleado() {
    string nombre, codigo;
    cout << "\n--- Buscar Empleado ---\n";
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Codigo: ";
    getline(cin, codigo);

    for (const auto& emp : empleados) {
        if (emp.nombre == nombre && emp.codigo == codigo) {
            cout << "\nInformación del Empleado:\n";
            cout << "Nombre: " << emp.nombre << "\n";
            cout << "Telefono: " << emp.telefono << "\n";
            cout << "Codigo: " << emp.codigo << "\n";
            cout << "Direccion: " << emp.direccion << "\n";
            cout << "Salario: " << emp.salario << "\n";
            return;
        }
    }
    cout << "Empleado no encontrado.\n";
}

void Nominas::modificarEmpleado() {
    string nombre, codigo;
    cout << "\n--- Modificar Empleado ---\n";
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Codigo: ";
    getline(cin, codigo);

    for (auto& emp : empleados) {
        if (emp.nombre == nombre && emp.codigo == codigo) {
            cout << "\nModificar Información:\n";
            cout << "Nuevo Nombre: ";
            getline(cin, emp.nombre);
            cout << "Nuevo Telefono: ";
            getline(cin, emp.telefono);
            cout << "Nuevo Codigo: ";
            getline(cin, emp.codigo);
            cout << "Nueva Direccion: ";
            getline(cin, emp.direccion);
            cout << "Nuevo Salario: ";
            cin >> emp.salario;
            cin.ignore();
            cout << "Empleado modificado exitosamente.\n";
            return;
        }
    }
    cout << "Empleado no encontrado.\n";
}
