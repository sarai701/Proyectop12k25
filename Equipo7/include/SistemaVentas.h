#ifndef SISTEMAVENTAS_H
#define SISTEMAVENTAS_H

#include <vector>
#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"

class SistemaVentas {
public:
    SistemaVentas();
    bool login(const std::string& usuario, const std::string& contraseña);
    void agregarCliente(const Cliente& cliente);
    void agregarProducto(const Producto& producto);
    void realizarVenta(const Cliente& cliente, const Producto& producto, int cantidad);
    void mostrarVentas() const;

private:
    std::vector<Cliente> clientes;
    std::vector<Producto> productos;
    std::vector<Venta> ventas;
    std::string usuario;
    std::string contraseña;
};

#endif // SISTEMAVENTAS_H

