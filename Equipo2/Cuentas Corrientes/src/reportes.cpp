#include "reportes.h"
#include <iostream>

//Clases con informes
#include "pago.h"
//...otros

using namespace std;
reportes::reportes()
{
    //ctor
}

void reportes::menuInformes() {
    pago pag;

    int opcion;
    do {
        system("cls");
        cout << "\n\n\t\tMenú de Reportes" << endl;
        cout << "\t\t-----------------------------" << endl;
        cout << "\t\t1. Listado de Cuentas por Pagar" << endl;
        cout << "\t\t2. Listado de Cuentas por Cobrar" << endl;
        cout << "\t\t3. Reporte de Pagos Realizados" << endl;
        cout << "\t\t4. Reporte de Ingresos Recibidos" << endl;
        cout << "\t\t5. Reporte de Transacciones Bancarias" << endl;
        cout << "\t\t9. Volver al menú principal" << endl;
        cout << "\n\t\tIngresa tu Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                pag.reporteCuentasPorPagar(); //Muestra todas las facturas pendientes de pago
                break;
            case 2:
                //reporte Cuentas Por Cobrar
                break;
            case 3:
                pag.reportePagos(); //Muestra todos los pagos registrados por acreedores/proveedores
                break;
            case 4:
                //reporteIngresos() ---pagos de clientes
                break;
            case 5:
                //pag.reporteTransaccionesBancarias(); Este creo que no
                break;
            case 6:
                break;
            default:
                cout << "\t\tOpción inválida..." << endl;
                system("pause");
        }
    } while (opcion != 6);
}
