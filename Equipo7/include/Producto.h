#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto {
public:
    Producto(const std::string& nombre, double precio);
    std::string getNombre() const;
    double getPrecio() const;

private:
    std::string nombre;
    double precio;
};

#endif // PRODUCTO_H
