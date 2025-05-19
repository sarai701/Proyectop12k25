#ifndef PAGO_H
#define PAGO_H

#include <iostream>
using namespace std;

class pago
{
    public:
        pago(); //Constructor de la clase pago
        void menuPagos(); //Menu de opcciones de la clase pagos
        void registrarPago(); //Aqui se registra un nuevo pago
        void listarPagosPorProveedor(); //Muestra los pagos especificamente a un proveedor/Acreedor
        void listarHistorialPagos(); //Muestra todo el historial de pagos
        void mostrarCuentasPorPagar(); //Muestra las facturas pendientes de pago
        void buscarPagosPorFacura(); //Para realizar una busqueda con el id de la factura especifica

        void reportePagos(); //Reporte todos los pagos registrados
        void reporteCuentasPorPagar(); //Reporte para todas las facturas pendientes de pago

    private:
        string idPago;
        string idFactura;
        string fechaPago;
        float montoPago;
        string metodoPago; // efectivo, transferencia, cheque, etc.
        string nitEntidad;
        string tipoEntidad;
        string estadoPago; // programado, ejecutado, rechazado
};
#endif // PAGO_H
