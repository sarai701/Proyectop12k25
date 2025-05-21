#include "Producto.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include "bitacora.h"

using namespace std;

// Rango de códigos válidos para productos (3209-3259)
const int CODIGO_INICIAL = 3209;
const int CODIGO_FINAL = 3259;

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

// Genera un código único que no haya sido usado, dentro del rango permitido
string Producto::generarCodigoUnico(const vector<Producto>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigoDisponible(lista, codigo)) {
            return codigo;
        }
    }
    return ""; // Si no hay disponibles, retorna cadena vacía
}

// Verifica si un código aún no ha sido asignado a ningún producto
bool Producto::codigoDisponible(const vector<Producto>& lista, const string& codigo) {
    return none_of(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });
}

// Comprueba si un código está dentro del rango numérico permitido
bool Producto::esCodigoValido(const string& codigo) {
    try {
        int num = stoi(codigo);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

// Agrega un nuevo producto a la lista de inventario
void Producto::agregar(vector<Producto>& lista, const string& usuarioActual) {
    Producto nuevo;
    nuevo.codigo = generarCodigoUnico(lista);

    if (nuevo.codigo.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR PRODUCTO (Código: " << nuevo.codigo << ") ===\n";
    cout << "\t\t(0 para cancelar)\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tNombre del producto: ";
    string nombre;
    getline(cin, nombre);

    if (nombre == "0") {
        cout << "\t\tOperación cancelada.\n";
        system("pause");
        return;
    }
    nuevo.setNombre(nombre);

    cout << "\t\tDescripción: ";
    string descripcion;
    getline(cin, descripcion);
    nuevo.setDescripcion(descripcion);

    cout << "\t\tPrecio: ";
    double precio;
    while (!(cin >> precio) || precio < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese precio (0 para cancelar): ";
        string input;
        getline(cin, input);
        if (input == "0") {
            cout << "\t\tOperación cancelada.\n";
            system("pause");
            return;
        }
    }
    nuevo.setPrecio(precio);

    cout << "\t\tStock inicial: ";
    int stock;
    while (!(cin >> stock)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock (0 para cancelar): ";
        string input;
        getline(cin, input);
        if (input == "0") {
            cout << "\t\tOperación cancelada.\n";
            system("pause");
            return;
        }
    }
    nuevo.setStock(stock);

    cout << "\t\tStock mínimo: ";
    int stockMin;
    while (!(cin >> stockMin)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock mínimo (0 para cancelar): ";
        string input;
        getline(cin, input);
        if (input == "0") {
            cout << "\t\tOperación cancelada.\n";
            system("pause");
            return;
        }
    }
    nuevo.setStockMinimo(stockMin);

    lista.push_back(nuevo);
    guardarEnArchivoBin(lista);
    bitacora::registrar(usuarioActual, "PRODUCTOS", "Agregado: " + nuevo.codigo);
    cout << "\n\t\tProducto registrado!\n";
    system("pause");
}

// Muestra todos los productos en una tabla formateada
void Producto::mostrar(const vector<Producto>& lista) {
    system("cls");
    cout << "\n\t\t=== INVENTARIO ===\n";
    cout << "\t\t" << left << setw(10) << "Código" << setw(25) << "Nombre"
         << setw(15) << "Precio" << setw(10) << "Stock" << setw(15) << "Stock Mín" << "\n";
    cout << "\t\t" << string(75, '-') << "\n";

    if (lista.empty()) {
        cout << "\t\tNo hay productos registrados.\n";
    } else {
        for (const auto& producto : lista) {
            cout << "\t\t" << left << setw(10) << producto.codigo
                 << setw(25) << producto.nombre.substr(0, 24)
                 << "$" << setw(14) << fixed << setprecision(2) << producto.precio
                 << setw(10) << producto.stock
                 << setw(15) << producto.stockMinimo << "\n";
        }
    }
    cout << "\n\t\tPresione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

// Modifica los datos de un producto existente
void Producto::modificar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        cout << "\n\t\t=== MODIFICAR PRODUCTO (Código: " << codigo << ") ===\n";
        cout << "\t\t(Deje en blanco para mantener el valor actual)\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Modificación del nombre
        cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        string nuevoNombre;
        getline(cin, nuevoNombre);
        if (!nuevoNombre.empty()) {
            it->setNombre(nuevoNombre);
        }

        // Modificación de la descripción
        cout << "\t\tNueva descripción (" << it->descripcion << "): ";
        string nuevaDesc;
        getline(cin, nuevaDesc);
        if (!nuevaDesc.empty()) {
            it->setDescripcion(nuevaDesc);
        }

        // Modificación del precio
        cout << "\t\tNuevo precio (" << it->precio << "): ";
        string precioStr;
        getline(cin, precioStr);
        if (!precioStr.empty()) {
            try {
                double nuevoPrecio = stod(precioStr);
                it->setPrecio(nuevoPrecio);
            } catch (...) {
                cout << "\t\tPrecio no válido. Se mantiene el actual.\n";
            }
        }

        // Modificación del stock
        cout << "\t\tNuevo stock (" << it->stock << "): ";
        string stockStr;
        getline(cin, stockStr);
        if (!stockStr.empty()) {
            try {
                int nuevoStock = stoi(stockStr);
                it->setStock(nuevoStock);
            } catch (...) {
                cout << "\t\tStock no válido. Se mantiene el actual.\n";
            }
        }

        // Modificación del stock mínimo
        cout << "\t\tNuevo stock mínimo (" << it->stockMinimo << "): ";
        string stockMinStr;
        getline(cin, stockMinStr);
        if (!stockMinStr.empty()) {
            try {
                int nuevoStockMin = stoi(stockMinStr);
                it->setStockMinimo(nuevoStockMin);
            } catch (...) {
                cout << "\t\tStock mínimo no válido. Se mantiene el actual.\n";
            }
        }

        guardarEnArchivoBin(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Modificado: " + codigo);
        cout << "\n\t\tProducto modificado exitosamente!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

// Elimina un producto de la lista por su código
void Producto::eliminar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        cout << "\n\t\t¿Está seguro que desea eliminar el producto " << it->nombre << "? (s/n): ";
        char confirmacion;
        cin >> confirmacion;

        if (tolower(confirmacion) == 's') {
            lista.erase(it);
            guardarEnArchivoBin(lista);
            bitacora::registrar(usuarioActual, "PRODUCTOS", "Eliminado: " + codigo);
            cout << "\n\t\tProducto eliminado exitosamente!\n";
        } else {
            cout << "\n\t\tOperación cancelada.\n";
        }
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

// Guarda la lista de productos en archivo binario
void Producto::guardarEnArchivoBin(const vector<Producto>& productos) {
    ofstream archivo("productos.bin", ios::binary | ios::out);

    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo abrir archivo de productos!\n";
        return;
    }

    try {
        // Escribir cantidad de productos
        size_t cantidad = productos.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        // Escribir cada producto
        for (const auto& producto : productos) {
            // Escribir ID
            size_t idSize = producto.id.size();
            archivo.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
            archivo.write(producto.id.c_str(), idSize);

            // Escribir código
            size_t codigoSize = producto.codigo.size();
            archivo.write(reinterpret_cast<const char*>(&codigoSize), sizeof(codigoSize));
            archivo.write(producto.codigo.c_str(), codigoSize);

            // Escribir nombre
            size_t nombreSize = producto.nombre.size();
            archivo.write(reinterpret_cast<const char*>(&nombreSize), sizeof(nombreSize));
            archivo.write(producto.nombre.c_str(), nombreSize);

            // Escribir descripción
            size_t descSize = producto.descripcion.size();
            archivo.write(reinterpret_cast<const char*>(&descSize), sizeof(descSize));
            archivo.write(producto.descripcion.c_str(), descSize);

            // Escribir precio, stock y stock mínimo
            archivo.write(reinterpret_cast<const char*>(&producto.precio), sizeof(producto.precio));
            archivo.write(reinterpret_cast<const char*>(&producto.stock), sizeof(producto.stock));
            archivo.write(reinterpret_cast<const char*>(&producto.stockMinimo), sizeof(producto.stockMinimo));
        }

        archivo.flush();
        if (!archivo) {
            throw runtime_error("Error al escribir en archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al guardar productos: " << e.what() << "\n";
        archivo.close();
        remove("productos.bin");
        return;
    }

    archivo.close();
}

// Carga la lista de productos desde archivo binario
void Producto::cargarDesdeArchivoBin(vector<Producto>& productos) {
    productos.clear();
    ifstream archivo("productos.bin", ios::binary | ios::in);

    if (!archivo) {
        return;
    }

    try {
        // Leer cantidad de productos
        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            Producto producto;

            // Leer ID
            size_t idSize;
            archivo.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
            producto.id.resize(idSize);
            archivo.read(&producto.id[0], idSize);

            // Leer código
            size_t codigoSize;
            archivo.read(reinterpret_cast<char*>(&codigoSize), sizeof(codigoSize));
            producto.codigo.resize(codigoSize);
            archivo.read(&producto.codigo[0], codigoSize);

            // Leer nombre
            size_t nombreSize;
            archivo.read(reinterpret_cast<char*>(&nombreSize), sizeof(nombreSize));
            producto.nombre.resize(nombreSize);
            archivo.read(&producto.nombre[0], nombreSize);

            // Leer descripción
            size_t descSize;
            archivo.read(reinterpret_cast<char*>(&descSize), sizeof(descSize));
            producto.descripcion.resize(descSize);
            archivo.read(&producto.descripcion[0], descSize);

            // Leer precio, stock y stock mínimo
            archivo.read(reinterpret_cast<char*>(&producto.precio), sizeof(producto.precio));
            archivo.read(reinterpret_cast<char*>(&producto.stock), sizeof(producto.stock));
            archivo.read(reinterpret_cast<char*>(&producto.stockMinimo), sizeof(producto.stockMinimo));

            productos.push_back(producto);
        }

        if (archivo.bad()) {
            throw runtime_error("Error de lectura del archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al cargar productos: " << e.what() << "\n";
        productos.clear();
    }

    archivo.close();
}
