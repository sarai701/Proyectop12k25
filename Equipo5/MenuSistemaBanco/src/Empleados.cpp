// Karla Patricia Ruiz Ordoñez 9959-24-6859
#include "Empleados.h"      // Inclusión del encabezado de empleados (clase y prototipos)
#include <iostream>         // Para entrada/salida estándar
#include <fstream>          // Para manejo de archivos
#include <algorithm>        // Para funciones como sort()

using namespace std;        // Espacio de nombres estándar

// ===================================================
// FUNCIONES UTILITARIAS
// ===================================================

// Limpia la pantalla dependiendo del sistema operativo
void Empleados::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa la ejecución hasta que el usuario presione ENTER
void Empleados::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// ===================================================
// FUNCIONES DE MANEJO DE ARCHIVOS
// ===================================================

// Carga los empleados desde el archivo "empleados.txt" y los almacena en el vector
void Empleados::cargarEmpleados() {
    empleados.clear();  // Limpia cualquier dato anterior
    ifstream archivo("empleados.txt");
    Empleado e;
    string linea;

    // Lee línea por línea el archivo
    while (getline(archivo, linea)) {
        size_t pos = 0;
        string datos[4];

        // Extrae los campos separados por comas (nombre, código, puesto, teléfono)
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[3] = linea; // El último campo (teléfono)

        // Asigna los datos al objeto empleado
        e.nombre = datos[0];
        e.codigo = datos[1];
        e.puesto = datos[2];
        e.telefono = datos[3];

        empleados.push_back(e);  // Lo agrega al vector
    }

    archivo.close();  // Cierra el archivo
    ordenarEmpleados();  // Ordena los empleados
}

// Guarda los empleados actuales en el archivo "empleados.txt"
void Empleados::guardarEmpleados() {
    ofstream archivo("empleados.txt");
    for (const auto& e : empleados) {
        archivo << e.nombre << "," << e.codigo << "," << e.puesto << "," << e.telefono << "\n";
    }
    archivo.close();
}

// Ordena alfabéticamente por nombre usando `std::sort` y lambda
void Empleados::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const Empleado& a, const Empleado& b) {
        return a.nombre < b.nombre;
    });
}

// ===================================================
// MENÚ Y OPCIONES PRINCIPALES
// ===================================================

// Menú principal para gestión de empleados
void Empleados::menuEmpleados() {
    int opcion;
    do {
        cargarEmpleados();  // Se actualiza la lista antes de mostrar el menú
        limpiarPantalla();

        // Menú de opciones
        cout << "\n===== MENÚ DE EMPLEADOS =====";
        cout << "\n1. Crear Empleado";
        cout << "\n2. Borrar Empleado";
        cout << "\n3. Buscar Empleado";
        cout << "\n4. Modificar Empleado";
        cout << "\n5. Despliegue de Empleados";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        // Control de opciones
        switch (opcion) {
            case 1: crearEmpleado(); break;
            case 2: borrarEmpleado(); break;
            case 3: buscarEmpleado(); break;
            case 4: modificarEmpleado(); break;
            case 5: desplegarEmpleados(); break;
            case 6:
                limpiarPantalla();  // Limpia antes de salir
                return;
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// ===================================================
// FUNCIONES DE CRUD (Crear, Leer, Modificar, Eliminar)
// ===================================================

// Crea un nuevo empleado y lo guarda
void Empleados::crearEmpleado() {
    limpiarPantalla();
    Empleado e;

    // Entrada de datos
    cout << "\n=== Crear Empleado ===";
    cout << "\nNombre: "; getline(cin, e.nombre);
    cout << "Código: "; getline(cin, e.codigo);
    cout << "Puesto de trabajo: "; getline(cin, e.puesto);
    cout << "Teléfono: "; getline(cin, e.telefono);

    empleados.push_back(e);  // Añadir al vector
    ordenarEmpleados();
    guardarEmpleados();  // Persistencia

    // Bitácora: registrar la acción
    bitacoralogEmpleados.insertar("Admin", 4001, "Empleados", "Crear");
    cout << "\nEmpleado agregado correctamente.";
    pausar();
}

// Elimina un empleado que coincida con nombre y código
void Empleados::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Empleado> nuevaLista;

    // Reconstruye la lista sin el empleado a eliminar
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
        bitacoralogEmpleados.insertar("Admin", 4002, "Empleados", "Borrar");
        cout << "\nEmpleado eliminado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Busca un empleado específico por nombre y código
void Empleados::buscarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Buscar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool encontrado = false;

    // Recorre los empleados en búsqueda de coincidencias
    for (const auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre   : " << e.nombre;
            cout << "\nCódigo   : " << e.codigo;
            cout << "\nPuesto   : " << e.puesto;
            cout << "\nTeléfono : " << e.telefono;
            bitacoralogEmpleados.insertar("Admin", 4003, "Empleados", "Buscar");
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}


// Modifica la información de un empleado existente
void Empleados::modificarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Modificar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool modificado = false;

    // Busca y actualiza los datos del empleado
    for (auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nIngrese nueva información:";
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre);
            cout << "Nuevo Código: "; getline(cin, e.codigo);
            cout << "Nuevo Puesto: "; getline(cin, e.puesto);
            cout << "Nuevo Teléfono: "; getline(cin, e.telefono);
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarEmpleados();
        guardarEmpleados();
        bitacoralogEmpleados.insertar("Admin", 4004, "Empleados", "Modificar");
        cout << "\nEmpleado modificado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Muestra la lista de todos los empleados
void Empleados::desplegarEmpleados() {
    limpiarPantalla();
    cout << "\n=== Empleados Registrados ===\n";

    if (empleados.empty()) {
        cout << "\nNo hay empleados registrados.";
    } else {
        for (const auto& e : empleados) {
            cout << "\n----------------------------";
            cout << "\nNombre   : " << e.nombre;
            cout << "\nCódigo   : " << e.codigo;
            cout << "\nPuesto   : " << e.puesto;
            cout << "\nTeléfono : " << e.telefono;
        }
        cout << "\n----------------------------";
        bitacoralogEmpleados.insertar("Admin", 4005, "Empleados", "Desplegar");
    }

    pausar();
}

