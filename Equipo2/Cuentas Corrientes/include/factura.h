// Encabezado para funciones de manejo de facturas - Dulce Reyes Mayo 2025
// factura.h
#ifndef FACTURA_H
#define FACTURA_H

#include <string>
#include <ctime>
#include <iomanip>
#include "cliente.h" // Asegúrate de que este archivo esté correctamente incluido

struct Factura {
    int codigo;
    cliente cliente; // ← CORREGIDO: uso de clase en minúscula
    double monto;
    std::string fecha;
    std::string hora;
    std::string tipo;
    std::string estado;
    std::string tipoOperacion;
};

// Prototipos de funciones
void menuFacturaCliente();
void menuFacturaProveedor();
void menuFacturaAcreedor();
void menuReporteFactura();
void registrarFacturaPorTipo(const std::string& tipo);
void mostrarFacturasPorTipo(const std::string& tipo);
void modificarFacturaPorTipo(const std::string& tipo);
void eliminarFacturaPorTipo(const std::string& tipo);
std::string obtenerFechaActual();
std::string obtenerHoraActual();
std::string formatearMonto(double monto);

#endif // FACTURA_H
