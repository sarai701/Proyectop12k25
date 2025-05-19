//Karla Patricia Ruiz Ordoñez 9959-24-6859
#include "Cuentas.h"// Se incluye el archivo de cabecera donde se declara la clase Cuentas.
#include <iostream> // Se incluye la biblioteca estándar para entrada y salida de datos.

// Se define un objeto estático de la clase Bitacora asociado a Cuentas.
Bitacora Cuentas::bitacoraCuentas; // Este objeto se usará para registrar acciones relacionadas a cuentas.

using namespace std; // Se usa el espacio de nombres estándar para evitar el uso repetido de std::

// Constructor por defecto de la clase Cuentas.
Cuentas::Cuentas() { // Inicializa el atributo tipoCuentaSeleccionada con un valor predeterminado.
    tipoCuentaSeleccionada = "No configurada";
}

// Método que muestra un menú interactivo para seleccionar el tipo de cuenta.
void Cuentas::menuTipoCuenta(const std::string& bancoNombre) { // Recibe como parámetro el nombre del banco para mostrarlo en pantalla.
    int opcion;  // Variable para almacenar la opción seleccionada por el usuario.

    do {   // Bucle do-while para mostrar el menú hasta que se seleccione una opción válida.
        // Se muestra el encabezado del menú.
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n";  // Se muestra el nombre del banco.
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Corriente";
        cout << "\n2. Cuenta de Ahorro";
        cout << "\nSeleccione una opción: ";

        // Se lee la opción ingresada por el usuario.
        cin >> opcion;

        // Se limpia el buffer del teclado para evitar problemas con entradas futuras.
        cin.ignore();

        // Se evalúa la opción seleccionada.
        switch (opcion) {
            case 1:
                tipoCuentaSeleccionada = "Corriente"; // Si se selecciona la opción 1, se asigna "Corriente" al atributo
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Cuenta Corriente seleccionada"); // y se registra en la bitácora con código 4610.
                return; // Se sale del método después de seleccionar.
            case 2:
                tipoCuentaSeleccionada = "Ahorro";  // Si se selecciona la opción 2, se asigna "Ahorro" al atributo
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Cuenta de Ahorro seleccionada"); // y se registra en la bitácora con código 4611.
                return; // Se sale del método después de seleccionar.
            default:
                // Si la opción no es válida, se muestra un mensaje de error.
                cout << "Opción inválida.\n";
                break;
        }
    } while (true); // El ciclo continúa hasta que se seleccione una opción válida.
}

// Método getter para obtener el tipo de cuenta seleccionada.
// Devuelve una cadena con el nombre del tipo de cuenta.
std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada;
}
