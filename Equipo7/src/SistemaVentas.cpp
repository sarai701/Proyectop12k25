#include <iostream>
#include "SistemaVentas.h"

using namespace std;

// Agrega un nuevo cliente al sistema.
// Solicita al usuario ingresar el nombre y correo electrónico del cliente.
// Luego, lo almacena en la lista de clientes.
void SistemaVentas::agregarCliente() {
    string nombre, email;
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;
    cout << "Ingrese el email del cliente: ";
    cin >> email;
    clientes.push_back(Cliente(nombre, email));
    cout << "Cliente agregado exitosamente.\n";
}

// Agrega un nuevo producto al sistema.
// Solicita al usuario ingresar el nombre y el precio del producto.
// Luego, lo almacena en la lista de productos.
void SistemaVentas::agregarProducto() {
    string nombre;
    double precio;
    cout << "Ingrese el nombre del producto: ";
    cin >> nombre;
    cout << "Ingrese el precio del producto: ";
    cin >> precio;
    productos.push_back(Producto(nombre, precio));
    cout << "Producto agregado exitosamente.\n";
}

// Registra una nueva venta en el sistema.
// Solicita al usuario ingresar el nombre del cliente, el nombre del producto y la cantidad deseada.
// Verifica la existencia del cliente y del producto antes de registrar la venta.
void SistemaVentas::realizarVenta() {
    string nombreCliente;
    string nombreProducto;
    int cantidad;

    cout << "Ingrese el nombre del cliente: ";
    cin >> nombreCliente;
    cout << "Ingrese el nombre del producto: ";
    cin >> nombreProducto;
    cout << "Ingrese la cantidad: ";
    cin >> cantidad;

    // Buscar cliente en la lista de clientes registrados
    Cliente cliente("", "");
    bool clienteEncontrado = false;
    for (const auto& c : clientes) {
        if (c.nombre == nombreCliente) {
            cliente = c;
            clienteEncontrado = true;
            break;
        }
    }

    // Buscar producto en la lista de productos disponibles
    Producto producto("", 0);
    bool productoEncontrado = false;
    for (const auto& p : productos) {
        if (p.nombre == nombreProducto) {
            producto = p;
            productoEncontrado = true;
            break;
        }
    }

    // Si el cliente y el producto existen, se registra la venta
    if (clienteEncontrado && productoEncontrado) {
        ventas.push_back(Venta(cliente, producto, cantidad));
        cout << "Venta realizada exitosamente.\n";
    } else {
        if (!clienteEncontrado) {
            cout << "Cliente no encontrado.\n";
        }
        if (!productoEncontrado) {
            cout << "Producto no encontrado.\n";
        }
    }
}


// Muestra la lista de todas las ventas realizadas.
// Se imprime el nombre del cliente, el producto comprado y la cantidad adquirida.
void SistemaVentas::mostrarVentas() {
    cout << "Ventas realizadas:\n";
    for (const auto& v : ventas) {
        cout << "Cliente: " << v.cliente.nombre << ", Producto: " << v.producto.nombre
             << ", Cantidad: " << v.cantidad << "\n";
    }
}


// Muestra el menú principal del sistema de ventas.
// Permite al usuario elegir entre agregar clientes, productos, realizar ventas o salir del sistema.
void SistemaVentas::mostrarMenu() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n--- Menu de Sistema de Ventas ---\n";
        cout << "1. Agregar Cliente\n";
        cout << "2. Agregar Producto\n";
        cout << "3. Realizar Venta\n";
        cout << "4. Mostrar Ventas\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarCliente();
                break;
            case 2:
                agregarProducto();
                break;
            case 3:
                realizarVenta();
                break;
            case 4:
                mostrarVentas();
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no válida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}


void SistemaVentas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");  // Para Windows
#else
    system("clear");  // Para Linux/Mac
#endif
}
