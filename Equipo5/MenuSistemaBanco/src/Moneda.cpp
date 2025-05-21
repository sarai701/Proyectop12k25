//Jonathan Samuel Gonzalez
#include "Moneda.h"      // Incluye la definición de la clase Moneda
#include "Bitacora.h"    // Incluye la clase Bitacora para registrar eventos
#include <iostream>      // Librería para entrada y salida estándar (cout, etc.)

using namespace std;     // Permite usar std::string, std::cout, etc., sin prefijo

Bitacora Moneda::bitacoraMoneda;  // Inicializa el objeto estático Bitacora para registrar cambios de moneda

string Moneda::moneda = "GTQ";    // Moneda predeterminada del sistema (quetzal)
double Moneda::tasaUSD = 0.13;    // Tasa de conversión de 1 quetzal a dólares (ejemplo: 1 GTQ = 0.13 USD)
double Moneda::tasaEUR = 0.11;    // Tasa de conversión de 1 quetzal a euros (ejemplo: 1 GTQ = 0.11 EUR)

// Devuelve el símbolo correspondiente a la moneda actual
string Moneda::getSimbolo() {
    if (moneda == "USD") return "$";   // Dólar
    else if (moneda == "EUR") return "€"; // Euro
    return "Q";                         // Quetzal (por defecto)
}

// Convierte una cantidad desde la moneda actual a quetzales
double Moneda::convertirAGtq(double cantidad) {
    if (moneda == "USD") return cantidad / tasaUSD;  // Convierte de USD a GTQ
    else if (moneda == "EUR") return cantidad / tasaEUR; // Convierte de EUR a GTQ
    return cantidad;  // Si ya está en GTQ, no se modifica
}

// Actualiza las tasas de cambio de USD y EUR respecto al quetzal
void Moneda::actualizarTasas(double usd, double eur) {
    tasaUSD = usd;    // Asigna nueva tasa para USD
    tasaEUR = eur;    // Asigna nueva tasa para EUR
    bitacoraMoneda.insertar("Admin", 4501, "Moneda", "Tasas actualizadas"); // Registra el cambio en la bitácora
}

// Convierte una cantidad desde quetzales a la moneda seleccionada
double Moneda::convertirDesdeGtq(double cantidad) {
    if (moneda == "USD") return cantidad * tasaUSD;  // Convierte de GTQ a USD
    else if (moneda == "EUR") return cantidad * tasaEUR; // Convierte de GTQ a EUR
    return cantidad;  // Si la moneda es GTQ, no se modifica
}

// Muestra la moneda actual y su símbolo en consola
void Moneda::mostrarMoneda() {
    cout << "Moneda actual: " << moneda << " (" << getSimbolo() << ")\n";  // Ej: "Moneda actual: USD ($)"
}
