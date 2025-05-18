//Karina Alejandra Arriaza Ortiz
#include "Inventario.h"
#include "producto.h"
#include "almacen.h"
#include "proveedor.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <sstream>
#include <vector>
#include "usuarios.h"
#include "bitacora.h"
#include "Inventario.h"
#include "Producto.h"
#include <algorithm>
#include <numeric>

using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;
std::vector<Inventario> Inventario::listaInventario;

// ----------- Funciones de archivo para Productos ------------
vector<Producto> Inventario::cargarProductosDesdeArchivo() {
    vector<Producto> productos;
    ifstream archivo("productos.bin", ios::binary);

    if (!archivo) {
        cerr << "Error al abrir el archivo de productos." << endl;
        return productos;
    }

    // Leer la cantidad de productos
    size_t cantidad;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

    // Leer cada producto
    for (size_t i = 0; i < cantidad; ++i) {
        Producto p;
        size_t size;

        // Leer ID
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        char* idBuffer = new char[size + 1];
        archivo.read(idBuffer, size);
        idBuffer[size] = '\0';
        p.setId(idBuffer);
        delete[] idBuffer;

        // Leer nombre
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        char* nombreBuffer = new char[size + 1];
        archivo.read(nombreBuffer, size);
        nombreBuffer[size] = '\0';
        p.setNombre(nombreBuffer);
        delete[] nombreBuffer;

        // Leer stock y stock mínimo
        int stock, stockMin;
        archivo.read(reinterpret_cast<char*>(&stock), sizeof(stock));
        archivo.read(reinterpret_cast<char*>(&stockMin), sizeof(stockMin));
        p.setStock(stock);
        p.setStockMinimo(stockMin);

        productos.push_back(p);
    }

    archivo.close();
    return productos;
}

void Inventario::guardarProductosEnArchivo(const vector<Producto>& productos) {
    ofstream archivo("productos.bin", ios::binary | ios::trunc);

    if (!archivo) {
        cerr << "Error al abrir el archivo de productos para escritura." << endl;
        return;
    }

    // Escribir la cantidad de productos
    size_t cantidad = productos.size();
    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

    // Escribir cada producto
    for (const auto& p : productos) {
        // Escribir ID
        string id = p.getId();
        size_t size = id.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(id.c_str(), size);

        // Escribir nombre
        string nombre = p.getNombre();
        size = nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(nombre.c_str(), size);

        // Escribir stock y stock mínimo
        int stock = p.getStock();
        int stockMin = p.getStockMinimo();
        archivo.write(reinterpret_cast<const char*>(&stock), sizeof(stock));
        archivo.write(reinterpret_cast<const char*>(&stockMin), sizeof(stockMin));
    }

    archivo.close();
}

vector<Almacen> Inventario::cargarAlmacenesDesdeArchivo() {
    vector<Almacen> almacenes;
    ifstream archivo("Almacenes.bin", ios::binary);

    if (!archivo) {
        cerr << "Error al abrir el archivo de almacenes." << endl;
        return almacenes;
    }

    // Leer la cantidad de almacenes
    size_t cantidad;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

    // Leer cada almacén
    for (size_t i = 0; i < cantidad; ++i) {
        Almacen a;
        size_t size;

        // Leer ID
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        char* idBuffer = new char[size + 1];
        archivo.read(idBuffer, size);
        idBuffer[size] = '\0';
        a.setId(idBuffer);
        delete[] idBuffer;

        // Leer nombre
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        char* nombreBuffer = new char[size + 1];
        archivo.read(nombreBuffer, size);
        nombreBuffer[size] = '\0';
        a.setNombre(nombreBuffer);
        delete[] nombreBuffer;

        // Leer capacidad y espacio disponible
        int capacidad, espacio;
        archivo.read(reinterpret_cast<char*>(&capacidad), sizeof(capacidad));
        archivo.read(reinterpret_cast<char*>(&espacio), sizeof(espacio));
        a.setCapacidad(capacidad);
        a.setEspacioDisponible(espacio);

        almacenes.push_back(a);
    }

    archivo.close();
    return almacenes;
}

void Inventario::guardarAlmacenesEnArchivo(const vector<Almacen>& almacenes) {
    ofstream archivo("Almacenes.bin", ios::binary | ios::trunc);

    if (!archivo) {
        cerr << "Error al abrir el archivo de almacenes para escritura." << endl;
        return;
    }

    // Escribir la cantidad de almacenes
    size_t cantidad = almacenes.size();
    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

    // Escribir cada almacén
    for (const auto& a : almacenes) {
        // Escribir ID
        string id = a.getId();
        size_t size = id.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(id.c_str(), size);

        // Escribir nombre
        string nombre = a.getNombre();
        size = nombre.size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(nombre.c_str(), size);

        // Escribir capacidad y espacio disponible
        int capacidad = a.getCapacidad();
        int espacio = a.getEspacioDisponible();
        archivo.write(reinterpret_cast<const char*>(&capacidad), sizeof(capacidad));
        archivo.write(reinterpret_cast<const char*>(&espacio), sizeof(espacio));
    }

    archivo.close();
}

// ----------- Métodos de Productos ------------
void crearProductoInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO PRODUCTO                     \n";
    cout << "------------------------------------------------------------\n";

    Producto nuevo;
    vector<Producto> productos = Inventario::cargarProductosDesdeArchivo();

    // Generar ID único
    string nuevoId = "PROD";
    if (!productos.empty()) {
        int maxNum = 0;
        for (const auto& p : productos) {
            string numStr = p.getId().substr(4);
            try {
                int num = stoi(numStr);
                if (num > maxNum) maxNum = num;
            } catch (...) {
                continue;
            }
        }
        ostringstream oss;
        oss << setw(3) << setfill('0') << (maxNum + 1);
        nuevoId += oss.str();
    } else {
        nuevoId += "001";
    }
    nuevo.setId(nuevoId);

    cout << "Ingrese nombre del producto: ";
    cin.ignore();
    string nombre;
    getline(cin, nombre);
    nuevo.setNombre(nombre);

    cout << "Ingrese descripción: ";
    string descripcion;
    getline(cin, descripcion);
    nuevo.setDescripcion(descripcion);

    cout << "Ingrese precio: ";
    double precio;
    cin >> precio;
    nuevo.setPrecio(precio);

    cout << "Ingrese stock inicial: ";
    int stock;
    cin >> stock;
    nuevo.setStock(stock);

    cout << "Ingrese stock mínimo: ";
    int stockMin;
    cin >> stockMin;
    nuevo.setStockMinimo(stockMin);

    productos.push_back(nuevo);
    Inventario::guardarProductosEnArchivo(productos);

    auditoria.registrar(usuarioRegistrado.getNombre(), "PRODUCTOS", "Creado producto " + nuevo.getId());
    cout << "\n\tProducto creado exitosamente.\n";
    system("pause");
}

void mostrarProductos() {
    system("cls");
    cout << "---------------------------------------------------------------\n";
    cout << "                      LISTA DE PRODUCTOS                        \n";
    cout << "---------------------------------------------------------------\n";

    vector<Producto> productos = Inventario::cargarProductosDesdeArchivo();
    if (productos.empty()) {
        cout << "\n\tNo hay productos registrados.\n";
        system("pause");
        return;
    }

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "ID       | Nombre           | Descripción       | Precio   | Stock  | Stock Mínimo\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (const auto& producto : productos) {
        string descCorta = producto.getDescripcion().substr(0, 16);
        if (producto.getDescripcion().length() > 16) descCorta += "...";

        cout << setw(8) << left << producto.getId() << " | "
             << setw(16) << left << producto.getNombre() << " | "
             << setw(18) << left << descCorta << " | "
             << setw(8) << left << fixed << setprecision(2) << producto.getPrecio() << " | "
             << setw(6) << left << producto.getStock() << " | "
             << setw(11) << left << producto.getStockMinimo() << "\n";
    }
    cout << "----------------------------------------------------------------------------------------\n";
    system("pause");
}

// ----------- Métodos de Almacenes ------------
void crearAlmacenInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO ALMACEN                      \n";
    cout << "------------------------------------------------------------\n";

    Almacen nuevo;
    vector<Almacen> almacenes = Inventario::cargarAlmacenesDesdeArchivo();

    // Generar ID único
    string nuevoId = "ALM";
    if (!almacenes.empty()) {
        int maxNum = 0;
        for (const auto& a : almacenes) {
            string numStr = a.getId().substr(3);
            try {
                int num = stoi(numStr);
                if (num > maxNum) maxNum = num;
            } catch (...) {
                continue;
            }
        }
        ostringstream oss;
        oss << setw(3) << setfill('0') << (maxNum + 1);
        nuevoId += oss.str();
    } else {
        nuevoId += "001";
    }
    nuevo.setId(nuevoId);

    cout << "Ingrese nombre del almacén: ";
    cin.ignore();
    string nombre;
    getline(cin, nombre);
    nuevo.setNombre(nombre);

    cout << "Ingrese dirección: ";
    string direccion;
    getline(cin, direccion);
    nuevo.setDireccion(direccion);

    cout << "Ingrese capacidad total: ";
    int capacidad;
    cin >> capacidad;
    nuevo.setCapacidad(capacidad);
    nuevo.setEspacioDisponible(capacidad); // Inicialmente todo el espacio está disponible

    almacenes.push_back(nuevo);
    Inventario::guardarAlmacenesEnArchivo(almacenes);

    auditoria.registrar(usuarioRegistrado.getNombre(), "ALMACENES", "Creado almacén " + nuevo.getId());
    cout << "\n\tAlmacén creado exitosamente.\n";
    system("pause");
}

void mostrarAlmacenes() {
    system("cls");
    cout << "---------------------------------------------------------------\n";
    cout << "                      LISTA DE ALMACENES                       \n";
    cout << "---------------------------------------------------------------\n";

    vector<Almacen> almacenes = Inventario::cargarAlmacenesDesdeArchivo();
    if (almacenes.empty()) {
        cout << "\n\tNo hay almacenes registrados.\n";
        system("pause");
        return;
    }

    cout << "---------------------------------------------------------------------\n";
    cout << "ID      | Nombre           | Dirección          | Capacidad | Disponible\n";
    cout << "---------------------------------------------------------------------\n";

    for (const auto& almacen : almacenes) {
        string dirCorta = almacen.getDireccion().substr(0, 17);
        if (almacen.getDireccion().length() > 17) dirCorta += "...";

        cout << setw(7) << left << almacen.getId() << " | "
             << setw(16) << left << almacen.getNombre() << " | "
             << setw(19) << left << dirCorta << " | "
             << setw(9) << left << almacen.getCapacidad() << " | "
             << setw(10) << left << almacen.getEspacioDisponible() << "\n";
    }
    cout << "---------------------------------------------------------------------\n";
    system("pause");
}

// ----------- Métodos de Inventario ------------
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
            case 1: consultarStockCompleto(); break;
            case 2: registrarMercancia(); break;
            case 3: ajustarInventario(); break;
            case 4: reporteExistencias(); break;
            case 5: break;
            default:
                cout << "\n\t\tOpcion invalida!";
                cin.ignore();
                cin.get();
        }
    } while(opcion != 5);
}

#include "Inventario.h"
#include "Producto.h"
#include <algorithm>
#include <iomanip>

void Inventario::consultarStockCompleto() {
    // Cargar productos desde su archivo
    vector<Producto> productos;
    Producto::cargarDesdeArchivoBin(productos);

    // Cargar información de inventario
    vector<ItemInventario> inventario = cargarInventarioDesdeArchivo();

    if (productos.empty() && inventario.empty()) {
        cout << "\n\t\tNo hay productos registrados en el sistema.\n";
        system("pause");
        return;
    }

    system("cls");
    cout << "\n\t\t=== CONSULTA COMPLETA DE STOCK ===\n";
    cout << "\t\t" << left << setw(10) << "Código" << setw(25) << "Nombre"
         << setw(10) << "Stock" << setw(15) << "Stock Mín"
         << setw(15) << "En Almacén" << setw(10) << "Estado" << "\n";
    cout << "\t\t" << string(85, '-') << "\n";

    for (const auto& producto : productos) {
        int enAlmacen = 0;
        auto it = find_if(inventario.begin(), inventario.end(),
            [&](const ItemInventario& item) {
                return item.idProducto == producto.getCodigo();
            });

        if (it != inventario.end()) {
            enAlmacen = it->cantidad;
        }

        string estado = (producto.getStock() >= producto.getStockMinimo()) ? "OK" : "BAJO";

        cout << "\t\t" << setw(10) << producto.getCodigo()
             << setw(25) << producto.getNombre().substr(0, 24)
             << setw(10) << producto.getStock()
             << setw(15) << producto.getStockMinimo()
             << setw(15) << enAlmacen
             << setw(10) << estado << "\n";
    }

    // Mostrar resumen
    int totalSistema = accumulate(productos.begin(), productos.end(), 0,
        [](int total, const Producto& p) { return total + p.getStock(); });

    int totalAlmacen = accumulate(inventario.begin(), inventario.end(), 0,
        [](int total, const ItemInventario& item) { return total + item.cantidad; });

    cout << "\n\t\tTOTAL EN SISTEMA: " << totalSistema
         << " | TOTAL EN ALMACÉN: " << totalAlmacen
         << " | DIFERENCIA: " << (totalSistema - totalAlmacen) << "\n";

    cout << "\n\t\tPresione cualquier tecla para volver...";
    cin.ignore();
    cin.get();
}

vector<Inventario::ItemInventario> Inventario::cargarInventarioDesdeArchivo() {
    vector<ItemInventario> inventario;
    ifstream archivo("inventario.bin", ios::binary);

    if (!archivo.is_open()) {
        return inventario;
    }

    try {
        size_t numItems;
        archivo.read(reinterpret_cast<char*>(&numItems), sizeof(numItems));

        inventario.resize(numItems);

        for (size_t i = 0; i < numItems; ++i) {
            // Leer idProducto
            size_t len;
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            inventario[i].idProducto.resize(len);
            archivo.read(&inventario[i].idProducto[0], len);

            // Leer cantidad
            archivo.read(reinterpret_cast<char*>(&inventario[i].cantidad), sizeof(inventario[i].cantidad));

            // Leer idAlmacen
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            inventario[i].idAlmacen.resize(len);
            archivo.read(&inventario[i].idAlmacen[0], len);
        }
    } catch (...) {
        cerr << "Error al leer archivo de inventario\n";
        inventario.clear();
    }

    return inventario;
}

void Inventario::registrarMercancia() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRAR MERCANCIA NUEVA            |" << endl;
    cout << "\t\t========================================" << endl;

    vector<Producto> productos = cargarProductosDesdeArchivo();
    vector<Almacen> almacenes = cargarAlmacenesDesdeArchivo();

    if (productos.empty() || almacenes.empty()) {
        cout << "\t\tDebe haber productos y almacenes registrados primero." << endl;
        system("pause");
        return;
    }

    // Mostrar productos disponibles
    cout << "\n\tProductos disponibles:\n";
    for (const auto& p : productos) {
        cout << "\t" << p.getId() << " - " << p.getNombre() << endl;
    }

    string idProducto;
    cout << "\t\tID del producto: ";
    cin >> idProducto;

    auto itProducto = find_if(productos.begin(), productos.end(),
        [&](const Producto& p) { return p.getId() == idProducto; });

    if (itProducto == productos.end()) {
        cout << "\t\tProducto no encontrado." << endl;
        system("pause");
        return;
    }

    // Mostrar almacenes disponibles
    cout << "\n\tAlmacenes disponibles:\n";
    for (const auto& a : almacenes) {
        cout << "\t" << a.getId() << " - " << a.getNombre()
             << " (Espacio: " << a.getEspacioDisponible() << ")" << endl;
    }

    string idAlmacen;
    cout << "\t\tID del almacén: ";
    cin >> idAlmacen;

    auto itAlmacen = find_if(almacenes.begin(), almacenes.end(),
        [&](const Almacen& a) { return a.getId() == idAlmacen; });

    if (itAlmacen == almacenes.end()) {
        cout << "\t\tAlmacén no encontrado." << endl;
        system("pause");
        return;
    }

    int cantidad;
    cout << "\t\tCantidad a registrar: ";
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "\t\tCantidad inválida." << endl;
        system("pause");
        return;
    }

    // Actualizar stock del producto
    itProducto->setStock(itProducto->getStock() + cantidad);

    // Actualizar espacio disponible en almacén (asumiendo 1 unidad = 1 espacio)
    itAlmacen->setEspacioDisponible(itAlmacen->getEspacioDisponible() - cantidad);

    // Guardar cambios
    guardarProductosEnArchivo(productos);
    guardarAlmacenesEnArchivo(almacenes);

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REG-MERC");
    cout << "\n\t\tMercancia registrada correctamente.";
    system("pause");
}

void Inventario::ajustarInventario() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| AJUSTAR INVENTARIO EXISTENTE         |" << endl;
    cout << "\t\t========================================" << endl;

    vector<Producto> productos = cargarProductosDesdeArchivo();
    if (productos.empty()) {
        cout << "\t\tNo hay productos registrados." << endl;
        system("pause");
        return;
    }

    // Mostrar productos
    for (const auto& p : productos) {
        cout << "\t" << p.getId() << " - " << p.getNombre()
             << " (Stock: " << p.getStock() << ")" << endl;
    }

    string idProducto;
    cout << "\t\tID del producto a ajustar: ";
    cin >> idProducto;

    auto it = find_if(productos.begin(), productos.end(),
        [&](const Producto& p) { return p.getId() == idProducto; });

    if (it == productos.end()) {
        cout << "\t\tProducto no encontrado." << endl;
        system("pause");
        return;
    }

    int nuevaCantidad;
    cout << "\t\tNueva cantidad: ";
    cin >> nuevaCantidad;

    if (nuevaCantidad < 0) {
        cout << "\t\tCantidad inválida." << endl;
        system("pause");
        return;
    }

    it->setStock(nuevaCantidad);
    guardarProductosEnArchivo(productos);

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "AJUSTE-INV");
    cout << "\n\t\tInventario ajustado correctamente." << endl;
    system("pause");
}

void Inventario::reporteExistencias() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REPORTE DE EXISTENCIAS               |" << endl;
    cout << "\t\t========================================" << endl;

    vector<Producto> productos = cargarProductosDesdeArchivo();
    if (productos.empty()) {
        cout << "\t\tNo hay productos registrados." << endl;
        system("pause");
        return;
    }

    cout << "\t\t" << left << setw(10) << "ID"
         << setw(20) << "NOMBRE"
         << setw(10) << "STOCK"
         << setw(15) << "STOCK MIN" << endl;
    cout << "\t\t" << string(55, '-') << endl;

    for (const auto& producto : productos) {
        cout << "\t\t" << setw(10) << producto.getId()
             << setw(20) << producto.getNombre()
             << setw(10) << producto.getStock()
             << setw(15) << producto.getStockMinimo() << endl;
    }

    // Calcular totales
    int totalStock = 0;
    for (const auto& p : productos) {
        totalStock += p.getStock();
    }

    cout << "\t\t" << string(55, '-') << endl;
    cout << "\t\t" << setw(30) << "TOTAL STOCK:"
         << setw(10) << totalStock << endl;

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REPORTE-INV");
    system("pause");
}
