#include <iostream>
#include "SistemaVentas.h"
#include <fstream>
#include <sstream>

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

// Agrega un nuevo producto al sistema y lo guarda en el archivo.
// Solicita al usuario el nombre y precio, luego lo guarda de forma persistente.
void SistemaVentas::agregarProducto() {
    std::string nombre;
    double precio;

    std::cout << "Ingrese el nombre del producto: ";
    std::cin >> nombre;

    std::cout << "Ingrese el precio del producto: ";
    std::cin >> precio;

    // Agregar a la lista en memoria
    productos.push_back(Producto(nombre, precio));

    // Guardar en archivo inmediatamente
    std::ofstream archivo("productos.txt");
    for (const auto& p : productos) {
        archivo << p.nombre << "," << p.precio << "\n";
    }

    std::cout << "Producto agregado exitosamente.\n";
    system("pause");
}






// Registra una nueva venta en el sistema.
// Solicita al usuario ingresar el nombre del cliente, el nombre del producto y la cantidad deseada.
// Verifica la existencia del cliente y del producto antes de registrar la venta.
void SistemaVentas::realizarVenta() {
    system("cls");

    string nombreCliente;
    string nombreProducto;
    int cantidad;

    std::cout << "Nombre del cliente: ";
    std::getline(std::cin, nombreCliente);
    std::cout << "Nombre del producto: ";
    std::getline(std::cin, nombreProducto);
    std::cout << "Cantidad: ";
    std::cin >> cantidad;
    std::cin.ignore();

    Cliente* clienteEncontrado = nullptr;
    Producto* productoEncontrado = nullptr;

    for (auto& c : clientes) {
        if (c.nombre == nombreCliente) {
            clienteEncontrado = &c;
            break;
        }
    }

    for (auto& p : productos) {
        if (p.nombre == nombreProducto) {
            productoEncontrado = &p;
            break;
        }
    }

    if (clienteEncontrado && productoEncontrado) {
        ventas.emplace_back(*clienteEncontrado, *productoEncontrado, cantidad);

        // Guardar en archivo
        std::ofstream archivo("ventas.txt", std::ios::app); // modo append
if (archivo.is_open()) {
    archivo << clienteEncontrado->nombre << ","
            << clienteEncontrado->email << ","  // <--- AÑADIDO
            << productoEncontrado->nombre << ","
            << productoEncontrado->precio << ","
            << cantidad << "\n"; // <--- SE QUITA el total
    archivo.close();
        } else {
            std::cerr << "No se pudo abrir el archivo para guardar la venta.\n";
        }

        std::cout << "Venta registrada con éxito.\n";
    } else {
        std::cout << "Cliente o producto no encontrado.\n";
    }
    system("pause");
}


// Muestra la lista de todas las ventas realizadas.
// Se imprime el nombre del cliente, el producto comprado y la cantidad adquirida.
void SistemaVentas::mostrarVentas() {
    system("cls");

    cout << "=== Lista de Ventas Realizadas ===\n\n";

    if (ventas.empty()) {
        std::cout << "No se ha registrado ninguna venta.\n";
        return;
    }

    for (const auto& venta : ventas) {
        double total = venta.producto.precio * venta.cantidad;
        std::cout << "Cliente: " << venta.cliente.nombre << "\n";
        std::cout << "Producto: " << venta.producto.nombre << "\n";
        std::cout << "Cantidad: " << venta.cantidad << "\n";
        std::cout << "Precio Unitario: Q" << venta.producto.precio << "\n";
        std::cout << "Total a Pagar: Q" << total << "\n";
        std::cout << "--------------------------\n";
        ventas.clear();

    }
}


// Muestra el menú principal del sistema de ventas.
// Permite al usuario elegir entre agregar clientes, productos, realizar ventas o salir del sistema.
void SistemaVentas::mostrarMenu() {
     int opcion;
    do {
        system ("cls");
        cargarClientes();
        cargarProductos();
        cargarVentas();
        std::cout << "--- Menu del Sistema de Ventas ---\n";
        std::cout << "1. Agregar cliente\n";
        std::cout << "2. Mostrar cliente\n";
        std::cout << "3. Agregar producto\n";
        std::cout << "4. Mostrar productos\n";
        std::cout << "5. Realizar venta\n";
        std::cout << "6. Mostrar ventas\n";
        std::cout << "7. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                agregarCliente();
                guardarClientes();
                break;
            case 2:
                mostrarClientes();
                break;
            case 3:
                agregarProducto();
                break;
            case 4:
                cargarProductos();
                mostrarProductos();
                break;
            case 5:
                realizarVenta();
                break;
            case 6:
                mostrarVentas();
                system ("pause");

                break;
            case 7:
                std::cout << "Saliendo del sistema...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
                break;
        }
    } while (opcion != 7);
}


void SistemaVentas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");  // Para Windows
#else
    system("clear");  // Para Linux/Mac
#endif
}






// Guardar ventas
void SistemaVentas::guardarVentas() {
    std::ofstream archivo("ventas.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de ventas.\n";
        return;
    }

    for (const auto& venta : ventas) {
        archivo << venta.cliente.nombre << ","
                << venta.cliente.email << ","
                << venta.producto.nombre << ","
                << venta.producto.precio << ","
                << venta.cantidad << "\n";
    }

    archivo.close();
}



// Mostrar productos en consola
void SistemaVentas::mostrarProductos() {
system ("cls");
if (productos.empty()) {
        std::cout << "No hay productos registrados.\n";
    } else {
        std::cout << "Lista de productos disponibles:\n";
        for (const auto& p : productos) {
            std::cout << "- " << p.nombre << ": Q" << p.precio << "\n";
        }
    }
    system("pause");
}







// Carga los productos desde el archivo al iniciar el programa.
// Se debe llamar una vez al inicio, no repetidamente.
void SistemaVentas::cargarProductos() {
    productos.clear();  // Limpiamos para evitar duplicados si se llama más de una vez
    std::ifstream archivo("productos.txt");
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre;
        double precio;

        std::getline(ss, nombre, ',');
        ss >> precio;

        productos.push_back(Producto(nombre, precio));
    }
}
























void SistemaVentas::cargarClientes() {
    std::ifstream archivo("clientes.txt");
    std::string nombre, email;

    while (std::getline(archivo, nombre) && std::getline(archivo, email)) {
        clientes.emplace_back(nombre, email);
    }
}





void SistemaVentas::cargarVentas() {
    std::ifstream archivo("ventas.txt");
    std::string linea;

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string clienteNombre, clienteEmail, productoNombre, precioStr, cantidadStr;

        // Leer todos los campos
        if (!getline(ss, clienteNombre, ',') ||
            !getline(ss, clienteEmail, ',') ||
            !getline(ss, productoNombre, ',') ||
            !getline(ss, precioStr, ',') ||
            !getline(ss, cantidadStr)) {
            std::cerr << "Error al leer una línea del archivo de ventas. Línea: " << linea << "\n";
            continue;
        }

        try {
            double precio = std::stod(precioStr);
            int cantidad = std::stoi(cantidadStr);

            Cliente cliente(clienteNombre, clienteEmail);
            Producto producto(productoNombre, precio);

            ventas.push_back(Venta(cliente, producto, cantidad));
        } catch (const std::exception& e) {
            std::cerr << "Error al convertir datos numéricos. Línea: " << linea << "\n";
            continue;
        }
    }

    archivo.close();
}


void SistemaVentas::guardarClientes() {
    std::ofstream archivo("clientes.txt");
    for (const auto& c : clientes) {
        archivo << c.nombre << "\n" << c.email << "\n";
    }
}



void SistemaVentas::guardarVenta(const Venta& v) {
    std::ofstream archivo("ventas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << v.cliente.nombre << ","
                << v.producto.nombre << ","
                << v.cantidad << ","
                << v.producto.precio << ","
                << (v.cantidad * v.producto.precio) << "\n";
    }
}


void SistemaVentas::mostrarClientes() {
    system("cls");
    if (clientes.empty()) {
        std::cout << "No hay clientes registrados.\n";
    } else {
        std::cout << "Lista de clientes registrados:\n";
        for (const auto& c : clientes) {
            std::cout << "- Nombre: " << c.nombre << ", Email: " << c.email << "\n";
        }
    }
    system("pause");
}

