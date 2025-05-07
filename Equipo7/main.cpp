#include <iostream>
#include "SistemaVentas.h"

int main() {
    SistemaVentas sistema;
    std::string usuario, contraseña;

    // Login
    std::cout << "Ingrese usuario: ";
    std::cin >> usuario;
    std::cout << "Ingrese contraseña: ";
    std::cin >> contraseña;

    if (sistema.login(usuario, contraseña)) {
        std::cout << "Login exitoso!" << std::endl;

        // Agregar un cliente
        Cliente cliente("Juan Perez", "juan@example.com");
        sistema.agregarCliente(cliente);

        // Agregar un producto
        Producto producto("Laptop", 1000.0);
        sistema.agregarProducto(producto);

        // Realizar una venta
        sistema.realizarVenta(cliente, producto, 2);

        // Mostrar ventas
        sistema.mostrarVentas();
    } else {
        std::cout << "Login fallido!" << std::endl;
    }

    return 0;
}
