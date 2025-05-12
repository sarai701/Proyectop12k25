// Autor: Jennifer Barrios - Coordinadora Equipo 3
// Carnet: 9959-24-10016
// Fecha: Mayo 2025
// Descripción: Encabezado para la gestión de pedidos del sistema

// Protección para evitar múltiples inclusiones
#ifndef PEDIDOS_H
#define PEDIDOS_H

// Bibliotecas necesarias
#include "bitacora.h"  // Para el registro de actividades del sistema
#include "usuarios.h"  // Para manejar información de usuarios

// Clase principal para manejo de pedidos
class Pedidos {
public:
    // Métodos básicos de acceso a datos

    // Obtiene el identificador único del pedido
    std::string getId() const;

    // Obtiene la descripción detallada del pedido
    std::string getDetalles() const;

    // Métodos de operaciones con pedidos

    // Muestra el menú principal de gestión de pedidos
    void gestionPedidos();

    // Crea un nuevo pedido en el sistema
    void crearPedido();

    // Muestra la lista de pedidos existentes
    void consultarPedidos();

    // Permite editar un pedido existente
    void modificarPedido();

    // Cancela/elimina un pedido del sistema
    void cancelarPedido();

    // Muestra el historial completo de pedidos
    void verHistorial();
};

// Fin del archivo de encabezado
#endif // PEDIDOS_H
