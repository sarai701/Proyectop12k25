// STEVEN ANDRE VASQUEZ CHAVEZ Carnet: 9959 24 11528

#include <iostream>
#include "SistemaVentas.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "encabezado.h"


using namespace std;

void SistemaVentas::menuVenta() {
    cargarVentasDesdeArchivo();  // Carga persistente
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
        cout << "\n\t\t\t------------------------\n";
        cout << "\t\t\t |   SISTEMA DE  VENTA   |\n";
        cout << "\t\t\t--------------------------\n";
        cout << "\t\t\t 1. NUEVA VENTA \n";
        cout << "\t\t\t 2. ELIMINAR VENTA \n"; // Opción nueva
        cout << "\t\t\t 3. SALIR\n";
        cout << "\t\t\t--------------------------\n";
        cout << "\t\t\tIngresa tu opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                nuevaVenta();
                break;
            case 2:
                EliminarVenta(); // Llamada a la nueva función
                break;
            case 3:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                system("pause");
        }
    } while (opcion != 3);
}

void SistemaVentas::nuevaVenta() {
    string codCliente, codVendedor;
    limpiarPantalla();
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t---------------------\n";
    cout << "\t\t\t |   NUEVA VENTA     |\n";
    cout << "\t\t\t---------------------\n";

    cout << "\t\t\tIngrese el codigo del vendedor: ";
    cin >> codVendedor;
    Vendedores* vendedor = buscarVendedor(codVendedor);
    if (!vendedor) {
        cout << "\t\t\t Vendedor no encontrado.\n";
        system("pause");
        return;
    }

    cout << "\t\t\tIngrese el codigo del cliente: ";
    cin >> codCliente;
    Cliente* cliente = buscarCliente(codCliente);
    if (!cliente) {
        cout << "\t\t\tCliente no encontrado.\n";
        system("pause");
        return;
    }

    Venta nueva(contadorCodigoVenta++, codCliente, codVendedor);
    char continuar;

    do {
        int codigoProducto, cantidad;
        bool encontrado = false;

        cout << "\t\t\tIngrese el codigo del producto: ";
        cin >> codigoProducto;

        for (auto& prod : Producto::obtenerProductos()) {
            if (prod.codigo == codigoProducto) {
                encontrado = true;
                cout << "\t\t\tProducto: " << prod.nombre << ", Precio: Q" << prod.precio << ", Stock: " << prod.cantidad << endl;
                cout << "\t\t\tIngrese cantidad a vender: ";
                cin >> cantidad;

                if (cantidad <= 0 || cantidad > prod.cantidad) {
                    cout << "\t\t\tCantidad invalida o insuficiente.\n";
                    break;
                }

                prod.cantidad -= cantidad;
                DetalleProducto detalle = {prod.codigo, prod.nombre, cantidad, prod.precio};
                nueva.productos.push_back(detalle);
                nueva.total += cantidad * prod.precio;
                break;
            }
        }

        if (!encontrado) {
            cout << "\t\t\tProducto no encontrado.\n";
            system("pause");
        }

        cout << "\t\t\t¿Desea agregar otro producto? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    ventas.push_back(nueva);
    guardarVentaEnArchivo(nueva);

    cout << "\t\t\tVenta registrada con exito. Codigo de venta: " << nueva.codigoVenta << endl;
    cout << "\t\t\tTotal de la venta: Q" << fixed << setprecision(2) << nueva.total << endl;
    system("pause");
}

void SistemaVentas::registroVenta() {
    cargarVentasDesdeArchivo();

    int codigo;
    limpiarPantalla();
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t--------------------------\n";
    cout << "\t\t\t |   REGISTRO DE VENTA   |\n";
    cout << "\t\t\t--------------------------\n";
    cout << "\t\t\tIngrese el codigo de venta: ";
    cin >> codigo;

    for (const auto& venta : ventas) {
        if (venta.codigoVenta == codigo) {
            Cliente* cliente = buscarCliente(venta.codCliente);
            Vendedores* vendedor = buscarVendedor(venta.codVendedor);

            for (const auto& detalle : venta.productos) {
                double subtotal = detalle.cantidad * detalle.precioUnitario;
                cout << "\t\t\t - " << detalle.nombreProducto
                     << " | Cant: " << detalle.cantidad
                     << " | Precio unit: Q" << detalle.precioUnitario
                     << " | Subtotal: Q" << subtotal << endl;
            }

            cout << "\t\t\tTOTAL: Q" << venta.total << endl;
            system("pause");
            return;
        }
    }

    cout << "\t\t\tVenta no encontrada.\n";
    system("pause");
}


void SistemaVentas::guardarVentaEnArchivo(const Venta& venta) {
    ofstream archivo("ventas.txt", ios::app);
    if (!archivo.is_open()) return;

    archivo << venta.codigoVenta << "," << venta.codCliente << "," << venta.codVendedor << "," << venta.total << "\n";
    for (const auto& p : venta.productos) {
        archivo << p.codigoProducto << "," << p.nombreProducto << "," << p.cantidad << "," << p.precioUnitario << "\n";
    }
    archivo << "END\n";
    archivo.close();
}

void SistemaVentas::cargarVentasDesdeArchivo() {
    ifstream archivo("ventas.txt");
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        Venta venta(0, "", "");
        stringstream ss(linea);
        string temp;

        // Leer venta: codigoVenta, codCliente, codVendedor, total
        getline(ss, temp, ',');
        venta.codigoVenta = stoi(temp);
        getline(ss, venta.codCliente, ',');
        getline(ss, venta.codVendedor, ',');
        getline(ss, temp);
        venta.total = stod(temp);

        // Leer los productos hasta "END"
        while (getline(archivo, linea) && linea != "END") {
            DetalleProducto d;
            stringstream ds(linea);

            getline(ds, temp, ',');
            d.codigoProducto = stoi(temp);
            getline(ds, d.nombreProducto, ',');
            getline(ds, temp, ',');
            d.cantidad = stoi(temp);
            getline(ds, temp);
            d.precioUnitario = stod(temp);

            venta.productos.push_back(d);
        }

        ventas.push_back(venta);

        // Actualizar el contador si el código es mayor
        if (venta.codigoVenta >= contadorCodigoVenta)
            contadorCodigoVenta = venta.codigoVenta + 1;
    }

    archivo.close();
}


void SistemaVentas::EliminarVenta() {
    int codigoVenta;
    limpiarPantalla();
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t--------------------------\n";
    cout << "\t\t\t |   ELIMINAR VENTA      |\n";
    cout << "\t\t\t--------------------------\n";
    cout << "\t\t\tIngrese el codigo de venta a eliminar: ";
    cin >> codigoVenta;

    // Buscar la venta y eliminarla del vector
    auto it = find_if(ventas.begin(), ventas.end(),
    [codigoVenta](const Venta& v) { return v.codigoVenta == codigoVenta; });

    if (it != ventas.end()) {
        ventas.erase(it);
        cout << "\t\t\tVenta eliminada exitosamente.\n";
        // Actualizar el archivo eliminando la venta (puedes escribir una nueva versión del archivo sin la venta eliminada)
        ofstream archivo("ventas.txt", ios::trunc);  // Abrir en modo truncado para sobrescribir el archivo
        if (archivo.is_open()) {
            for (const auto& v : ventas) {
                archivo << v.codigoVenta << "," << v.codCliente << "," << v.codVendedor << "," << v.total << "\n";
                for (const auto& p : v.productos) {
                    archivo << p.codigoProducto << "," << p.nombreProducto << "," << p.cantidad << "," << p.precioUnitario << "\n";
                }
                archivo << "END\n";
            }
            archivo.close();
        } else {
            cout << "\t\t\tNo se pudo actualizar el archivo.\n";
        }
    } else {
        cout << "\t\t\tVenta no encontrada.\n";
    }
    system("pause");
}


void SistemaVentas::eliminarVentaEnArchivo(int codigoVenta) {
    vector<Venta> ventasActualizadas;

    // Cargar las ventas actuales en el vector
    cargarVentasDesdeArchivo();

    // Filtrar las ventas que no se eliminaron
    for (const auto& venta : ventas) {
        if (venta.codigoVenta != codigoVenta) {
            ventasActualizadas.push_back(venta);
        }
    }

    // Sobrescribir el archivo con las ventas actualizadas
    ofstream archivoVentas("ventas.bin", ios::binary); // Asegurar que se sobre escriba bien

    for (const auto& venta : ventasActualizadas) {
        archivoVentas << venta.codigoVenta << "\n";
        archivoVentas << venta.codCliente << "\n";
        archivoVentas << venta.codVendedor << "\n";
        archivoVentas << venta.total << "\n";

        for (const auto& detalle : venta.productos) {
            archivoVentas << detalle.codigoProducto << "\n";
            archivoVentas << detalle.nombreProducto << "\n";
            archivoVentas << detalle.cantidad << "\n";
            archivoVentas << detalle.precioUnitario << "\n";
        }
    }

    archivoVentas.close();
}


Vendedores* SistemaVentas::buscarVendedor(const string& codigo) {

    for (auto& vendedor : Vendedores::obtenerVendedores()) {
        if (vendedor.codigo == codigo) {
            return &vendedor;
        }
    }

    return nullptr;
}

Venta* SistemaVentas::obtenerVentaPorCodigo(int codigo) {
    for (auto& venta : ventas) {
        if (venta.codigoVenta == codigo) {
            return &venta;
        }
    }
    return nullptr;
}

// Implementación de la función buscarClientePorCodigo en SistemaVentas.cpp
Cliente* SistemaVentas::obtenerClientePorCodigo(const std::string& codigo) {
    for (auto& cliente : clientes) {
        if (cliente.codigo == codigo) {
            return &cliente;
        }
    }
    return nullptr; // Si no se encuentra el cliente, retorna nullptr
}


void SistemaVentas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
