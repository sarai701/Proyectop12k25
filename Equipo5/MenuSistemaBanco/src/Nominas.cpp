//Programaddo por Priscila Sarai Guzmán Calgua 9959-23-450
#include "Nominas.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Bitacora.h"

Bitacora bitacoralog3;
using namespace std;

// Limpia la pantalla según el sistema operativo
void Nominas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa hasta que el usuario presione ENTER
void Nominas::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Cargar empleados desde archivo
void Nominas::cargarEmpleados() {
    empleados.clear();
    ifstream archivo("empleados.txt");
    EmpleadoNomina e;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = 0;
        string datos[5];

        for (int i = 0; i < 4; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[4] = linea;

        e.nombre = datos[0];
        e.telefono = datos[1];
        e.codigo = datos[2];
        e.direccion = datos[3];
        e.salario = stof(datos[4]);

        empleados.push_back(e);
    }

    archivo.close();
    ordenarEmpleados();
}

// Guardar empleados en archivo
void Nominas::guardarEmpleados() {
    ofstream archivo("empleados.txt");
    for (const auto& e : empleados) {
        archivo << e.nombre << "," << e.telefono << "," << e.codigo << "," << e.direccion << "," << e.salario << "\n";
    }
    archivo.close();
}

// Ordenar alfabéticamente por nombre
void Nominas::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const EmpleadoNomina& a, const EmpleadoNomina& b) {
        return a.nombre < b.nombre;
    });
}

// Menú de nóminas
void Nominas::menuNominas() {
    int opcion;
    do {
        cargarEmpleados();
        limpiarPantalla();
        cout << "\n===== MENÚ DE NÓMINAS =====";
        cout << "\n1. Crear Empleado";
        cout << "\n2. Borrar Empleado";
        cout << "\n3. Buscar Empleado";
        cout << "\n4. Modificar Empleado";
        cout << "\n5. Despliegue de Empleados";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearEmpleado(); break;
            case 2: borrarEmpleado(); break;
            case 3: buscarEmpleado(); break;
            case 4: modificarEmpleado(); break;
            case 5: desplegarEmpleados(); break;
            case 6:
                limpiarPantalla();
                return;
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// Crear nuevo empleado
void Nominas::crearEmpleado() {
    limpiarPantalla();
    EmpleadoNomina e;

    cout << "\n=== Crear Empleado ===";
    cout << "\nNombre: "; getline(cin, e.nombre);
    cout << "Teléfono: "; getline(cin, e.telefono);
    cout << "Código: "; getline(cin, e.codigo);
    cout << "Dirección: "; getline(cin, e.direccion);
    cout << "Salario: Q"; cin >> e.salario;
    cin.ignore();

    empleados.push_back(e);
    ordenarEmpleados();
    guardarEmpleados();

    bitacoralog3.insertar("Admin", 4001, "Nominas", "Crear empleado");
    cout << "\nEmpleado agregado correctamente.";
    pausar();
}

// Borrar empleado por nombre y código
void Nominas::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool eliminado = false;
    vector<EmpleadoNomina> nuevaLista;

    for (const auto& e : empleados) {
        if (e.nombre != nombre || e.codigo != codigo) {
            nuevaLista.push_back(e);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        empleados = nuevaLista;
        guardarEmpleados();
        bitacoralog3.insertar("Admin", 4002, "Nominas", "Eliminar empleado");
        cout << "\nEmpleado eliminado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Buscar empleado por nombre y código
void Nominas::buscarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Buscar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre    : " << e.nombre;
            cout << "\nTeléfono  : " << e.telefono;
            cout << "\nCódigo    : " << e.codigo;
            cout << "\nDirección : " << e.direccion;
            cout << "\nSalario   : Q" << e.salario;
            encontrado = true;
            bitacoralog3.insertar("Admin", 4003, "Nominas", "Buscar empleado");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Modificar datos de un empleado
void Nominas::modificarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Modificar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nIngrese nueva información:";
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre);
            cout << "Nuevo Teléfono: "; getline(cin, e.telefono);
            cout << "Nuevo Código: "; getline(cin, e.codigo);
            cout << "Nueva Dirección: "; getline(cin, e.direccion);
            cout << "Nuevo Salario: Q"; cin >> e.salario;
            cin.ignore();
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarEmpleados();
        guardarEmpleados();
        bitacoralog3.insertar("Admin", 4004, "Nominas", "Modificar empleado");
        cout << "\nEmpleado modificado exitosamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Mostrar todos los empleados
void Nominas::desplegarEmpleados() {
    limpiarPantalla();
    cout << "\n=== Empleados Registrados ===\n";

    if (empleados.empty()) {
        cout << "\nNo hay empleados registrados.";
    } else {
        for (const auto& e : empleados) {
            cout << "\n-----------------------------";
            cout << "\nNombre    : " << e.nombre;
            cout << "\nTeléfono  : " << e.telefono;
            cout << "\nCódigo    : " << e.codigo;
            cout << "\nDirección : " << e.direccion;
            cout << "\nSalario   : Q" << e.salario;
        }
        cout << "\n-----------------------------";
        bitacoralog3.insertar("Admin", 4005, "Nominas", "Ver empleados");
    }

    pausar();
}

