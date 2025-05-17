#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include "usuarios.h"
#include "bitacora.h"
#include "clientes.h"
#include "producto.h"
#include "almacen.h"
#include "envios.h"
#include "transportistas.h"

class Clientes;
class Producto;
class Almacen;

// Declaraciones externas
extern usuarios usuarioRegistrado;
extern bitacora auditoria;

class Pedidos {
public:
    struct DetallePedido {
        std::string codigoProducto;
        int cantidad;
        double precioUnitario;
    };

    // Constructor
    Pedidos();

    // Métodos de gestión
    void gestionPedidos(const std::vector<Clientes>& clientes,
                      const std::vector<Producto>& productos,
                      const std::vector<Almacen>& almacenes);

    // Métodos CRUD
    void crearPedido(const std::vector<Clientes>& clientes,
                   const std::vector<Producto>& productos,
                   const std::vector<Almacen>& almacenes);

    void consultarPedidos();
    void modificarPedido(const std::vector<Clientes>& clientes,
                        const std::vector<Producto>& productos,
                        const std::vector<Almacen>& almacenes);
    void cancelarPedido();
    void completarPedido(const std::string& idPedido, std::vector<Producto>& productos);
    void verHistorial();

    // Persistencia
    static void guardarEnArchivo(const std::vector<Pedidos>& lista);
    static void cargarDesdeArchivo(std::vector<Pedidos>& lista);
    void setEstado(const std::string& nuevoEstado) { estado = nuevoEstado; }

    // Getters
    std::string getId() const { return id; }
    std::string getDetalles() const;
    std::string getEstado() const { return estado; }
    std::string getIdCliente() const { return idCliente; }


private:
    std::string id;
    std::string estado;
    std::string idCliente;
    std::string idAlmacen;
    std::time_t fechaPedido;
    std::vector<DetallePedido> detalles;

    // Generación de IDs
    static std::string generarIdUnico(const std::vector<Pedidos>& lista);
    static bool idDisponible(const std::vector<Pedidos>& lista, const std::string& id);

    // Validaciones
    static bool validarCliente(const std::string& idCliente, const std::vector<Clientes>& clientes);
    static bool validarProducto(const std::string& codigoProducto, const std::vector<Producto>& productos);
    static bool validarAlmacen(const std::string& idAlmacen, const std::vector<Almacen>& almacenes);

    // Lista estática de pedidos
    static std::vector<Pedidos> listaPedidos;

};

#endif // PEDIDOS_H
