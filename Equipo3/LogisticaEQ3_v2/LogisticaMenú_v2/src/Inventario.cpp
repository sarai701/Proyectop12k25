//Karina Alejandra Arriaza Ortiz
#include "inventario.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>

#include "envios.h"
#include "pedidos.h"
#include "transportistas.h"
#include "almacen.h"
#include "clientes.h"
#include "bitacora.h"
#include "producto.h"
#include "proveedor.h"

using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// ----------- Funciones de archivo para Productos ------------
vector<Producto> Productos::cargarProductosDesdeArchivo() {
    ifstream archivo("productos.dat", ios::binary);
    vector<Producto> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Producto producto;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        producto.id.resize(size);
        archivo.read(&producto.id[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        producto.nombre.resize(size);
        archivo.read(&producto.nombre[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        producto.descripcion.resize(size);
        archivo.read(&producto.descripcion[0], size);

        archivo.read(reinterpret_cast<char*>(&producto.precio), sizeof(producto.precio));
        archivo.read(reinterpret_cast<char*>(&producto.stock), sizeof(producto.stock));
        archivo.read(reinterpret_cast<char*>(&producto.stockMinimo), sizeof(producto.stockMinimo));

        lista.push_back(producto);
    }
    archivo.close();
    return lista;
}

void Productos::guardarProductosEnArchivo(const vector<Producto>& productos) {
    ofstream archivo("productos.dat", ios::binary | ios::trunc);
    for (const auto& producto : productos) {
        size_t size;

        size = producto.id.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(producto.id.c_str(), size);

        size = producto.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(producto.nombre.c_str(), size);

        size = producto.descripcion.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(producto.descripcion.c_str(), size);

        archivo.write(reinterpret_cast<const char*>(&producto.precio), sizeof(producto.precio));
        archivo.write(reinterpret_cast<const char*>(&producto.stock), sizeof(producto.stock));
        archivo.write(reinterpret_cast<const char*>(&producto.stockMinimo), sizeof(producto.stockMinimo));
    }
    archivo.close();
}

// ----------- Métodos de Productos ------------
void Productos::crearProductoInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO PRODUCTO                     \n";
    cout << "------------------------------------------------------------\n";

    Producto nuevo;
    vector<Producto> productos = cargarProductosDesdeArchivo();

    nuevo.id = generarIdProductoUnico(productos);

    cout << "Ingrese nombre del producto: ";
    cin.ignore();
    getline(cin, nuevo.nombre);

    cout << "Ingrese descripción: ";
    getline(cin, nuevo.descripcion);

    cout << "Ingrese precio: ";
    cin >> nuevo.precio;

    cout << "Ingrese stock inicial: ";
    cin >> nuevo.stock;

    cout << "Ingrese stock mínimo: ";
    cin >> nuevo.stockMinimo;

    productos.push_back(nuevo);
    guardarProductosEnArchivo(productos);

    auditoria.registrar(usuarioRegistrado.getNombre(), "PRODUCTOS", "Creado producto " + nuevo.id);
    cout << "\n\tProducto creado exitosamente.\n";
}

void Productos::mostrarProductos() {
    system("cls");
    cout << "---------------------------------------------------------------\n";
    cout << "                      LISTA DE PRODUCTOS                        \n";
    cout << "---------------------------------------------------------------\n";

    vector<Producto> productos = cargarProductosDesdeArchivo();
    if (productos.empty()) {
        cout << "\n\tNo hay productos registrados.\n";
        system("pause");
        return;
    }

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "ID       | Nombre           | Descripción       | Precio   | Stock  | Stock Mínimo\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (const auto& producto : productos) {
        cout << setw(8) << left << producto.id << " | "
             << setw(16) << left << producto.nombre << " | "
             << setw(18) << left << producto.descripcion.substr(0, 16) + (producto.descripcion.length() > 16 ? "..." : "") << " | "
             << setw(8) << left << fixed << setprecision(2) << producto.precio << " | "
             << setw(6) << left << producto.stock << " | "
             << setw(11) << left << producto.stockMinimo << "\n";
    }
    cout << "----------------------------------------------------------------------------------------\n";

    system("pause");
}

// ----------- Funciones de archivo para Almacenes ------------
vector<Almacen> Almacenes::cargarAlmacenesDesdeArchivo() {
    ifstream archivo("almacenes.dat", ios::binary);
    vector<Almacen> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Almacen almacen;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        almacen.id.resize(size);
        archivo.read(&almacen.id[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        almacen.nombre.resize(size);
        archivo.read(&almacen.nombre[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        almacen.direccion.resize(size);
        archivo.read(&almacen.direccion[0], size);

        archivo.read(reinterpret_cast<char*>(&almacen.capacidad), sizeof(almacen.capacidad));
        archivo.read(reinterpret_cast<char*>(&almacen.espacioDisponible), sizeof(almacen.espacioDisponible));

        lista.push_back(almacen);
    }
    archivo.close();
    return lista;
}

void Almacenes::guardarAlmacenesEnArchivo(const vector<Almacen>& almacenes) {
    ofstream archivo("almacenes.dat", ios::binary | ios::trunc);
    for (const auto& almacen : almacenes) {
        size_t size;

        size = almacen.id.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(almacen.id.c_str(), size);

        size = almacen.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(almacen.nombre.c_str(), size);

        size = almacen.direccion.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(almacen.direccion.c_str(), size);

        archivo.write(reinterpret_cast<const char*>(&almacen.capacidad), sizeof(almacen.capacidad));
        archivo.write(reinterpret_cast<const char*>(&almacen.espacioDisponible), sizeof(almacen.espacioDisponible));
    }
    archivo.close();
}

// ----------- Métodos de Almacenes ------------
void Almacenes::crearAlmacenInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO ALMACEN                      \n";
    cout << "------------------------------------------------------------\n";

    Almacen nuevo;
    vector<Almacen> almacenes = cargarAlmacenesDesdeArchivo();

    nuevo.id = generarIdAlmacenUnico(almacenes);

    cout << "Ingrese nombre del almacén: ";
    cin.ignore();
    getline(cin, nuevo.nombre);

    cout << "Ingrese dirección: ";
    getline(cin, nuevo.direccion);

    cout << "Ingrese capacidad total: ";
    cin >> nuevo.capacidad;

    nuevo.espacioDisponible = nuevo.capacidad;

    almacenes.push_back(nuevo);
    guardarAlmacenesEnArchivo(almacenes);

    auditoria.registrar(usuarioRegistrado.getNombre(), "ALMACENES", "Creado almacén " + nuevo.id);
    cout << "\n\tAlmacén creado exitosamente.\n";
}

void Almacenes::mostrarAlmacenes() {
    system("cls");
    cout << "---------------------------------------------------------------\n";
    cout << "                      LISTA DE ALMACENES                       \n";
    cout << "---------------------------------------------------------------\n";

    vector<Almacen> almacenes = cargarAlmacenesDesdeArchivo();
    if (almacenes.empty()) {
        cout << "\n\tNo hay almacenes registrados.\n";
        system("pause");
        return;
    }

    cout << "---------------------------------------------------------------------\n";
    cout << "ID      | Nombre           | Dirección          | Capacidad | Disponible\n";
    cout << "---------------------------------------------------------------------\n";

    for (const auto& almacen : almacenes) {
        cout << setw(7) << left << almacen.id << " | "
             << setw(16) << left << almacen.nombre << " | "
             << setw(19) << left << almacen.direccion.substr(0, 17) + (almacen.direccion.length() > 17 ? "..." : "") << " | "
             << setw(9) << left << almacen.capacidad << " | "
             << setw(10) << left << almacen.espacioDisponible << "\n";
    }
    cout << "---------------------------------------------------------------------\n";

    system("pause");
}

// ----------- Funciones de archivo para Proveedores ------------
vector<Proveedor> Proveedores::cargarProveedoresDesdeArchivo() {
    ifstream archivo("proveedores.dat", ios::binary);
    vector<Proveedor> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Proveedor proveedor;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        proveedor.id.resize(size);
        archivo.read(&proveedor.id[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        proveedor.nombre.resize(size);
        archivo.read(&proveedor.nombre[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        proveedor.contacto.resize(size);
        archivo.read(&proveedor.contacto[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        proveedor.telefono.resize(size);
        archivo.read(&proveedor.telefono[0], size);

        lista.push_back(proveedor);
    }
    archivo.close();
    return lista;
}

void Proveedores::guardarProveedoresEnArchivo(const vector<Proveedor>& proveedores) {
    ofstream archivo("proveedores.dat", ios::binary | ios::trunc);
    for (const auto& proveedor : proveedores) {
        size_t size;

        size = proveedor.id.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.id.c_str(), size);

        size = proveedor.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.nombre.c_str(), size);

        size = proveedor.contacto.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.contacto.c_str(), size);

        size = proveedor.telefono.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.telefono.c_str(), size);
    }
    archivo.close();
}

// ----------- Métodos de Proveedores ------------
void Proveedores::crearProveedorInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                   CREAR NUEVO PROVEEDOR                    \n";
    cout << "------------------------------------------------------------\n";

    Proveedor nuevo;
    vector<Proveedor> proveedores = cargarProveedoresDesdeArchivo();

    nuevo.id = generarIdProveedorUnico(proveedores);

    cout << "Ingrese nombre del proveedor: ";
    cin.ignore();
    getline(cin, nuevo.nombre);

    cout << "Ingrese persona de contacto: ";
    getline(cin, nuevo.contacto);

    cout << "Ingrese teléfono: ";
    getline(cin, nuevo.telefono);

    proveedores.push_back(nuevo);
    guardarProveedoresEnArchivo(proveedores);

    auditoria.registrar(usuarioRegistrado.getNombre(), "PROVEEDORES", "Creado proveedor " + nuevo.id);
    cout << "\n\tProveedor creado exitosamente.\n";
}

void Proveedores::mostrarProveedores() {
    system("cls");
    cout << "---------------------------------------------------------------\n";
    cout << "                     LISTA DE PROVEEDORES                      \n";
    cout << "---------------------------------------------------------------\n";

    vector<Proveedor> proveedores = cargarProveedoresDesdeArchivo();
    if (proveedores.empty()) {
        cout << "\n\tNo hay proveedores registrados.\n";
        system("pause");
        return;
    }

    cout << "---------------------------------------------------------------------\n";
    cout << "ID      | Nombre           | Contacto          | Teléfono\n";
    cout << "---------------------------------------------------------------------\n";

    for (const auto& proveedor : proveedores) {
        cout << setw(7) << left << proveedor.id << " | "
             << setw(16) << left << proveedor.nombre << " | "
             << setw(18) << left << proveedor.contacto << " | "
             << setw(10) << left << proveedor.telefono << "\n";
    }
    cout << "---------------------------------------------------------------------\n";

    system("pause");
}

string generarIdUnico(const vector<Entidad>& lista, const string& prefijo) {
    if (lista.empty()) {
        return prefijo + "001";
    }

    // Encontrar el máximo ID existente
    int maxId = 0;
    for (const auto& item : lista) {
        string numStr = item.id.substr(prefijo.length());
        try {
            int num = stoi(numStr);
            if (num > maxId) maxId = num;
        } catch (...) {
            continue;
        }
    }

    // Generar nuevo ID
    ostringstream oss;
    oss << prefijo << setw(3) << setfill('0') << (maxId + 1);
    return oss.str();
}

// Ejemplos de uso:
string generarIdProductoUnico(const vector<Producto>& productos) {
    return generarIdUnico(productos, "PROD");
}

string generarIdAlmacenUnico(const vector<Almacen>& almacenes) {
    return generarIdUnico(almacenes, "ALM");
}

string generarIdProveedorUnico(const vector<Proveedor>& proveedores) {
    return generarIdUnico(proveedores, "PROV");
}

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

void Inventario::consultarProductosDesdeArchivo() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| CONSULTA DE PRODUCTOS                |" << endl;
    cout << "\t\t========================================" << endl;

    ifstream archivo("productos.txt");
    if (!archivo.is_open()) {
        cout << "\t\tNo se pudo abrir el archivo de productos." << endl;
        system("pause");
        return;
    }

    string id, nombre, categoria;
    float precio;

    // Encabezado
    cout << "\t\t" << left << setw(10) << "ID"
         << setw(20) << "NOMBRE"
         << setw(10) << "PRECIO"
         << setw(15) << "CATEGORIA" << endl;
    cout << "\t\t" << string(55, '-') << endl;

    while (archivo >> id >> nombre >> precio >> categoria) {
        cout << "\t\t" << setw(10) << id
             << setw(20) << nombre
             << setw(10) << fixed << setprecision(2) << precio
             << setw(15) << categoria << endl;
    }

    archivo.close();
    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "CONS-PROD");
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
    cout << "\t\t" << string(40, '-') << endl;
    cout << "\t\t" << string(40, '-') << endl;
    while (archivo >> id >> nombre >> cantidad) {
        cout << "\t\t" << setw(10) << id
             << setw(20) << nombre
             << setw(10) << cantidad << endl;
    }
    archivo.close();

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REPORTE");
    system("pause");
}
