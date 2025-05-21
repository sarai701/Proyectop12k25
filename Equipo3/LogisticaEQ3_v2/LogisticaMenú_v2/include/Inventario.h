//Karina Alejandra Arriaza Ortiz 9959-24-15190
// modificado por // 9959-24-11603 GE
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "bitacora.h"
#include "usuarios.h"
#include "producto.h"
#include "almacen.h"
#include "proveedor.h"
#include <vector>
#include <string>
#include <ctime>

class Inventario {
private:
    std::string codigoProducto;
    std::string idAlmacen;
    std::string idProveedor;
    int cantidad;
    time_t fechaRegistro;
    std::string estado;

    // Variable estática para almacenar todos los registros de inventario
    static std::vector<Inventario> listaInventario;

public:
    // Constructor
    Inventario() : cantidad(0), fechaRegistro(time(nullptr)), estado("activo") {}

    // Métodos principales
    void controlInventario(std::vector<Producto>& productos,
                         std::vector<Almacen>& almacenes,
                         std::vector<Proveedor>& proveedores);

    void consultarStock(const std::vector<Producto>& productos,
                      const std::vector<Almacen>& almacenes);

    void registrarMercancia(std::vector<Producto>& productos,
                          const std::vector<Almacen>& almacenes,
                          const std::vector<Proveedor>& proveedores);

    void ajustarInventario(std::vector<Producto>& productos,
                         const std::vector<Almacen>& almacenes);

    void reporteExistencias(const std::vector<Producto>& productos,
                           const std::vector<Almacen>& almacenes);

    void transferirEntreAlmacenes(std::vector<Almacen>& almacenes,
                                 std::vector<Producto>& productos);

    // Métodos de persistencia
    static void guardarEnArchivoBin(const std::vector<Inventario>& lista);
    static void cargarDesdeArchivoBin(std::vector<Inventario>& lista);

    // Getters
    std::string getCodigoProducto() const { return codigoProducto; }
    std::string getIdAlmacen() const { return idAlmacen; }
    std::string getIdProveedor() const { return idProveedor; }
    int getCantidad() const { return cantidad; }
    time_t getFechaRegistro() const { return fechaRegistro; }
    std::string getEstado() const { return estado; }

    // Setters
    void setCodigoProducto(const std::string& codigo) { codigoProducto = codigo; }
    void setIdAlmacen(const std::string& id) { idAlmacen = id; }
    void setIdProveedor(const std::string& id) { idProveedor = id; }
    void setCantidad(int cant) { cantidad = cant; }
    void setFechaRegistro(time_t fecha) { fechaRegistro = fecha; }
    void setEstado(const std::string& est) { estado = est; }
};

#endif // INVENTARIO_H
