#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "bitacora.h"
#include "usuario.h"

 class Pedidos {
 public:
     void gestionPedidos();
     void crearPedido();
     void consultarPedidos();
     void modificarPedido();
     void cancelarPedido();
     void verHistorial();
 };

#endif // PEDIDOS_H
