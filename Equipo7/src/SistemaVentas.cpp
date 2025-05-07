
// Mantenimiento: Steven andre vasquez chavez 9959-24-11528.
#include "SistemaVentas.h"
#include <iostream>

SistemaVentas::SistemaVentas() {
    // Configuración de usuario y contraseña por defecto
    usuario = "admin";
    contraseña = "12345";
}

bool SistemaVentas::login(const std::string& user, const std::string& pass) {
    return (usuario == user && contraseña == pass);
}

void SistemaVentas::agregarCliente(const Cliente& cliente) {
    clientes.push_back(cliente);
}

void SistemaVentas::agregarProducto(const Producto& producto) {
    productos.push_back(producto);
}

void SistemaVentas::realizarVenta(const Cliente& cliente, const Producto& producto, int cantidad) {
    Venta nuevaVenta(cliente, producto, cantidad);
    ventas.push_back(nuevaVenta);
    std::cout << "Venta realizada: " << cantidad << " " << producto.getNombre()
              << "(s) a " << cliente.getNombre() << std::endl;
}

void SistemaVentas::mostrarVentas() const {
    std::cout << "Ventas realizadas:" << std::endl;
    for (const auto& venta : ventas) {
        std::cout << "Total venta: " << venta.calcularTotal() << std::endl;
    }
}
