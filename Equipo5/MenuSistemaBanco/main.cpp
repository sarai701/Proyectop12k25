//Programado por Priscila Sarai Guzmán Calgua 9959-23-450
#include <iostream>
#include <fstream>
#include <string>
#include "Empleados.h"
#include "Cliente.h"
#include "Proveedores.h"
#include "Contabilidad.h"
#include "Auditoria.h"
#include "Usuario.h"
#include <conio.h>
#include "Nominas.h"
#include "Bitacora.h"
#include "Bancos.h"
#include "Moneda.h"
#include <limits>
using namespace std;
// Función para pausar el sistema hasta que el usuario presione ENTER
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
// Función para limpiar errores de entrada en caso de que el usuario ingrese datos no válidos
void limpiarBufferEntrada() {
    cin.clear();// Limpia errores de entrada
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora lo que quede en el buffer
}

void realizarBackup() {
    // Crear directorio si no existe (Windows)
    system("mkdir backup 2> nul");

    // Lista de archivos a respaldar
    const char* archivos[] = {
        "clientes.txt", "proveedores.txt", "empleados.txt",
        "movimientos.txt", "prestamos.txt", "bitacora.txt",
        "auditores.txt", "pagos.txt", "salarios.txt"
    };

    // Copiar cada archivo sobrescribiendo el anterior
    for (const char* archivo : archivos) {
        string comando = "copy /Y " + string(archivo) + // /Y para sobrescribir en Windows
                        " backup\\" + string(archivo) + ".bak > nul";
        system(comando.c_str());
    }
}

void menuArchivo(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla();
    int opcion;
    do {
        cout << "\n--- MENÚ ARCHIVO ---";
        cout << "\n1. Backup";
        cout << "\n2. Volver al Menú General";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        // Validación de entrada
        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "\nEntrada inválida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
            case 1:
                realizarBackup();
                cout << "\nBackup realizado exitosamente!\n";
                bitacora.insertar(usuario, 4905, "Sistema", "Backup realizado");
                break;
            case 2:
                return;
            default:
                cout << "\nOpción inválida.\n";
                break;
        }
        pausar();
        Usuario::limpiarPantalla();
    } while (true);
}
// Muestra el menú Catálogos, que permite acceder a diferentes módulos del sistema
void menuCatalogos(const string& usuario, Bitacora& bitacora, Empleados& empleados, Cliente& cliente, Proveedor& proveedor, Auditoria& auditoria, Nominas& nominas) {
    Usuario::limpiarPantalla();
    int opcion;
    do {
        cout << "\n--- MENÚ CATÁLOGOS ---";
        cout << "\n1. Nóminas";
        cout << "\n2. Cliente";
        cout << "\n3. Empleados";
        cout << "\n4. Auditoría";
        cout << "\n5. Proveedores";
        cout << "\n6. Volver al Menú General";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        if(cin.fail()) {
            limpiarBufferEntrada();
            cout << "\nEntrada inválida. Intente de nuevo.\n";
            continue;
        }
// Cada caso accede a un módulo del sistema y registra la acción en la bitácora
        switch (opcion) {
            case 1:
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
    } while (true);
}
// Muestra el menú Procesos, que incluye movimientos, préstamos, contabilidad y configuración bancaria
void menuProcesos(const string& usuario, Bitacora& bitacora, Cliente& cliente, Contabilidad& contabilidad) {
    Usuario::limpiarPantalla();
    Bancos bancos;
    Moneda moneda;
// Configuración bancaria al inicio del menú Procesos
    cout << "\nSeleccione configuración bancaria y moneda para Procesos:\n";
    bancos.menuConfiguracion();
    bitacora.insertar(usuario, 4300, "Procesos", "Configuración bancaria y moneda seleccionada");

    int opcionProcesos;
    do {
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
// Acciones para cada opción de clientes
        switch (opcionProcesos) {
            case 1: {
                Usuario::limpiarPantalla();
                int opcionClientes;
                do {
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

                    switch (opcionClientes) {
                        case 1:
                            cliente.registrarMovimiento();
                            bitacora.insertar(usuario, 4100, "Clientes", "Movimiento registrado");
                            break;
                        case 2:
                            cliente.mostrarMovimientos();
                            bitacora.insertar(usuario, 4101, "Clientes", "Movimientos mostrados");
                            break;
                        case 3:
                            cliente.abrirArchivoMovimientos();
                            bitacora.insertar(usuario, 4102, "Clientes", "Mostrar movimientos");
                            break;
                        case 4:
                            cliente.registrarPrestamo();
                            bitacora.insertar(usuario, 4103, "Clientes", "Préstamo registrado");
                            break;
                        case 5:
                            cliente.mostrarPrestamos();
                            bitacora.insertar(usuario, 4104, "Clientes", "Préstamos mostrados");
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Opción no válida.\n";
                    }
                    pausar();
                    Usuario::limpiarPantalla();
                } while (opcionClientes != 6);
                break;
            }
            case 2:
                contabilidad.menuContabilidad();
                bitacora.insertar(usuario, 4301, "Contabilidad", "Ingresó al módulo Contabilidad");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 3:
                cout << "\n--- Configuración bancaria actual ---\n";
                bancos.mostrarConfiguracion();
                moneda.mostrarMoneda();
                bitacora.insertar(usuario, 4302, "Procesos", "Mostró configuración bancaria y moneda");
                pausar();
                Usuario::limpiarPantalla();
                break;
            case 4:
                cout << "Volviendo al menú general...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcionProcesos != 4);
}
// Muestra el menú Informes
void menuInformes(const string& usuario, Bitacora& bitacora) {
    Usuario::limpiarPantalla();
    int opcionInformes;
    do {
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
                bitacora.mostrar();// Muestra las acciones realizadas
                bitacora.insertar(usuario, 4990, "Informes", "Bitácora mostrada");
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
// Menú principal del sistema, se accede luego de iniciar sesión
void menuGeneral(const string& usuario) {
     // Objetos que usarán los menús
    Bitacora bitacora;
    Empleados empleados;
    Cliente cliente;
    Proveedor proveedor;
    Auditoria auditoria;
    Nominas nominas;
    Contabilidad contabilidad;

    int opcion;
    do {
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
 // Acciones según la opción seleccionada
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
        // Llama al menú de autenticación y verifica si el usuario se autenticó correctamente
        if (Usuario::menuAutenticacion(usuarioLogueado)) {
            bitacoraGlobal.insertar(usuarioLogueado, 4900, "Sistema", "Inicio de sesión exitoso");
            menuGeneral(usuarioLogueado);
        } else {
            cout << "\nAutenticación fallida.\n";
            bitacoraGlobal.insertar("Desconocido", 4902, "Sistema", "Falló intento de login");
            break;
        }
    }
    return 0;
}


