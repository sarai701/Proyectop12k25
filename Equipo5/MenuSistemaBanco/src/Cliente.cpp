//Boris de León 9959-24-6203
// Modificado por Boris de Leon el 10 de mayo
#include "Cliente.h"
#include "Bitacora.h" // Agrega la bitacora
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

Bitacora bitacoralogCliente; // Instancia global para registrar eventos
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

    while (getline(archivo, linea)) {
        size_t pos = 0;
        int campo = 0;
        string datos[4];  // Solo 4 campos ahora (sin saldo)
        for (int i = 0; i < 3; ++i) {
            pos = linea.find(',');
            datos[i] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[3] = linea; // Dirección

        c.codigo = datos[0];
        c.nombre = datos[1];
        c.telefono = datos[2];
        c.direccion = datos[3];

        clientes.push_back(c);
    }

    archivo.close();
    ordenarClientes();
}

// Guarda todos los clientes en el archivo clientes
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

void Cliente::setUsuario(const string& u) {
    usuario = u;
}

void Cliente::menuClienteCRUD() {
    int opcion;
    do {
        cargarClientes(); // cargar clientes
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
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


// Muestra el menú principal
void Cliente::menuCliente() {
    int opcion;
    do {
        cargarClientes(); // Cargar al entrar o después de cada operación
        limpiarPantalla();
        cout << "\nUsuario: " << usuario << endl;
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

    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Crear Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, c.codigo);  // Colocado primero
    cout << "Nombre: "; getline(cin, c.nombre);
    cout << "Teléfono: "; getline(cin, c.telefono);
    cout << "Dirección: "; getline(cin, c.direccion);

    clientes.push_back(c);
    ordenarClientes();
    guardarClientes();

    cout << "\nCliente agregado correctamente.";
    bitacoralogCliente.insertar(usuario, 4101, "Clientes", "Crear Cliente");

    pausar();
}

// Borra un cliente por código
void Cliente::borrarCliente() {
    limpiarPantalla();
    string codigo;
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Borrar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool eliminado = false;
    vector<Cliente> nuevaLista;

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
        bitacoralogCliente.insertar(usuario, 4102, "Clientes", "Borrar Cliente");

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
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Buscar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool encontrado = false;

    for (const auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nCliente encontrado:";
            cout << "\nCódigo    : " << c.codigo;
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTeléfono  : " << c.telefono;
            cout << "\nDirección : " << c.direccion;
            encontrado = true;
            bitacoralogCliente.insertar(usuario, 4103, "Clientes", "Buscar Cliente");
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
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Modificar Cliente ===";
    cout << "\nCódigo de Cliente: "; getline(cin, codigo);

    bool modificado = false;

    for (auto& c : clientes) {
        if (c.codigo == codigo) {
            cout << "\nIngrese nueva información:";
            cout << "\nNuevo Código: "; getline(cin, c.codigo);
            cout << "Nuevo Nombre: "; getline(cin, c.nombre);
            cout << "Nuevo Teléfono: "; getline(cin, c.telefono);
            cout << "Nueva Dirección: "; getline(cin, c.direccion);
            modificado = true;
            break;
        }
    }


if (modificado) { // Si se realizó alguna modificación en el cliente:
    ordenarClientes(); // Ordena la lista de clientes para mantener el orden alfabético o lógico.
    guardarClientes(); // Guarda la lista actualizada de clientes en el archivo correspondiente,
    bitacoralogCliente.insertar(usuario, 4104, "Clientes", "Modificar Cliente"); // Registra la acción realizada en la bitácora del sistema
        cout << "\nCliente modificado exitosamente.";
    } else {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}

// Muestra todos los clientes
void Cliente::desplegarClientes() {
    limpiarPantalla();
    cout << "\nUsuario: " << usuario << endl;
    cout << "\n=== Clientes Registrados ===\n";

    if (clientes.empty()) {
        cout << "\nNo hay clientes registrados.";
    } else {
        for (const auto& c : clientes) {
            cout << "\n-----------------------------";
            cout << "\nCódigo    : " << c.codigo;  // Muestra primero el código
            cout << "\nNombre    : " << c.nombre;
            cout << "\nTeléfono  : " << c.telefono;
            cout << "\nDirección : " << c.direccion;
        }
        cout << "\n-----------------------------";
        bitacoralogCliente.insertar(usuario, 4105, "Clientes", "Desplegar Cliente");
    }

    pausar();
}

void Cliente::registrarMovimiento() {
    limpiarPantalla();
    cargarClientes();  // Solución agregada

    string codigoCliente, descripcion, fecha;
    double monto=0;
    cout << "\n=== Registrar Movimiento ===";
    cout << "\nCódigo del Cliente: ";
    cin.ignore();
    getline(cin, codigoCliente);

    bool encontrado = false;
    for (const auto& c : clientes) {   // Recorre cada cliente dentro del vector 'clientes'.
        if (c.codigo == codigoCliente) {
            encontrado = true;
            cout << "Descripción del movimiento: ";
            getline(cin, descripcion);

            cout << "Fecha del movimiento (DD/MM/AAAA): ";
            getline(cin, fecha);
            cout << "Monto del movimiento: ";
            cin >> monto;
            cin.ignore();

            ofstream archivo("movimientos.txt", ios::app);
            archivo << codigoCliente << "," << descripcion << "," << fecha << "," << monto  << "\n";
            archivo.close();

            cout << "\nMovimiento registrado correctamente.";

            break;
        }
    }

    if (!encontrado) {
        cout << "\nCliente no encontrado.";
    }

    pausar();
}


void Cliente::mostrarMovimientos() {
    limpiarPantalla();                         // Limpia la pantalla antes de mostrar información.
    string codigoCliente, linea;               // Declara variables para código del cliente y línea leída.
    cout << "\n=== Mostrar Movimientos ===";   // Muestra título del menú.
    cout << "\nCódigo del Cliente: ";          // Solicita al usuario ingresar el código del cliente.
    cin.ignore();                             // Limpia el buffer de entrada para evitar errores.
    getline(cin, codigoCliente);              // Lee el código del cliente ingresado por el usuario.

    ifstream archivo("movimientos.txt");      // Abre el archivo con los movimientos.
    bool hayMovimientos = false;               // Variable para saber si hay movimientos encontrados.

    while (getline(archivo, linea)) {          // Lee línea por línea el archivo.
        size_t pos = linea.find(',');          // Encuentra la posición de la coma separadora.
        string codigo = linea.substr(0, pos);  // Extrae el código del cliente de la línea.
        string descripcion = linea.substr(pos + 1); // Extrae la descripción del movimiento.

        if (codigo == codigoCliente) {          // Compara el código leído con el ingresado.
            cout << "\n- " << descripcion;      // Muestra la descripción del movimiento.
            hayMovimientos = true;               // Marca que sí hay movimientos para este cliente.
        }
    }


    archivo.close();

    if (!hayMovimientos) {
        cout << "\nNo hay movimientos registrados para este cliente.";
    }

    pausar();
}

void Cliente::abrirArchivoMovimientos() {
    limpiarPantalla();                       // Limpia la pantalla antes de mostrar contenido.
    cout << "\n=== Contenido del archivo movimientos.txt ===\n";  // Muestra título.

    ifstream archivo("movimientos.txt");    // Abre el archivo de movimientos en modo lectura.
    string linea;                           // Variable para almacenar cada línea leída.
    while (getline(archivo, linea)) {      // Lee línea por línea hasta el final del archivo.
        cout << linea << "\n";              // Imprime cada línea del archivo en pantalla.
    }
    archivo.close();                        // Cierra el archivo después de leerlo.

    pausar();                              // Pausa el programa hasta que el usuario presione ENTER.
}


void Cliente::registrarPrestamo() {
    limpiarPantalla();                                // Limpia pantalla antes de iniciar.
    string codigoCliente, estado;                      // Variables para código y estado del préstamo.
    double monto;                                      // Variable para monto del préstamo.
    cout << "\n=== Registrar Préstamo ===";            // Muestra título de la función.
    cout << "\nCódigo del Cliente: ";                  // Solicita código del cliente.
    cin.ignore();                                      // Ignora caracteres previos en el buffer.
    getline(cin, codigoCliente);                       // Lee el código del cliente.

    bool encontrado = false;                           // Variable para verificar si cliente existe.
    for (const auto& c :clientes) {                    // Itera sobre todos los clientes.
        if (c.codigo == codigoCliente) {               // Verifica si el código coincide.
            encontrado = true;                         // Marca cliente como encontrado.
            cout << "Monto del préstamo: ";            // Solicita monto del préstamo.
            cin >> monto;                              // Lee el monto.
            cin.ignore();                              // Limpia buffer después de entrada numérica.
            cout << "¿Está pagado? (Sí/No): ";         // Pregunta estado del pago.
            getline(cin, estado);                       // Lee el estado del préstamo.

            ofstream archivo("prestamos.txt", ios::app); // Abre archivo para agregar datos.
            archivo << codigoCliente << "," << monto << ", se realizo el pago del prestamo? " << estado << "\n"; // Escribe datos en archivo.
            archivo.close();                            // Cierra el archivo.

            cout << "\nPréstamo registrado correctamente."; // Mensaje de confirmación.

            break;                                     // Sale del ciclo al encontrar el cliente.
        }
    }

    if (!encontrado) {                                 // Si cliente no fue encontrado.
        cout << "\nCliente no encontrado.";            // Muestra mensaje de error.
    }

    pausar();                                         // Pausa hasta que usuario presione ENTER.
}

void Cliente::mostrarPrestamos() {
    limpiarPantalla();                                // Limpia pantalla antes de mostrar préstamos.
    string codigoCliente, linea;                       // Variables para código y línea leída.
    cout << "\n=== Mostrar Préstamos ===";             // Muestra título.
    cout << "\nCódigo del Cliente: ";                  // Solicita código del cliente.
    cin.ignore();                                      // Ignora caracteres previos.
    getline(cin, codigoCliente);                       // Lee código del cliente.

    ifstream archivo("prestamos.txt");                 // Abre archivo de préstamos.
    bool hayPrestamos = false;                          // Indicador si hay préstamos para cliente.

    while (getline(archivo, linea)) {                   // Lee línea por línea.
        size_t pos1 = linea.find(',');                  // Encuentra primer separador.
        size_t pos2 = linea.find(',', pos1 + 1);        // Encuentra segundo separador.
        string codigo = linea.substr(0, pos1);           // Extrae código cliente.
        string monto = linea.substr(pos1 + 1, pos2 - pos1 - 1); // Extrae monto.
        string estado = linea.substr(pos2 + 1);          // Extrae estado del préstamo.

        if (codigo == codigoCliente) {                   // Si el código coincide con el cliente.
            cout << "\nMonto: Q." << monto << " - Estado: " << estado; // Muestra préstamo.
            hayPrestamos = true;                         // Marca que hay préstamos.
        }
    }

    archivo.close();                                    // Cierra archivo.

    if (!hayPrestamos) {                               // Si no hay préstamos.
        cout << "\nNo hay préstamos registrados para este cliente."; // Muestra mensaje.
    }

    pausar();                                          // Pausa hasta que usuario presione ENTER.
}
