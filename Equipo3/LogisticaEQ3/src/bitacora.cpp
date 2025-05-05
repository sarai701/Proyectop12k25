//LUIS ANGEL MENDEZ FUENTES 9959-24-6845
// MAYO 2025
#include "bitacora.h"  // Inclusión del encabezado que declara la clase bitacora
#include <iostream>    // Librería para entrada y salida estándar
#include <iomanip>     // Librería para manipulación de formato (como setw)

using namespace std;   // Uso del espacio de nombres estándar para evitar el uso de std::

// Método para insertar un registro en la bitácora
void bitacora::insertar(string usuario, string codigo, string accion) {
    // Abre el archivo bitacora.txt en modo de añadir al final (append)
    ofstream file("bitacora.txt", ios::app);
    if (file.is_open()) {
        // Escribe en el archivo el usuario, el código y la acción con formato fijo
        file << left << setw(20) << usuario    // Campo de 20 caracteres alineado a la izquierda
             << setw(10) << codigo             // Campo de 10 caracteres
             << setw(15) << accion << endl;    // Campo de 15 caracteres y salto de línea
        file.close();  // Cierra el archivo después de escribir
    } else {
        // Mensaje de error si no se pudo abrir el archivo
        cerr << "\n\t\tError al abrir la bitácora!";
    }
}

// Método para mostrar el contenido de la bitácora en pantalla
void bitacora::desplegar() {
    system("cls");  // Limpia la pantalla (solo en sistemas Windows)

    ifstream file("bitacora.txt");  // Abre el archivo para lectura

    // Encabezado decorativo de la bitácora
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRO DE BITACORA - LOGISTICA     |" << endl;
    cout << "\t\t========================================" << endl;

    if (file.is_open()) {
        string linea;
        while (getline(file, linea)) {
            // Muestra cada línea del archivo con sangría
            cout << "\t\t" << linea << endl;
        }
        file.close();  // Cierra el archivo después de la lectura
    } else {
        // Si el archivo no existe o no se pudo abrir, muestra este mensaje
        cout << "\t\tNo hay registros en la bitácora." << endl;
    }

    // Pie del marco
    cout << "\t\t========================================" << endl;
    system("pause");  // Pausa la ejecución hasta que el usuario presione una tecla
}

// Método que muestra el menú de opciones de la bitácora
void bitacora::menuBitacora() {
    int opcion;  // Variable para almacenar la opción del usuario

    do {
        system("cls");  // Limpia la pantalla antes de mostrar el menú

        // Menú principal de la bitácora
        cout << "\t\t========================================" << endl;
        cout << "\t\t| ADMINISTRACION DE BITACORA           |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Ver registros" << endl;
        cout << "\t\t 2. Exportar a archivo" << endl;
        cout << "\t\t 3. Volver" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion: ";
        cin >> opcion;  // Se lee la opción ingresada por el usuario

        switch(opcion) {
            case 1:
                desplegar();  // Muestra los registros
                break;
            case 2:
                // Este caso está aún sin implementar
                cout << "\n\t\t[Exportando bitácora...]" << endl;
                system("pause");
                break;
            case 3:
                // Vuelve al menú anterior o finaliza el ciclo
                break;
            default:
                // Si la opción no es válida, se notifica al usuario
                cout << "\n\t\tOpcion invalida!";
                cin.get(); // Espera entrada para evitar que se salte la pausa
        }
    } while(opcion != 3);  // Repite hasta que el usuario seleccione la opción 3 (Volver)
}
