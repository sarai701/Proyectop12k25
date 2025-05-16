//Modificacion por Ferdynand Monroy abril 2025
//Modificación para guardado y mejoras de interfaz por Anthony Suc, 2 de mayo 2025
//Implementacion de archivos Kevin Lopez, 2 de mayo de 2025
#include "Inventario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Inventario::Inventario() {
    system("cls");
    cout << "Cargando inventario..." << endl;
    cargarDesdeArchivo();
}

void Inventario::agregarProducto(int codigo, string nombre, float precio, int stock, string tipo) {
    system("cls");
    cout << "=== AGREGAR NUEVO PRODUCTO ===" << endl;

    if (buscarProducto(codigo) != nullptr) {
        cerr << "\nError: El código " << codigo << " ya existe." << endl;
        system("pause");
        return;
    }

    productos.push_back(Producto(codigo, nombre, precio, stock, tipo));
    guardarEnArchivo();

    cout << "\nProducto agregado exitosamente!" << endl;
    system("pause");
}

void Inventario::mostrarInventarioGeneral() {
    system("cls");
    cout << "\n--- Kardex ---\n";
    cout << "Codigo\tNombre\tPrecio\tStock\tTipo\n";
    for (const auto& p : productos) {
        cout << p.codigo << "\t" << p.nombre << "\t" << p.precio << "\t" << p.stock << "\t" << p.tipo << endl;
    }
    cout << "\n";
    system("pause");
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
    system("cls");
    cout << "\n--- Informe de " << tipo << " ---\n";
    cout << "Codigo\tNombre\tPrecio\tStock\n";
    for (const auto& p : productos) {
        if (p.tipo == tipo) {
            cout << p.codigo << "\t" << p.nombre << "\t" << p.precio << "\t" << p.stock << endl;
        }
    }
    cout << "\n";
    system("pause");
}

void Inventario::ventas(int codigo, int stock) {
    Producto* p = buscarProducto(codigo);
    if (p != nullptr) {
        if (p->stock >= stock) {
            p->stock -= stock;
            cout << "Venta realizada: " << stock << " unidades de " << p->nombre << " vendidas." << endl;
            guardarEnArchivo();
        } else {
            cout << "No hay suficiente stock para realizar la venta." << endl;
        }
    } else {
        cout << "Producto no encontrado." << endl;
    }
}

void Inventario::guardarEnArchivo() const {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir archivo para escritura." << endl;
        return;
    }

    for (const auto& p : productos) {
        archivo << p.codigo << "," << p.nombre << ","
                << p.precio << "," << p.stock << ","
                << p.tipo << "\n";
    }
}

void Inventario::cargarDesdeArchivo() {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se encontró archivo. Se creará uno nuevo." << endl;
        return;
    }

    productos.clear();
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string item;
        string datos[5];
        int i = 0;

        while (getline(ss, item, ',') && i < 5) {
            datos[i++] = item;
        }

        if (i == 5) {
            try {
                productos.emplace_back(
                    stoi(datos[0]),
                    datos[1],
                    stof(datos[2]),
                    stoi(datos[3]),
                    datos[4]
                );
            } catch (...) {
                cerr << "Error en línea: " << linea << endl;
            }
        }
    }
}

bool Inventario::eliminarProducto(int codigo) {
    system("cls");
    cout << "=== ELIMINAR PRODUCTO ===" << endl;

    auto it = remove_if(productos.begin(), productos.end(),
        [codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != productos.end()) {
        productos.erase(it, productos.end());
        guardarEnArchivo();
        cout << "\nProducto eliminado exitosamente!" << endl;
        system("pause");
        return true;
    }

    cout << "\nError: No se encontró el producto con código " << codigo << endl;
    system("pause");
    return false;
}

Inventario::~Inventario() {
    guardarEnArchivo();
}
