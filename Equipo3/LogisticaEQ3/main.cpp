// Gabriela - Mayo 2025
#include <iostream>
#include "Reportes.h"
#include "Usuario.h"
#include "Inventario.h"
#include "Facturacion.h"
#include "Bitacora.h"

using namespace std;

int main() {
    int opcion;
    // Crear instancias de los módulos
    Reportes reportes;
    Usuarios usuarios;
    Inventario inventario;
    Facturacion facturacion;
    Bitacora bitacora;
    Envios envios;
    Pedidos pedidos


    do {
        // Menú principal del sistema logístico
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| SISTEMA LOGISTICO - MENU PRINCIPAL   |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Módulo de Reportes" << endl;
        cout << "\t\t 2. Módulo de Usuarios" << endl;
        cout << "\t\t 3. Módulo de Inventario" << endl;
        cout << "\t\t 4. Módulo de Facturación" << endl;
        cout << "\t\t 5. Módulo de Bitácora" << endl;
         cout << "\t\t 5. Módulo de Envios" << endl;
          cout << "\t\t 5. Módulo de Pedidos" << endl;
        cout << "\t\t 6. Salir" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tSeleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                reportes.mostrarMenuReportes(); // Llamar al módulo de reportes
                break;
            case 2:
                usuarios.mostrarMenuUsuarios(); // Llamar al módulo de usuarios
                break;
            case 3:
                inventario.mostrarMenuInventario(); // Llamar al módulo de inventario
                break;
            case 4:
                facturacion.mostrarMenuFacturacion(); // Llamar al módulo de facturación
                break;

            case 5:
                bitacora.mostrarMenuBitacora(); // Llamar al módulo de bitácora
                break;
            case 6:
                bitacora.mostrarMenuEnvios(); // Llamar al módulo de bitácora
                break;
            case 7:
                bitacora.mostrarMenuPedidos(); // Llamar al módulo de bitácora
                break;
            case 8:
                cout << "\nSaliendo del sistema... Gracias por usar el sistema logístico." << endl;
                break;
            default:
                cout << "\nOpción inválida. Intente de nuevo." << endl;
                system("pause");
                break;
        }

    } while(opcion != 6);

    return 0;
}
