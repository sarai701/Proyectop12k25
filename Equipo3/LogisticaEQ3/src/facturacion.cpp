// Angoly Camila Araujo Mayen Mayo 2025 Progra1
// 9959-24-17623

#include "facturacion.h" // Inclusión del encabezado donde están declaradas las funciones de la clase Facturacion
#include <iostream> // Inclusión de la biblioteca estándar para entrada/salida
using namespace std;

// Variables externas definidas en otro lugar del programa
extern usuarios usuarioRegistrado; // Objeto global para el usuario registrado
extern bitacora auditoria;         // Objeto global para el registro de auditorías

// Método principal que gestiona el menú de facturación
void Facturacion::gestionFacturacion() {
    int opcion; // Variable para almacenar la opción seleccionada por el usuario
    do {
        system("cls"); // Limpia la pantalla
        cout << "\t\t========================================" << endl;
        cout << "\t\t| FACTURACION Y ANALISIS - LOGISTICA    |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Generar factura" << endl;
        cout << "\t\t 2. Consultar estado de pago" << endl;
        cout << "\t\t 3. Registrar pago" << endl;
        cout << "\t\t 4. Reportes financieros" << endl;
        cout << "\t\t 5. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";
        cin >> opcion; // Captura la opción del usuario

        // Evaluación de la opción usando switch
        switch(opcion) {
            case 1: generarFactura(); break;              // Opción 1: Generar factura
            case 2: consultarEstadoPago(); break;         // Opción 2: Consultar estado de pago
            case 3: registrarPago(); break;               // Opción 3: Registrar pago
            case 4: verReportesFinancieros(); break;      // Opción 4: Ver reportes financieros
            case 5: break;                                // Opción 5: Salir del menú
            default:
                cout << "\n\t\tOpcion invalida!"; // Mensaje de error para opción no válida
                cin.get();
        }
    } while(opcion != 5); // El menú se repite hasta que el usuario elija salir
}

// Función que simula la generación de una factura
void Facturacion::generarFactura() {
    cout << "\n\t\t[Generando factura...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "400", "FACT"); // Registro en la bitácora
    system("pause"); // Pausa para visualizar el mensaje
}

// Función que simula la consulta del estado de pago
void Facturacion::consultarEstadoPago() {
    cout << "\n\t\t[Consultando estado de pago...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "400", "CONSPAG"); // Registro en la bitácora
    system("pause");
}

// Función que simula el registro de un pago
void Facturacion::registrarPago() {
    cout << "\n\t\t[Registrando pago...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "400", "REGPAG"); // Registro en la bitácora
    system("pause");
}

// Función que simula la visualización de reportes financieros
void Facturacion::verReportesFinancieros() {
    cout << "\n\t\t[Mostrando reportes financieros...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "400", "REPFIN"); // Registro en la bitácora
    system("pause");
}

