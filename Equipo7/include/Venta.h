#ifndef VENTA_H
#define VENTA_H

#include "Cliente.h"
#include "Producto.h"

class Venta {
public:
    Cliente cliente;
    Producto producto;
    int cantidad;

    Venta(Cliente c, Producto p, int cant);
};

#endif // VENTA_H
