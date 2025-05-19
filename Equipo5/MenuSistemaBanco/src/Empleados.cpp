//Karla Ruiz 9959-24-6859
#include "Empleados.h"      // Incluye el encabezado que define la clase Empleados
#include <iostream>         // Incluye la biblioteca de entrada/salida estándar
#include <fstream>          // Incluye la biblioteca para operaciones de archivos
#include <algorithm>        // Incluye la biblioteca para algoritmos como sort
#include "Bitacora.h"      // Incluye el encabezado para la clase Bitacora

using namespace std;       // Usa el espacio de nombres estándar para evitar escribir std:: en cada uso

// Instancia global de la bitácora para registrar acciones en el módulo de empleados
Bitacora bitacoralogEmpleados;

// Limpia la pantalla dependiendo del sistema operativo
void Empleados::limpiarPantalla() {
#ifdef _WIN32                // Si el sistema es Windows
    system("cls");         // Ejecuta el comando para limpiar la consola
#else                       // Si no es Windows (asume un sistema UNIX/Linux)
    system("clear");       // Ejecuta el comando para limpiar la consola
#endif
}

// Pausa la ejecución del programa hasta que el usuario presione ENTER
void Empleados::pausar() {
    cout << "\nPresione ENTER para continuar..."; // Muestra un mensaje al usuario
    cin.ignore();          // Ignora la entrada anterior
    cin.get();            // Espera a que el usuario presione ENTER
}

// Carga la información de empleados desde el archivo empleados.txt
void Empleados::cargarEmpleados() {
    empleados.clear();     // Limpiar lista actual de empleados
    ifstream archivo("empleados.txt"); // Abre el archivo empleados.txt en modo lectura
    Empleado e;           // Crea una instancia de la estructura Empleado
    string linea;         // Variable para almacenar cada línea leída del archivo

    // Lee cada línea del archivo
    while (getline(archivo, linea)) {
        size_t pos = 0;   // Variable para almacenar la posición de la coma
        string datos[4];  // Array para almacenar los datos del empleado

        // Extrae los datos de la línea (separados por comas)
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');           // Busca la posición de la coma
            datos[i] = linea.substr(0, pos); // Extrae el dato hasta la coma
            linea.erase(0, pos + 1);         // Elimina el dato procesado de la línea
        }
        datos[3] = linea; // Asigna el último campo (teléfono)

        // Asigna los datos extraídos a la estructura Empleado
        e.nombre = datos[0];
        e.codigo = datos[1];
        e.puesto = datos[2];
        e.telefono = datos[3];

        empleados.push_back(e); // Agrega el empleado a la lista
    }

    archivo.close();          // Cierra el archivo
    ordenarEmpleados();       // Ordena empleados después de cargar
}

// Guarda la lista de empleados en el archivo empleados.txt
void Empleados::guardarEmpleados() {
    ofstream archivo("empleados.txt"); // Abre el archivo empleados.txt en modo escritura
    for (const auto& e : empleados) {   // Itera sobre cada empleado en la lista
        archivo << e.nombre << ","        // Escribe el nombre en el archivo
                << e.codigo << ","        // Escribe el código en el archivo
                << e.puesto << ","        // Escribe el puesto en el archivo
                << e.telefono << "\n";    // Escribe el teléfono y salta a la siguiente línea
    }
    archivo.close();          // Cierra el archivo
}

// Ordena la lista de empleados alfabéticamente por nombre
void Empleados::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const Empleado& a, const Empleado& b) {
        return a.nombre < b.nombre; // Ordena usando el nombre como criterio
    });
}

// Muestra el menú principal del módulo de empleados
void Empleados::menuEmpleados() {
    int opcion;             // Variable para almacenar la opción seleccionada
    do {
        cargarEmpleados();   // Siempre cargar antes de mostrar menú
        limpiarPantalla();   // Limpia la pantalla
        cout << "\n===== MENÚ DE EMPLEADOS ====="; // Muestra el encabezado del menú
        cout << "\n1. Crear Empleado";  // Opción para crear un nuevo empleado
        cout << "\n2. Borrar Empleado";  // Opción para borrar un empleado
        cout << "\n3. Buscar Empleado";  // Opción para buscar un empleado
        cout << "\n4. Modificar Empleado"; // Opción para modificar un empleado
        cout << "\n5. Despliegue de Empleados"; // Opción para mostrar todos los empleados
        cout << "\n6. Salir";           // Opción para salir del menú
        cout << "\nSeleccione una opción: "; // Pide al usuario que seleccione una opción
        cin >> opcion;         // Lee la opción seleccionada
        cin.ignore();          // Limpia el buffer de entrada

        // Controla el flujo según la opción seleccionada
        switch (opcion) {
            case 1: crearEmpleado(); break; // Llama a crearEmpleado
            case 2: borrarEmpleado(); break; // Llama a borrarEmpleado
            case 3: buscarEmpleado(); break; // Llama a buscarEmpleado
            case 4: modificarEmpleado(); break; // Llama a modificarEmpleado
            case 5: desplegarEmpleados(); break; // Llama a desplegarEmpleados
            case 6:                       // Opción para salir
                limpiarPantalla(); // Limpia antes de salir
                return;            // Sale del menú
            default:                  // Si la opción es inválida
                cout << "\nOpción inválida."; // Muestra mensaje de error
                pausar();           // Pausa para que el usuario vea el mensaje
        }
    } while (true); // Repite indefinidamente hasta seleccionar salir
}

// Crea un nuevo registro de empleado
void Empleados::crearEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    Empleado e;        // Crea una nueva instancia de Empleado
    cout << "\n=== Crear Empleado ==="; // Mensaje de inicio de creación
    cout << "\nNombre: "; getline(cin, e.nombre); // Lee el nombre
    cout << "Código: "; getline(cin, e.codigo);   // Lee el código
    cout << "Puesto de trabajo: "; getline(cin, e.puesto); // Lee el puesto
    cout << "Teléfono: "; getline(cin, e.telefono); // Lee el teléfono

    empleados.push_back(e); // Agrega el nuevo empleado a la lista
    ordenarEmpleados();      // Ordena la lista de empleados
    guardarEmpleados();      // Guarda la lista actualizada en el archivo

    // Registro de bitácora (código 4001)
    bitacoralogEmpleados.insertar("Admin", 4001, "Empleados", "Crear");

    cout << "\nEmpleado agregado correctamente."; // Mensaje de éxito
    pausar(); // Pausa la ejecución
}

// Elimina un empleado por nombre y código
void Empleados::borrarEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    string nombre, codigo; // Variables para almacenar el nombre y código del empleado a borrar
    cout << "\n=== Borrar Empleado ==="; // Mensaje de inicio de borrado
    cout << "\nNombre: "; getline(cin, nombre); // Lee el nombre
    cout << "Código: "; getline(cin, codigo);   // Lee el código

    bool eliminado = false; // Bandera para verificar si se eliminó un empleado
    vector<Empleado> nuevaLista; // Lista temporal para almacenar empleados que no se eliminan

    // Itera sobre la lista de empleados
    for (const auto& e : empleados) {
        // Si el empleado no coincide con el nombre y código, lo agrega a la nueva lista
        if (e.nombre != nombre || e.codigo != codigo) {
            nuevaLista.push_back(e);
        } else {
            eliminado = true; // Si coincide, marca como eliminado
        }
    }

    if (eliminado) { // Si se eliminó un empleado
        empleados = nuevaLista; // Actualiza la lista de empleados
        guardarEmpleados();      // Guarda la lista actualizada en el archivo
        // Registro de bitácora (código 4002)
        bitacoralogEmpleados.insertar("Admin", 4002, "Empleados", "Borrar");
        cout << "\nEmpleado eliminado correctamente."; // Mensaje de éxito
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontró el empleado
    }

    pausar(); // Pausa la ejecución
}

// Busca un empleado por nombre y código
void Empleados::buscarEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    string nombre, codigo; // Variables para almacenar el nombre y código del empleado a buscar
    cout << "\n=== Buscar Empleado ==="; // Mensaje de inicio de búsqueda
    cout << "\nNombre: "; getline(cin, nombre); // Lee el nombre
    cout << "Código: "; getline(cin, codigo);   // Lee el código

    bool encontrado = false; // Bandera para verificar si se encontró el empleado

    // Itera sobre la lista de empleados
    for (const auto& e : empleados) {
        // Si coincide el nombre y código, muestra la información del empleado
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre   : " << e.nombre; // Muestra el nombre
            cout << "\nCódigo   : " << e.codigo; // Muestra el código
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto
            cout << "\nTeléfono : " << e.telefono; // Muestra el teléfono

            // Registro de bitácora (código 4003)
            bitacoralogEmpleados.insertar("Admin", 4003, "Empleados", "Buscar");
            encontrado = true; // Marca como encontrado
            break; // Sale del bucle
        }
    }

    if (!encontrado) {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontró el empleado
    }

    pausar(); // Pausa la ejecución
}

// Modifica los datos de un empleado existente
void Empleados::modificarEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    string nombre, codigo; // Variables para almacenar el nombre y código del empleado a modificar
    cout << "\n=== Modificar Empleado ==="; // Mensaje de inicio de modificación
    cout << "\nNombre: "; getline(cin, nombre); // Lee el nombre
    cout << "Código: "; getline(cin, codigo);   // Lee el código

    bool modificado = false; // Bandera para verificar si se modificó el empleado

    // Itera sobre la lista de empleados
    for (auto& e : empleados) {
        // Si coincide el nombre y código, permite modificar la información
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nIngrese nueva información:";
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre); // Lee el nuevo nombre
            cout << "Nuevo Código: "; getline(cin, e.codigo); // Lee el nuevo código
            cout << "Nuevo Puesto: "; getline(cin, e.puesto); // Lee el nuevo puesto
            cout << "Nuevo Teléfono: "; getline(cin, e.telefono); // Lee el nuevo teléfono
            modificado = true; // Marca como modificado
            break; // Sale del bucle
        }
    }

    if (modificado) {
        ordenarEmpleados(); // Ordena la lista después de la modificación
        guardarEmpleados();  // Guarda la lista actualizada en el archivo
        // Registro de bitácora (código 4004)
        bitacoralogEmpleados.insertar("Admin", 4004, "Empleados", "Modificar");
        cout << "\nEmpleado modificado correctamente."; // Mensaje de éxito
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontró el empleado
    }

    pausar(); // Pausa la ejecución
}

// Muestra todos los empleados en pantalla
void Empleados::desplegarEmpleados() {
    limpiarPantalla(); // Limpia la pantalla
    cout << "\n=== Empleados Registrados ===\n"; // Mensaje de encabezado

    if (empleados.empty()) { // Si no hay empleados registrados
        cout << "\nNo hay empleados registrados."; // Mensaje correspondiente
    } else {
        for (const auto& e : empleados) { // Itera sobre la lista de empleados
            cout << "\n----------------------------"; // Separador
            cout << "\nNombre   : " << e.nombre; // Muestra el nombre
            cout << "\nCódigo   : " << e.codigo; // Muestra el código
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto
            cout << "\nTeléfono : " << e.telefono; // Muestra el teléfono
        }
        cout << "\n----------------------------";

        // Registro de bitácora (código 4005)
        bitacoralogEmpleados.insertar("Admin", 4005, "Empleados", "Desplegar");
    }

    pausar(); // Pausa la ejecución
}

