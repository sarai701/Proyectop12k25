#ifndef COMPRAS_H
#define COMPRAS_H

#include <vector>
#include "producto.h"

class Compras {
public:
    void registrarCompra(std::vector<Producto>& listaCompras);
    void mostrarHistorial(const std::vector<Producto>& listaCompras);
    void buscarPorProveedor(const std::vector<Producto>& listaCompras);
    double calcularTotalGastado(const std::vector<Producto>& listaCompras);
    void guardarCompras(const std::vector<Producto>& listaCompras);
    std::vector<Producto> cargarCompras();
};

#endif
