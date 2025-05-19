#ifndef ENVIOS_H
#define ENVIOS_H

#include "bitacora.h"
#include "usuarios.h"
#include <string>
#include <vector>
#include "transportistas.h"

 //JENNIFER BARRIOS COORD EQ 3
 //9959-24-10016

 class Envios {
 public:
     void gestionEnvios();
     void generarGuia();
     void asignarTransportista();
     void rastrearEnvio();
     void confirmarEntrega();

     static void crearEnvio(const std::string& idPedido,
                         const std::vector<Transportistas>& transportistas);



 };

 #endif // ENVIOS_H
