//Jonathan Samuel Gonzalez
#include "Moneda.h"
#include "Bitacora.h"
std::string Moneda::moneda = "GTQ"; // Valor por defecto: Quetzales

std::string Moneda::getSimbolo() {
    if (moneda == "USD") return "$";
    else if (moneda == "EUR") return "€";
    return "Q"; // Símbolo para Quetzales
}
