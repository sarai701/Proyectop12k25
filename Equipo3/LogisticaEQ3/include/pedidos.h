#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "bitacora.h"
#include "usuarios.h"

//JENNIFER BARRIOS COORD EQ 3
//9959-24-10016
//MAYO 2025

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
