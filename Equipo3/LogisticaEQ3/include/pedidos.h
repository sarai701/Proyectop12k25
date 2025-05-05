#ifndef PEDIDOS_H
#define PEDIDOS_H
#include "bitacora.h"
#include "usuarios.h"
#include <string>
#include <vector>
#include <ctime>

// Declaración de variables externas
extern usuarios usuarioRegistrado;
extern bitacora auditoria;

// Códigos para bitácora
const std::string COD_CREAR = "3000";
const std::string COD_CONSULTAR = "3001";
const std::string COD_MODIFICAR = "3002";
const std::string COD_CANCELAR = "3003";
const std::string COD_HISTORIAL = "3004";

class Pedidos {
public:
    void gestionPedidos();
    void crearPedido();
    void consultarPedidos();
    void modificarPedido();
    void cancelarPedido();
    void verHistorial();

private:
    struct Pedido {
        std::string id;
        std::string cliente;
        std::string producto;
        int cantidad;
        std::string fecha;
        std::string estado;
        std::string direccion;
        std::string telefono;
        std::string notas;
    };

    std::vector<Pedido> pedidos;

    void cargarPedidos();
    void guardarPedidos();
    std::string generarIdPedido();
    std::string obtenerFechaActual();
};

#endif // PEDIDOS_H
