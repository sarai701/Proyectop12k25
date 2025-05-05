#ifndef SISTEMAVENTAS_H
#define SISTEMAVENTAS_H

#include <vector>
#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"

class SistemaVentas {
private:
    std::vector<Cliente> clientes;
    std::vector<Producto> productos;
    std::vector<Venta> ventas;

public:
    void agregarCliente();
    void agregarProducto();
    void realizarVenta();
    void mostrarVentas();
    void mostrarMenu();
};

#endif // SISTEMAVENTAS_H
