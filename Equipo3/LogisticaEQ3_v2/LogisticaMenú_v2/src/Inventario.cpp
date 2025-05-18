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
using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;
std::vector<Inventario> Inventario::listaInventario;

// ----------- Funciones de archivo para Productos ------------
vector<Producto> cargarProductosDesdeArchivo() {
    ifstream archivo("productos.bin", ios::binary);
    vector<Producto> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Producto producto;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        string tempStr(size, '\0');
        archivo.read(&tempStr[0], size);
        producto.setId(tempStr);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tempStr.resize(size);
        archivo.read(&tempStr[0], size);
        producto.setNombre(tempStr);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tempStr.resize(size);
        archivo.read(&tempStr[0], size);
        producto.setDescripcion(tempStr);

        double precio;
        archivo.read(reinterpret_cast<char*>(&precio), sizeof(precio));
        producto.setPrecio(precio);

        int stock;
        archivo.read(reinterpret_cast<char*>(&stock), sizeof(stock));
        producto.setStock(stock);

        int stockMin;
        archivo.read(reinterpret_cast<char*>(&stockMin), sizeof(stockMin));
        producto.setStockMinimo(stockMin);

        lista.push_back(producto);
    }
    archivo.close();
    return lista;
}

void guardarProductosEnArchivo(const vector<Producto>& productos) {
    ofstream archivo("productos.bin", ios::binary | ios::trunc);
    for (const auto& producto : productos) {
        size_t size;

        size = producto.getId().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(producto.getId().c_str(), size);

        size = producto.getNombre().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(producto.getNombre().c_str(), size);

        size = producto.getDescripcion().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(producto.getDescripcion().c_str(), size);

        double precio = producto.getPrecio();
        archivo.write(reinterpret_cast<const char*>(&precio), sizeof(precio));

        int stock = producto.getStock();
        archivo.write(reinterpret_cast<const char*>(&stock), sizeof(stock));

        int stockMin = producto.getStockMinimo();
        archivo.write(reinterpret_cast<const char*>(&stockMin), sizeof(stockMin));
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
    vector<Producto> productos = cargarProductosDesdeArchivo();

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
    guardarProductosEnArchivo(productos);

    auditoria.registrar(usuarioRegistrado.getNombre(), "PRODUCTOS", "Creado producto " + nuevo.getId());
    cout << "\n\tProducto creado exitosamente.\n";
    system("pause");
}

void mostrarProductos() {
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

// ----------- Funciones de archivo para Almacenes ------------
vector<Almacen> cargarAlmacenesDesdeArchivo() {
    ifstream archivo("Almacenes.bin", ios::binary);
    vector<Almacen> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Almacen almacen;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        string tempStr(size, '\0');
        archivo.read(&tempStr[0], size);
        almacen.setId(tempStr);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tempStr.resize(size);
        archivo.read(&tempStr[0], size);
        almacen.setNombre(tempStr);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tempStr.resize(size);
        archivo.read(&tempStr[0], size);
        almacen.setDireccion(tempStr);

        int capacidad;
        archivo.read(reinterpret_cast<char*>(&capacidad), sizeof(capacidad));
        almacen.setCapacidad(capacidad);

        int espacioDisp;
        archivo.read(reinterpret_cast<char*>(&espacioDisp), sizeof(espacioDisp));
        almacen.setEspacioDisponible(espacioDisp);

        lista.push_back(almacen);
    }
    archivo.close();
    return lista;
}

void guardarAlmacenesEnArchivo(const vector<Almacen>& almacenes) {
    ofstream archivo("Almacenes.bin", ios::binary | ios::trunc);
    for (const auto& almacen : almacenes) {
        size_t size;

        size = almacen.getId().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(almacen.getId().c_str(), size);

        size = almacen.getNombre().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(almacen.getNombre().c_str(), size);

        size = almacen.getDireccion().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(almacen.getDireccion().c_str(), size);

        int capacidad = almacen.getCapacidad();
        archivo.write(reinterpret_cast<const char*>(&capacidad), sizeof(capacidad));

        int espacioDisp = almacen.getEspacioDisponible();
        archivo.write(reinterpret_cast<const char*>(&espacioDisp), sizeof(espacioDisp));
    }
    archivo.close();
}

// ----------- Métodos de Almacenes ------------
void crearAlmacenInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO ALMACEN                      \n";
    cout << "------------------------------------------------------------\n";

    Almacen nuevo;
    vector<Almacen> almacenes = cargarAlmacenesDesdeArchivo();

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
    guardarAlmacenesEnArchivo(almacenes);

    auditoria.registrar(usuarioRegistrado.getNombre(), "ALMACENES", "Creado almacén " + nuevo.getId());
    cout << "\n\tAlmacén creado exitosamente.\n";
    system("pause");
}

void mostrarAlmacenes() {
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

// ----------- Funciones de archivo para Proveedores ------------
vector<Proveedor> cargarProveedoresDesdeArchivo() {
    ifstream archivo("proveedores.bin", ios::binary);
    vector<Proveedor> lista;
    if (!archivo) return lista;

    while (!archivo.eof()) {
        Proveedor proveedor;
        size_t size;

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (archivo.eof()) break;
        string tempStr(size, '\0');
        archivo.read(&tempStr[0], size);
        proveedor.setId(tempStr);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tempStr.resize(size);
        archivo.read(&tempStr[0], size);
        proveedor.setNombre(tempStr);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tempStr.resize(size);
        archivo.read(&tempStr[0], size);
        proveedor.setContacto(tempStr);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tempStr.resize(size);
        archivo.read(&tempStr[0], size);
        proveedor.setTelefono(tempStr);

        lista.push_back(proveedor);
    }
    archivo.close();
    return lista;
}

void guardarProveedoresEnArchivo(const vector<Proveedor>& proveedores) {
    ofstream archivo("Proveedores.bin", ios::binary | ios::trunc);
    for (const auto& proveedor : proveedores) {
        size_t size;

        size = proveedor.getId().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.getId().c_str(), size);

        size = proveedor.getNombre().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.getNombre().c_str(), size);

        size = proveedor.getContacto().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.getContacto().c_str(), size);

        size = proveedor.getTelefono().size();
        archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
        archivo.write(proveedor.getTelefono().c_str(), size);
    }
    archivo.close();
}

// ----------- Métodos de Proveedores ------------
void crearProveedorInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                   CREAR NUEVO PROVEEDOR                    \n";
    cout << "------------------------------------------------------------\n";

    Proveedor nuevo;
    vector<Proveedor> proveedores = cargarProveedoresDesdeArchivo();

    // Generar ID único
    string nuevoId = "PROV";
    if (!proveedores.empty()) {
        int maxNum = 0;
        for (const auto& p : proveedores) {
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

    cout << "Ingrese nombre del proveedor: ";
    cin.ignore();
    string nombre;
    getline(cin, nombre);
    nuevo.setNombre(nombre);

    cout << "Ingrese persona de contacto: ";
    string contacto;
    getline(cin, contacto);
    nuevo.setContacto(contacto);

    cout << "Ingrese telefono: ";
    string telefono;
    getline(cin, telefono);
    nuevo.setTelefono(telefono);

    proveedores.push_back(nuevo);
    guardarProveedoresEnArchivo(proveedores);

    auditoria.registrar(usuarioRegistrado.getNombre(), "PROVEEDORES", "Creado proveedor " + nuevo.getId());
    cout << "\n\tProveedor creado exitosamente.\n";
    system("pause");
}

void mostrarProveedores() {
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
        cout << setw(7) << left << proveedor.getId() << " | "
             << setw(16) << left << proveedor.getNombre() << " | "
             << setw(18) << left << proveedor.getContacto() << " | "
             << setw(10) << left << proveedor.getTelefono() << "\n";
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
            case 1: consultarStock(); break;
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

void Inventario::consultarStock() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| CONSULTA DE STOCK                    |" << endl;
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

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "CONS-STOCK");
    system("pause");
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
