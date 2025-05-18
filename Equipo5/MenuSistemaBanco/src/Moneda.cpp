//Jonathan Samuel Gonzalez
#include "Moneda.h"
#include "Bitacora.h"
#include <iostream>

Bitacora Moneda::bitacoraMoneda;

std::string Moneda::moneda = "GTQ";
double Moneda::tasaUSD = 0.13;
double Moneda::tasaEUR = 0.11;

std::string Moneda::getSimbolo() {
    if (moneda == "USD") return "$";
    else if (moneda == "EUR") return "€";
    return "Q";
}

double Moneda::convertirAGtq(double cantidad) {
    if (moneda == "USD") return cantidad / tasaUSD;
    else if (moneda == "EUR") return cantidad / tasaEUR;
    return cantidad;
}

void Moneda::actualizarTasas(double usd, double eur) {
    tasaUSD = usd;
    tasaEUR = eur;
    bitacoraMoneda.insertar("Admin", 4501, "Moneda", "Tasas actualizadas");
}

double Moneda::convertirDesdeGtq(double cantidad) {
    if (moneda == "USD") return cantidad * tasaUSD;
    else if (moneda == "EUR") return cantidad * tasaEUR;
    return cantidad;
}

void Moneda::mostrarMoneda() {
    std::cout << "Moneda actual: " << moneda << " (" << getSimbolo() << ")\n";
}

