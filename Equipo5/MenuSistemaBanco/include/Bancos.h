//Jonathan Samuel Gonzalez
#ifndef BANCOS_H
#define BANCOS_H

#include <string>
#include "Bitacora.h"
#include "Moneda.h"

class Bancos {
private:
    static Bitacora bitacoraBancos;

    std::string bancoSeleccionado;
    std::string tipoCuentaSeleccionada;
    std::string monedaSeleccionada;

    void menuSeleccionBanco();
    void menuTipoCuenta();
    void menuTipoMoneda();

public:
    Bancos();

    void menuConfiguracion();
    void mostrarConfiguracion();

    static void limpiarPantalla();
    static void pausar();

    std::string getBanco() const;
    std::string getCuenta() const;
    std::string getMoneda() const;
};

#endif
