//STEVEN ANDRE VASQUEZ CHAVEZ 9959 24 11528

#ifndef VENDEDORES_H
#define VENDEDORES_H

#include <iostream>
#include <vector>
#include <string>

class Vendedores {
public:
    std::string nombre;
    std::string telefono;
    std::string codigo;

    Vendedores(); // Constructor vacío
    Vendedores(std::string n, std::string t, std::string cod);

    static void MenuVendedores();
    static void AgregarVendedor();
    static void ModificarVendedor();
    static void EliminarVendedor();
    static void MostrarVendedores();
    static std::vector<Vendedores>& obtenerVendedores(); // Nuevo método


private:
    static std::vector<Vendedores> vendedores;
    static int contadorVendedores;
};

#endif // VENDEDORES_H
