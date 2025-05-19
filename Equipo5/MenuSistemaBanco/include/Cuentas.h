#ifndef CUENTAS_H // Verifica si CUENTAS_H no ha sido definido.
#define CUENTAS_H // Define CUENTAS_H para evitar inclusiones múltiples.

#include <string> // Incluye la biblioteca para manejar cadenas de texto.
#include "Bitacora.h" // Incluye el encabezado de la clase Bitacora.

class Cuentas { // Define la clase Cuentas.
private:
    std::string tipoCuentaSeleccionada; // Almacena el tipo de cuenta seleccionada.
    static Bitacora bitacoraCuentas; // Instancia estática de Bitacora para registrar acciones.

public:
    Cuentas(); // Constructor de la clase Cuentas.

    void menuTipoCuenta(const std::string& bancoNombre); // Método para mostrar el menú de tipos de cuenta.
    std::string getTipoCuenta() const; // Método para obtener el tipo de cuenta seleccionada.
};

#endif // Fin de la directiva de inclusión condicional.
