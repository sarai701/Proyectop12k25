#include "producto.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

string generarCodigoProducto() {
    static int counter = 0;
    stringstream ss;
    ss << "PROD-" << setw(4) << setfill('0') << ++counter;
    return ss.str();
}

void guardarProductos(const vector<Producto>& productos) {
    ofstream archivo("productos.txt");
    if (archivo.is_open()) {
        for (const auto& producto : productos) {
            archivo << producto.codigo << "|"
                    << producto.nombre << "|"
                    << producto.descripcion << "|"
                    << producto.precio << "|"
                    << producto.stock << "\n";
        }
        archivo.close();
    }
}

vector<Producto> cargarProductos() {
    vector<Producto> productos;
    ifstream archivo("productos.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Producto producto;
        string token;

        getline(ss, producto.codigo, '|');
        getline(ss, producto.nombre, '|');
        getline(ss, producto.descripcion, '|');

        getline(ss, token, '|');
        producto.precio = stod(token);

        getline(ss, token);
        producto.stock = stoi(token);

        productos.push_back(producto);
    }

    return productos;
}

void ingresarProducto() {
    Producto nuevo;
    nuevo.codigo = generarCodigoProducto();

    cout << "\n--- REGISTRAR PRODUCTO ---\n";
    cout << "Código: " << nuevo.codigo << endl;
    cout << "Nombre: ";
    getline(cin, nuevo.nombre);
    cout << "Descripción: ";
    getline(cin, nuevo.descripcion);
    cout << "Precio: ";
    cin >> nuevo.precio;
    cout << "Stock: ";
    cin >> nuevo.stock;
    cin.ignore();

    vector<Producto> productos = cargarProductos();
    productos.push_back(nuevo);
    guardarProductos(productos);

    cout << "✔ Producto registrado\n";
}

void consultarProductos() {
    vector<Producto> productos = cargarProductos();

    cout << "\n--- LISTA DE PRODUCTOS ---\n";
    if (productos.empty()) {
        cout << "No hay productos registrados\n";
        return;
    }

    for (const auto& producto : productos) {
        cout << "Código: " << producto.codigo << "\n"
             << "Nombre: " << producto.nombre << "\n"
             << "Descripción: " << producto.descripcion << "\n"
             << "Precio: $" << fixed << setprecision(2) << producto.precio << "\n"
             << "Stock: " << producto.stock << "\n\n";
    }
}

void modificarProducto() {
    consultarProductos();
    vector<Producto> productos = cargarProductos();

    if (productos.empty()) return;

    string codigo;
    cout << "Ingrese código del producto a modificar: ";
    getline(cin, codigo);

    auto it = find_if(productos.begin(), productos.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it == productos.end()) {
        cerr << "❌ Producto no encontrado\n";
        return;
    }

    cout << "Nuevo nombre [" << it->nombre << "]: ";
    getline(cin, it->nombre);
    cout << "Nueva descripción [" << it->descripcion << "]: ";
    getline(cin, it->descripcion);
    cout << "Nuevo precio [" << it->precio << "]: ";
    cin >> it->precio;
    cout << "Nuevo stock [" << it->stock << "]: ";
    cin >> it->stock;
    cin.ignore();

    guardarProductos(productos);
    cout << "✔ Producto actualizado\n";
}

void borrarProducto() {
    consultarProductos();
    vector<Producto> productos = cargarProductos();

    if (productos.empty()) return;

    string codigo;
    cout << "Ingrese código del producto a eliminar: ";
    getline(cin, codigo);

    auto it = remove_if(productos.begin(), productos.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it == productos.end()) {
        cerr << "❌ Producto no encontrado\n";
        return;
    }

    productos.erase(it, productos.end());
    guardarProductos(productos);
    cout << "✔ Producto eliminado\n";
}
