//Clase para el menu de procesos - Astrid Ruíz 9959 24 2976 Mayo 2025
#include <iostream>
#include "procesos.h"
#include "transaccion.h"
#include "factura.h"  // Incluimos el encabezado de facturas Dulce Reyes

using namespace std;

// Menú principal de procesos
void menuProcesos() {
    int opcion;
    do {
        system("cls");
        cout << "\n\n\t\tMenu Procesos" << endl;
        cout << "\t\t------------------------" << endl;
        cout << "\t\t1. Registro de Factura" << endl;
        cout << "\t\t2. Gestionar pagos a Proveedor o Acreedor" << endl;
        cout << "\t\t3. Gestionar cobro a Cliente" << endl;
        cout << "\t\t4. Gestionar transacciones bancarias" << endl;
        cout << "\t\t5. Volver al menu principal" << endl;
        cout << "\n\t\tIngrese una opción: ";
        cin >> opcion;
        switch(opcion){
        case 1:
            menuFactura(); // Ahora llama al submenú de facturas
            break;
        case 2:
            //menuGestionarPagos();  // Por implementar
            break;
        case 3:
            //menuGestionarCobro();  // Por implementar
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

// Menú de facturas completo
void menuFactura() {
    int opcion;

    do {
        system("cls");
        cout << "--- Menu Factura ---\n";
        cout << "1. Registrar Factura\n";
        cout << "2. Modificar Factura\n";
        cout << "3. Eliminar Factura\n";
        cout << "4. Ver Facturas\n";
        cout << "5. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: registrarFactura(); break;
            case 2: modificarFactura(); break;
            case 3: eliminarFactura(); break;
            case 4: verFacturas(); break;
            case 5: break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
        }
    } while(opcion != 5);
}

// Menú de transacciones (ya estaba en tu código)
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
