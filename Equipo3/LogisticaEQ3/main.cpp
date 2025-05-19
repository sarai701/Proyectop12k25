// 9959-24-11603
// Programa principal que integra los módulos de usuarios, pedidos, inventario, envíos, facturación, reportes y bitácora.
// Incluye autenticación de usuario y menú general de navegación del sistema.

#include <iostream>
#include "usuarios.h"
#include "pedidos.h"
#include "inventario.h"
#include "envios.h"
#include "facturacion.h"
#include "reportes.h"
#include "bitacora.h"

using namespace std;

// Instancias de clases globales para gestionar los distintos módulos
usuarios usuarioRegistrado;
bitacora auditoria;
Pedidos gestorPedidos;
Inventario gestorInventario;
Envios gestorEnvios;
Facturacion gestorFacturacion;
Reportes gestorReportes;

// Prototipo del menú principal
void menuGeneral();

int main() {
    bool accessUsuarios;

    // Inicio de sesión del usuario
    accessUsuarios = usuarioRegistrado.loginUsuarios();

    // Si el login es exitoso, se muestra el menú principal
    if (accessUsuarios) {
        menuGeneral();
    }

    // Mensaje de despedida al salir
    system("cls");
    cout << "** Hasta la próxima **";
    return 0;
}

// Función que muestra el menú general del sistema
void menuGeneral() {
    int choice;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t|     SISTEMA DE GESTIÓN LOGÍSTICA     |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Gestión de Pedidos" << endl;
        cout << "\t\t 2. Control de Inventario" << endl;
        cout << "\t\t 3. Envíos y Transportes" << endl;
        cout << "\t\t 4. Facturación y Análisis" << endl;
        cout << "\t\t 5. Reportes y Análisis" << endl;
        cout << "\t\t 6. Salir del Sistema" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpción a escoger: [1/2/3/4/5/6]" << endl;
        cout << "\t\tIngresa tu opción: ";
        cin >> choice;

        switch(choice) {
            case 1:
                gestorPedidos.gestionPedidos();
                break;
            case 2:
                gestorInventario.controlInventario();
                break;
            case 3:
                gestorEnvios.gestionEnvios();
                break;
            case 4:
                gestorFacturacion.gestionFacturacion();
                break;
            case 5:
                gestorReportes.generarReportes();
                break;
            case 6: break;
            default:
                cout << "\n\t\tOpción inválida... Intenta de nuevo...";
                cin.get();
        }
    } while(choice != 6);
}
