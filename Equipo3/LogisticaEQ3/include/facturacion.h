// Angoly Araujo Mayo 2025
// 9959-24-17623
#ifndef FACTURACION_H
#define FACTURACION_H

#include "bitacora.h"
#include "usuarios.h"

class Facturacion {
public:
    void gestionFacturacion();
    void generarFactura();
    void consultarEstadoPago();
    void registrarPago();
    void verReportesFinancieros();
};

#endif // FACTURACION_H

