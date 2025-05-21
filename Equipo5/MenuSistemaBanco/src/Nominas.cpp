// Programado por Priscila Sarai Guzmán Calgua 9959-23-450
#include "Nominas.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Bitacora.h"
#include "Moneda.h"
#include <string>
#include <stdexcept>

// Instancia global de la bitácora para registrar operaciones
Bitacora bitacoralogNominas;

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

// Carga empleados desde el archivo binario 'nominas.dat'
void Nominas::cargarEmpleados() {
    empleados.clear(); // Limpia el vector antes de cargar
    ifstream archivo("nominas.dat", ios::binary);

    try {
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo nominas.dat");
        }

        while (archivo.peek() != EOF) {
            EmpleadoNomina e;
            size_t len;

            // Lectura de nombre
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            e.nombre.resize(len);
            archivo.read(&e.nombre[0], len);

            // Lectura de teléfono
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            e.telefono.resize(len);
            archivo.read(&e.telefono[0], len);

            // Lectura de código
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            e.codigo.resize(len);
            archivo.read(&e.codigo[0], len);

            // Lectura de dirección
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            e.direccion.resize(len);
            archivo.read(&e.direccion[0], len);

            // Lectura de salario
            archivo.read(reinterpret_cast<char*>(&e.salario), sizeof(e.salario));

            empleados.push_back(e);
        }

        archivo.close();
        ordenarEmpleados(); // Ordena alfabéticamente por nombre

    } catch (const exception& ex) {
        cout << "\nError al cargar empleados: " << ex.what() << endl;
    }
}

// Guarda empleados en el archivo binario 'nominas.dat'
void Nominas::guardarEmpleados() {
    try {
        ofstream archivo("nominas.dat", ios::binary | ios::trunc);
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo nominas.dat para escritura.");
        }

        for (const auto& e : empleados) {
            size_t len;

            // Guardar nombre
            len = e.nombre.size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
            archivo.write(e.nombre.c_str(), len);

            // Guardar teléfono
            len = e.telefono.size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
            archivo.write(e.telefono.c_str(), len);

            // Guardar código
            len = e.codigo.size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
            archivo.write(e.codigo.c_str(), len);

            // Guardar dirección
            len = e.direccion.size();
            archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
            archivo.write(e.direccion.c_str(), len);

            // Guardar salario
            archivo.write(reinterpret_cast<const char*>(&e.salario), sizeof(e.salario));
        }

        archivo.close();

    } catch (const exception& ex) {
        cout << "\nError al guardar empleados: " << ex.what() << endl;
    }
}

// Ordena la lista de empleados por nombre
void Nominas::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const EmpleadoNomina& a, const EmpleadoNomina& b) {
        return a.nombre < b.nombre;
    });
}

// Asigna el nombre del usuario que usa el sistema
void Nominas::setUsuario(const string& u) {
    usuario = u;
}

// Lee el salario ingresado y lo convierte a double, validando errores
double leerSalario() {
    string entrada;
    double salario;
    cout << "Salario (GTQ): Q";
    getline(cin, entrada);

    try {
        salario = stod(entrada);
    } catch (const invalid_argument& e) {
        throw runtime_error("Entrada inválida. Debe ingresar un número para el salario.");
    } catch (const out_of_range& e) {
        throw runtime_error("El salario ingresado es demasiado grande.");
    }

    return salario;
}

// Muestra el menú principal de gestión de nóminas
void Nominas::menuNominas() {
    int opcion;
    do {
        cargarEmpleados();
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
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
            case 6: limpiarPantalla(); return;
            default: cout << "\nOpción inválida."; pausar(); break;
        }
    } while (true);
}

// Crea un nuevo empleado y lo agrega a la lista
void Nominas::crearEmpleado() {
    limpiarPantalla();
    EmpleadoNomina e;

    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Crear Empleado ===";
    cout << "\nNombre: "; getline(cin, e.nombre);
    cout << "Teléfono: "; getline(cin, e.telefono);
    cout << "Código: "; getline(cin, e.codigo);
    cout << "Dirección: "; getline(cin, e.direccion);

    // Validación del salario ingresado
    bool valido = false;
    while (!valido) {
        try {
            e.salario = leerSalario();
            valido = true;
        } catch (const runtime_error& ex) {
            cout << ex.what() << endl;
            cout << "Intente de nuevo.\n";
        }
    }

    empleados.push_back(e);
    ordenarEmpleados();
    guardarEmpleados();

    bitacoralogNominas.insertar(usuario, 4001, "Nominas", "Crear empleado");
    cout << "\nEmpleado agregado correctamente.";
    pausar();
}

// Elimina un empleado que coincida con nombre y código
void Nominas::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool eliminado = false;
    vector<EmpleadoNomina> nuevaLista;

    // Crea una nueva lista sin el empleado a eliminar
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
        bitacoralogNominas.insertar(usuario, 4002, "Nominas", "Eliminar empleado");
        cout << "\nEmpleado eliminado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Busca un empleado por nombre y código y muestra sus datos
void Nominas::buscarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\nUsuario: " << usuario << endl;
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
            cout << "\nSalario   : " << Moneda::getSimbolo()
                 << Moneda::convertirDesdeGtq(e.salario);
            encontrado = true;
            bitacoralogNominas.insertar(usuario, 4003, "Nominas", "Buscar empleado");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Modifica los datos de un empleado existente
void Nominas::modificarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\nUsuario: " << usuario << endl;
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
            cout << "Nuevo Salario (GTQ): Q"; cin >> e.salario;
            cin.ignore();
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarEmpleados();
        guardarEmpleados();
        bitacoralogNominas.insertar(usuario, 4004, "Nominas", "Modificar empleado");
        cout << "\nEmpleado modificado exitosamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Muestra todos los empleados registrados
void Nominas::desplegarEmpleados() {
    limpiarPantalla();
    cout << "\nUsuario: " << usuario << endl;
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
            cout << "\nSalario   : " << Moneda::getSimbolo()
                 << Moneda::convertirDesdeGtq(e.salario);
        }
        cout << "\n-----------------------------";
        bitacoralogNominas.insertar(usuario, 4005, "Nominas", "Ver empleados");
    }

    pausar();
}
