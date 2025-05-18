//Karina Alejandra Arriaza Ortiz
#include <iostream>
<<<<<<< HEAD
<<<<<<< HEAD
#include <vector>
#include <iomanip>
#include <algorithm>
#include <set>
#include <stdexcept>

using namespace std;

const int CODIGO_INICIAL = 3600;
const int CODIGO_FINAL = 3699;
=======
<<<<<<< HEAD
=======
>>>>>>> ffd3338976ae7d3d40875f6f300ac94460248d9a
#include <fstream>
#include <iomanip>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <map>

using namespace std;
const int CODIGO_INICIAL = 3600;
const int CODIGO_FINAL = 3699;

class Almacen {
private:
    string id;
    string nombre;
    string ubicacion;
    int capacidad;

public:
    Almacen(string id, string nombre, string ubicacion, int capacidad)
        : id(id), nombre(nombre), ubicacion(ubicacion), capacidad(capacidad) {}

    // Getters
    string getId() const { return id; }
    string getNombre() const { return nombre; }
    string getUbicacion() const { return ubicacion; }
    int getCapacidad() const { return capacidad; }
};

class producto {
private:
    string id;
    string nombre;
    int cantidad;
    string almacenId;

public:
    producto(string id, string nombre, int cantidad, string almacenId = "")
        : id(id), nombre(nombre), cantidad(cantidad), almacenId(almacenId) {}

    // Getters
    string getId() const { return id; }
    string getNombre() const { return nombre; }
    int getCantidad() const { return cantidad; }
    string getAlmacenId() const { return almacenId; } // Nuevo getter

    // Setters
    void setCantidad(int nuevaCantidad) { cantidad = nuevaCantidad; }
    void setNombre(string nuevoNombre) { nombre = nuevoNombre; }
    void setAlmacenId(string nuevoAlmacenId) { almacenId = nuevoAlmacenId; } // Nuevo setter
};

// Clase para manejar el inventario
class Inventario {
private:
    map<string, vector<string>> productosPorAlmacen;
    vector<Almacen> almacenes;
    int siguienteCodigo = CODIGO_INICIAL;
    vector<producto> productos;

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
    void reporteExistencias();
    void asignarProductoAlmacen();
    void consultarProductosEnAlmacen();
    void transferirProducto();
    void ajustarInventario();
    void gestionarAlmacenes();
};

// Implementación de los métodos

void Inventario::registrarMercancia() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRAR MERCANCIA NUEVA            |" << endl;
    cout << "\t\t========================================" << endl;

    string id = generarCodigoUnico();
    string nombre, almacenId;
    int cantidad;

    cout << "\t\tID generado automaticamente: " << id << endl;
    cout << "\t\tNombre del producto: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\t\tCantidad: ";
    cin >> cantidad;

    // Mostrar almacenes disponibles
    cout << "\n\t\tAlmacenes disponibles:\n";
    for (const auto& almacen : almacenes) {
        cout << "\t\t" << almacen.getId() << " - " << almacen.getNombre() << endl;
    }

    cout << "\t\tID del almacen (dejar vacío si no se asigna): ";
    cin.ignore();
    getline(cin, almacenId);

    // Verificar si el almacén existe
    if (!almacenId.empty()) {
        bool almacenExiste = false;
        for (const auto& almacen : almacenes) {
            if (almacen.getId() == almacenId) {
                almacenExiste = true;
                break;
            }
        }

        if (!almacenExiste) {
            cout << "\n\t\tAlmacen no encontrado. Producto registrado sin asignar a almacen.\n";
            almacenId = "";
        } else {
            productosPorAlmacen[almacenId].push_back(id);
        }
    }

    productos.emplace_back(id, nombre, cantidad, almacenId);
    cout << "\n\t\tMercancia registrada correctamente con ID: " << id << endl;
    system("pause");
}
>>>>>>> 296cd50756a892cdc97a9b778a2a348ccc059bd2

<<<<<<< HEAD
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

<<<<<<< HEAD
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

=======
>>>>>>> 296cd50756a892cdc97a9b778a2a348ccc059bd2
void Inventario::registrarMercancia() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRAR MERCANCIA NUEVA            |" << endl;
    cout << "\t\t========================================" << endl;

<<<<<<< HEAD
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
=======
    string id, nombre;
    int cantidad;

    cout << "\t\tID del producto: ";
    cin >> id;
    cout << "\t\tNombre del producto: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\t\tCantidad: ";
    cin >> cantidad;

    // Verificar si el producto ya existe
    if (buscarProductoPorId(id) != nullptr) {
        cout << "\n\t\tError: Producto con este ID ya existe!" << endl;
    } else {
        productos.emplace_back(id, nombre, cantidad);
        cout << "\n\t\tMercancia registrada correctamente." << endl;
>>>>>>> 296cd50756a892cdc97a9b778a2a348ccc059bd2
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
=======
// Modificación en consultarStock para mostrar ubicación
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

        // Mostrar información del almacén si existe
        if (!producto->getAlmacenId().empty()) {
            for (const auto& almacen : almacenes) {
                if (almacen.getId() == producto->getAlmacenId()) {
                    cout << "\t\tAlmacen: " << almacen.getNombre()
                         << " (" << almacen.getUbicacion() << ")" << endl;
                    break;
                }
            }
        } else {
            cout << "\t\tAlmacen: No asignado" << endl;
        }
    } else {
        cout << "\n\t\tProducto no encontrado." << endl;
    }

    system("pause");
}

// Nueva función para transferir productos entre almacenes
void Inventario::transferirProducto() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| TRANSFERIR PRODUCTO ENTRE ALMACENES   |" << endl;
    cout << "\t\t========================================" << endl;

    string productoId, origenId, destinoId;

    cout << "\t\tID del producto a transferir: ";
    cin >> productoId;

    producto* p = buscarProductoPorId(productoId);
    if (p == nullptr) {
        cout << "\n\t\tProducto no encontrado!\n";
        system("pause");
        return;
    }

    origenId = p->getAlmacenId();
    if (origenId.empty()) {
        cout << "\n\t\tEl producto no está asignado a ningún almacén!\n";
        system("pause");
        return;
    }

    cout << "\t\tID del almacén destino: ";
    cin >> destinoId;

    // Verificar almacén destino
    bool destinoExiste = false;
    for (const auto& almacen : almacenes) {
        if (almacen.getId() == destinoId) {
            destinoExiste = true;
            break;
        }
    }

    if (!destinoExiste) {
        cout << "\n\t\tAlmacén destino no encontrado!\n";
        system("pause");
        return;
    }

    // Actualizar registros
    auto& productosOrigen = productosPorAlmacen[origenId];
    productosOrigen.erase(remove(productosOrigen.begin(), productosOrigen.end(), productoId), productosOrigen.end());

    productosPorAlmacen[destinoId].push_back(productoId);
    p->setAlmacenId(destinoId);

    cout << "\n\t\tProducto transferido correctamente!\n";
    system("pause");
}

// Actualizar el menú de controlInventario para incluir transferencia
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
        cout << "\t\t 5. Gestionar almacenes" << endl;
        cout << "\t\t 6. Transferir producto entre almacenes" << endl; // Nueva opción
        cout << "\t\t 7. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";
        cin >> opcion;

        switch(opcion) {
            case 1: consultarStock(); break;
            case 2: registrarMercancia(); break;
            case 3: ajustarInventario(); break;
            case 4: reporteExistencias(); break;
            case 5: gestionarAlmacenes(); break;
            case 6: transferirProducto(); break; // Nueva opción
            case 7: break;
            default: cout << "\n\t\tOpcion invalida!"; cin.get();
        }
    } while(opcion != 7);
>>>>>>> ffd3338976ae7d3d40875f6f300ac94460248d9a
}

// Modificación en reporteExistencias para mostrar almacén
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
         << setw(10) << "CANTIDAD"
         << setw(15) << "ALMACEN" << endl;
    cout << "\t\t" << string(55, '-') << endl;

    for (const auto& producto : productos) {
        string almacenInfo = "No asignado";
        if (!producto.getAlmacenId().empty()) {
            for (const auto& almacen : almacenes) {
                if (almacen.getId() == producto.getAlmacenId()) {
                    almacenInfo = almacen.getNombre();
                    break;
                }
            }
        }

        cout << "\t\t" << setw(10) << producto.getId()
             << setw(20) << producto.getNombre()
             << setw(10) << producto.getCantidad()
             << setw(15) << almacenInfo << endl;
    }

    system("pause");
}

void Inventario::asignarProductoAlmacen() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| ASIGNAR PRODUCTO A ALMACEN           |" << endl;
    cout << "\t\t========================================" << endl;

    string productoId, almacenId;

    cout << "\t\tID del producto: ";
    cin >> productoId;

    // Verificar que el producto existe
    if (buscarProductoPorId(productoId) == nullptr) {
        cout << "\n\t\tProducto no encontrado!\n";
        system("pause");
        return;
    }

    cout << "\t\tID del almacen: ";
    cin >> almacenId;

    // Verificar que el almacén existe
    bool almacenExiste = false;
    for (const auto& almacen : almacenes) {
        if (almacen.getId() == almacenId) {
            almacenExiste = true;
            break;
        }
    }

    if (!almacenExiste) {
        cout << "\n\t\tAlmacen no encontrado!\n";
        system("pause");
        return;
    }

    // Asignar producto al almacén
    productosPorAlmacen[almacenId].push_back(productoId);
    cout << "\n\t\tProducto asignado correctamente al almacen!\n";
    system("pause");
}

void Inventario::consultarProductosEnAlmacen() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| PRODUCTOS EN ALMACEN                 |" << endl;
    cout << "\t\t========================================" << endl;

    string almacenId;
    cout << "\t\tID del almacen: ";
    cin >> almacenId;

    if (productosPorAlmacen.find(almacenId) == productosPorAlmacen.end()) {
        cout << "\n\t\tAlmacen no encontrado o sin productos!\n";
        system("pause");
        return;
    }

    cout << "\n\t\tPRODUCTOS EN ESTE ALMACEN:\n";
    for (const auto& productoId : productosPorAlmacen[almacenId]) {
        producto* p = buscarProductoPorId(productoId);
        if (p != nullptr) {
            cout << "\t\t" << setw(10) << p->getId()
                 << setw(20) << p->getNombre()
                 << setw(10) << p->getCantidad() << endl;
        }
    }
    system("pause");
}
void Inventario::ajustarInventario() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| AJUSTAR INVENTARIO                   |" << endl;
    cout << "\t\t========================================" << endl;

    string id;
    cout << "\t\tIngrese ID del producto: ";
    cin >> id;

    producto* producto = buscarProductoPorId(id);
    if (producto != nullptr) {
        int opcion;
        cout << "\n\t\tProducto encontrado:" << endl;
        cout << "\t\tID: " << producto->getId() << endl;
        cout << "\t\tNombre: " << producto->getNombre() << endl;
        cout << "\t\tCantidad actual: " << producto->getCantidad() << endl;

        cout << "\n\t\t1. Modificar cantidad" << endl;
        cout << "\t\t2. Cambiar nombre" << endl;
        cout << "\t\t3. Volver" << endl;
        cout << "\t\tOpcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                int nuevaCantidad;
                cout << "\t\tNueva cantidad: ";
                cin >> nuevaCantidad;
                producto->setCantidad(nuevaCantidad);
                cout << "\n\t\tCantidad actualizada correctamente!" << endl;
                break;
            }
            case 2: {
                string nuevoNombre;
                cout << "\t\tNuevo nombre: ";
                cin.ignore();
                getline(cin, nuevoNombre);
                producto->setNombre(nuevoNombre);
                cout << "\n\t\tNombre actualizado correctamente!" << endl;
                break;
            }
            case 3:
                break;
            default:
                cout << "\n\t\tOpcion invalida!" << endl;
        }
    } else {
        cout << "\n\t\tProducto no encontrado." << endl;
    }

    system("pause");
}

void Inventario::gestionarAlmacenes() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| GESTION DE ALMACENES                 |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t1. Crear nuevo almacen" << endl;
        cout << "\t\t2. Listar almacenes" << endl;
        cout << "\t\t3. Asignar producto a almacen" << endl;
        cout << "\t\t4. Consultar productos en almacen" << endl;
        cout << "\t\t5. Volver" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                system("cls");
                cout << "\t\t========================================" << endl;
                cout << "\t\t| CREAR NUEVO ALMACEN                  |" << endl;
                cout << "\t\t========================================" << endl;

                string id, nombre, ubicacion;
                int capacidad;

                cout << "\t\tID del almacen: ";
                cin >> id;
                cout << "\t\tNombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "\t\tUbicacion: ";
                getline(cin, ubicacion);
                cout << "\t\tCapacidad: ";
                cin >> capacidad;

                almacenes.emplace_back(id, nombre, ubicacion, capacidad);
                productosPorAlmacen[id] = vector<string>(); // Inicializar lista vacía para este almacén

                cout << "\n\t\tAlmacen creado exitosamente!" << endl;
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "\t\t========================================" << endl;
                cout << "\t\t| LISTADO DE ALMACENES                 |" << endl;
                cout << "\t\t========================================" << endl;

                if (almacenes.empty()) {
                    cout << "\t\tNo hay almacenes registrados." << endl;
                } else {
                    cout << "\t\t" << left << setw(10) << "ID"
                         << setw(20) << "NOMBRE"
                         << setw(20) << "UBICACION"
                         << setw(10) << "CAPACIDAD" << endl;
                    cout << "\t\t" << string(60, '-') << endl;

                    for (const auto& almacen : almacenes) {
                        cout << "\t\t" << setw(10) << almacen.getId()
                             << setw(20) << almacen.getNombre()
                             << setw(20) << almacen.getUbicacion()
                             << setw(10) << almacen.getCapacidad() << endl;
                    }
                }
                system("pause");
                break;
            }
            case 3:
                asignarProductoAlmacen();
                break;
            case 4:
                consultarProductosEnAlmacen();
                break;
            case 5:
                break;
            default:
                cout << "\n\t\tOpcion invalida!" << endl;
                system("pause");
        }
    } while(opcion != 5);
}
