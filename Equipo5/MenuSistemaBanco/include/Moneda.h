//Jonathan Samuel Gonzalez
#ifndef MONEDA_H
#define MONEDA_H
#include "Bitacora.h"

#include <string>

class Moneda {
private:
    static Bitacora bitacoraMoneda;

public:
    static std::string moneda;
    static double tasaUSD;
    static double tasaEUR;

    static std::string getSimbolo();
    static void actualizarTasas(double usd, double eur);
    static double convertirAGtq(double cantidad);
    static double convertirDesdeGtq(double cantidad);
};

#endif
