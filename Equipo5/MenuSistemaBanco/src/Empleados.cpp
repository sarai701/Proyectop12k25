//Programaddo por Karla Patricia Ruiz Ordoñez 9959-24-6859
#include "Empleados.h"      // Incluye la declaración de la clase Empleados y sus métodos
#include <iostream>         // Permite usar entradas y salidas estándar (cin, cout)
#include <fstream>          // Permite manejo de archivos (ifstream, ofstream)
#include <algorithm>        // Para usar funciones como sort
#include "Bitacora.h"       // Bitácora para registrar acciones

using namespace std;

Bitacora bitacoralogEmpleados; // Instancia para registrar acciones de empleados en la bitácora

// Método para limpiar pantalla según el sistema operativo
void Empleados::limpiarPantalla() {
#ifdef _WIN32
    system("cls");           // En Windows limpia con cls
#else
    system("clear");         // En otros sistemas (Linux, Mac) limpia con clear
#endif
}

// Método para pausar la ejecución del programa hasta que el usuario presione ENTER
void Empleados::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();            // Ignora cualquier carácter en el buffer
    cin.get();               // Espera a que el usuario presione ENTER
}

// Carga los datos de empleados desde el archivo empleados.txt
void Empleados::cargarEmpleados() {
    empleados.clear();                       // Limpia el vector antes de cargar nuevos datos
    ifstream archivo("empleados.txt");      // Abre el archivo de lectura
    Empleado e;
    string linea;

    while (getline(archivo, linea)) {       // Lee línea por línea
        size_t pos = 0;
        string datos[4];

        // Divide la línea por comas para separar los campos
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[3] = linea; // Último campo (teléfono)

        // Asigna los valores al objeto Empleado
        e.nombre = datos[0];
        e.codigo = datos[1];
        e.puesto = datos[2];
        e.telefono = datos[3];

        empleados.push_back(e);             // Agrega el empleado al vector
    }

    archivo.close();                        // Cierra el archivo
    ordenarEmpleados();                     // Ordena alfabéticamente
}

// Guarda la lista de empleados actual en el archivo empleados.txt
void Empleados::guardarEmpleados() {
    ofstream archivo("empleados.txt");      // Abre el archivo para escritura
    for (const auto& e : empleados) {
        archivo << e.nombre << "," << e.codigo << "," << e.puesto << "," << e.telefono << "\n";
    }
    archivo.close();                        // Cierra el archivo
}

// Ordena alfabéticamente el vector de empleados por nombre
void Empleados::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const Empleado& a, const Empleado& b) {
        return a.nombre < b.nombre;
    });
}

// Muestra el menú principal de empleados y gestiona las opciones del usuario
void Empleados::menuEmpleados() {
    int opcion;
    do {
        cargarEmpleados();                  // Carga datos antes de cada acción
        limpiarPantalla();
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

        switch (opcion) {
            case 1: crearEmpleado(); break;
            case 2: borrarEmpleado(); break;
            case 3: buscarEmpleado(); break;
            case 4: modificarEmpleado(); break;
            case 5: desplegarEmpleados(); break;
            case 6:
                limpiarPantalla(); return;  // Salir del menú
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// Crea un nuevo empleado solicitando los datos al usuario
void Empleados::crearEmpleado() {
    limpiarPantalla();
    Empleado e;
    cout << "\n=== Crear Empleado ===";
    cout << "\nNombre: "; getline(cin, e.nombre);
    cout << "Código: "; getline(cin, e.codigo);
    cout << "Puesto de trabajo: "; getline(cin, e.puesto);
    cout << "Teléfono: "; getline(cin, e.telefono);

    empleados.push_back(e);                 // Agrega al vector
    ordenarEmpleados();                     // Ordena por nombre
    guardarEmpleados();                     // Guarda en archivo
    bitacoralogEmpleados.insertar("Admin", 5001, "Empleados", "Crear");  // Registra en bitácora

    cout << "\nEmpleado agregado correctamente.";
    pausar();
}

// Borra un empleado buscándolo por nombre y código
void Empleados::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Empleado> nuevaLista;

    for (const auto& e : empleados) {
        if (e.nombre != nombre || e.codigo != codigo) {
            nuevaLista.push_back(e);        // Conserva el empleado
        } else {
            eliminado = true;               // Marca como eliminado
        }
    }

    if (eliminado) {
        empleados = nuevaLista;             // Reemplaza la lista
        guardarEmpleados();                 // Guarda cambios
        bitacoralogEmpleados.insertar("Admin", 5002, "Empleados", "Borrar");
        cout << "\nEmpleado eliminado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Busca un empleado por nombre y código, y muestra su información
void Empleados::buscarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Buscar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre   : " << e.nombre;
            cout << "\nCódigo   : " << e.codigo;
            cout << "\nPuesto   : " << e.puesto;
            cout << "\nTeléfono : " << e.telefono;
            bitacoralogEmpleados.insertar("Admin", 5003, "Empleados", "Buscar");
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
        ordenarEmpleados();                 // Reordena por nombre
        guardarEmpleados();                 // Guarda cambios
        bitacoralogEmpleados.insertar("Admin", 5004, "Empleados", "Modificar");
        cout << "\nEmpleado modificado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Despliega todos los empleados registrados
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
        bitacoralogEmpleados.insertar("Admin", 5005, "Empleados", "Desplegar");
    }

    pausar();
}


