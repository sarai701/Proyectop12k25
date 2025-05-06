// 9959-24-11603 GE
// Declaración de la clase Reportes, que se encarga de generar distintos
// informes y análisis para el sistema logístico.

#ifndef REPORTES_H
#define REPORTES_H

#include "bitacora.h"   // Para registrar acciones en la bitácora
#include "usuarios.h"   // Para acceder a información del usuario actual

// Clase que encapsula las funcionalidades relacionadas con reportes y análisis
class Reportes {
public:
    // Método principal para generar reportes desde el menú
    void generarReportes();

    // Genera un informe de ventas
    void informeVentas();

    // Realiza un análisis de los tiempos de entrega
    void analisisTiemposEntrega();

    // Muestra un reporte del estado actual del inventario
    void reporteInventarios();

    // Evalúa el desempeño de los proveedores
    void evaluacionProveedores();
};

#endif // REPORTES_H
