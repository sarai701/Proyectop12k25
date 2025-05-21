//Karla Ruiz 9959-24-6859
#include "Empleados.h" // Incluye el encabezado de la clase Empleados.
#include <iostream>    // Incluye la biblioteca estándar de entrada/salida.
#include <fstream>     // Incluye la biblioteca para manejo de archivos.
#include <algorithm>   // Incluye funciones de algoritmos, como sort.
#include "Bitacora.h"  // Incluye el encabezado de la clase Bitacora.
#include <limits>

using namespace std; // Permite usar elementos del espacio de nombres std sin prefijo.

Bitacora bitacoralogEmpleados; // Inicializa una instancia estática de Bitacora para registrar acciones.

void Empleados::limpiarPantalla() { // Método para limpiar la pantalla según el sistema operativo.
#ifdef _WIN32
    system("cls"); // Comando para limpiar la pantalla en Windows.
#else
    system("clear"); // Comando para limpiar la pantalla en sistemas Unix.
#endif
}

void Empleados::pausar() { // Método para pausar la ejecución del programa.
    cout << "\nPresione ENTER para continuar..."; // Mensaje para el usuario.
    cin.ignore(); // Ignora el carácter de nueva línea.
    cin.get(); // Espera a que el usuario presione ENTER.
}

void Empleados::cargarEmpleados() { // Método para cargar empleados desde un archivo.
    empleados.clear(); // Limpia el vector de empleados actual.
    ifstream archivo("empleados.txt"); // Abre el archivo para lectura.
    Empleado e; // Crea una instancia de Empleado.
    string linea; // Variable para almacenar cada línea del archivo.

    while (getline(archivo, linea)) { // Lee el archivo línea por línea.
        size_t pos = 0; // Variable para almacenar la posición de la coma.
        string datos[4]; // Array para almacenar los datos del empleado.

        for (int i = 0; i < 3; ++i) { // Extrae los primeros tres campos.
            pos = linea.find(','); // Encuentra la posición de la coma.
            datos[i] = linea.substr(0, pos); // Obtiene el substring hasta la coma.
            linea.erase(0, pos + 1); // Elimina la parte procesada de la línea.
        }
        datos[3] = linea; // Almacena el último campo.

        e.nombre = datos[0]; // Asigna el nombre del empleado.
        e.codigo = datos[1]; // Asigna el código del empleado.
        e.puesto = datos[2]; // Asigna el puesto del empleado.
        e.telefono = datos[3]; // Asigna el teléfono del empleado.

        empleados.push_back(e); // Agrega el empleado al vector.
    }

    archivo.close(); // Cierra el archivo.
    ordenarEmpleados(); // Ordena la lista de empleados.
}

void Empleados::guardarEmpleados() { // Método para guardar empleados en un archivo.
    ofstream archivo("empleados.txt"); // Abre el archivo para escritura.
    for (const auto& e : empleados) { // Itera sobre cada empleado.
        archivo << e.nombre << "," << e.codigo << "," << e.puesto << "," << e.telefono << "\n"; // Escribe los datos en el archivo.
    }
    archivo.close(); // Cierra el archivo.
}

void Empleados::ordenarEmpleados() { // Método para ordenar empleados alfabéticamente por nombre.
    sort(empleados.begin(), empleados.end(), [](const Empleado& a, const Empleado& b) {
        return a.nombre < b.nombre; // Compara los nombres de los empleados.
    });
}

void Empleados::setUsuario(const string& u) {
    usuario = u;
}
void Empleados::menuEmpleados() { // Método para mostrar el menú principal de empleados.
    int opcion; // Variable para almacenar la opción seleccionada por el usuario.
    do {
        cargarEmpleados(); // Carga la lista de empleados antes de mostrar el menú.
        limpiarPantalla(); // Limpia la pantalla.
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== MENÚ DE EMPLEADOS ====="; // Muestra el encabezado del menú.
        cout << "\n1. Crear Empleado"; // Opción para crear un nuevo empleado.
        cout << "\n2. Borrar Empleado"; // Opción para borrar un empleado.
        cout << "\n3. Buscar Empleado"; // Opción para buscar un empleado.
        cout << "\n4. Modificar Empleado"; // Opción para modificar un empleado.
        cout << "\n5. Desplegar Empleados"; // Opción para mostrar todos los empleados.
        cout << "\n6. Salir"; // Opción para salir del menú.
        cout << "\nSeleccione una opción: "; // Solicita al usuario que seleccione una opción.
        cin >> opcion; // Lee la opción ingresada por el usuario.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el carácter de nueva línea.

        switch (opcion) { // Estructura de control para manejar la opción seleccionada.
            case 1: crearEmpleado(); break; // Llama al método para crear un empleado.
            case 2: borrarEmpleado(); break; // Llama al método para borrar un empleado.
            case 3: buscarEmpleado(); break; // Llama al método para buscar un empleado.
            case 4: modificarEmpleado(); break; // Llama al método para modificar un empleado.
            case 5: desplegarEmpleados(); break; // Llama al método para mostrar todos los empleados.
            case 6:
                limpiarPantalla(); // Limpia la pantalla al salir.
                return; // Sale del método.
            default:
                cout << "\nOpción inválida."; // Informa al usuario que la opción es inválida.
                pausar(); // Pausa la ejecución.
        }
    } while (true); // Repite el ciclo hasta que se seleccione una opción válida.
}

void Empleados::crearEmpleado() { // Método para crear un nuevo empleado.
    limpiarPantalla(); // Limpia la pantalla.
    Empleado e; // Crea una instancia de Empleado.
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Crear Empleado ==="; // Encabezado del proceso de creación.
    cout << "\nNombre: "; getline(cin, e.nombre); // Solicita el nombre.
    cout << "Código: "; getline(cin, e.codigo); // Solicita el código.
    cout << "Puesto de trabajo: "; getline(cin, e.puesto); // Solicita el puesto.
    cout << "Teléfono: "; getline(cin, e.telefono); // Solicita el teléfono.

    empleados.push_back(e); // Agrega el nuevo empleado al vector.
    ordenarEmpleados(); // Ordena la lista de empleados.
    guardarEmpleados(); // Guarda la lista actualizada en el archivo.

    bitacoralogEmpleados.insertar(usuario, 4006, "Empleados", "Crear empleado"); // Registra la acción en la bitácora.
    cout << "\nEmpleado agregado correctamente."; // Mensaje de confirmación.
    pausar(); // Pausa la ejecución.
}

void Empleados::borrarEmpleado() { // Método para borrar un empleado.
    limpiarPantalla(); // Limpia la pantalla.
    string nombre, codigo; // Variables para almacenar el nombre y código del empleado a borrar.
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Borrar Empleado ==="; // Encabezado del proceso de borrado.
    cout << "\nNombre: "; getline(cin, nombre); // Solicita el nombre.
    cout << "Código: "; getline(cin, codigo); // Solicita el código.

    bool eliminado = false; // Variable para indicar si se eliminó el empleado.
    vector<Empleado> nuevaLista; // Vector temporal para almacenar empleados restantes.

    for (const auto& e : empleados) { // Itera sobre cada empleado.
        if (e.nombre != nombre || e.codigo != codigo) { // Si no coincide con el empleado a borrar.
            nuevaLista.push_back(e); // Agrega a la nueva lista.
        } else {
            eliminado = true; // Marca que se eliminó un empleado.
        }
    }

    if (eliminado) { // Si se eliminó un empleado.
        empleados = nuevaLista; // Actualiza la lista de empleados.
        guardarEmpleados(); // Guarda la lista actualizada en el archivo.
        bitacoralogEmpleados.insertar(usuario, 4007, "Empleados", "Borrar empleado"); // Registra la acción en la bitácora.
        cout << "\nEmpleado eliminado correctamente."; // Mensaje de confirmación.
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontró al empleado.
    }

    pausar(); // Pausa la ejecución.
}

void Empleados::buscarEmpleado() { // Método para buscar un empleado.
    limpiarPantalla(); // Limpia la pantalla.
    string nombre, codigo; // Variables para almacenar el nombre y código del empleado a buscar.
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Buscar Empleado ==="; // Encabezado del proceso de búsqueda.
    cout << "\nNombre: "; getline(cin, nombre); // Solicita el nombre.
    cout << "Código: "; getline(cin, codigo); // Solicita el código.

    bool encontrado = false; // Variable para indicar si se encontró el empleado.

    for (const auto& e : empleados) { // Itera sobre cada empleado.
        if (e.nombre == nombre && e.codigo == codigo) { // Si se encuentra el empleado.
            cout << "\nEmpleado encontrado:"; // Mensaje de confirmación.
            cout << "\nNombre   : " << e.nombre; // Muestra el nombre.
            cout << "\nCódigo   : " << e.codigo; // Muestra el código.
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto.
            cout << "\nTeléfono : " << e.telefono; // Muestra el teléfono.
            bitacoralogEmpleados.insertar(usuario, 4008, "Empleados", "Buscar empleado"); // Registra la acción en la bitácora.
            encontrado = true; // Marca que se encontró al empleado.
            break; // Sale del bucle.
        }
    }

    if (!encontrado) { // Si no se encontró el empleado.
        cout << "\nEmpleado no encontrado."; // Mensaje informando que no se encontró.
    }

    pausar(); // Pausa la ejecución.
}

void Empleados::modificarEmpleado() { // Método para modificar información de un empleado.
    limpiarPantalla(); // Limpia la pantalla.
    string nombre, codigo; // Variables para almacenar el nombre y código del empleado a modificar.
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Modificar Empleado ==="; // Encabezado del proceso de modificación.
    cout << "\nNombre: "; getline(cin, nombre); // Solicita el nombre.
    cout << "Código: "; getline(cin, codigo); // Solicita el código.

    bool modificado = false; // Variable para indicar si se modificó el empleado.

    for (auto& e : empleados) { // Itera sobre cada empleado.
        if (e.nombre == nombre && e.codigo == codigo) { // Si se encuentra el empleado.
            cout << "\nIngrese nueva información:"; // Mensaje para ingresar nueva información.
            cout << "\nNuevo Nombre: "; getline(cin, e.nombre); // Solicita el nuevo nombre.
            cout << "Nuevo Código: "; getline(cin, e.codigo); // Solicita el nuevo código.
            cout << "Nuevo Puesto: "; getline(cin, e.puesto); // Solicita el nuevo puesto.
            cout << "Nuevo Teléfono: "; getline(cin, e.telefono); // Solicita el nuevo teléfono.
            modificado = true; // Marca que se modificó el empleado.
            break; // Sale del bucle.
        }
    }

    if (modificado) { // Si se modificó el empleado.
        ordenarEmpleados(); // Ordena la lista de empleados.
        guardarEmpleados(); // Guarda la lista actualizada en el archivo.
        bitacoralogEmpleados.insertar(usuario, 4009, "Empleados", "Modificar empleado"); // Registra la acción en la bitácora.
        cout << "\nEmpleado modificado correctamente."; // Mensaje de confirmación.
    } else {
        cout << "\nEmpleado no encontrado."; // Mensaje si no se encontró al empleado.
    }

    pausar(); // Pausa la ejecución.
}

void Empleados::desplegarEmpleados() { // Método para mostrar todos los empleados.
    limpiarPantalla(); // Limpia la pantalla.
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Empleados Registrados ===\n"; // Encabezado de la lista de empleados.

    if (empleados.empty()) { // Si no hay empleados registrados.
        cout << "\nNo hay empleados registrados."; // Mensaje informando que no hay empleados.
    } else {
        for (const auto& e : empleados) { // Itera sobre cada empleado.
            cout << "\n----------------------------"; // Línea divisoria.
            cout << "\nNombre   : " << e.nombre; // Muestra el nombre.
            cout << "\nCódigo   : " << e.codigo; // Muestra el código.
            cout << "\nPuesto   : " << e.puesto; // Muestra el puesto.
            cout << "\nTeléfono : " << e.telefono; // Muestra el teléfono.
        }
        cout << "\n----------------------------"; // Línea divisoria final.
        bitacoralogEmpleados.insertar(usuario, 4010, "Empleados", "Desplegar empleados"); // Registra la acción en la bitácora.
    }

    pausar(); // Pausa la ejecución.
}
