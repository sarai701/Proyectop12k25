//Karla Patricia Ruiz Ordoñez
#ifndef CUENTAS_H
#define CUENTAS_H

#include <string>
#include "Bitacora.h"

// Esta clase sirve para manejar los tipos de cuentas que puede tener un usuario
class Cuentas {
private:
    // Aquí se guarda qué tipo de cuenta eligió el usuario (Monetaria, Ahorro, etc.)
    std::string tipoCuentaSeleccionada;

    // Bitácora donde se registran los movimientos o elecciones que se hagan
    static Bitacora bitacoraCuentas;

public:
    // Constructor: inicializa el tipo de cuenta como "No configurada"
    Cuentas();

    // Muestra el menú donde el usuario puede elegir entre los tipos de cuenta
    void menuTipoCuenta(const std::string& bancoNombre);

    // Devuelve el tipo de cuenta que fue seleccionado
    std::string getTipoCuenta() const;
};

#endif
