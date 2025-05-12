//Programado por Priscila Sarai Guzm�n Calgua 9959-23-450

#include "Nominas.h"
#include <iostream>
#include <fstream>//Librer�a para archivos de lectura o escritura
#include <algorithm>// Para la funci�n sort (ordenamiento)
#include "Bitacora.h"
#include "Moneda.h"

// Creamos un objeto global de bit�cora para registrar las acciones realizadas en Nominas
Bitacora bitacoralog3;

using namespace std;

void Nominas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa la ejecuci�n del programa hasta que el usuario presione enter
void Nominas::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Carga todos los empleados desde el archivo empleados.txt
// Los separa por comas y los guarda en el vector empleados
void Nominas::cargarEmpleados() {
    empleados.clear(); // Limpiamos la lista antes de cargar
    ifstream archivo("empleados.txt"); // Abrimos archivo en modo lectura
    EmpleadoNomina e;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos = 0;
        string datos[5];

        for (int i = 0; i < 4; ++i) {
            pos = linea.find(',');        // Buscar coma
            datos[i] = linea.substr(0, pos); // Extraer campo
            linea.erase(0, pos + 1);      // Eliminar campo extra�do
        }
        datos[4] = linea; // �ltimo campo (salario)

        // Asignar los datos al objeto empleado
        e.nombre = datos[0];
        e.telefono = datos[1];
        e.codigo = datos[2];
        e.direccion = datos[3];
        e.salario = stof(datos[4]);

        empleados.push_back(e); // Agregar a la lista
    }

    archivo.close();
    ordenarEmpleados();
}

// Guarda todos los empleados en empleados.txt
// Cada campo separado por comas
void Nominas::guardarEmpleados() {
    ofstream archivo("empleados.txt"); // Abrimos archivo en modo escritura
    for (const auto& e : empleados) {
        archivo << e.nombre << "," << e.telefono << "," << e.codigo
                << "," << e.direccion << "," << e.salario << "\n";
    }
    archivo.close();
}

// Ordena los empleados por nombre usando sort y una lambda
void Nominas::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const EmpleadoNomina& a, const EmpleadoNomina& b) {
        return a.nombre < b.nombre;
    });
}

void Nominas::menuNominas() {
    int opcion;
    do {
        cargarEmpleados();
        limpiarPantalla();
        cout << "\n===== MEN� DE N�MINAS =====";
        cout << "\n1. Crear Empleado";
        cout << "\n2. Borrar Empleado";
        cout << "\n3. Buscar Empleado";
        cout << "\n4. Modificar Empleado";
        cout << "\n5. Despliegue de Empleados";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opci�n: ";
        cin >> opcion;
        cin.ignore(); // Para evitar errores con getline despu�s de cin

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
                cout << "\nOpci�n inv�lida.";
                pausar();
        }
    } while (true);
}

// Agrega un nuevo empleado a la lista y lo guarda en archivo
void Nominas::crearEmpleado() {
    limpiarPantalla();
    EmpleadoNomina e;

    cout << "\n=== Crear Empleado ===";
    cout << "\nNombre: "; getline(cin, e.nombre);
    cout << "Tel�fono: "; getline(cin, e.telefono);
    cout << "C�digo: "; getline(cin, e.codigo);
    cout << "Direcci�n: "; getline(cin, e.direccion);
    cout << "Salario: Q"; cin >> e.salario;
    cin.ignore();

    empleados.push_back(e);
    ordenarEmpleados();
    guardarEmpleados();

    // Registro en la bit�cora
    bitacoralog3.insertar("Admin", 4001, "Nominas", "Crear empleado");
    cout << "\nEmpleado agregado correctamente.";
    pausar();
}

// Elimina un empleado seg�n su nombre y c�digo
void Nominas::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "C�digo: "; getline(cin, codigo);

    bool eliminado = false;
    vector<EmpleadoNomina> nuevaLista;

    for (const auto& e : empleados) {
        if (e.nombre != nombre || e.codigo != codigo) {
            nuevaLista.push_back(e); // Si no coincide, se conserva
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

// Busca un empleado por nombre y c�digo
void Nominas::buscarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Buscar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "C�digo: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre    : " << e.nombre;
            cout << "\nTel�fono  : " << e.telefono;
            cout << "\nC�digo    : " << e.codigo;
            cout << "\nDirecci�n : " << e.direccion;
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

// Permite modificar los datos de un empleado existente
void Nominas::modificarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Modificar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "C�digo: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& e : empleados) {
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nIngrese nueva informaci�n:";
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre);
            cout << "Nuevo Tel�fono: "; getline(cin, e.telefono);
            cout << "Nuevo C�digo: "; getline(cin, e.codigo);
            cout << "Nueva Direcci�n: "; getline(cin, e.direccion);
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

// Muestra en pantalla todos los empleados registrados
void Nominas::desplegarEmpleados() {
    limpiarPantalla();
    cout << "\n=== Empleados Registrados ===\n";

    if (empleados.empty()) {
        cout << "\nNo hay empleados registrados.";
    } else {
        for (const auto& e : empleados) {
            cout << "\n-----------------------------";
            cout << "\nNombre    : " << e.nombre;
            cout << "\nTel�fono  : " << e.telefono;
            cout << "\nC�digo    : " << e.codigo;
            cout << "\nDirecci�n : " << e.direccion;
            cout << "\nSalario   : " << Moneda::getSimbolo() << e.salario;
        }
        cout << "\n-----------------------------";
        bitacoralog3.insertar("Admin", 4005, "Nominas", "Ver empleados");
    }

    pausar();
}

