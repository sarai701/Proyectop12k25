//clase para mantenimiento Factura Dulce Reyes
#include "factura.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void registrarFactura() {
    Factura f;
    ofstream archivo("facturas.txt", ios::app);

    cout << "\n--- Registrar Factura ---\n";
    cout << "Código: "; cin >> f.codigo;
    cout << "Cliente: "; cin.ignore(); getline(cin, f.cliente);
    cout << "Fecha: "; getline(cin, f.fecha);
    cout << "Monto: "; cin >> f.monto;

    archivo << f.codigo << "," << f.cliente << "," << f.fecha << "," << f.monto << endl;
    archivo.close();

    cout << "Factura registrada exitosamente.\n";
    system("pause");
}

void modificarFactura() {
    string codigoBuscado;
    cout << "\n--- Modificar Factura ---\n";
    cout << "Ingrese el código de la factura a modificar: ";
    cin >> codigoBuscado;

    ifstream archivo("facturas.txt");
    ofstream temp("temp.txt");
    Factura f;
    string linea, montoStr;
    bool encontrada = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, f.codigo, ',');
        getline(ss, f.cliente, ',');
        getline(ss, f.fecha, ',');
        getline(ss, montoStr, ',');
        f.monto = stof(montoStr);

        if (f.codigo == codigoBuscado) {
            cout << "Factura encontrada. Ingrese nuevos datos:\n";
            cout << "Nuevo Cliente: "; cin.ignore(); getline(cin, f.cliente);
            cout << "Nueva Fecha: "; getline(cin, f.fecha);
            cout << "Nuevo Monto: "; cin >> f.monto;
            encontrada = true;
        }

        temp << f.codigo << "," << f.cliente << "," << f.fecha << "," << f.monto << endl;
    }

    archivo.close();
    temp.close();
    remove("facturas.txt");
    rename("temp.txt", "facturas.txt");

    if (encontrada)
        cout << "Factura modificada con éxito.\n";
    else
        cout << "Factura no encontrada.\n";

    system("pause");
}

void eliminarFactura() {
    string codigoBuscado;
    cout << "\n--- Eliminar Factura ---\n";
    cout << "Ingrese el código de la factura a eliminar: ";
    cin >> codigoBuscado;

    ifstream archivo("facturas.txt");
    ofstream temp("temp.txt");
    Factura f;
    string linea, montoStr;
    bool eliminada = false;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, f.codigo, ',');
        getline(ss, f.cliente, ',');
        getline(ss, f.fecha, ',');
        getline(ss, montoStr, ',');
        f.monto = stof(montoStr);

        if (f.codigo != codigoBuscado) {
            temp << f.codigo << "," << f.cliente << "," << f.fecha << "," << f.monto << endl;
        } else {
            eliminada = true;
        }
    }

    archivo.close();
    temp.close();
    remove("facturas.txt");
    rename("temp.txt", "facturas.txt");

    if (eliminada)
        cout << "Factura eliminada exitosamente.\n";
    else
        cout << "Factura no encontrada.\n";

    system("pause");
}

void verFacturas() {
    cout << "\n--- Lista de Facturas ---\n";
    ifstream archivo("facturas.txt");
    Factura f;
    string linea, montoStr;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, f.codigo, ',');
        getline(ss, f.cliente, ',');
        getline(ss, f.fecha, ',');
        getline(ss, montoStr, ',');
        f.monto = stof(montoStr);

        cout << "Código: " << f.codigo
             << ", Cliente: " << f.cliente
             << ", Fecha: " << f.fecha
             << ", Monto: " << f.monto << endl;
    }

    archivo.close();
    system("pause");
}
