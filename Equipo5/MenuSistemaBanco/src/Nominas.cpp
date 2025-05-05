//Programaddo por Priscila Sarai Guzmán Calgua 9959-23-450
#include "Nominas.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// Limpia la pantalla según el sistema operativo
void Nominas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa el programa hasta que el usuario presione ENTER
void Nominas::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Carga los empleados desde el archivo empleados.txt
void Nominas::cargarEmpleados() {
    empleados.clear();  // Vaciar lista actual
    ifstream archivo("empleados.txt");
    Empleados e;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = 0;
        int campo = 0;
        string datos[5];
        for (int i = 0; i < 4; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[4] = linea; // Salario

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

// Guarda todos los empleados en el archivo empleados.txt
void Nominas::guardarEmpleados() {
    ofstream archivo("empleados.txt");
    for (const auto& e : empleados) {
        archivo << e.nombre << "," << e.telefono << "," << e.codigo << "," << e.direccion << "," << e.salario << "\n";
    }
    archivo.close();
}

// Ordena los empleados alfabéticamente por nombre
void Nominas::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const Empleados& a, const Empleados& b) {
        return a.nombre < b.nombre;
    });
}

// Muestra el menú principal
void Nominas::menuNominas() {
    int opcion;
    do {
        cargarEmpleados(); // Cargar al entrar o después de cada operación
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

// Agrega un nuevo empleado
void Nominas::crearEmpleado() {
    limpiarPantalla();
    Empleados e;

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

    cout << "\nEmpleado agregado correctamente.";
    pausar();
}

// Borra un empleado por nombre y código
void Nominas::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Empleados> nuevaLista;

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
        cout << "\nEmpleado eliminado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Busca un empleado por nombre y código
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
            break;
        }
    }

    if (!encontrado) {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Modifica los datos de un empleado
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
        cout << "\nEmpleado modificado exitosamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Muestra todos los empleados
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
    }

    pausar();
}

