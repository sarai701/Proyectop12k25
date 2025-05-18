#ifndef ENVIOS_H
#define ENVIOS_H

#include <string>
#include <vector>
#include "transportistas.h"

// Estructura que representa un envío
struct Envio {
    std::string idEnvio;                  // ID numérico único del envío
    std::string idPedido;                 // ID del pedido asociado
    std::string idTransportista;          // ID del transportista asignado
    std::string idCliente;                // ID del cliente receptor
    std::string estado;                   // Estado actual del envío (Ej: "En camino", "Entregado")
};

class Envios {
public:
    // Menú principal para gestión de envíos
    void gestionEnvios();

    // Crear un envío mediante interacción con usuario
    void crearEnvioInteractivo();

    // Crear un envío desde otro módulo (por ejemplo, desde pedidos)
    static void crearEnvio(const std::string& idPedido, const std::vector<Transportistas>& transportistasDisponibles);

    // Mostrar todos los envíos
    void mostrarEnvios();

    // Cargar envíos desde archivo binario
    static std::vector<Envio> cargarEnviosDesdeArchivo();

    // Guardar todos los envíos en archivo binario
    static void guardarEnviosEnArchivo(const std::vector<Envio>& envios);

    // Generar automáticamente el siguiente ID disponible para un nuevo envío
    static int generarIdEnvio();

    // Versión alternativa de creación interactiva con parámetros
    void crearEnvioInteractivo(const std::string& idPedido, const std::vector<Transportistas>& listaTransportistas);

private:
    // Vector que almacena los envíos en memoria
    static std::vector<Envio> envios;
};

#endif // ENVIOS_H

