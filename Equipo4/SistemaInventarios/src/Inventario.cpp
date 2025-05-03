//Modificacion por Ferdynand Monroy abril 2025
#include "Inventario.h"
#include <iostream>

using namespace std;

Inventario::Inventario() {}

void Inventario::agregarProducto(int codigo, string nombre, float precio, int stock, string tipo) {
    productos.push_back(Producto(codigo, nombre, precio, stock, tipo));
}

void Inventario::mostrarInventarioGeneral() {
    cout << "\n--- Inventario General ---\n";
    cout << "Codigo\tNombre\tPrecio\tStock\tTipo\n";
    for (const auto& p : productos) {
        cout << p.codigo << "\t" << p.nombre << "\t" << p.precio << "\t" << p.stock << "\t" << p.tipo << endl;
    }
}

Producto* Inventario::buscarProducto(int codigo) {
    for (auto& p : productos) {
        if (p.codigo == codigo) {
            return &p;
        }
    }
    return nullptr;
}

void Inventario::mostrarInventarioPorTipo(string tipo) {
    cout << "\n--- Inventario de " << tipo << " ---\n";
    cout << "Codigo\tNombre\tPrecio\tStock\n";
    for (const auto& p : productos) {
        if (p.tipo == tipo) {
            cout << p.codigo << "\t" << p.nombre << "\t" << p.precio << "\t" << p.stock << endl;
        }
    }
}
void Inventario::ventas(int codigo, int stock) {
    Producto* p = buscarProducto(codigo);
    if (p != nullptr) {
        if (p->stock >= stock) {
            p->stock -= stock;
            cout << "Venta realizada: " << stock << " unidades de " << p->nombre << " vendidas." << endl;
        } else {
            cout << "No hay suficiente stock para realizar la venta." << endl;
        }
    } else {
        cout << "Producto no encontrado." << endl;
    }
}

Inventario::~Inventario() {}
