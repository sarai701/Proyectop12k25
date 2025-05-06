
// Mantenimiento: Steven andre vasquez chavez 9959-24-11528.

#include <iostream>
#include "SistemaVentas.h"
#include <conio.h>   // Para getch() en Windows


using namespace std;



// Agrega un nuevo cliente al sistema.
// Solicita al usuario ingresar el nombre y correo electrónico del cliente.
// Luego, lo almacena en la lista de clientes.
void SistemaVentas::agregarCliente() {

    cout << "\n--- Registrar nuevo cliente ---\n";
    string nombre, contacto ;
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;
    cout << "Ingrese el numero telefonico del cliente: ";
    cin >> contacto;
    clientes.push_back(Cliente(nombre, contacto ));
    cout << "Cliente agregado exitosamente.\n";


    cout << "\nPresione ENTER para regresar al menu...";

    // Espera explícitamente la tecla Enter (ASCII 13)
    char tecla;
    do {
        tecla = getch(); // Captura la tecla sin mostrarla
    } while (tecla != 13); // 13 = ASCII de Enter

    system("cls"); // Limpia la pantalla al regresar
}

// Agrega un nuevo producto al sistema.
// Solicita al usuario ingresar el nombre y el precio del producto.
// Luego, lo almacena en la lista de productos.
void SistemaVentas::agregarProducto() {
    cout << "\n--- Registrar nuevo producto ---\n";
    string nombre;
    double precio;
    cout << "Ingrese el nombre del producto: ";
    cin >> nombre;
    cout << "Ingrese el precio del producto: ";
    cin >> precio;
    productos.push_back(Producto(nombre, precio));
    cout << "Producto agregado exitosamente.\n";

    cout << "\nPresione ENTER para regresar al menu...";

    // Espera explícitamente la tecla Enter (ASCII 13)
    char tecla;
    do {
        tecla = getch(); // Captura la tecla sin mostrarla
    } while (tecla != 13); // 13 = ASCII de Enter

    system("cls"); // Limpia la pantalla al regresar
}

// Muestra los productos disponibles en el catálogo.
// Imprime el nombre y el precio de cada producto.
void SistemaVentas::mostrarCatalogo() {
    cout << "--- Catalogo de Productos ---\n";
    if (productos.empty()) {
        cout << "No hay productos registrados.\n";
    } else {
        for (const auto& producto : productos) {
            cout << "Producto: " << producto.nombre << ", Precio: Q" << producto.precio << "\n";
        }
    }

    cout << "\nPresione ENTER para regresar al menu...";

    // Espera explícitamente la tecla Enter (ASCII 13)
    char tecla;
    do {
        tecla = getch(); // Captura la tecla sin mostrarla
    } while (tecla != 13); // 13 = ASCII de Enter

    system("cls"); // Limpia la pantalla al regresar
}



// Registra una nueva venta en el sistema.
// Solicita al usuario ingresar el nombre del cliente, el nombre del producto y la cantidad deseada.
// Verifica la existencia del cliente y del producto antes de registrar la venta.
void SistemaVentas::realizarVenta() {
    cout << "\n--- Realizar la venta ---\n";
    string nombreCliente;
    string nombreProducto;
    int cantidad;

    cout << "Ingrese el nombre del cliente: ";
    cin >> nombreCliente; // se guarda el nombre del cliente
    cout << "Ingrese el nombre del producto: ";
    cin >> nombreProducto; // se guarda el nombre del producto
    cout << "Ingrese la cantidad: ";
    cin >> cantidad; // se lee y se guarda la cantidad de productos deseados

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
    cout << "\nPresione ENTER para regresar al menu...";

    // Espera explícitamente la tecla Enter (ASCII 13)
    char tecla;
    do {
        tecla = getch(); // Captura la tecla sin mostrarla
    } while (tecla != 13); // 13 = ASCII de Enter

    system("cls"); // Limpia la pantalla al regresar
}

// Muestra la lista de todas las ventas realizadas.
// Se imprime el nombre del cliente, el producto comprado y la cantidad adquirida
void SistemaVentas::mostrarVentas() {
    cout << "Ventas realizadas:\n";
    for (const auto& v : ventas) {
        cout << "Cliente: " << v.cliente.nombre
             << ", Producto: " << v.producto.nombre
             << ", Cantidad: " << v.cantidad << "\n";

        double total = v.producto.precio * v.cantidad;
        cout << "El total a pagar es de: Q" << total << "\n\n";
    }

    cout << "Presione ENTER para regresar al menú...";

    // Espera explícitamente la tecla Enter (ASCII 13)
    char tecla;
    do {
        tecla = getch(); // Captura la tecla sin mostrarla
    } while (tecla != 13); // 13 = ASCII de Enter

    system("cls"); // Limpia la pantalla al regresar
}



// Muestra el menú principal del sistema de ventas.
// Permite al usuario elegir entre agregar clientes, productos, realizar ventas o salir del sistema.
void SistemaVentas::mostrarMenu() {
    int opcion;
    do {
        cout << "\n--- Menu de Sistema de Ventas ---\n";
        cout << "1. Agregar Cliente\n";
        cout << "2. Agregar Producto\n";
        cout << "3. Realizar Venta\n";
        cout << "4. Mostrar Ventas\n";
        cout << "5. Mostrar catalogo \n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                system("cls");
                agregarCliente();
                break;
            case 2:
                system("cls");
                agregarProducto();
                break;
            case 3:
                system("cls");
                realizarVenta();
                break;
            case 4:
                system("cls");
                mostrarVentas();
                break;
            case 5:
                system("cls");
                mostrarCatalogo();
                break;

            case 6:
                system("cls");
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                cout << "\nPresione ENTER para regresar al menu...";


          // Espera explícitamente la tecla Enter (ASCII 13)
       char tecla;
    do {
        tecla = getch(); // Captura la tecla sin mostrarla
    } while (tecla != 13); // 13 = ASCII de Enter

    system("cls"); // Limpia la pantalla al regresar
        }
    } while (opcion != 6);
}
