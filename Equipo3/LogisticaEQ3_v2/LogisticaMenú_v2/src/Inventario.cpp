//Karina Alejandra Arriaza Ortiz
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;
const int CODIGO_INICIAL = 3600;
const int CODIGO_FINAL = 3699;

// Clase para representar un producto
class producto {
private:
    string id;
    string nombre;
    int cantidad;

public:
    producto(string id, string nombre, int cantidad)
        : id(id), nombre(nombre), cantidad(cantidad) {}

    // Getters
    string getId() const { return id; }
    string getNombre() const { return nombre; }
    int getCantidad() const { return cantidad; }

    // Setters
    void setCantidad(int nuevaCantidad) { cantidad = nuevaCantidad; }
    void setNombre(string nuevoNombre) { nombre = nuevoNombre; }
};

// Clase para manejar el inventario
class Inventario {
private:
    vector<producto> productos;
    int siguienteCodigo = 3600;

    producto* buscarProductoPorId(const string& id) {
        for (auto& producto : productos) {
            if (producto.getId() == id) {
                return &producto;
            }
        }
        return nullptr;
    }

    string generarCodigoUnico() {
        if (siguienteCodigo > 3699) {
            // Buscar códigos no utilizados dentro del rango
            for (int i = 3600; i <= 3699; i++) {
                string codigo = to_string(i);
                if (buscarProductoPorId(codigo) == nullptr) {
                    return codigo;
                }
            }
            throw runtime_error("No hay codigos disponibles en el rango 3600-3699");
        }
        return to_string(siguienteCodigo++);
    }

public:
    void controlInventario();
    void consultarStock();
    void registrarMercancia();
    void ajustarInventario();
    void reporteExistencias();
};

// Implementación de los métodos

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

    string id = generarCodigoUnico();
    string nombre;
    int cantidad;

    cout << "\t\tID generado automaticamente: " << id << endl;
    cout << "\t\tNombre del producto: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\t\tCantidad: ";
    cin >> cantidad;

    productos.emplace_back(id, nombre, cantidad);
    cout << "\n\t\tMercancia registrada correctamente con ID: " << id << endl;

    system("pause");
}

void Inventario::consultarStock() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| CONSULTAR STOCK DE PRODUCTO          |" << endl;
    cout << "\t\t========================================" << endl;

    string id;
    cout << "\t\tIngrese ID del producto: ";
    cin >> id;

    producto* producto = buscarProductoPorId(id);
    if (producto != nullptr) {
        cout << "\n\t\tProducto encontrado:" << endl;
        cout << "\t\tID: " << producto->getId() << endl;
        cout << "\t\tNombre: " << producto->getNombre() << endl;
        cout << "\t\tCantidad en stock: " << producto->getCantidad() << endl;
    } else {
        cout << "\n\t\tProducto no encontrado." << endl;
    }

    system("pause");
}

void Inventario::ajustarInventario() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| AJUSTAR INVENTARIO EXISTENTE         |" << endl;
    cout << "\t\t========================================" << endl;

    string id;
    cout << "\t\tIngrese ID del producto a ajustar: ";
    cin >> id;

    producto* producto = buscarProductoPorId(id);
    if (producto != nullptr) {
        int nuevaCantidad;
        cout << "\t\tCantidad actual: " << producto->getCantidad() << endl;
        cout << "\t\tNueva cantidad: ";
        cin >> nuevaCantidad;

        producto->setCantidad(nuevaCantidad);
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

    if (productos.empty()) {
        cout << "\t\tNo hay productos registrados." << endl;
        system("pause");
        return;
    }

    // Imprimir encabezados
    cout << "\t\t" << left << setw(10) << "ID"
         << setw(20) << "NOMBRE"
         << setw(10) << "CANTIDAD" << endl;
    cout << "\t\t" << string(40, '-') << endl;

    // Imprimir todos los productos
    for (const auto& producto : productos) {
        cout << "\t\t" << setw(10) << producto.getId()
             << setw(20) << producto.getNombre()
             << setw(10) << producto.getCantidad() << endl;
    }

    system("pause");
}
