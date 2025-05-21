#include "Producto.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "encabezado.h" //Marlon De Leon 5001

using namespace std;

std::vector<ProductoInfo> Producto::productos;
int Producto::ultimoCodigo = 5000;

Producto::Producto() {
    CargarDesdeBinario(); // Carga los productos al inicio
}

std::vector<ProductoInfo>& Producto::obtenerProductos() {
    return productos;
}

int Producto::generarCodigo() {
    return ultimoCodigo <= 7000 ? ultimoCodigo++ : 7000;
}

void Producto::NuevoProducto() {
    system("cls");
    ProductoInfo nuevo;
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t--------------------\n";
    cout << "\t\t\t |   NUEVO PRODUCTO  |\n";
    cout << "\t\t\t----------------------\n";

    cout << "\t\t\tIngrese el nombre del producto: ";
    cin.ignore();
    getline(cin, nuevo.nombre);

    cout << "\t\t\tIngrese la cantidad de productos: ";
    cin >> nuevo.cantidad;

    cout << "\t\t\tIngrese el precio del producto: ";
    cin >> nuevo.precio;

    nuevo.codigo = generarCodigo();
    productos.push_back(nuevo);
    GuardarEnBinario();

    cout << "\t\t\tProducto agregado con código: " << nuevo.codigo << endl;
    cout << "\n\t\t\tPresiona ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

void Producto::MostrarProductos() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t----------------------\n";
    cout << "\t\t\t |   MOSTRAR PRODUCTO  |\n";
    cout << "\t\t\t------------------------\n";

    if (productos.empty()) {
        cout << "\t\t\tNo hay productos registrados.\n";
    } else {
        cout << "\t\t\t Lista de productos:\n";
        for (const auto& prod : productos) {
            cout << " | Codigo: " << prod.codigo
                 << " | Nombre: " << prod.nombre
                 << " | Cantidad: " << prod.cantidad
                 << " | Precio: Q" << prod.precio << endl;
        }
    }

    cout << "\t\t\t Presiona ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

void Producto::EliminarProducto() {
    int codigo;
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t------------------------\n";
    cout << "\t\t\t|   ELIMINAR PRODUCTO  |\n";
    cout << "\t\t\t------------------------\n";

    cout << "\t\t\t Ingrese el codigo del producto a eliminar: ";
    cin >> codigo;

    for (auto it = productos.begin(); it != productos.end(); ++it) {
        if (it->codigo == codigo) {
            cout << "\t\t\t Producto encontrado: " << it->nombre << endl;
            cout << "\t\t\t Desea eliminarlo? (s/n): ";
            char respuesta;
            cin >> respuesta;
            if (respuesta == 's' || respuesta == 'S') {
                productos.erase(it);
                GuardarEnBinario();
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

    cout << "\t\t\t No se encontro un producto con ese codigo.\n";
    cout << "\t\t\t Presiona ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

void Producto::AumentarExistencias() {
    int codigo, cantidadExtra;
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t-----------------------------\n";
    cout << "\t\t\t|   AUMENTAR EXISTENCIAS   |\n";
    cout << "\t\t\t-----------------------------\n";
    cout << "\t\t\tIngrese el codigo del producto: ";
    cin >> codigo;

    for (auto& prod : productos) {
        if (prod.codigo == codigo) {
            cout << "\t\t\tProducto: " << prod.nombre << endl;
            cout << "\t\t\tExistencias actuales: " << prod.cantidad << endl;
            cout << "\t\t\tIngrese la cantidad a aumentar: ";
            cin >> cantidadExtra;
            prod.cantidad += cantidadExtra;
            GuardarEnBinario();
            cout << "\t\t\tExistencias actualizadas correctamente.\n";
            cout << "\t\t\tPresiona ENTER para continuar...";
            cin.ignore();
            cin.get();
            return;
        }
    }

    cout << "\t\t\tProducto no encontrado.\n";
    cout << "\t\t\tPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void Producto::GuardarEnBinario() {
    ofstream archivo("productos.bin", ios::binary);
    if (!archivo) {
        cout << "\t\t\tError al guardar en archivo binario.\n";
        return;
    }

    for (const auto& prod : productos) {
        size_t len = prod.nombre.size();
        archivo.write(reinterpret_cast<const char*>(&len), sizeof(len));
        archivo.write(prod.nombre.c_str(), len);
        archivo.write(reinterpret_cast<const char*>(&prod.cantidad), sizeof(prod.cantidad));
        archivo.write(reinterpret_cast<const char*>(&prod.precio), sizeof(prod.precio));
        archivo.write(reinterpret_cast<const char*>(&prod.codigo), sizeof(prod.codigo));
    }

    archivo.close();
}

void Producto::CargarDesdeBinario() {
    ifstream archivo("productos.bin", ios::binary);
    if (!archivo) return;

    productos.clear();
    ProductoInfo temp;

    while (archivo.peek() != EOF) {
        size_t len;
        archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
        temp.nombre.resize(len);
        archivo.read(&temp.nombre[0], len);

        archivo.read(reinterpret_cast<char*>(&temp.cantidad), sizeof(temp.cantidad));
        archivo.read(reinterpret_cast<char*>(&temp.precio), sizeof(temp.precio));
        archivo.read(reinterpret_cast<char*>(&temp.codigo), sizeof(temp.codigo));

        productos.push_back(temp);

        if (temp.codigo >= ultimoCodigo && temp.codigo < 7000) {
            ultimoCodigo = temp.codigo + 1;
        }
    }

    archivo.close();
}

void Producto::MenuProducto() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
        cout << "\n\t\t\t |----------------------------------|\n";
        cout << "\t\t\t |  SISTEMA DE PRODUCTOS            |\n";
        cout << "\t\t\t |----------------------------------|\n";
        cout << "\t\t\t |  1. NUEVO PRODUCTO               |\n";
        cout << "\t\t\t |  2. ELIMINAR PRODUCTO            |\n";
        cout << "\t\t\t |  3. AUMENTAR EXISTENCIAS         |\n";
        cout << "\t\t\t |  4. SALIR AL MENÚ PRINCIPAL      |\n";
        cout << "\t\t\t |----------------------------------|\n";
        cout << "\t\t\t Ingresa tu opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: NuevoProducto(); break;
            case 2: EliminarProducto(); break;
            case 3: AumentarExistencias(); break;
            case 4: return;
            default:
                cout << "\n\t\t\tOpción inválida... Intenta de nuevo...\n";
                cin.ignore();
                cin.get();
        }
    } while (opcion != 4);
}
