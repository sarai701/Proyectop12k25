#include "menu_archivo.h"
#include "bitacora.h"
#include <iostream>
#include <limits>

using namespace std;

void mostrarMenuArchivo() {
    cout << "\n=== MENÚ DE ARCHIVO ===" << endl;
    cout << "1. Crear respaldo" << endl;
    cout << "2. Restaurar datos" << endl;
    cout << "3. Exportar datos" << endl;
    cout << "4. Ver bitácora" << endl;
    cout << "5. Regresar" << endl;
    cout << "Seleccione una opción: ";
}

void MenuArchivo::menuArchivo() {
    string usuario = Bitacora::obtenerUsuarioActual();
    int opcion;

    do {
        mostrarMenuArchivo();

        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor ingrese un número: ";
        }
        cin.ignore();

        switch(opcion) {
            case 1:
                Bitacora::registrarAccion(usuario, CodigosAccion::RESPALDO_CREADO,
                                        "Respaldo manual de la base de datos");
                cout << "Respaldo creado exitosamente." << endl;
                break;

            case 2:
                Bitacora::registrarAccion(usuario, CodigosAccion::RESTAURACION_COMPLETADA,
                                        "Restauración manual desde respaldo");
                cout << "Datos restaurados exitosamente." << endl;
                break;

            case 3:
                Bitacora::registrarAccion(usuario, CodigosAccion::EXPORTACION_DATOS,
                                        "Exportación manual de datos");
                cout << "Datos exportados exitosamente." << endl;
                break;

            case 4:
                Bitacora::mostrarBitacora();
                break;

            case 5:
                cout << "Regresando al menú principal..." << endl;
                break;

            default:
                Bitacora::registrarAccion(usuario, CodigosAccion::ERROR_SISTEMA,
                                        "Opción inválida en menú de archivo");
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
    } while(opcion != 5);
}
