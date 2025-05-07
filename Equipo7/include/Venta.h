#ifndef VENTA_H
#define VENTA_H

#include "Cliente.h"
#include "Producto.h"

class Venta {
public:
    Venta(const Cliente& cliente, const Producto& producto, int cantidad);
    double calcularTotal() const;

private:
    Cliente cliente;
    Producto producto;
    int cantidad;
};

#endif // VENTA_H
