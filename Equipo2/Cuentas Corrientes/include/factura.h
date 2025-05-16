// clase para mantenimiento Factura Dulce Reyes
#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Factura {
    string codigo;
    string cliente;
    string fecha;
    float monto;
};

void registrarFactura();
void modificarFactura();
void eliminarFactura();
void verFacturas();

#endif
