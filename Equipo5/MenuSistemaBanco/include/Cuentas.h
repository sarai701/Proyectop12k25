//Karla Patricia Ruiz Ordo�ez
#ifndef CUENTAS_H
#define CUENTAS_H

#include <string>
#include "Bitacora.h"

// Esta clase sirve para manejar los tipos de cuentas que puede tener un usuario
class Cuentas {
private:
    // Aqu� se guarda qu� tipo de cuenta eligi� el usuario (Monetaria, Ahorro, etc.)
    std::string tipoCuentaSeleccionada;

    // Bit�cora donde se registran los movimientos o elecciones que se hagan
    static Bitacora bitacoraCuentas;

public:
    // Constructor: inicializa el tipo de cuenta como "No configurada"
    Cuentas();

    // Muestra el men� donde el usuario puede elegir entre los tipos de cuenta
    void menuTipoCuenta(const std::string& bancoNombre);

    // Devuelve el tipo de cuenta que fue seleccionado
    std::string getTipoCuenta() const;
};

#endif
