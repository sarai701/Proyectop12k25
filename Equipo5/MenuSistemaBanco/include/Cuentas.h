#ifndef CUENTAS_H
#define CUENTAS_H

#include <string>
#include "Bitacora.h"

class Cuentas {
private:
    std::string tipoCuentaSeleccionada;
    static Bitacora bitacoraCuentas;

public:
    Cuentas();

    void menuTipoCuenta(const std::string& bancoNombre);
    std::string getTipoCuenta() const;
};

#endif
