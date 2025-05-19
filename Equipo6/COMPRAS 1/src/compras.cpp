#include "compras.h"
#include "producto.h"
#include "cliente.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

string generarIdCompra() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << "CMP-" << (1900 + ltm->tm_year)
       << setw(2) << setfill('0') << (1 + ltm->tm_mon)
       << setw(2) << setfill('0') << ltm->tm_mday << "-"
       << setw(4) << setfill('0') << rand() % 10000;

    return ss.str();
}

void guardarCompra(const Compra& compra) {
    ofstream archivo("compras.txt", ios::app);
    if (archivo.is_open()) {
        archivo << compra.id << "|"
                << compra.idCliente << "|"
                << compra.fecha << "|"
                << fixed << setprecision(2) << compra.total << "|";

        for (const auto& item : compra.items) {
            archivo << item.codigoProducto << ","
                    << item.cantidad << ","
                    << fixed << setprecision(2) << item.precioUnitario << ";";
        }
        archivo << "\n";
        archivo.close();
    }
}

vector<Compra> cargarCompras() {
    vector<Compra> compras;
    ifstream archivo("compras.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Compra compra;
        string token;

        getline(ss, compra.id, '|');
        getline(ss, compra.idCliente, '|');

        getline(ss, token, '|');
        compra.fecha = stol(token);

        getline(ss, token, '|');
        compra.total = stod(token);

        string itemsStr;
        getline(ss, itemsStr);
        stringstream itemsSS(itemsStr);
        string itemToken;

        while (getline(itemsSS, itemToken, ';')) {
            if (itemToken.empty()) continue;

            stringstream itemStream(itemToken);
            ItemCompra item;

            getline(itemStream, item.codigoProducto, ',');
            getline(itemStream, token, ',');
            item.cantidad = stoi(token);
            getline(itemStream, token, ',');
            item.precioUnitario = stod(token);

            compra.items.push_back(item);
        }

        compras.push_back(compra);
    }

    return compras;
}

void registrarCompra(vector<Producto>& listaCompras) {
    Compra nuevaCompra;
    nuevaCompra.id = generarIdCompra();
    nuevaCompra.fecha = time(nullptr);

    cout << "\n=== REGISTRAR COMPRA ===\n";

    // Seleccionar cliente
    consultarClientes();
    cout << "ID del cliente: ";
    getline(cin, nuevaCompra.idCliente);

    // Verificar cliente existe
    vector<Cliente> clientes = cargarClientes();
    bool clienteExiste = any_of(clientes.begin(), clientes.end(),
        [&nuevaCompra](const Cliente& c) { return c.id == nuevaCompra.idCliente; });

    if (!clienteExiste) {
        cerr << "❌ Cliente no existe\n";
        return;
    }

    // Registrar items
    char continuar;
    vector<Producto> productos = cargarProductos();

    do {
        ItemCompra item;

        cout << "\nCódigo del producto: ";
        getline(cin, item.codigoProducto);

        // Buscar producto
        auto it = find_if(productos.begin(), productos.end(),
            [&item](const Producto& p) { return p.codigo == item.codigoProducto; });

        if (it == productos.end()) {
            cerr << "❌ Producto no encontrado\n";
            continue;
        }

        cout << "Cantidad (disponible: " << it->stock << "): ";
        cin >> item.cantidad;
        cin.ignore();

        if (item.cantidad <= 0 || item.cantidad > it->stock) {
            cerr << "❌ Cantidad inválida\n";
            continue;
        }

        item.precioUnitario = it->precio;
        nuevaCompra.items.push_back(item);
        nuevaCompra.total += item.precioUnitario * item.cantidad;

        // Actualizar stock
        it->stock -= item.cantidad;
        guardarProductos(productos);

        cout << "✔ Producto agregado (Subtotal: $"
             << fixed << setprecision(2) << (item.precioUnitario * item.cantidad) << ")\n";

        cout << "¿Agregar otro producto? (s/n): ";
        cin >> continuar;
        cin.ignore();
    } while (continuar == 's' || continuar == 'S');

    if (nuevaCompra.items.empty()) {
        cout << "❌ Compra cancelada (no hay productos)\n";
        return;
    }

    guardarCompra(nuevaCompra);
    cout << "\n✔ COMPRA REGISTRADA\n"
         << "ID: " << nuevaCompra.id << "\n"
         << "Cliente: " << nuevaCompra.idCliente << "\n"
         << "Total: $" << fixed << setprecision(2) << nuevaCompra.total << "\n";
}

void mostrarHistorial(const vector<Producto>& listaCompras) {
    vector<Compra> compras = cargarCompras();
    vector<Cliente> clientes = cargarClientes();
    vector<Producto> productos = cargarProductos();

    cout << "\n=== HISTORIAL DE COMPRAS ===\n";
    if (compras.empty()) {
        cout << "No hay compras registradas\n";
        return;
    }

    for (const auto& compra : compras) {
        // Buscar nombre del cliente
        string nombreCliente = "Desconocido";
        auto clienteIt = find_if(clientes.begin(), clientes.end(),
            [&compra](const Cliente& c) { return c.id == compra.idCliente; });

        if (clienteIt != clientes.end()) {
            nombreCliente = clienteIt->nombre;
        }

        cout << "ID: " << compra.id << "\n"
             << "Fecha: " << ctime(&compra.fecha)
             << "Cliente: " << nombreCliente << " (" << compra.idCliente << ")\n"
             << "Total: $" << fixed << setprecision(2) << compra.total << "\n"
             << "Productos:\n";

        for (const auto& item : compra.items) {
            // Buscar nombre del producto
            string nombreProducto = "Desconocido";
            auto productoIt = find_if(productos.begin(), productos.end(),
                [&item](const Producto& p) { return p.codigo == item.codigoProducto; });

            if (productoIt != productos.end()) {
                nombreProducto = productoIt->nombre;
            }

            cout << "  - " << nombreProducto << " (" << item.codigoProducto << ")\n"
                 << "    Cantidad: " << item.cantidad << "\n"
                 << "    Precio unitario: $" << item.precioUnitario << "\n"
                 << "    Subtotal: $" << (item.cantidad * item.precioUnitario) << "\n";
        }
        cout << "------------------------\n";
    }
}

void buscarPorProveedor(const vector<Producto>& listaCompras) {
    string proveedor;
    cout << "Ingrese el nombre del proveedor: ";
    getline(cin, proveedor);

    vector<Compra> compras = cargarCompras();
    bool encontrado = false;

    for (const auto& compra : compras) {
        for (const auto& item : compra.items) {
            // Buscar productos que coincidan con el proveedor
            auto producto = find_if(listaCompras.begin(), listaCompras.end(),
                [&item](const Producto& p) { return p.codigo == item.codigoProducto; });

            if (producto != listaCompras.end() && producto->nombre.find(proveedor) != string::npos) {
                if (!encontrado) {
                    cout << "\n=== COMPRAS DEL PROVEEDOR " << proveedor << " ===" << endl;
                    encontrado = true;
                }
                cout << "ID Compra: " << compra.id << " | Producto: " << producto->nombre
                     << " | Cantidad: " << item.cantidad << " | Total: $" << item.precioUnitario * item.cantidad << endl;
            }
        }
    }

    if (!encontrado) {
        cout << "No se encontraron compras para el proveedor " << proveedor << endl;
    }
}

double calcularTotalGastado(const vector<Producto>& listaCompras) {
    vector<Compra> compras = cargarCompras();
    double total = 0.0;

    for (const auto& compra : compras) {
        total += compra.total;
    }

    return total;
}
