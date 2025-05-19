//STEVEN ANDRE VASQUEZ CHAVEZ 9959 24 11528

#ifndef VENTA_H
#define VENTA_H
#include <string>
#include <vector>

// Estructura que define el detalle de cada producto en una venta
struct DetalleProducto {
    int codigoProducto;      // Código único del producto
    std::string nombreProducto; // Nombre del producto
    int cantidad;            // Cantidad de unidades del producto vendidas
    double precioUnitario;   // Precio unitario del producto

    // Constructor de la estructura DetalleProducto
    // Permite inicializar los atributos con los valores especificados
};

// Clase que representa una venta
class Venta {
public:
    int codigoVenta;         // Código único de la venta
    std::string codCliente;  // Código del cliente que realizó la compra
    std::string codVendedor; // Código del vendedor que procesó la venta
    std::vector<DetalleProducto> productos; // Vector de productos vendidos en la venta
    double total;            // Total de la venta (suma de los productos vendidos)

    // Constructor de la clase Venta
    // Inicializa los atributos de la venta con los valores dados
    // El total se establece inicialmente en 0.0
    Venta(int codVta, std::string cliente, std::string vendedor)
        : codigoVenta(codVta), codCliente(cliente), codVendedor(vendedor), total(0.0) {}

    // Aquí se pueden agregar métodos adicionales para calcular el total,
    // agregar productos a la venta, entre otros.
};

#endif // VENTA_H
