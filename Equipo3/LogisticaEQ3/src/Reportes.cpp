// 9959-24-11603 GE
// Implementación de la clase Reportes con mensajes simulados para cada función.

#include "reportes.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Variables externas
extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// Simula una pausa con "procesando..."
void mostrarProcesando(const string& mensaje) {
    cout << "\n\t\t" << mensaje;
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\n";
}

void Reportes::generarReportes() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| REPORTES Y ANALISIS - LOGISTICA      |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Informe de ventas" << endl;
        cout << "\t\t 2. Análisis de tiempos de entrega" << endl;
        cout << "\t\t 3. Reporte de inventarios" << endl;
        cout << "\t\t 4. Evaluación de proveedores" << endl;
        cout << "\t\t 5. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";
        cin >> opcion;

        switch(opcion) {
            case 1: informeVentas(); break;
            case 2: analisisTiemposEntrega(); break;
            case 3: reporteInventarios(); break;
            case 4: evaluacionProveedores(); break;
            case 5: break;
            default:
                cout << "\n\t\tOpcion invalida!";
                cin.ignore();
                cin.get();
        }
    } while(opcion != 5);
}

void Reportes::informeVentas() {
    mostrarProcesando("Generando informe de ventas");
    cout << "\t\tVentas totales del mes: Q125,300.00\n";
    cout << "\t\tClientes atendidos: 230\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "500", "REPVENT");
    system("pause");
}

void Reportes::analisisTiemposEntrega() {
    mostrarProcesando("Analizando tiempos de entrega");
    cout << "\t\tTiempo promedio de entrega: 2.3 días\n";
    cout << "\t\tRetrasos detectados: 5\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "500", "ANALTIME");
    system("pause");
}

void Reportes::reporteInventarios() {
    mostrarProcesando("Generando reporte de inventario");
    cout << "\t\tProductos en stock: 750\n";
    cout << "\t\tProductos con bajo inventario: 12\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "500", "REPINV");
    system("pause");
}

void Reportes::evaluacionProveedores() {
    mostrarProcesando("Evaluando proveedores");
    cout << "\t\tProveedor A: Entregas a tiempo 98%\n";
    cout << "\t\tProveedor B: Entregas a tiempo 75% - Revisión recomendada\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "500", "EVAPROV");
    system("pause");
}
