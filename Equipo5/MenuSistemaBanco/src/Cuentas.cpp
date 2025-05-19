//Karla Patricia Ruiz Ordo�ez 9959-24-6859
#include "Cuentas.h"// Se incluye el archivo de cabecera donde se declara la clase Cuentas.
#include <iostream> // Se incluye la biblioteca est�ndar para entrada y salida de datos.

// Se define un objeto est�tico de la clase Bitacora asociado a Cuentas.
Bitacora Cuentas::bitacoraCuentas; // Este objeto se usar� para registrar acciones relacionadas a cuentas.

using namespace std; // Se usa el espacio de nombres est�ndar para evitar el uso repetido de std::

// Constructor por defecto de la clase Cuentas.
Cuentas::Cuentas() { // Inicializa el atributo tipoCuentaSeleccionada con un valor predeterminado.
    tipoCuentaSeleccionada = "No configurada";
}

// M�todo que muestra un men� interactivo para seleccionar el tipo de cuenta.
void Cuentas::menuTipoCuenta(const std::string& bancoNombre) { // Recibe como par�metro el nombre del banco para mostrarlo en pantalla.
    int opcion;  // Variable para almacenar la opci�n seleccionada por el usuario.

    do {   // Bucle do-while para mostrar el men� hasta que se seleccione una opci�n v�lida.
        // Se muestra el encabezado del men�.
        cout << "\n===== TIPO DE CUENTA =====\n";
        cout << "--------------------------------------\n";
        cout << " Banco:    " << bancoNombre << "\n";  // Se muestra el nombre del banco.
        cout << "--------------------------------------\n";
        cout << "\n1. Cuenta Corriente";
        cout << "\n2. Cuenta de Ahorro";
        cout << "\nSeleccione una opci�n: ";

        // Se lee la opci�n ingresada por el usuario.
        cin >> opcion;

        // Se limpia el buffer del teclado para evitar problemas con entradas futuras.
        cin.ignore();

        // Se eval�a la opci�n seleccionada.
        switch (opcion) {
            case 1:
                tipoCuentaSeleccionada = "Corriente"; // Si se selecciona la opci�n 1, se asigna "Corriente" al atributo
                bitacoraCuentas.insertar("Admin", 4610, "Cuentas", "Cuenta Corriente seleccionada"); // y se registra en la bit�cora con c�digo 4610.
                return; // Se sale del m�todo despu�s de seleccionar.
            case 2:
                tipoCuentaSeleccionada = "Ahorro";  // Si se selecciona la opci�n 2, se asigna "Ahorro" al atributo
                bitacoraCuentas.insertar("Admin", 4611, "Cuentas", "Cuenta de Ahorro seleccionada"); // y se registra en la bit�cora con c�digo 4611.
                return; // Se sale del m�todo despu�s de seleccionar.
            default:
                // Si la opci�n no es v�lida, se muestra un mensaje de error.
                cout << "Opci�n inv�lida.\n";
                break;
        }
    } while (true); // El ciclo contin�a hasta que se seleccione una opci�n v�lida.
}

// M�todo getter para obtener el tipo de cuenta seleccionada.
// Devuelve una cadena con el nombre del tipo de cuenta.
std::string Cuentas::getTipoCuenta() const {
    return tipoCuentaSeleccionada;
}
