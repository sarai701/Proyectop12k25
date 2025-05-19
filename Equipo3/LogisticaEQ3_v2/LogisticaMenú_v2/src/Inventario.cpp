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
            case 2: registrarMercancia(); break;
            case 3: ajustarInventario(); break;
            case 4: reporteExistencias(); break;
            case 5: break;
            default: cout << "\n\t\tOpcion invalida!"; cin.get();
        }
    } while(opcion != 5);
}

// Registrar nueva mercancía
void Inventario::registrarMercancia() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRAR MERCANCIA NUEVA            |" << endl;
    cout << "\t\t========================================" << endl;

    ofstream archivo("inventario.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de inventario!" << endl;
        return;
    }

    string id, nombre;
    int cantidad;

    cout << "\t\tID del producto: ";
    cin >> id;
    cout << "\t\tNombre del producto: ";
    cin >> nombre;
    cout << "\t\tCantidad: ";
    cin >> cantidad;

    archivo << id << " " << nombre << " " << cantidad << endl;
    archivo.close();

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REG-MERC");
    cout << "\n\t\tMercancia registrada correctamente.";
    system("pause");
}

void Inventario::consultarStock() {
    cout << "\n\t\t[Consultando stock...]" << endl;
    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "STOCK");
    system("pause");
}
void Inventario::ajustarInventario() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| AJUSTAR INVENTARIO EXISTENTE         |" << endl;
    cout << "\t\t========================================" << endl;

    string idBuscado;
    cout << "\t\tIngrese ID del producto a ajustar: ";
    cin >> idBuscado;

    ifstream archivoIn("inventario.txt");
    ofstream archivoTemp("temp.txt");
    if (!archivoIn.is_open() || !archivoTemp.is_open()) {
        cerr << "\n\t\tError al abrir archivos!" << endl;
        return;
    }

    string id, nombre;
    int cantidad, nuevaCantidad;
    bool encontrado = false;

    while (archivoIn >> id >> nombre >> cantidad) {
        if (id == idBuscado) {
            encontrado = true;
            cout << "\t\tCantidad actual: " << cantidad << endl;
            cout << "\t\tNueva cantidad: ";
            cin >> nuevaCantidad;
            archivoTemp << id << " " << nombre << " " << nuevaCantidad << endl;
        } else {
            archivoTemp << id << " " << nombre << " " << cantidad << endl;
        }
    }

    archivoIn.close();
    archivoTemp.close();

    remove("inventario.txt");
    rename("temp.txt", "inventario.txt");

    if (encontrado) {
        auditoria.insertar(usuarioRegistrado.getNombre(), "200", "AJUSTE-MERC");
        cout << "\n\t\tInventario ajustado correctamente." << endl;
    } else {
        cout << "\n\t\tProducto no encontrado." << endl;
    }

    system("pause");
}

void Inventario::reporteExistencias() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REPORTE DE EXISTENCIAS               |" << endl;
    cout << "\t\t========================================" << endl;

    ifstream archivo("inventario.txt");
    if (!archivo.is_open()) {
        cout << "\t\tNo hay productos registrados." << endl;
        system("pause");
        return;
    }

    string id, nombre;
    int cantidad;

    // Imprimir encabezados
    cout << "\t\t" << left << setw(10) << "ID"
         << setw(20) << "NOMBRE"
         << setw(10) << "CANTIDAD" << endl;
    cout << "\t\t" << string(40, '-') << endl; // Línea divisoria

    // Imprimir los datos del inventario
    while (archivo >> id >> nombre >> cantidad) {
        cout << "\t\t" << setw(10) << id
             << setw(20) << nombre
             << setw(10) << cantidad << endl;
    }
    archivo.close();

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REPORTE");
    system("pause");
}
