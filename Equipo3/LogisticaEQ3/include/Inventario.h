//Karina Alejandra Arriaza Ortiz
#ifndef INVENTARIO_H
#define INVENTARIO_H
#include "bitacora.h"
#include "usuario.h"

class Inventario {
public:
    void controlInventario();
    void consultarStock();
    void registrarMercancia();
    void ajustarInventario();
    void reporteExistencias();
};
#endif // INVENTARIO_H
