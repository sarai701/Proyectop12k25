#ifndef CUENTAS_H
#define CUENTAS_H

#include <iostream>
using namespace std;

class Cuentas {
private:
    string bancoSeleccionado;
public:
    void setBanco(string banco);
    void mostrarTipoCuenta();
    void mostrarTipoMoneda(string tipoCuenta);
};

#endif
