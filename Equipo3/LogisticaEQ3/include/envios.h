#ifndef ENVIOS_H
 #define ENVIOS_H

 #include "bitacora.h"
 #include "usuario.h"

 class Envios {
 public:
     void gestionEnvios();
     void generarGuia();
     void asignarTransportista();
     void rastrearEnvio();
     void confirmarEntrega();
 };

 #endif // ENVIOS_H
