#ifndef CUENTAS_H
#define CUENTAS_H

#include <string>

class Cuentas {
private:
    int tipoCuentaSeleccionada; // 1 = Monetaria, 2 = Ahorro

public:
    Cuentas();

    // Muestra el menú para seleccionar el tipo de cuenta
    void menuTipoCuenta();

    // Retorna el tipo seleccionado (1 o 2)
    int getTipoCuenta() const;

    // Limpia pantalla y pausa
    void limpiarPantalla();
    void pausar();
};

#endif
