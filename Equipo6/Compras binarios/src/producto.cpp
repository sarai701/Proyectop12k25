#include "producto.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

// Inicializar contador estático
int Producto::contadorCodigo = 0;

// Constructores
Producto::Producto() : codigo(""), nombre(""), descripcion(""), precio(0.0), stock(0) {}

Producto::Producto(const string& codigo, const string& nombre,
                   const string& descripcion, double precio, int stock)
    : codigo(codigo), nombre(nombre), descripcion(descripcion), precio(precio), stock(stock) {}

// Getters
string Producto::getCodigo() const { return codigo; }
string Producto::getNombre() const { return nombre; }
string Producto::getDescripcion() const { return descripcion; }
double Producto::getPrecio() const { return precio; }
int Producto::getStock() const { return stock; }

// Setters
void Producto::setCodigo(const string& c) { codigo = c; }
void Producto::setNombre(const string& n) { nombre = n; }
void Producto::setDescripcion(const string& d) { descripcion = d; }
void Producto::setPrecio(double p) { precio = p; }
void Producto::setStock(int s) { stock = s; }

// Generar código único
string Producto::generarCodigoProducto() {
    ++contadorCodigo;
    stringstream ss;
    ss << "PROD-" << setw(4) << setfill('0') << contadorCodigo;
    return ss.str();
}

// Ajustar contador según los productos existentes
void Producto::ajustarContador(const vector<Producto>& productos) {
    int maxContador = 0;
    for (const auto& p : productos) {
        const string& c = p.getCodigo();
        if (c.size() == 9 && c.substr(0, 5) == "PROD-") {
            try {
                int num = stoi(c.substr(5));
                if (num > maxContador)
                    maxContador = num;
            } catch (...) {}
        }
    }
    contadorCodigo = maxContador;
}

// Guardar productos en archivo
void Producto::guardarProductos(const vector<Producto>& productos) {
    ofstream archivo("productos.txt");
    if (archivo.is_open()) {
        for (const auto& p : productos) {
            archivo << p.codigo << "|"
                    << p.nombre << "|"
                    << p.descripcion << "|"
                    << p.precio << "|"
                    << p.stock << "\n";
        }
        archivo.close();
    } else {
        cerr << "❌ Error al abrir archivo para guardar productos.\n";
    }
}

// Cargar productos desde archivo
vector<Producto> Producto::cargarProductos() {
    vector<Producto> productos;
    ifstream archivo("productos.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string codigo, nombre, descripcion, token;
        double precio = 0;
        int stock = 0;

        getline(ss, codigo, '|');
        getline(ss, nombre, '|');
        getline(ss, descripcion, '|');

        try {
            getline(ss, token, '|');
            precio = stod(token);
            getline(ss, token);
            stock = stoi(token);
        } catch (...) {
            cerr << "❌ Error al cargar producto. Línea: " << linea << "\n";
            continue;
        }

        productos.emplace_back(codigo, nombre, descripcion, precio, stock);
    }

    ajustarContador(productos);
    return productos;
}

// Ingresar nuevo producto
void Producto::ingresarProducto() {
    vector<Producto> productos = cargarProductos();
    Producto nuevo;

    nuevo.setCodigo(generarCodigoProducto());

    cout << "\n--- REGISTRAR PRODUCTO ---\n";
    cout << "Código: " << nuevo.getCodigo() << endl;

    cout << "Nombre: ";
    getline(cin, nuevo.nombre);

    cout << "Descripción: ";
    getline(cin, nuevo.descripcion);

    cout << "Precio: ";
    while (!(cin >> nuevo.precio) || nuevo.precio < 0) {
        cout << "❌ Ingrese un precio válido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Stock: ";
    while (!(cin >> nuevo.stock) || nuevo.stock < 0) {
        cout << "❌ Ingrese un stock válido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore();
    productos.push_back(nuevo);
    guardarProductos(productos);
    cout << "✔ Producto registrado correctamente.\n";
}

// Consultar productos
void Producto::consultarProductos() {
    vector<Producto> productos = cargarProductos();

    cout << "\n--- LISTA DE PRODUCTOS ---\n";
    if (productos.empty()) {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (const auto& p : productos) {
        cout << "Código: " << p.codigo << "\n"
             << "Nombre: " << p.nombre << "\n"
             << "Descripción: " << p.descripcion << "\n"
             << "Precio: $" << fixed << setprecision(2) << p.precio << "\n"
             << "Stock: " << p.stock << "\n\n";
    }
}

// Modificar producto
void Producto::modificarProducto() {
    vector<Producto> productos = cargarProductos();

    if (productos.empty()) {
        cout << "No hay productos para modificar.\n";
        return;
    }

    string codigo;
    cout << "Ingrese código del producto a modificar: ";
    getline(cin, codigo);

    auto it = find_if(productos.begin(), productos.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it == productos.end()) {
        cout << "❌ Producto no encontrado.\n";
        return;
    }

    cout << "Nuevo nombre [" << it->nombre << "]: ";
    string nuevoNombre;
    getline(cin, nuevoNombre);
    if (!nuevoNombre.empty()) it->nombre = nuevoNombre;

    cout << "Nueva descripción [" << it->descripcion << "]: ";
    string nuevaDesc;
    getline(cin, nuevaDesc);
    if (!nuevaDesc.empty()) it->descripcion = nuevaDesc;

    cout << "Nuevo precio [" << it->precio << "]: ";
    while (!(cin >> it->precio) || it->precio < 0) {
        cout << "❌ Ingrese un precio válido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Nuevo stock [" << it->stock << "]: ";
    while (!(cin >> it->stock) || it->stock < 0) {
        cout << "❌ Ingrese un stock válido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore();
    guardarProductos(productos);
    cout << "✔ Producto actualizado correctamente.\n";
}

// Borrar producto
void Producto::borrarProducto() {
    vector<Producto> productos = cargarProductos();

    if (productos.empty()) {
        cout << "No hay productos para eliminar.\n";
        return;
    }

    string codigo;
    cout << "Ingrese código del producto a eliminar: ";
    getline(cin, codigo);

    auto it = remove_if(productos.begin(), productos.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it == productos.end()) {
        cout << "❌ Producto no encontrado.\n";
        return;
    }

    productos.erase(it, productos.end());
    guardarProductos(productos);
    cout << "✔ Producto eliminado correctamente.\n";
}
