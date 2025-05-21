//STEVEN ANDRE VASQUEZ CHAVEZ 9959 24 11528

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <vector>
using namespace std;

// Estructura que define la información de un producto
struct ProductoInfo {
    string nombre;  // Nombre del producto
    int cantidad;   // Cantidad disponible en inventario
    float precio;   // Precio unitario del producto
    int codigo;     // Código único que identifica al producto
};

// Clase Producto que maneja las operaciones relacionadas con los productos
class Producto {
public:
    // Constructor de la clase Producto
    Producto();

    // Menú principal para la gestión de productos
    void MenuProducto();

    // Método para agregar un nuevo producto
    void NuevoProducto();

    // Método para mostrar la lista de productos existentes
    void MostrarProductos();

    // Método para eliminar un producto de la lista
    void EliminarProducto();

    // Método estático que obtiene la lista de productos
    static std::vector<ProductoInfo>& obtenerProductos();  // Nuevo método para obtener los productos

private:
    // Lista estática que almacena todos los productos
    static std::vector<ProductoInfo> productos;  // Vector estático para contener los productos

    // Método privado para generar un código aleatorio único para los productos
    int generarCodigoAleatorio();
};

#endif // PRODUCTO_H
