// Clase para el menu de procesos - Astrid Ruíz 9959 24 2976 Mayo 2025
#include <iostream>
#include <limits>
#include "procesos.h"
#include "transaccion.h"
#include "factura.h"  // Incluimos el encabezado de facturas - Dulce Reyes
#include "pago.h"
using namespace std;

// Menú principal de procesos
void menuProcesos() {
    pago pag;
    int opcion;
    do {
        system("cls");
        cout << "\n\n\t\tMenu Procesos" << endl;
        cout << "\t\t------------------------" << endl;
        cout << "\t\t1. Facturas (Clientes/Proveedores/Acreedores)" << endl;
        cout << "\t\t2. Gestionar pagos a Proveedor o Acreedor" << endl;
        cout << "\t\t3. Gestionar cobro a Cliente" << endl;
        cout << "\t\t4. Gestionar transacciones bancarias" << endl;
        cout << "\t\t5. Volver al menu principal" << endl;
        cout << "\n\t\tIngrese una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1:
                menuFactura(); // Submenú con 3 tipos de factura
                break;
            case 2:
                pag.menuPagos();
                system("pause");
                break;
            case 3:
                cout << "\t\tOpción en desarrollo..." << endl;
                system("pause");
                break;
            case 4:
                menuTransacciones();
                break;
            case 5:
                break;
            default:
                cout << "\t\tOpción inválida." << endl;
                system("pause");
        }
    } while(opcion != 5);
}

// Submenú de Facturas - Dulce Reyes Mayo 2025
void menuFactura() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t\tMenu de Facturas" << endl;
        cout << "\t\t-----------------------------" << endl;
        cout << "\t\t1. Factura de Cliente" << endl;
        cout << "\t\t2. Factura de Proveedor" << endl;
        cout << "\t\t3. Factura de Acreedor" << endl;
        cout << "\t\t4. Reportes Factura " << endl;
        cout << "\t\t5. Volver al menu anterior" << endl;
        cout << "\n\t\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                menuFacturaCliente();
                break;
            case 2:
                menuFacturaProveedor();
                break;
            case 3:
                menuFacturaAcreedor();
                break;
            case 4:
                menuReporteFactura();
                break;
            case 5:
                break;
            default:
                cout << "\t\tOpción inválida." << endl;
                system("pause");
        }
    } while (opcion != 5);
}

// Menú de transacciones bancarias (manteniendo estructura original)
void menuTransacciones() {
    int opcion;
    transaccion t;

    do {
        system("cls");
        cout << "\n\n\t\tTransacciones Bancarias" << endl;
        cout << "\t\t1. Realizar Depósito" << endl;
        cout << "\t\t2. Realizar Retiro" << endl;
        cout << "\t\t3. Realizar Transferencia" << endl;
        cout << "\t\t4. Listar Transacciones" << endl;
        cout << "\t\t5. Editar Transacción" << endl;
        cout << "\t\t6. Eliminar Transacción" << endl;
        cout << "\t\t7. Volver" << endl;
        cout << "\n\t\tIngrese una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string id;

        switch (opcion) {
            case 1:
                t.registrarTransaccion("Deposito");
                t.guardarEnArchivo();
                system("pause");
                break;
            case 2:
                t.registrarTransaccion("Retiro");
                t.guardarEnArchivo();
                system("pause");
                break;
            case 3:
                t.registrarTransaccion("Transferencia");
                t.guardarEnArchivo();
                system("pause");
                break;
            case 4:
                transaccion::mostrarTodasDesdeArchivo();
                system("pause");
                break;
            case 5:
                cout << "Ingrese ID de transacción a editar: ";
                cin >> id;
                transaccion::editarTransaccion(id);
                system("pause");
                break;
            case 6:
                cout << "Ingrese ID de transacción a eliminar: ";
                cin >> id;
                transaccion::eliminarTransaccion(id);
                system("pause");
                break;
            case 7:
                break;
            default:
                cout << "\n\t\tOpción inválida." << endl;
                system("pause");
        }
    } while (opcion != 7);
}
