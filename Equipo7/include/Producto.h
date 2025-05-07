#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto {
public:
    std::string nombre;
    double precio;

    Producto(std::string n, double p);
};

#endif // PRODUCTO_H
