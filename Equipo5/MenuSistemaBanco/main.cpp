//Programado por Priscila Sarai Guzmán Calgua 9959-23-450
#include <iostream>      // Biblioteca para entrada y salida estándar (cin, cout)
#include <fstream>       // Biblioteca para manejo de archivos (ifstream, ofstream)
#include <string>
#include "Empleados.h"
#include "Cliente.h"
#include "Proveedores.h"
#include "Contabilidad.h"
#include "Auditoria.h"
#include "Usuario.h"
#include <conio.h>       // Biblioteca para funciones de consola (como getch)
#include "Nominas.h"
#include "Bitacora.h"
#include "Bancos.h"
#include "Moneda.h"
#include <limits>        // Biblioteca para usar limits, como numeric_limits (para manejar buffers)

using namespace std;

// Función para pausar el sistema hasta que el usuario presione ENTER
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    // Ignorar cualquier entrada pendiente en el buffer hasta encontrar salto de línea
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Esperar a que el usuario presione ENTER
    cin.get();
}

// Función para limpiar errores de entrada y vaciar el buffer
void limpiarBufferEntrada() {
    cin.clear(); // Limpia cualquier error previo de cin (como entrada no numérica cuando se esperaba un número)
    // Ignora todo lo que quede en el buffer de entrada para evitar problemas en lecturas siguientes
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

void realizarBackup() { //Crea un carpeta llamado "backup" si no existe
    // Crear directorio si no existe (Windows)
    system("mkdir backup 2> nul");  //El "2> nul" redirige cualquier mensaje de error (por ejemplo, si ya existe) para no mostrarlo.
    //Si los archivos de respaldo ya existen, se sobrescriben automáticamente.
    // Lista de archivos a respaldar
    const char* archivos[] = {
        "bitacora.dat", "movimientos.dat",
        "auditores.dat", "clientes.dat", "empleados.dat", "login.dat",
        "nominas.dat", "pagos.dat", "prestamos.dat", "proveedores.dat"
    };

    // Copiar cada archivo sobrescribiendo el anterior
    for (const char* archivo : archivos) {
        string comando = "copy /Y " + string(archivo) + // - copy /Y: copia el archivo y sobrescribe el existente sin preguntar
                        " backup\\" + string(archivo) + ".bak > nul"; //archivo.bak: destino del archivo, con extensión .bak
        system(comando.c_str());                                      //// - > nul: redirige la salida estándar para evitar mostrar mensajes
    }
}


// Función que muestra el menú Archivo, recibe el usuario actual y un objeto bitácora para registrar acciones
void menuArchivo(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla(); // Llama a método para limpiar la pantalla (generalmente usando sistema operativo)
    int opcion;                 // Variable para guardar la opción seleccionada por el usuario

    do {
        // Mostrar las opciones disponibles en el menú Archivo
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n--- MENÚ ARCHIVO ---";
        cout << "\n1. Backup";
        cout << "\n2. Volver al Menú General";
        cout << "\nSeleccione una opción: ";

        cin >> opcion;// Leer la opción ingresada

        // Validar que la entrada sea correcta y no haya fallado la lectura
        if(cin.fail()) {
            limpiarBufferEntrada();  // Limpiar buffer y errores si la entrada fue inválida
            cout << "\nEntrada inválida. Intente de nuevo.\n";
            continue; // Volver a mostrar el menú
        }

        switch (opcion) {
            case 1:
                realizarBackup();
                cout << "\nBackup realizado exitosamente!\n";
                bitacora.insertar(usuario, 4905, "Sistema", "Backup realizado");
                break;

            case 2:
                // Opción para regresar al menú general, salir de este menú
                return;

            default:
                cout << "\nOpción inválida.\n";
                break;
        }

        pausar();
        Usuario::limpiarPantalla();

    } while (true);
}

// Función que muestra el menú Catálogos con varias opciones para gestionar diferentes módulos del sistema
void menuCatalogos(const string& usuario, Bitacora& bitacora, Empleados& empleados, Cliente& cliente, Proveedor& proveedor, Auditoria& auditoria, Nominas& nominas) {
    Usuario::limpiarPantalla();
    int opcion;// Variable para almacenar la opción del usuario

    do {
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n--- MENÚ CATÁLOGOS ---";
        cout << "\n1. Nóminas";
        cout << "\n2. Cliente";
        cout << "\n3. Empleados";
        cout << "\n4. Auditoría";
        cout << "\n5. Proveedores";
        cout << "\n6. Volver al Menú General";
        cout << "\nSeleccione una opción: ";

        cin >> opcion;

        // Validar entrada, asegurándose que sea correcta y sin errores
        if(cin.fail()) {
            limpiarBufferEntrada();  // Limpiar buffer y errores si la entrada fue inválida
            cout << "\nEntrada inválida. Intente de nuevo.\n";
            continue;// Volver a mostrar el menú
        }

        // Según la opción, se accede al módulo correspondiente y se registra la acción en bitácora
        switch (opcion) {
            case 1:
                // Acceder al menú de nóminas
                nominas.menuNominas();
                bitacora.insertar(usuario, 4000, "Nominas", "Ingresó al módulo de Nóminas");
                break;

            case 2:
                cliente.menuClienteCRUD();
                bitacora.insertar(usuario, 4100, "Clientes", "Ingresó al módulo de Clientes (CRUD)");
                break;

            case 3:
                empleados.menuEmpleados();
                bitacora.insertar(usuario, 4001, "Empleados", "Ingresó al módulo de Empleados");
                break;

            case 4:
                auditoria.menuAuditoria();
                bitacora.insertar(usuario, 4400, "Auditoría", "Ingresó al módulo de Auditoría");
                break;

            case 5:
                proveedor.menuProveedor();
                bitacora.insertar(usuario, 4200, "Proveedores", "Ingresó al módulo de Proveedores");
                break;

            case 6:
                return;

            default:
                cout << "\nOpción inválida.\n";
                break;
        }

        pausar();
        Usuario::limpiarPantalla();
    } while (true); // Ciclo hasta que se salga con la opción 6
}

// Menú de Procesos que incluye movimientos de clientes, contabilidad y configuración bancaria
void menuProcesos(const string& usuario, Bitacora& bitacora, Cliente& cliente, Contabilidad& contabilidad) {
    Usuario::limpiarPantalla();

    Bancos bancos; // Objeto para manejar configuración bancaria
    bancos.setUsuario(usuario);
    Moneda moneda; // Objeto para manejar tipo de moneda
    contabilidad.setUsuario(usuario);


    // Al iniciar el menú de procesos, solicita configuración bancaria
    cout << "\nSeleccione configuración bancaria:\n";
    cout << "\nUsuario: " << usuario << endl;
    bancos.menuConfiguracion(); // Muestra opciones para configurar banco y moneda
    bitacora.insertar(usuario, 4300, "Procesos", "Configuración bancaria");

    int opcionProcesos;
    do {
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n--- MENÚ PROCESOS ---" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Contabilidad" << endl;
        cout << "3. Mostrar configuración bancaria" << endl;
        cout << "4. Volver al Menú General" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcionProcesos;

        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "Entrada inválida. Intente de nuevo.\n";
            continue;
        }

        // Según la opción elegida en el menú de procesos
        switch (opcionProcesos) {
            case 1: {
                Usuario::limpiarPantalla();
                int opcionClientes;
                do {
                    // Submenú para procesos relacionados con clientes
                    cout << "\nUsuario: " << usuario << endl;
                    cout << "\n--- PROCESOS - CLIENTES ---" << endl;
                    cout << "1. Registrar movimiento" << endl;
                    cout << "2. Mostrar movimientos" << endl;
                    cout << "3. Abrir archivo movimientos.txt" << endl;
                    cout << "4. Registrar préstamo" << endl;
                    cout << "5. Mostrar préstamos" << endl;
                    cout << "6. Volver" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> opcionClientes;

                    if(cin.fail()) {
                        limpiarBufferEntrada();
                        cout << "Entrada inválida. Intente de nuevo.\n";
                        continue;
                    }

                    // Acciones específicas para clientes según opción
                    switch (opcionClientes) {
                        case 1:
                            cliente.registrarMovimiento(); // Registra un movimiento bancario
                            bitacora.insertar(usuario, 4106, "Clientes", "Movimiento registrado");
                            break;
                        case 2:
                            cliente.mostrarMovimientos(); // Muestra los movimientos registrados
                            bitacora.insertar(usuario, 4107, "Clientes", "Movimientos mostrados");
                            break;
                        case 3:
                            cliente.abrirArchivoMovimientos(); // Abre archivo externo con movimientos
                            bitacora.insertar(usuario, 4108, "Clientes", "Mostrar movimientos");
                            break;
                        case 4:
                            cliente.registrarPrestamo(); // Registra un préstamo para el cliente
                            bitacora.insertar(usuario, 4109, "Clientes", "Préstamo registrado");
                            break;
                        case 5:
                            cliente.mostrarPrestamos(); // Muestra préstamos registrados
                            bitacora.insertar(usuario, 4110, "Clientes", "Préstamos mostrados");
                            break;
                        case 6:
                            break; // Sale del submenú clientes
                        default:
                            cout << "Opción no válida.\n";
                    }
                    pausar();
                    Usuario::limpiarPantalla();
                } while (opcionClientes != 6);
                break;
            }
            case 2:
                // Menú para módulo de Contabilidad
                contabilidad.menuContabilidad();
                bitacora.insertar(usuario, 4301, "Contabilidad", "Ingresó al módulo Contabilidad");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 3:
                // Muestra configuración actual del banco y moneda
                cout << "\n--- Configuración bancaria actual ---\n";
                bancos.mostrarConfiguracion();
                bitacora.insertar(usuario, 4302, "Procesos", "Mostró configuración bancaria");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 4:
                cout << "Volviendo al menú general...\n"; // Opción para regresar al menú general
                break;
            default:
                cout << "Opción no válida.\n"; // Mensaje si la opción no existe
        }
    } while (opcionProcesos != 4); // Se repite hasta que el usuario decida salir
}

// Menú para mostrar informe (bitacora)
void menuInformes(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla();
    int opcionInformes;
    do {
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n--- MENÚ INFORMES ---" << endl;
        cout << "1. Bitácora" << endl;
        cout << "2. Volver al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcionInformes;

        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "Entrada inválida. Intente de nuevo.\n";
            continue;
        }

        switch (opcionInformes) {
            case 1:
                bitacora.mostrar(); // Muestra todas las acciones registradas en la bitácora
                bitacora.insertar(usuario, 4990, "Informes", "Bitácora mostrada"); // Registra la acción
                break;
            case 2:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
        pausar();
        Usuario::limpiarPantalla();
    } while (opcionInformes != 2);
}

// Menú principal
void menuGeneral(const string& usuario) {
    // Crea los objetos necesarios para los diferentes módulos del sistema
    Bitacora bitacora;
    Empleados empleados;
    empleados.setUsuario(usuario);
    Cliente cliente;
    cliente.setUsuario(usuario);
    Proveedor proveedor;
    proveedor.setUsuario(usuario);
    Auditoria auditoria;
    auditoria.setUsuario(usuario);
    Nominas nominas;
    nominas.setUsuario(usuario);
    Contabilidad contabilidad;

    int opcion;
    do {
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n======= MENÚ GENERAL =======";
        cout << "\n1. Archivo";
        cout << "\n2. Catálogos";
        cout << "\n3. Procesos";
        cout << "\n4. Informes";
        cout << "\n5. Cerrar Sesión";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;

        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "\nEntrada inválida. Intente de nuevo.\n";
            continue;
        }

        // Ejecuta la función correspondiente al módulo seleccionado
        switch (opcion) {
            case 1:
                menuArchivo(usuario, bitacora);
                break;
            case 2:
                menuCatalogos(usuario, bitacora, empleados, cliente, proveedor, auditoria, nominas);
                break;
            case 3:
                menuProcesos(usuario, bitacora, cliente, contabilidad);
                break;
            case 4:
                menuInformes(usuario, bitacora);
                break;
            case 5:
                // Registra en bitácora que el usuario cerró sesión y termina el programa
                bitacora.insertar(usuario, 4901, "Sistema", "Usuario cerró sesión");
                cout << "\nCerrando sesión...\n";
                return;
            default:
                cout << "\nOpción inválida.\n";
                bitacora.insertar(usuario, 4902, "Sistema", "Opción inválida en Menú General");
                break;
        }
        pausar();
        Usuario::limpiarPantalla();
    } while (true);
}

int main() {
    Bitacora bitacoraGlobal;// Bitácora general para registrar

    while (true) {
        string usuarioLogueado;//Variable para guardar el nombre del usuario
        Usuario usuario;
        // Llama al menú de autenticación y verifica si el usuario se autenticó correctamente
         if (usuario.menuAutenticacion(usuarioLogueado)) {

            menuGeneral(usuarioLogueado);
        } else {
            cout << "\nAutenticación fallida.\n";
            bitacoraGlobal.insertar("Desconocido", 4902, "Sistema", "Falló intento de login");
            break;
        }
    }
    return 0;
}


