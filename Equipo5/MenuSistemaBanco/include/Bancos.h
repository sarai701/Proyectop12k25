//Jonathan Samuel Gonzalez
#ifndef BANCOS_H
#define BANCOS_H

#include <string>

class Bancos {
public:
    Bancos();
    void menuConfiguracion(); // Men� de configuraci�n inicial
    void mostrarConfiguracion(); // Muestra la configuraci�n actual

    // Getters para acceder a las selecciones
    std::string getBanco() const;
    std::string getCuenta() const;
    std::string getMoneda() const;

private:
    void menuSeleccionBanco();
    void menuTipoCuenta();
    void menuTipoMoneda();
    void limpiarPantalla();
    void pausar();

    std::string bancoSeleccionado;
    std::string tipoCuentaSeleccionada;
    std::string monedaSeleccionada;
};

#endif
