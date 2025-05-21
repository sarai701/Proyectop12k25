
// Steven andre vasquez chavez carnet No. 9959 24 11528

#include "Producto.h"
#include <iostream>
#include <cstdlib>  // Para rand()
#include <ctime>    // Para time()
#include "encabezado.h"

using namespace std;

// Constructor de la clase Producto. Inicializa la semilla para generar numeros aleatorios.
Producto::Producto() {
    srand(time(0)); // Inicializa la semilla para numeros aleatorios
}

// Inicializacion del vector de productos.
std::vector<ProductoInfo> Producto::productos;

// Funcion que devuelve el vector de productos.
std::vector<ProductoInfo>& Producto::obtenerProductos() {
    return productos;
}

// Genera un codigo aleatorio para un producto entre 100 y 150.
int Producto::generarCodigoAleatorio() {
    return 100 + rand() % 51; // Genera un codigo entre 100 y 150
}

// Funcion que permite agregar un nuevo producto al sistema.
void Producto::NuevoProducto() {
    system("cls");
    ProductoInfo nuevo;
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
    cout << "\n\t\t\t--------------------\n";
    cout << "\t\t\t |   NUEVO PRODUCTO  |\n";
    cout << "\t\t\t----------------------\n";

    // Solicita el nombre del producto.
    cout << "\t\t\tIngrese el nombre del producto: ";
    cin.ignore();
    getline(cin, nuevo.nombre);

    // Solicita la cantidad de productos.
    cout << "\t\t\tIngrese la cantidad de productos: ";
    cin >> nuevo.cantidad;

    // Solicita el precio del producto.
    cout << "\t\t\tIngrese el precio del producto: ";
    cin >> nuevo.precio;

    // Genera un codigo aleatorio para el producto y lo agrega al vector de productos.
    nuevo.codigo = generarCodigoAleatorio();
    productos.push_back(nuevo);

    // Muestra el codigo del producto agregado.
    cout << "\t\t\tProducto agregado con codigo: " << nuevo.codigo << endl;
    cout << "\n\t\t\tPresiona ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Funcion que muestra todos los productos registrados.
void Producto::MostrarProductos() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
    cout << "\n\t\t\t----------------------\n";
    cout << "\t\t\t |   MOSTRAR PRODUCTO  |\n";
    cout << "\t\t\t------------------------\n";

    // Verifica si hay productos registrados.
    if (productos.empty()) {
        cout << "\t\t\tNo hay productos registrados.\n";
    } else {
        // Muestra la lista de productos.
        cout << "\t\t\t Lista de productos:\n";
        for (const auto& prod : productos) {
            cout << "\t\t\t Codigo: " << prod.codigo
                 << " | Nombre: " << prod.nombre
                 << " | Cantidad: " << prod.cantidad
                 << " | Precio: Q" << prod.precio << endl;
        }
    }

    cout << "\t\t\t Presiona ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Funcion que permite eliminar un producto por su codigo.
void Producto::EliminarProducto() {
    int codigo;
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n"; //Marlon De Leon 5001
    cout << "\t\t\t------------------------\n";
    cout << "\t\t\t|   ELIMINAR PRODUCTO  |\n";
    cout << "\t\t\t------------------------\n";

    // Solicita el codigo del producto a eliminar.
    cout << "\t\t\t Ingrese el codigo del producto a eliminar: ";
    cin >> codigo;

    // Busca el producto con el codigo ingresado y lo elimina si es encontrado.
    for (auto it = productos.begin(); it != productos.end(); ++it) {
        if (it->codigo == codigo) {
            cout << "\t\t\t Producto encontrado: " << it->nombre << endl;
            cout << "\t\t\t Desea eliminarlo? (s/n): ";
            char respuesta;
            cin >> respuesta;
            if (respuesta == 's' || respuesta == 'S') {
                productos.erase(it);
                cout << "\t\t\t Producto eliminado exitosamente.\n";
            } else {
                cout << "\t\t\t Operacion cancelada.\n";
            }

            cout << "\t\t\t Presiona ENTER para regresar al menu...";
            cin.ignore();
            cin.get();
            return;
        }
    }

    // Si no se encuentra el producto, muestra un mensaje.
    cout << "\t\t\t No se encontro un producto con ese codigo.\n";
    cout << "\t\t\t Presiona ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

// Menu principal para gestionar los productos.
void Producto::MenuProducto() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual << "\n";//Marlon De Leon 5001
        cout << "\t\t\t |----------------------------------|\n";
        cout << "\t\t\t |  SISTEMA DE PRODUCTOS            |\n";
        cout << "\t\t\t |----------------------------------|\n";
        cout << "\t\t\t |  1. NUEVO PRODUCTO               |\n";
        cout << "\t\t\t |  2. ELIMINAR PRODUCTO            |\n";
        cout << "\t\t\t |  3. REGRESAR AL MENU PRINCIPAL   |\n";
        cout << "\t\t\t |----------------------------------|\n";
        cout << "\t\t\tIngresa tu opcion: ";
        cin >> opcion;

        // Procesa la opcion seleccionada por el usuario.
        switch (opcion) {
            case 1:
                NuevoProducto();
                break;
            case 2:
                EliminarProducto();
                break;
            case 3:
                return;
            default:
                cout << "\n\t\t\tOpcion invalida... Por favor intenta otra vez...\n";
                cin.ignore();
                cin.get();
        }
    } while (opcion !=3);
}
