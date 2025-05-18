//Karina Alejandra Arriaza Ortiz
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include <string>
#include "Producto.h"
#include "Almacen.h"
#include "proveedor.h"

class Inventario {
public:
    // Estructura para representar un ítem de inventario
    struct ItemInventario {
        std::string idProducto;
        std::string idAlmacen;
        int cantidad;
        std::string ubicacion;  // Ejemplo: "Pasillo A, Estante 3"
        std::string fechaIngreso;
        std::string lote;
    };

    // Métodos para gestión de archivos
    static std::vector<ItemInventario> cargarInventarioDesdeArchivo();
    static void guardarInventarioEnArchivo(const std::vector<ItemInventario>& inventario);

    // Métodos para gestión de inventario
    static void agregarProductoAInventario();
    static void ajustarStock();
    static void transferirEntreAlmacenes();
    static void mostrarInventario();
    static void buscarProductoEnInventario();
    static void generarReporteInventario();

    // Métodos auxiliares
    static bool verificarDisponibilidad(const std::string& idProducto, int cantidadRequerida);
    static std::vector<ItemInventario> obtenerProductosBajoStockMinimo();
    static std::vector<ItemInventario> obtenerProductosPorAlmacen(const std::string& idAlmacen);
    static int obtenerStockTotalProducto(const std::string& idProducto);

private:
    // Métodos internos
    static std::string generarIdRegistroUnico(const std::vector<ItemInventario>& inventario);
};

#endif // INVENTARIO_H
