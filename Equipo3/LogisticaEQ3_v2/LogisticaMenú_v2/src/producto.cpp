//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025
// modificado por // 9959-24-11603 GE
#include "Producto.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// Constructor
Producto::Producto() : precio(0.0), stock(0), stockMinimo(0) {}

// Getters
string Producto::getId() const { return id; }
string Producto::getCodigo() const { return codigo; }
string Producto::getNombre() const { return nombre; }
string Producto::getDescripcion() const { return descripcion; }
double Producto::getPrecio() const { return precio; }
int Producto::getStock() const { return stock; }
int Producto::getStockMinimo() const { return stockMinimo; }

// Setters
void Producto::setId(const string& id) { this->id = id; }
void Producto::setCodigo(const string& codigo) { this->codigo = codigo; }
void Producto::setNombre(const string& nombre) { this->nombre = nombre; }
void Producto::setDescripcion(const string& descripcion) { this->descripcion = descripcion; }
void Producto::setPrecio(double precio) { this->precio = precio; }
void Producto::setStock(int stock) { this->stock = stock; }
void Producto::setStockMinimo(int stockMinimo) { this->stockMinimo = stockMinimo; }

// Implementación de métodos estáticos
const int CODIGO_INICIAL = 3209;
const int CODIGO_FINAL = 3259;

string Producto::generarCodigoUnico(const vector<Producto>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigoDisponible(lista, codigo)) {
            return codigo;
        }
    }
    return "";
}

bool Producto::esCodigoValido(const string& codigo) {
    try {
        int num = stoi(codigo);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

bool Producto::codigoDisponible(const vector<Producto>& lista, const string& codigo) {
    return none_of(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });
}

void Producto::agregar(vector<Producto>& lista, const string& usuario) {
    Producto nuevo;
    nuevo.codigo = generarCodigoUnico(lista);

    if (nuevo.codigo.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles\n";
        return;
    }

    cout << "\n\t\t=== AGREGAR PRODUCTO (Código: " << nuevo.codigo << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tNombre del producto: ";
    getline(cin, nuevo.nombre);

    cout << "\t\tPrecio: ";
    while (!(cin >> nuevo.precio)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese precio: ";
    }

    cout << "\t\tStock inicial: ";
    while (!(cin >> nuevo.stock)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock: ";
    }

    lista.push_back(nuevo);
    guardarEnArchivoBin(lista);
    bitacora::registrar(usuario, "PRODUCTOS", "Agregado: " + nuevo.codigo);
    cout << "\n\t\tProducto registrado!\n";
}

void Producto::mostrar(const vector<Producto>& lista) {
    system("cls");
    cout << "\n\t\t=== INVENTARIO ===\n";
    cout << "\t\t" << left << setw(10) << "Código" << setw(30) << "Nombre"
         << setw(15) << "Precio" << setw(10) << "Stock" << "\n";
    cout << "\t\t" << string(65, '-') << "\n";

    for (const auto& producto : lista) {
        cout << "\t\t" << left << setw(10) << producto.codigo << setw(30) << producto.nombre
             << "$" << setw(14) << fixed << setprecision(2) << producto.precio
             << setw(10) << producto.stock << "\n";
    }
}

void Producto::modificar(vector<Producto>& lista, const string& usuario, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        cout << "\n\t\t=== MODIFICAR PRODUCTO (Código: " << codigo << ") ===\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        cout << "\t\tNuevo precio (" << it->precio << "): ";
        while (!(cin >> it->precio)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese precio: ";
        }

        cout << "\t\tNuevo stock (" << it->stock << "): ";
        while (!(cin >> it->stock)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese stock: ";
        }

        guardarEnArchivoBin(lista);
        bitacora::registrar(usuario, "PRODUCTOS", "Modificado: " + codigo);
        cout << "\n\t\tProducto modificado!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
}

void Producto::eliminar(vector<Producto>& lista, const string& usuario, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivoBin(lista);
        bitacora::registrar(usuario, "PRODUCTOS", "Eliminado: " + codigo);
        cout << "\n\t\tProducto eliminado!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
}

void Producto::guardarEnArchivoBin(const vector<Producto>& productos) {
    ofstream archivo("productos.bin", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir archivo para escritura\n";
        return;
    }

    size_t size = productos.size();
    archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const auto& p : productos) {
        size_t len = p.codigo.size();
        archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
        archivo.write(p.codigo.c_str(), len);

        len = p.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
        archivo.write(p.nombre.c_str(), len);

        archivo.write(reinterpret_cast<const char*>(&p.precio), sizeof(p.precio));
        archivo.write(reinterpret_cast<const char*>(&p.stock), sizeof(p.stock));
    }
}

void Producto::cargarDesdeArchivoBin(vector<Producto>& productos) {
    ifstream archivo("productos.bin", ios::binary);
    if (!archivo) return;

    size_t size;
    archivo.read(reinterpret_cast<char*>(&size), sizeof(size));

    for (size_t i = 0; i < size; ++i) {
        Producto p;

        size_t len;
        archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
        p.codigo.resize(len);
        archivo.read(&p.codigo[0], len);

        archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
        p.nombre.resize(len);
        archivo.read(&p.nombre[0], len);

        archivo.read(reinterpret_cast<char*>(&p.precio), sizeof(p.precio));
        archivo.read(reinterpret_cast<char*>(&p.stock), sizeof(p.stock));

        productos.push_back(p);
    }
}
