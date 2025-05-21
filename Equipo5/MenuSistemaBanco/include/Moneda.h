//Jonathan Samuel Gonzalez
#ifndef MONEDA_H
#define MONEDA_H

#include "Bitacora.h"  // Incluye la clase Bitacora para registrar acciones relacionadas con la moneda
#include <string>      // Necesario para utilizar el tipo string

using namespace std;   // Permite usar string directamente sin el prefijo std::

class Moneda {
private:
    // Bitácora para registrar cambios o eventos relacionados con la moneda
    static Bitacora bitacoraMoneda;

public:
    // Moneda seleccionada actualmente por el sistema ("GTQ", "USD", "EUR")
    static string moneda;

    // Tasa de conversión de quetzales a dólares
    static double tasaUSD;

    // Tasa de conversión de quetzales a euros
    static double tasaEUR;

    // Devuelve el símbolo correspondiente a la moneda actual ("Q", "$", "€")
    static string getSimbolo();

    // Permite actualizar las tasas de conversión (USD y EUR)
    static void actualizarTasas(double usd, double eur);

    // Convierte una cantidad desde la moneda actual a quetzales (GTQ)
    static double convertirAGtq(double cantidad);

    // Convierte una cantidad desde quetzales (GTQ) a la moneda seleccionada
    static double convertirDesdeGtq(double cantidad);

    // Muestra en consola la moneda actual junto a su símbolo
    static void mostrarMoneda();
};

#endif
