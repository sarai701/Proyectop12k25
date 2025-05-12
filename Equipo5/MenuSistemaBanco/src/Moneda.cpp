//Jonathan Samuel Gonzalez
#include "Moneda.h"
#include "Bitacora.h"

Bitacora bitacoralog7;
Bitacora Moneda::bitacoraMoneda;

std::string Moneda::moneda = "GTQ";
double Moneda::tasaUSD = 0.13;  // 1 GTQ = 0.13 USD (ejemplo)
double Moneda::tasaEUR = 0.11;  // 1 GTQ = 0.11 EUR (ejemplo)

std::string Moneda::getSimbolo() {
    if (moneda == "USD") return "$";
    else if (moneda == "EUR") return "€";
    return "Q";
}

// Convierte desde la moneda actual a GTQ
double Moneda::convertirAGtq(double cantidad) {
    if (moneda == "USD") return cantidad / tasaUSD;
    else if (moneda == "EUR") return cantidad / tasaEUR;
    return cantidad; // Si ya es GTQ
}

void Moneda::actualizarTasas(double usd, double eur) {
    tasaUSD = usd;
    tasaEUR = eur;
    bitacoraMoneda.insertar("Admin", 4501, "Moneda", "Tasas actualizadas");
}



// Convierte desde GTQ a la moneda actual
double Moneda::convertirDesdeGtq(double cantidad) {
    if (moneda == "USD") return cantidad * tasaUSD;
    else if (moneda == "EUR") return cantidad * tasaEUR;
    return cantidad;
}

