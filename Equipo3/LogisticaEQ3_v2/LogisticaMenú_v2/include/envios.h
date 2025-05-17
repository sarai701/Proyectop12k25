#ifndef ENVIOS_H
#define ENVIOS_H

#include <string>
#include <vector>
#include "transportistas.h"

struct Envio {
    std::string idPedido;
    std::string idTransportista;
    std::string estado;
};

class Envios {
public:
    static void crearEnvio(const std::string& idPedido, const std::vector<Transportistas>& transportistasDisponibles);
    static std::vector<Envio> cargarEnviosDesdeArchivo();
    static void guardarEnviosEnArchivo(const std::vector<Envio>& envios);
    void crearEnvioInteractivo();
    void mostrarEnvios();
    void gestionEnvios();
};

#endif // ENVIOS_H
