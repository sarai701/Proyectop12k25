//Karina Alejandra Arriaza Ortiz
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include <string>
#include "Producto.h"
#include "Almacen.h"
#include "Proveedor.h"

// Declaración adelantada para resolver dependencias circulares
class usuarios;
class bitacora;

class Inventario {
public:
    struct ItemInventario {
        std::string idProducto;
        std::string idAlmacen;
        int cantidad;
        std::string ubicacion;
        std::string fechaIngreso;
        std::string lote;
    };

    // Métodos estáticos para gestión de archivos
    static std::vector<Producto> cargarProductosDesdeArchivo();
    static void guardarProductosEnArchivo(const std::vector<Producto>& productos);
    static std::vector<Almacen> cargarAlmacenesDesdeArchivo();
    static void guardarAlmacenesEnArchivo(const std::vector<Almacen>& almacenes);
    static std::vector<Proveedor> cargarProveedoresDesdeArchivo();
    static void guardarProveedoresEnArchivo(const std::vector<Proveedor>& proveedores);

    // Métodos de la clase
    void controlInventario();
    void consultarStock();
    void registrarMercancia();
    void ajustarInventario();
    void reporteExistencias();
    void mostrarInventario();
    void agregarProductoAInventario();
    void transferirEntreAlmacenes();
    void buscarProductoEnInventario();
    void generarReporteInventario();

    // Métodos auxiliares
    static std::vector<Producto> cargarProductosDesdeArchivo();
static void guardarProductosEnArchivo(const std::vector<Producto>&);
    static bool verificarDisponibilidad(const std::string& idProducto, int cantidadRequerida);
    static std::vector<ItemInventario> obtenerProductosBajoStockMinimo();
    static std::vector<ItemInventario> obtenerProductosPorAlmacen(const std::string& idAlmacen);
    static int obtenerStockTotalProducto(const std::string& idProducto);

private:
    static std::string generarIdRegistroUnico(const std::vector<ItemInventario>& inventario);
};

#endif // INVENTARIO_H
