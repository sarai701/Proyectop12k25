#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <vector>

struct Producto {
    std::string codigo;
    std::string nombre;
    std::string descripcion;
    double precio;
    int stock;
};

void guardarProductos(const std::vector<Producto>& productos);
std::vector<Producto> cargarProductos();
void ingresarProducto();
void consultarProductos();
void modificarProducto();
void borrarProducto();
std::string generarCodigoProducto();

#endif
