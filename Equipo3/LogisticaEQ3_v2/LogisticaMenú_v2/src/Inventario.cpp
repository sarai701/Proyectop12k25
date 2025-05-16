//Karina Alejandra Arriaza Ortiz
#include "inventario.h"
#include <iostream>
using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

void Inventario::controlInventario() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| CONTROL DE INVENTARIO - LOGISTICA     |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Consultar stock" << endl;
        cout << "\t\t 2. Registrar mercancia" << endl;
        cout << "\t\t 3. Ajustar inventario" << endl;
        cout << "\t\t 4. Reporte de existencias" << endl;
        cout << "\t\t 5. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";
        cin >> opcion;

        switch(opcion) {
            case 1: consultarStock(); break;
            //case 2: registrarMercancia(); break;
            //case 3: ajustarInventario(); break;
            //case 4: reporteExistencias(); break;
            case 5: break;
            default: cout << "\n\t\tOpcion invalida!"; cin.get();
        }
    } while(opcion != 5);
}

void Inventario::consultarStock() {
    cout << "\n\t\t[Consultando stock...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "STOCK");
    system("pause");
}
// Implementar dem�s funciones...
