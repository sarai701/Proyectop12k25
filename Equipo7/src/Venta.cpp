#include "Venta.h"

Venta::Venta(const Cliente& cliente, const Producto& producto, int cantidad)
    : cliente(cliente), producto(producto), cantidad(cantidad) {}

double Venta::calcularTotal() const {
    return producto.getPrecio() * cantidad;
}
