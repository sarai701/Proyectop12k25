//Karina Alejandra Arriaza Ortiz
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <set>
#include <stdexcept>

using namespace std;

const int CODIGO_INICIAL = 3600;
const int CODIGO_FINAL = 3699;

// Clase para representar un producto
class Producto {
private:
    string id;
    string nombre;
    int cantidad;

public:
    Producto(string id, string nombre, int cantidad)
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
    vector<Producto> productos;
    set<string> codigosUtilizados; // Para llevar registro de códigos usados
    int siguienteCodigo = CODIGO_INICIAL;

    string generarCodigoUnico() {
        // Primero intentamos con el siguiente código secuencial disponible
        while (siguienteCodigo <= CODIGO_FINAL) {
            string codigo = to_string(siguienteCodigo);
            if (codigosUtilizados.find(codigo) == codigosUtilizados.end()) {
                codigosUtilizados.insert(codigo);
                siguienteCodigo++;
                return codigo;
            }
            siguienteCodigo++;
        }

        // Si no hay secuenciales disponibles, buscar cualquier código libre
        for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; i++) {
            string codigo = to_string(i);
            if (codigosUtilizados.find(codigo) == codigosUtilizados.end()) {
                codigosUtilizados.insert(codigo);
                return codigo;
            }
        }

        throw runtime_error("No hay códigos disponibles en el rango " +
                          to_string(CODIGO_INICIAL) + "-" + to_string(CODIGO_FINAL));
    }

    Producto* buscarProductoPorId(const string& id) {
        for (auto& producto : productos) {
            if (producto.getId() == id) {
                return &producto;
            }
        }
        return nullptr;
    }

public:
    void controlInventario();
    void consultarStock();
    void registrarMercancia();
    void ajustarInventario();
    void reporteExistencias();
};

// Implementación de los métodos

void Inventario::registrarMercancia() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRAR MERCANCIA NUEVA            |" << endl;
    cout << "\t\t========================================" << endl;

    try {
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
    } catch (const runtime_error& e) {
        cerr << "\n\t\tError: " << e.what() << endl;
    }

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

    Producto* producto = buscarProductoPorId(id);
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

    Producto* producto = buscarProductoPorId(id);
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
