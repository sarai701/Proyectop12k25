#ifndef ENVIOS_H
#define ENVIOS_H

#include <string>
#include <vector>
#include "transportistas.h"

struct Envio {
    std::string idPedido;
    std::string idTransportista;
    std::string idCliente;
    std::string estado;
};

class Envios {
public:
    static void gestionEnvios();
    static void crearEnvioInteractivo();
    static void crearEnvio(const std::string& idPedido, const std::vector<Transportistas>& transportistasDisponibles);
    static void mostrarEnvios();

    // ✅ Estas dos funciones deben ser públicas
    static std::vector<Envio> cargarEnviosDesdeArchivo();
    static void guardarEnviosEnArchivo(const std::vector<Envio>& envios);
};

#endif

