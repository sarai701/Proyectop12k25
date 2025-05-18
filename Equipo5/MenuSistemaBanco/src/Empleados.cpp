//Karla Ruiz 9959-24-6859
#include "Empleados.h"       // Incluye el archivo de cabecera con la definición de la clase Empleados
#include <iostream>          // Para entrada y salida estándar (cout, cin)
#include <fstream>           // Para manejo de archivos (lectura y escritura)
#include <algorithm>         // Para usar sort y otras funciones estándar
#include "Bitacora.h"        // Para manejar la bitácora de eventos del sistema

using namespace std;

// Instancia global para registrar eventos de empleados en la bitácora
Bitacora bitacoralogEmpleados;

// Función que limpia la pantalla según el sistema operativo (Windows o Linux/Unix)
void Empleados::limpiarPantalla() {
#ifdef _WIN32
    system("cls");      // En Windows usa 'cls'
#else
    system("clear");    // En otros sistemas usa 'clear'
#endif
}

// Pausa el programa y espera que el usuario presione ENTER para continuar
void Empleados::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();       // Ignora cualquier entrada previa pendiente
    cin.get();          // Espera que se presione ENTER
}

// Carga los empleados desde el archivo 'empleados.txt' al vector 'empleados'
void Empleados::cargarEmpleados() {
    empleados.clear();  // Limpia el vector para evitar duplicados al recargar
    ifstream archivo("empleados.txt"); // Abre el archivo para lectura
    Empleado e;                    // Variable temporal para almacenar un empleado
    string linea;                  // Línea leída del archivo

    // Lee el archivo línea por línea hasta que se acabe
    while (getline(archivo, linea)) {
        size_t pos = 0;
        string datos[4];           // Array para almacenar nombre, código, puesto y teléfono

        // Extrae cada dato separado por comas
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');         // Encuentra la posición de la coma
            datos[i] = linea.substr(0, pos); // Extrae la subcadena antes de la coma
            linea.erase(0, pos + 1);       // Elimina la parte extraída para procesar el siguiente dato
        }
        datos[3] = linea;    // El último dato es lo que queda en la línea (teléfono)

        // Asigna los datos a un empleado
        e.nombre = datos[0];
        e.codigo = datos[1];
        e.puesto = datos[2];
        e.telefono = datos[3];

        // Añade el empleado al vector
        empleados.push_back(e);
    }

    archivo.close();       // Cierra el archivo
    ordenarEmpleados();    // Ordena los empleados alfabéticamente por nombre
}

// Guarda el contenido del vector 'empleados' en el archivo 'empleados.txt'
void Empleados::guardarEmpleados() {
    ofstream archivo("empleados.txt");   // Abre archivo para escritura (sobrescribe)
    for (const auto& e : empleados) {    // Recorre cada empleado
        archivo << e.nombre << "," << e.codigo << "," << e.puesto << "," << e.telefono << "\n"; // Guarda en formato CSV
    }
    archivo.close();   // Cierra el archivo
}

// Ordena el vector 'empleados' alfabéticamente por nombre usando función lambda
void Empleados::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const Empleado& a, const Empleado& b) {
        return a.nombre < b.nombre;    // Compara nombres para ordenar
    });
}

// Menú principal para administrar empleados, muestra opciones y ejecuta la opción elegida
void Empleados::menuEmpleados() {
    int opcion;
    do {
        cargarEmpleados();  // Carga los empleados antes de mostrar menú
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
        cin.ignore();    // Limpiar el buffer para evitar problemas con getline

        switch (opcion) {
            case 1: crearEmpleado(); break;
            case 2: borrarEmpleado(); break;
            case 3: buscarEmpleado(); break;
            case 4: modificarEmpleado(); break;
            case 5: desplegarEmpleados(); break;
            case 6:
                limpiarPantalla();
                return;    // Sale del menú y termina la función
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// Crea un nuevo empleado pidiendo datos por consola y lo agrega a la lista
void Empleados::crearEmpleado() {
    limpiarPantalla();
    Empleado e;
    cout << "\n=== Crear Empleado ===";
    cout << "\nNombre: "; getline(cin, e.nombre);
    cout << "Código: "; getline(cin, e.codigo);
    cout << "Puesto de trabajo: "; getline(cin, e.puesto);
    cout << "Teléfono: "; getline(cin, e.telefono);

    empleados.push_back(e);  // Añade al vector
    ordenarEmpleados();      // Ordena para mantener orden alfabético
    guardarEmpleados();      // Guarda cambios en archivo

    // Inserta evento en la bitácora, con código dentro del rango 4000-4999 para banco
    bitacoralogEmpleados.insertar("Admin", 4001, "Empleados", "Crear");
    cout << "\nEmpleado agregado correctamente.";
    pausar();
}

// Borra un empleado que coincida con nombre y código ingresados
void Empleados::borrarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Borrar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Empleado> nuevaLista;

    // Filtra empleados diferentes a los datos proporcionados (los que no se borran)
    for (const auto& e : empleados) {
        if (e.nombre != nombre || e.codigo != codigo) {
            nuevaLista.push_back(e);
        } else {
            eliminado = true;  // Marca que se encontró y eliminó al empleado
        }
    }

    if (eliminado) {
        empleados = nuevaLista;   // Actualiza la lista sin el empleado borrado
        guardarEmpleados();       // Guarda cambios en archivo
        bitacoralogEmpleados.insertar("Admin", 4002, "Empleados", "Borrar");
        cout << "\nEmpleado eliminado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Busca y muestra la información de un empleado por nombre y código
void Empleados::buscarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Buscar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool encontrado = false;

    // Recorre empleados buscando coincidencia exacta en nombre y código
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

// Modifica la información de un empleado encontrado por nombre y código
void Empleados::modificarEmpleado() {
    limpiarPantalla();
    string nombre, codigo;
    cout << "\n=== Modificar Empleado ===";
    cout << "\nNombre: "; getline(cin, nombre);
    cout << "Código: "; getline(cin, codigo);

    bool modificado = false;

    // Busca el empleado para modificarlo directamente en el vector
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
        ordenarEmpleados();      // Ordena después de modificar por si cambió el nombre
        guardarEmpleados();      // Guarda en archivo
        bitacoralogEmpleados.insertar("Admin", 4004, "Empleados", "Modificar");
        cout << "\nEmpleado modificado correctamente.";
    } else {
        cout << "\nEmpleado no encontrado.";
    }

    pausar();
}

// Despliega en pantalla la lista completa de empleados registrados
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
