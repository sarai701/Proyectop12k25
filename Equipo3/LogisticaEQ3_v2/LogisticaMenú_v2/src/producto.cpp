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

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

using namespace std;

// Rango de códigos válidos para productos (3209-3259)
const int CODIGO_INICIAL = 3209;
const int CODIGO_FINAL = 3259;

// Genera un código único que no haya sido usado, dentro del rango permitido
string Producto::generarCodigoUnico(const vector<Producto>& lista) {
    // Recorre el rango buscando el primer código disponible
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigoDisponible(lista, codigo)) {
            return codigo; // Retorna el primer código libre
        }
    }
    return ""; // Si no hay disponibles, retorna cadena vacía
}

// Verifica si un código aún no ha sido asignado a ningún producto
bool Producto::codigoDisponible(const vector<Producto>& lista, const string& codigo) {
    // Retorna true si ningún producto tiene ese código
    return none_of(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });
}

// Comprueba si un código está dentro del rango numérico permitido
bool Producto::esCodigoValido(const string& codigo) {
    try {
        int num = stoi(codigo); // Intenta convertir a entero
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false; // Si ocurre una excepción, el código no es válido
    }
}

// Agrega un nuevo producto a la lista de inventario
void Producto::agregar(vector<Producto>& lista, const string& usuarioActual) {
    Producto nuevo;
    nuevo.codigo = generarCodigoUnico(lista); // Asigna código único

    // Verifica si hay códigos disponibles
    if (nuevo.codigo.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles\n";
        system("pause");
        return;
    }

    // Solicita los datos del nuevo producto
    cout << "\n\t\t=== AGREGAR PRODUCTO (Código: " << nuevo.codigo << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia buffer

    // Captura del nombre del producto
    cout << "\t\tNombre del producto: ";
    getline(cin, nuevo.nombre);

    // Captura y validación del precio
    cout << "\t\tPrecio: ";
    while (!(cin >> nuevo.precio)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese precio: ";
    }

    // Captura y validación del stock
    cout << "\t\tStock inicial: ";
    while (!(cin >> nuevo.stock)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock: ";
    }

    // Agrega a la lista y guarda en archivo
    lista.push_back(nuevo);
    guardarEnArchivoBin(lista);

    // Registra en bitácora
    bitacora::registrar(usuarioActual, "PRODUCTOS", "Agregado: " + nuevo.codigo);
    cout << "\n\t\tProducto registrado!\n";
    system("pause");
}

// Muestra todos los productos en una tabla formateada
void Producto::mostrar(const vector<Producto>& lista) {
    system("cls");
    cout << "\n\t\t=== INVENTARIO ===\n";
    cout << "\t\t" << left << setw(10) << "Código" << setw(30) << "Nombre"
         << setw(15) << "Precio" << setw(10) << "Stock" << "\n";
    cout << "\t\t" << string(65, '-') << "\n";

    // Muestra los datos de cada producto
    for (const auto& producto : lista) {
        cout << "\t\t" << left << setw(10) << producto.codigo << setw(30) << producto.nombre
             << "$" << setw(14) << fixed << setprecision(2) << producto.precio
             << setw(10) << producto.stock << "\n";
    }
    system("pause");
}

// Modifica los datos de un producto existente
void Producto::modificar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    // Busca el producto por su código
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    // Si se encuentra, permite modificarlo
    if (it != lista.end()) {
        cout << "\n\t\t=== MODIFICAR PRODUCTO (Código: " << codigo << ") ===\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia buffer

        // Modificación del nombre
        cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        getline(cin, it->nombre);

        // Modificación del precio
        cout << "\t\tNuevo precio (" << it->precio << "): ";
        while (!(cin >> it->precio)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor numérico para el precio: ";
        }

        // Modificación del stock
        cout << "\t\tNuevo stock (" << it->stock << "): ";
        while (!(cin >> it->stock)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un valor entero para el stock: ";
        }

        // Guarda cambios y registra modificación
        guardarEnArchivoBin(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto modificado - Código: " + codigo);
        cout << "\n\t\tProducto modificado exitosamente!\n";
    } else {
        // Si no se encuentra el producto
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

// Elimina un producto de la lista por su código
void Producto::eliminar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    // Busca el producto por código
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    // Si lo encuentra, lo elimina
    if (it != lista.end()) {
        lista.erase(it); // Elimina producto
        guardarEnArchivoBin(lista); // Guarda cambios
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Producto eliminado - Código: " + codigo);
        cout << "\n\t\tProducto eliminado exitosamente!\n";
    } else {
        // Producto no encontrado
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

// Guarda la lista de productos en el archivo de texto

void Producto::guardarEnArchivoBin(const vector<Producto>& productos) {
    ofstream archivo("productos.bin", ios::binary | ios::out);

    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo abrir archivo de productos!\n";
        return;
    }

    try {
        // Escribir cantidad de productos primero
        size_t cantidad = productos.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        // Escribir cada producto
        for (const auto& producto : productos) {
            // Escribir código
            size_t codigoSize = producto.codigo.size();
            archivo.write(reinterpret_cast<const char*>(&codigoSize), sizeof(codigoSize));
            archivo.write(producto.codigo.c_str(), codigoSize);

            // Escribir nombre
            size_t nombreSize = producto.nombre.size();
            archivo.write(reinterpret_cast<const char*>(&nombreSize), sizeof(nombreSize));
            archivo.write(producto.nombre.c_str(), nombreSize);

            // Escribir precio y stock
            archivo.write(reinterpret_cast<const char*>(&producto.precio), sizeof(producto.precio));
            archivo.write(reinterpret_cast<const char*>(&producto.stock), sizeof(producto.stock));
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


void Producto::cargarDesdeArchivoBin(vector<Producto>& productos) {
    productos.clear();
    ifstream archivo("productos.bin", ios::binary | ios::in);


    if (!archivo) {
        // Si el archivo no existe, no es un error (primera ejecución)
        return;
    }

    try {
        // Leer cantidad de productos
        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            Producto producto;

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

            // Leer precio y stock
            archivo.read(reinterpret_cast<char*>(&producto.precio), sizeof(producto.precio));
            archivo.read(reinterpret_cast<char*>(&producto.stock), sizeof(producto.stock));

            productos.push_back(producto);
        }

        if (archivo.bad()) {
            throw runtime_error("Error de lectura del archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al cargar productos: " << e.what() << "\n";
        productos.clear(); // Limpiar lista parcialmente cargada
    }

    archivo.close();
}

void Producto::setStock(int nuevoStock) {
    stock = nuevoStock;
}
