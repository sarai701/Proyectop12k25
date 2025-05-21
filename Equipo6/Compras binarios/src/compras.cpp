#include "compras.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>

using namespace std;

void Compras::registrarCompra(vector<Producto>& listaCompras) {
    try {
        Producto p;
        string temp;

        cout << "Ingrese código del producto: ";
        getline(cin, temp);
        if (temp.empty()) throw invalid_argument("❌ El código no puede estar vacío.");
        p.setCodigo(temp);

        cout << "Ingrese nombre del producto: ";
        getline(cin, temp);
        if (temp.empty()) throw invalid_argument("❌ El nombre no puede estar vacío.");
        p.setNombre(temp);

        cout << "Ingrese descripción del producto: ";
        getline(cin, temp);
        if (temp.empty()) throw invalid_argument("❌ La descripción no puede estar vacía.");
        p.setDescripcion(temp);

        double precio;
        cout << "Ingrese precio: ";
        if (!(cin >> precio) || precio < 0) throw invalid_argument("❌ Precio inválido.");
        p.setPrecio(precio);

        int stock;
        cout << "Ingrese cantidad (stock): ";
        if (!(cin >> stock) || stock < 0) throw invalid_argument("❌ Stock inválido.");
        p.setStock(stock);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        listaCompras.push_back(p);
        cout << "✅ Compra registrada exitosamente.\n";
    }
    catch (const exception& e) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << e.what() << "\n";
    }
}

void Compras::mostrarHistorial(const vector<Producto>& listaCompras) {
    try {
        if (listaCompras.empty()) {
            throw runtime_error("⚠ No hay compras registradas.");
        }

        cout << "\n--- Historial de Compras ---\n";
        for (const auto& p : listaCompras) {
            cout << "Código: " << p.getCodigo() << "\n"
                 << "Nombre: " << p.getNombre() << "\n"
                 << "Descripción: " << p.getDescripcion() << "\n"
                 << "Precio: $" << fixed << setprecision(2) << p.getPrecio() << "\n"
                 << "Cantidad: " << p.getStock() << "\n\n";
        }
    }
    catch (const exception& e) {
        cerr << e.what() << "\n";
    }
}

void Compras::buscarPorProveedor(const vector<Producto>& listaCompras) {
    try {
        string proveedor;
        cout << "Ingrese nombre del proveedor para buscar: ";
        getline(cin, proveedor);
        if (proveedor.empty()) throw invalid_argument("❌ El nombre del proveedor no puede estar vacío.");

        bool encontrado = false;
        for (const auto& p : listaCompras) {
            if (p.getDescripcion() == proveedor) {
                cout << "Código: " << p.getCodigo() << "\n"
                     << "Nombre: " << p.getNombre() << "\n"
                     << "Precio: $" << fixed << setprecision(2) << p.getPrecio() << "\n"
                     << "Cantidad: " << p.getStock() << "\n\n";
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "⚠ No se encontraron compras de ese proveedor.\n";
        }
    }
    catch (const exception& e) {
        cerr << e.what() << "\n";
    }
}

double Compras::calcularTotalGastado(const vector<Producto>& listaCompras) {
    try {
        if (listaCompras.empty()) {
            throw runtime_error("⚠ No hay compras para calcular el total.");
        }

        double total = 0.0;
        for (const auto& p : listaCompras) {
            total += p.getPrecio() * p.getStock();
        }
        return total;
    }
    catch (const exception& e) {
        cerr << e.what() << "\n";
        return 0.0;
    }
}
