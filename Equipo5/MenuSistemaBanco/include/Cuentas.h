#ifndef CUENTAS_H             // Verifica si CUENTAS_H no ha sido definido
#define CUENTAS_H             // Define CUENTAS_H para evitar inclusiones múltiples

#include <string>             // Incluye la biblioteca estándar de cadenas
#include "Bitacora.h"        // Incluye el encabezado de la clase Bitacora

// Clase que gestiona las cuentas bancarias
class Cuentas {
private:
    std::string tipoCuentaSeleccionada; // Almacena el tipo de cuenta seleccionada
    static Bitacora bitacoraCuentas;    // Instancia estática de la bitácora para registrar acciones

public:
    Cuentas();                          // Constructor de la clase Cuentas

    // Muestra el menú para seleccionar el tipo de cuenta
    void menuTipoCuenta(const std::string& bancoNombre);

    // Devuelve el tipo de cuenta seleccionada
    std::string getTipoCuenta() const; // Método constante que devuelve el tipo de cuenta
};

#endif // CUENTAS_H                 // Fin de la protección de inclusión
