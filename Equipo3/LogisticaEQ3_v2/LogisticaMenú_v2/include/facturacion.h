// Angoly  Araujo  Mayo 2025
// 9959-24-17623
#ifndef FACTURACION_H
#define FACTURACION_H

#include <iostream>
using namespace std;

struct Factura {
    int idFactura;
    int idCliente;
    int idPedido;
    float monto;
    bool pagada;
    char cliente[50];
};

class Facturacion {
private:
    const char* archivoFacturas = "facturas.bin";
    const char* archivoBitacora = "bitacora.bin";

    void guardarEnArchivo(Factura factura);
    void mostrarClientes();
    void mostrarPedidos();
    int generarIdFactura();
    void registrarBitacora(const Factura& factura, const string& accion, const string& usuario = "Camila");

public:
    void mostrarMenuFacturacion();
    void crearFactura();
    void mostrarFacturas();
    void modificarFactura();
    void eliminarFactura();
};

#endif
