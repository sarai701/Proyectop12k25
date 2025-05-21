// Venta.h
#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <vector>

struct DetalleProducto {
    int codigoProducto;
    std::string nombreProducto;
    int cantidad;
    double precioUnitario;
};

class Venta {
public:
    int codigoVenta;
    std::string codCliente;
    std::string codVendedor;
    std::vector<DetalleProducto> productos;
    double total;

    Venta(int codVta, std::string cliente, std::string vendedor)
        : codigoVenta(codVta), codCliente(cliente), codVendedor(vendedor), total(0.0) {}
};

#endif
