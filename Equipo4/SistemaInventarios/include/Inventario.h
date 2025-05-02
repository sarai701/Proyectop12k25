//Modificacion por Ferdynand Monroy abril 2025
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include "Producto.h"

class Inventario {
private:
    std::vector<Producto> productos;
public:
    Inventario();
    void agregarProducto(int codigo, std::string nombre, float precio, int stock, std::string tipo);
    void mostrarInventarioGeneral();
    void mostrarInventarioPorTipo(std::string tipo);
    Producto* buscarProducto(int codigo); // Nueva función
    ~Inventario();
};

#endif
