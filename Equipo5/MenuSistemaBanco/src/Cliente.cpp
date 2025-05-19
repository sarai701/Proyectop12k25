// Boris de León 9959-24-6203
// Modificado por Boris de Leon el 10 de mayo
#include "Cliente.h"
#include "Bitacora.h" // Agrega la bitacora
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

Bitacora log; // Instancia global para registrar eventos
using namespace std;

// Limpia la pantalla según el sistema operativo
void Cliente::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa el programa hasta que el usuario presione ENTER
void Cliente::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Carga los clientes desde el archivo clientes.txt
void Cliente::cargarClientes() {
    clientes.clear();  // Vaciar lista actual
    ifstream archivo("clientes.txt");
    Cliente c;
    string linea;

    // Leer línea por línea del archivo
    while (getline(archivo, linea)) {
        size_t pos = 0;
        int campo = 0;
        string datos[4];  // Solo 4 campos ahora (sin saldo)

        // Separar los 3 primeros campos
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[3] = linea; // Dirección

        // Asignar datos al objeto cliente
        c.codigo = datos[0];
        c.nombre = datos[1];
        c.telefono = datos[2];
        c.direccion = datos[3];

        clientes.push_back(c); // Agregar a la lista
    }

    archivo.close();
    ordenarClientes(); // Ordenar después de cargar
}

// Guarda todos los clientes en el archivo clientes.txt
void Cliente::guardarClientes() {
    ofstream archivo("clientes.txt");
    for (const auto& c : clientes) {
        archivo << c.codigo << "," << c.nombre << "," << c.telefono << "," << c.direccion << "\n";
    }
    archivo.close();
}

// Ordena los clientes alfabéticamente por nombre
void Cliente::ordenarClientes() {
    sort(clientes.begin(), clientes.end(), [](const Cliente& a, const Cliente& b) {
        return a.nombre < b.nombre;
    });
}

// Menú CRUD de clientes básico
void Cliente::menuClienteCRUD() {
    int opcion;
    do {
        cargarClientes(); // cargar clientes
        limpiarPantalla();
        cout << "\n===== MENÚ DE CLIENTES =====";
        cout << "\n1. Crear Cliente";
        cout << "\n2. Borrar Cliente";
        cout << "\n3. Buscar Cliente";
        cout << "\n4. Modificar Cliente";
        cout << "\n5. Desplegar Clientes";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        // Selección según opción
        switch (opcion) {
            case 1: crearCliente(); break;
            case 2: borrarCliente(); break;
            case 3: buscarCliente(); break;
            case 4: modificarCliente(); break;
            case 5: desplegarClientes(); break;
            case 6: limpiarPantalla(); return;
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// Menú principal de clientes con funciones extendidas
void Cliente::menuCliente() {
    int opcion;
    do {
        cargarClientes(); // Cargar al entrar o después de cada operación
        limpiarPantalla();
        cout << "\n===== MENÚ DE CLIENTES =====";
        cout << "\n1. Crear Cliente";
        cout << "\n2. Borrar Cliente";
        cout << "\n3. Buscar Cliente";
        cout << "\n4. Modificar Cliente";
        cout << "\n5. Despliegue de Clientes";
        cout << "\n6. Registrar movimiento";
        cout << "\n7. Mostrar movimientos";
        cout << "\n8. Abrir archivo movimientos.txt";
        cout << "\n9. Registrar prestamo";
        cout << "\n10. Mostrar prestamos";
        cout << "\n11. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        // Opciones según la entrada del usuario
        switch (opcion) {
            case 1: crearCliente(); break;
            case 2: borrarCliente(); break;
            case 3: buscarCliente(); break;
            case 4: modificarCliente(); break;
            case 5: desplegarClientes(); break;
            case 6: registrarMovimiento(); break;
            case 7: mostrarMovimientos(); break;
            case 8: abrirArchivoMovimientos(); break;
            case 9: registrarPrestamo(); break;
            case 10: mostrarPrestamos(); break;
            case 11:
                limpiarPantalla();
                return;
            default:
                cout << "\nOpción inválida.";
                pausar();
        }
    } while (true);
}

// Agrega un nuevo cliente
void Cliente::crearCliente() {
    limpiarPantalla();
    Cliente c;

    cout << "\n=== Crear Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, c.codigo);  // Colocado primero
    cout << "Nombre: "; getline(cin, c.nombre);
    cout << "Teléfono: "; getline(cin, c.telefono);
    cout << "Dirección: "; getline(cin, c.direccion);

    clientes.push_back(c); // Agregar cliente
    ordenarClientes();     // Ordenar lista
    guardarClientes();     // Guardar en archivo

    cout << "\nCliente agregado correctamente.";
    log.insertar("Admin", 4101, "Clientes", "Crear Cliente"); // Registrar en bitácora

    pausar();
}

// Borra un cliente por código
void Cliente::borrarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Borrar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Cliente> nuevaLista;

    // Recorrer y copiar los que no coinciden
    for (const auto& c : clientes) {
        if (c.codigo != codigo) {
            nuevaLista.push_back(c);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        clientes = nuevaLista;
        guardarClientes();
        log.insertar("Admin", 4104, "Clientes", "Borrar Cliente"); // Bitácora
        cout << "\nCliente eliminado correctamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Busca un cliente por código
void Cliente::buscarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Buscar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& c : clientes) {
        if (c.codigo == codigo) {
            // Mostrar datos si se encuentra
            cout << "\nCliente encontrado:";
            cout << "\nCódigo    : " << c.codigo;
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTeléfono  : " << c.telefono;
            cout << "\nDirección : " << c.direccion;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Modifica los datos de un cliente
void Cliente::modificarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\n=== Modificar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& c : clientes) {
        if (c.codigo == codigo) {
            // Solicitar nuevos datos
            cout << "\nIngrese nueva información:";
            cout << "\nNuevo Código: "; getline(cin, c.codigo);
            cout << "Nuevo Nombre: "; getline(cin, c.nombre);
            cout << "Nuevo Teléfono: "; getline(cin, c.telefono);
            cout << "Nueva Dirección: "; getline(cin, c.direccion);
            modificado = true;
            break;
        }
    }

    if (modificado) {
        ordenarClientes();
        guardarClientes();
        log.insertar("Admin", 4103, "Clientes", "Modificar Cliente"); // Bitácora

        cout << "\nCliente modificado exitosamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Muestra todos los clientes
void Cliente::desplegarClientes() {
    limpiarPantalla();
    cout << "\n=== Clientes Registrados ===\n";

    if (clientes.empty()) {
        cout << "\nNo hay clientes registrados.";
    } else {
        // Mostrar todos los datos de cada cliente
        for (const auto& c : clientes) {
            cout << "\n-----------------------------";
            cout << "\nCódigo    : " << c.codigo;  // Muestra primero el código
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTeléfono  : " << c.telefono;
            cout << "\nDirección : " << c.direccion;
        }
        cout << "\n-----------------------------";
    }

    pausar();
}

// Registra un movimiento financiero para un cliente
void Cliente::registrarMovimiento() {
    limpiarPantalla();
    cargarClientes();  // Solución agregada

    string codigoCliente, descripcion, fecha;
    double monto = 0;
    cout << "\n=== Registrar Movimiento ===";
    cout << "\nCódigo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    bool encontrado = false;
    for (const auto& c : clientes) {
        if (c.codigo == codigoCliente) {
            encontrado = true;

            // Solicitar datos del movimiento
            cout << "Descripción del movimiento: ";
            getline(cin, descripcion);

            cout << "Fecha del movimiento (DD/MM/AAAA): ";
            getline(cin, fecha);

            cout << "Monto del movimiento: ";
            cin >> monto;
            cin.ignore();

            // Guardar en archivo de movimientos
            ofstream archivo("movimientos.txt", ios::app);
            archivo << codigoCliente << "," << descripcion << "," << fecha << "," << monto << "\n";
            archivo.close();

            cout << "\nMovimiento registrado correctamente.";
            log.insertar("Admin", 5101, "Movimientos", "Registrar Movimiento");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Muestra los movimientos registrados para un cliente específico.
// Lee el archivo "movimientos.txt" y filtra por el código del cliente.
// Si encuentra movimientos, los muestra. Si no, avisa que no hay registros.
void Cliente::mostrarMovimientos() {
    limpiarPantalla();
    string codigoCliente, linea;
    cout << "\n=== Mostrar Movimientos ===";
    cout << "\nCódigo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    ifstream archivo("movimientos.txt");
    bool hayMovimientos = false;

    while (getline(archivo, linea)) {
        size_t pos = linea.find(',');
        string codigo = linea.substr(0, pos);
        string descripcion = linea.substr(pos + 1);

        if (codigo == codigoCliente) {
            cout << "\n- " << descripcion;
            hayMovimientos = true;
        }
    }

    archivo.close();

    if (!hayMovimientos) {
        cout << "\nNo hay movimientos registrados para este cliente.";
    }

    pausar();
}

// Muestra todo el contenido del archivo "movimientos.txt" sin filtrar.
// Ideal para revisión general o depuración.
void Cliente::abrirArchivoMovimientos() {
    limpiarPantalla();
    cout << "\n=== Contenido del archivo movimientos.txt ===\n";

    ifstream archivo("movimientos.txt");
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << "\n";
    }
    archivo.close();

    pausar();
}

// Registra un préstamo para un cliente si existe en el vector 'clientes'.
// Guarda en "prestamos.txt" el código, monto y estado (pagado o no).
// También registra la acción en el log del sistema.
void Cliente::registrarPrestamo() {
    limpiarPantalla();
    string codigoCliente, estado;
    double monto;
    cout << "\n=== Registrar Préstamo ===";
    cout << "\nCódigo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    bool encontrado = false;
    for (const auto& c :clientes) {
        if (c.codigo == codigoCliente) {
            encontrado = true;
            cout << "Monto del préstamo: ";
            cin >> monto;
            cin.ignore();
            cout << "¿Está pagado? (Sí/No): ";
            getline(cin, estado);

            ofstream archivo("prestamos.txt", ios::app);
            archivo << codigoCliente << "," << monto << ", se realizo el pago del prestamo? " << estado << "\n";
            archivo.close();

            cout << "\nPréstamo registrado correctamente.";
            log.insertar("Admin", 5201, "Préstamos", "Registrar Préstamo");
            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Muestra los préstamos de un cliente según su código.
// Lee "prestamos.txt" y muestra monto y estado de pago si hay registros.
// Informa si no hay préstamos asociados al cliente ingresado.
void Cliente::mostrarPrestamos() {
    limpiarPantalla();
    string codigoCliente, linea;
    cout << "\n=== Mostrar Préstamos ===";
    cout << "\nCódigo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    ifstream archivo("prestamos.txt");
    bool hayPrestamos = false;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        string codigo = linea.substr(0, pos1);
        string monto = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string estado = linea.substr(pos2 + 1);

        if (codigo == codigoCliente) {
            cout << "\nMonto: Q." << monto << " - Estado: " << estado;
            hayPrestamos = true;
        }
    }

    archivo.close();

    if (!hayPrestamos) {
        cout << "\nNo hay préstamos registrados para este cliente.";
    }

    pausar();
}
