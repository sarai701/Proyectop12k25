#ifndef SISTEMAVENTAS_H
#define SISTEMAVENTAS_H

#include <vector>
#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"


// Clase que representa el sistema de ventas.
// Se encarga de gestionar clientes, productos y ventas.
class SistemaVentas {
private:
    std::vector<Cliente> clientes; // Lista de clientes registrados en el sistema.
    std::vector<Producto> productos; // Lista de productos disponibles para la venta.
    std::vector<Venta> ventas; // Registro de ventas realizadas.

    void limpiarPantalla(); // Limpia la consola según el sistema operativo

public:
     // Agrega un nuevo cliente al sistema.
    // Solicita el nombre y correo del cliente.
    void agregarCliente();

    // Agrega un nuevo producto al sistema.
    // Solicita el nombre y el precio del producto.
    void agregarProducto();

    // Registra una nueva venta en el sistema.
    // Solicita el nombre del cliente, el nombre del producto y la cantidad a vender.
    // Verifica la existencia del cliente y del producto antes de registrar la venta.
    void realizarVenta();

     // Muestra un listado de todas las ventas realizadas.
    // Incluye el nombre del cliente, el producto adquirido y la cantidad comprada.
    void mostrarVentas();

    // Muestra el menú principal del sistema de ventas.
    // Permite al usuario elegir entre agregar clientes, productos, realizar ventas o salir del sistema.
    void mostrarMenu();


};

#endif // SISTEMAVENTAS_H
