//Jonathan Samuel Gonzalez
#ifndef BANCOS_H
#define BANCOS_H

#include <string>         // Para el uso de std::string
#include "Bitacora.h"     // Para registrar las acciones realizadas
#include "Moneda.h"       // Para manejar la configuración de moneda

using namespace std;      // Evita tener que escribir std:: antes de string, cout, etc.

// Clase que gestiona la configuración bancaria del sistema
class Bancos {
private:
    string usuario;//bitacora
        // Objeto de bitácora para registrar acciones del módulo Bancos

    string bancoSeleccionado;           // Nombre del banco seleccionado
    string tipoCuentaSeleccionada;      // Tipo de cuenta seleccionada (Corriente o Ahorro)
    string monedaSeleccionada;          // Tipo de moneda seleccionada (GTQ, USD, EUR)

    // Métodos internos para los distintos menús de selección
    void menuSeleccionBanco();          // Menú para seleccionar banco
    void menuTipoCuenta();              // Menú para seleccionar tipo de cuenta
    void menuTipoMoneda();              // Menú para seleccionar tipo de moneda

public:
    void setUsuario(const string& u);//bitacora
    Bancos();                           // Constructor

    void menuConfiguracion();           // Menú principal de configuración bancaria
    void mostrarConfiguracion();        // Muestra la configuración actual al usuario

    static void limpiarPantalla();      // Limpia la consola
    static void pausar();               // Pausa la ejecución esperando ENTER

    // Métodos para obtener los valores seleccionados
    string getBanco() const;            // Devuelve el banco seleccionado
    string getCuenta() const;           // Devuelve el tipo de cuenta seleccionada
    string getMoneda() const;           // Devuelve la moneda seleccionada
};

#endif
