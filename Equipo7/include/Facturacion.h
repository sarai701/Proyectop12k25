//STEVEN ANDRE VASQUEZ CHAVEZ 9959 24 11528

#ifndef FACTURACION_H
#define FACTURACION_H

#include "Cliente.h"
#include "Venta.h"
#include "SistemaVentas.h"


class Facturacion {
public:
    Facturacion();
    virtual ~Facturacion();

    void menuFacturacion(SistemaVentas& sistema);

    void generarFactura(SistemaVentas& sistema);

    void mostrarFactura(Cliente* cliente, Venta* venta);

    Cliente* obtenerClientePorCodigo(const std::string& codCliente);

protected:
    static int contadorFactura;

private:
    int generarCodigoFactura();
};

#endif // FACTURACION_H
