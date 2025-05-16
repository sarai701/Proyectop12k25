#include <iostream>
#include <fstream>
#include <string>
#include "Empleados.h"
#include "Cliente.h"
#include "Proveedores.h"
#include "Contabilidad.h"
#include "Auditoria.h"
#include "Usuario.h"
#include <conio.h> // para getch()
#include "Nominas.h"
#include "Bitacora.h"
#include "Bancos.h"

using namespace std;

// Pausar el programa esperando ENTER
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// Mostrar el menú principal, ahora recibe el nombre del usuario
void mostrarMenu(const string& usuario, Bancos& bancos) {
    Empleados empleados;
    Cliente cliente;
    Proveedor proveedor;
    Contabilidad contabilidad;
    Auditoria auditoria;
    Nominas nominas;
    Bitacora bitacora;

    int opcion;
    do {
        cout << "\n------------------------------------";
        cout << "\n        SISTEMA BANCARIO";
        cout << "\n------------------------------------";
        cout << "\n 1. Nominas";
        cout << "\n 2. Cliente";
        cout << "\n 3. Empleados";
        cout << "\n 4. Contabilidad";
        cout << "\n 5. Auditoria";
        cout << "\n 6. Proveedores";
        cout << "\n 7. Bitacora";
        cout << "\n 8. Bancos";
        cout << "\n 9. Salir";
        cout << "\n------------------------------------";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                nominas.menuNominas();
                bitacora.insertar(usuario, 4000, "Nominas", "Ingresó al módulo de Nóminas");
                break;
            case 2:
                cliente.menuCliente();
                bitacora.insertar(usuario, 4100, "Clientes", "Ingresó al módulo de Clientes");
                break;
            case 3:
                empleados.menuEmpleados();
                bitacora.insertar(usuario, 4001, "Empleados", "Ingresó al módulo de Empleados");
                break;
            case 4:
                contabilidad.menuContabilidad();
                bitacora.insertar(usuario, 4301, "Contabilidad", "Generar reporte contable");
                break;
            case 5:
                auditoria.menuAuditoria();
                bitacora.insertar(usuario, 4401, "Auditoría", "Revisar transacciones");
                break;
            case 6:
                proveedor.menuProveedor();
                bitacora.insertar(usuario, 4200, "Proveedores", "Ingresó al módulo de Proveedores");
                break;
            case 7:
                bitacora.menuBitacora();
                bitacora.insertar(usuario, 4402, "Sistema", "Usuario revisó la bitácora");
                break;
            case 8:
                bancos.mostrarConfiguracion();  // Usa la instancia configurada
                bitacora.insertar(usuario, 4500, "Sistema", "Usuario revisó la bancos");
                break;
            case 9:
                bitacora.insertar(usuario, 4901, "Sistema", "Usuario cerró sesión");
                cout << "\nSaliendo del sistema... Gracias!\n";
                break;

            default:
                cout << "\nOpción inválida. Intente de nuevo.\n";
                bitacora.insertar(usuario, 4902, "Sistema", "Intento de opción inválida");
                break;
        }

        pausar();
        Usuario::limpiarPantalla();

    } while (opcion != 9);
}

// Función principal
int main() {
    while (true) {
        string usuarioLogueado;
        if (Usuario::menuAutenticacion(usuarioLogueado)) {
            Bitacora bitacora;
            bitacora.insertar(usuarioLogueado, 1000, "Sistema", "Inicio de sesión exitoso");

            // Configuración inicial obligatoria
            Bancos configuracion;
            configuracion.menuConfiguracion();

            mostrarMenu(usuarioLogueado, configuracion);
        } else {
            cout << "\nAutenticación fallida.\n";
            break;
        }
    }
    return 0;
}
