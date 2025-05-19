//Karla Ruiz 9959-24-6859
#include "Empleados.h"      // Incluye el encabezado que define la clase Empleados
#include <iostream>         // Incluye la biblioteca de entrada/salida est�ndar
#include <fstream>          // Incluye la biblioteca para operaciones de archivos
#include <algorithm>        // Incluye la biblioteca para algoritmos como sort
#include "Bitacora.h"      // Incluye el encabezado para la clase Bitacora

using namespace std;       // Usa el espacio de nombres est�ndar para evitar escribir std:: en cada uso

// Instancia global de la bit�cora para registrar acciones en el m�dulo de empleados
Bitacora bitacoralogEmpleados;

// Limpia la pantalla dependiendo del sistema operativo
void Empleados::limpiarPantalla() {
#ifdef _WIN32                // Si el sistema es Windows
    system("cls");         // Ejecuta el comando para limpiar la consola
#else                       // Si no es Windows (asume un sistema UNIX/Linux)
    system("clear");       // Ejecuta el comando para limpiar la consola
#endif
}

// Pausa la ejecuci�n del programa hasta que el usuario presione ENTER
void Empleados::pausar() {
    cout << "\nPresione ENTER para continuar..."; // Muestra un mensaje al usuario
    cin.ignore();          // Ignora la entrada anterior
    cin.get();            // Espera a que el usuario presione ENTER
}

// Carga la informaci�n de empleados desde el archivo empleados.txt
void Empleados::cargarEmpleados() {
    empleados.clear();     // Limpiar lista actual de empleados
    ifstream archivo("empleados.txt"); // Abre el archivo empleados.txt en modo lectura
    Empleado e;           // Crea una instancia de la estructura Empleado
    string linea;         // Variable para almacenar cada l�nea le�da del archivo

    // Lee cada l�nea del archivo
    while (getline(archivo, linea)) {
        size_t pos = 0;   // Variable para almacenar la posici�n de la coma
        string datos[4];  // Array para almacenar los datos del empleado

        // Extrae los datos de la l�nea (separados por comas)
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');           // Busca la posici�n de la coma
            datos[i] = linea.substr(0, pos); // Extrae el dato hasta la coma
            linea.erase(0, pos + 1);         // Elimina el dato procesado de la l�nea
        }
        datos[3] = linea; // Asigna el �ltimo campo (tel�fono)

        // Asigna los datos extra�dos a la estructura Empleado
        e.nombre = datos[0];
        e.codigo = datos[1];
        e.puesto = datos[2];
        e.telefono = datos[3];

        empleados.push_back(e); // Agrega el empleado a la lista
    }

    archivo.close();          // Cierra el archivo
    ordenarEmpleados();       // Ordena empleados despu�s de cargar
}

// Guarda la lista de empleados en el archivo empleados.txt
void Empleados::guardarEmpleados() {
    ofstream archivo("empleados.txt"); // Abre el archivo empleados.txt en modo escritura
    for (const auto& e : empleados) {   // Itera sobre cada empleado en la lista
        archivo << e.nombre << ","        // Escribe el nombre en el archivo
                << e.codigo << ","        // Escribe el c�digo en el archivo
                << e.puesto << ","        // Escribe el puesto en el archivo
                << e.telefono << "\n";    // Escribe el tel�fono y salta a la siguiente l�nea
    }
    archivo.close();          // Cierra el archivo
}

// Ordena la lista de empleados alfab�ticamente por nombre
void Empleados::ordenarEmpleados() {
    sort(empleados.begin(), empleados.end(), [](const Empleado& a, const Empleado& b) {
        return a.nombre < b.nombre; // Ordena usando el nombre como criterio
    });
}

// Muestra el men� principal del m�dulo de empleados
void Empleados::menuEmpleados() {
    int opcion;             // Variable para almacenar la opci�n seleccionada
    do {
        cargarEmpleados();   // Siempre cargar antes de mostrar men�
        limpiarPantalla();   // Limpia la pantalla
        cout << "\n===== MEN� DE EMPLEADOS ====="; // Muestra el encabezado del men�
        cout << "\n1. Crear Empleado";  // Opci�n para crear un nuevo empleado
        cout << "\n2. Borrar Empleado";  // Opci�n para borrar un empleado
        cout << "\n3. Buscar Empleado";  // Opci�n para buscar un empleado
        cout << "\n4. Modificar Empleado"; // Opci�n para modificar un empleado
        cout << "\n5. Despliegue de Empleados"; // Opci�n para mostrar todos los empleados
        cout << "\n6. Salir";           // Opci�n para salir del men�
        cout << "\nSeleccione una opci�n: "; // Pide al usuario que seleccione una opci�n
        cin >> opcion;         // Lee la opci�n seleccionada
        cin.ignore();          // Limpia el buffer de entrada

        // Controla el flujo seg�n la opci�n seleccionada
        switch (opcion) {
            case 1: crearEmpleado(); break; // Llama a crearEmpleado
            case 2: borrarEmpleado(); break; // Llama a borrarEmpleado
            case 3: buscarEmpleado(); break; // Llama a buscarEmpleado
            case 4: modificarEmpleado(); break; // Llama a modificarEmpleado
            case 5: desplegarEmpleados(); break; // Llama a desplegarEmpleados
            case 6:                       // Opci�n para salir
                limpiarPantalla(); // Limpia antes de salir
                return;            // Sale del men�
            default:                  // Si la opci�n es inv�lida
                cout << "\nOpci�n inv�lida."; // Muestra mensaje de error
                pausar();           // Pausa para que el usuario vea el mensaje
        }
    } while (true); // Repite indefinidamente hasta seleccionar salir
}

// Crea un nuevo registro de empleado
void Empleados::crearEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    Empleado e;        // Crea una nueva instancia de Empleado
    cout << "\n=== Crear Empleado ==="; // Mensaje de inicio de creaci�n
    cout << "\nNombre: "; getline(cin, e.nombre); // Lee el nombre
    cout << "C�digo: "; getline(cin, e.codigo);   // Lee el c�digo
    cout << "Puesto de trabajo: "; getline(cin, e.puesto); // Lee el puesto
    cout << "Tel�fono: "; getline(cin, e.telefono); // Lee el tel�fono

    empleados.push_back(e); // Agrega el nuevo empleado a la lista
    ordenarEmpleados();      // Ordena la lista de empleados
    guardarEmpleados();      // Guarda la lista actualizada en el archivo

    // Registro de bit�cora (c�digo 4001)
    bitacoralogEmpleados.insertar("Admin", 4001, "Empleados", "Crear");

    cout << "\nEmpleado agregado correctamente."; // Mensaje de �xito
    pausar(); // Pausa la ejecuci�n
}

// Elimina un empleado por nombre y c�digo
void Empleados::borrarEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    string nombre, codigo; // Variables para almacenar el nombre y c�digo del empleado a borrar
    cout << "\n=== Borrar Empleado ==="; // Mensaje de inicio de borrado
    cout << "\nNombre: "; getline(cin, nombre); // Lee el nombre
    cout << "C�digo: "; getline(cin, codigo);   // Lee el c�digo

    bool eliminado = false; // Bandera para verificar si se elimin� un empleado
    vector<Empleado> nuevaLista; // Lista temporal para almacenar empleados que no se eliminan

    // Itera sobre la lista de empleados
    for (const auto& e : empleados) {
        // Si el empleado no coincide con el nombre y c�digo, lo agrega a la nueva lista
        if (e.nombre != nombre || e.codigo != codigo) {
            nuevaLista.push_back(e);
        } else {
            eliminado = true; // Si coincide, marca como eliminado
        }
    }

    if (eliminado) { // Si se elimin� un empleado
        empleados = nuevaLista; // Actualiza la lista de empleados
        guardarEmpleados();      // Guarda la lista actualizada en el archivo
        // Registro de bit�cora (c�digo 4002)
        bitacoralogEmpleados.insertar("Admin", 4002, "Empleados", "Borrar");
        cout << "\nEmpleado eliminado correctamente."; // Mensaje de �xito
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontr� el empleado
    }

    pausar(); // Pausa la ejecuci�n
}

// Busca un empleado por nombre y c�digo
void Empleados::buscarEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    string nombre, codigo; // Variables para almacenar el nombre y c�digo del empleado a buscar
    cout << "\n=== Buscar Empleado ==="; // Mensaje de inicio de b�squeda
    cout << "\nNombre: "; getline(cin, nombre); // Lee el nombre
    cout << "C�digo: "; getline(cin, codigo);   // Lee el c�digo

    bool encontrado = false; // Bandera para verificar si se encontr� el empleado

    // Itera sobre la lista de empleados
    for (const auto& e : empleados) {
        // Si coincide el nombre y c�digo, muestra la informaci�n del empleado
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nEmpleado encontrado:";
            cout << "\nNombre   : " << e.nombre; // Muestra el nombre
            cout << "\nC�digo   : " << e.codigo; // Muestra el c�digo
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto
            cout << "\nTel�fono : " << e.telefono; // Muestra el tel�fono

            // Registro de bit�cora (c�digo 4003)
            bitacoralogEmpleados.insertar("Admin", 4003, "Empleados", "Buscar");
            encontrado = true; // Marca como encontrado
            break; // Sale del bucle
        }
    }

    if (!encontrado) {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontr� el empleado
    }

    pausar(); // Pausa la ejecuci�n
}

// Modifica los datos de un empleado existente
void Empleados::modificarEmpleado() {
    limpiarPantalla(); // Limpia la pantalla
    string nombre, codigo; // Variables para almacenar el nombre y c�digo del empleado a modificar
    cout << "\n=== Modificar Empleado ==="; // Mensaje de inicio de modificaci�n
    cout << "\nNombre: "; getline(cin, nombre); // Lee el nombre
    cout << "C�digo: "; getline(cin, codigo);   // Lee el c�digo

    bool modificado = false; // Bandera para verificar si se modific� el empleado

    // Itera sobre la lista de empleados
    for (auto& e : empleados) {
        // Si coincide el nombre y c�digo, permite modificar la informaci�n
        if (e.nombre == nombre && e.codigo == codigo) {
            cout << "\nIngrese nueva informaci�n:";
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre); // Lee el nuevo nombre
            cout << "Nuevo C�digo: "; getline(cin, e.codigo); // Lee el nuevo c�digo
            cout << "Nuevo Puesto: "; getline(cin, e.puesto); // Lee el nuevo puesto
            cout << "Nuevo Tel�fono: "; getline(cin, e.telefono); // Lee el nuevo tel�fono
            modificado = true; // Marca como modificado
            break; // Sale del bucle
        }
    }

    if (modificado) {
        ordenarEmpleados(); // Ordena la lista despu�s de la modificaci�n
        guardarEmpleados();  // Guarda la lista actualizada en el archivo
        // Registro de bit�cora (c�digo 4004)
        bitacoralogEmpleados.insertar("Admin", 4004, "Empleados", "Modificar");
        cout << "\nEmpleado modificado correctamente."; // Mensaje de �xito
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontr� el empleado
    }

    pausar(); // Pausa la ejecuci�n
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
            cout << "\nC�digo   : " << e.codigo; // Muestra el c�digo
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto
            cout << "\nTel�fono : " << e.telefono; // Muestra el tel�fono
        }
        cout << "\n----------------------------";

        // Registro de bit�cora (c�digo 4005)
        bitacoralogEmpleados.insertar("Admin", 4005, "Empleados", "Desplegar");
    }

    pausar(); // Pausa la ejecuci�n
}

