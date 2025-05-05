#ifndef ENVIOS_H
#define ENVIOS_H

#include "bitacora.h"
#include "usuarios.h"
#include <string>

class Envios {
private:
    std::string numeroGuia;
    std::string transportista;
    std::string estado;
    std::string destino;
public:
    void gestionEnvios();
    void generarGuia();
    void asignarTransportista();
    void rastrearEnvio();
    void confirmarEntrega();
    void guardarEnvio(const std::string& archivo);
    void cargarEnvios(const std::string& archivo);
};

#endif // ENVIOS_H
