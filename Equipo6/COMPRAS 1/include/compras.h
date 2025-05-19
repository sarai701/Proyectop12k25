#ifndef COMPRAS_H
#define COMPRAS_H

#include <string>
#include <vector>
#include <ctime>
#include "producto.h"

struct ItemCompra {
    std::string codigoProducto;
    int cantidad;
    double precioUnitario;
};

struct Compra {
    std::string id;
    std::string idCliente;
    std::time_t fecha;
    std::vector<ItemCompra> items;
    double total;
};

void guardarCompra(const Compra& compra);
std::vector<Compra> cargarCompras();
void registrarCompra(std::vector<Producto>& listaCompras);
void mostrarHistorial(const std::vector<Producto>& listaCompras);
void buscarPorProveedor(const std::vector<Producto>& listaCompras);
double calcularTotalGastado(const std::vector<Producto>& listaCompras);
std::string generarIdCompra();

#endif
