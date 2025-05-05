#include <iostream>
#include <fstream>

#include "usuarios.h"
#include "catalogos.h"
#include "procesos.h"

using namespace std;

void menuGeneral ();
void menuInicio();

//Objetos
usuarios usuariosrRegistrado;
Catalogos catalogo;

int main()
{
    menuInicio();

    system("cls");
    cout << "\n\t\tSALIENDO DEL SISTEMA...\n";
    return 0;
}

void menuInicio() {
    int opcion;
    bool accesoUsuarios;

    do {
        system("cls");
        cout << "\n\t\t-------------------------" << endl;
        cout << "\t\t   SISTEMA DE USUARIOS   " << endl;
        cout << "\t\t-------------------------" << endl << endl;
        cout << "\t\t1. Iniciar Sesión" << endl;
        cout << "\t\t2. Registrarse" << endl;
        cout << "\t\t3. Salir" << endl;
        cout << "\t\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer después de leer un número

        switch (opcion) {
            case 1:
                system("cls");
                accesoUsuarios = usuariosrRegistrado.loginUsuarios();
                if (accesoUsuarios) {
                    menuGeneral();
                    return; // Salir después de terminar el menú general
                }
                break;
            case 2:
                system("cls");
                usuariosrRegistrado.registrarUsuario();
                break;
            case 3:
                return; // Salir del programa
            default:
                cout << "\n\t\tOpción inválida. Intente de nuevo." << endl;
                system("pause");
        }
    } while (opcion != 3);
}

void menuGeneral(){
    int opciones;
    do{
        system("cls"); // Limpia la pantalla
        cout << "\n\n\t\tCuentas por Cobrar - Menu" << endl;
        cout << "\t\t------------------------" << endl;
        cout << "\t\t1. Menu de Catalogos" << endl;
        cout << "\t\t2. Menu de Procesos" << endl;
        cout << "\t\t3. Menu de Reportes" << endl;
        cout << "\t\t4. Menu de Configuracion" << endl;
        cout << "\t\t5. Salir" << endl;
        cout << "\n\t\tIngrese una opcion: ";
        cin >> opciones;

        switch (opciones) {
            case 1:
                catalogo.menuCatalogos();
                break;
            case 2:
                menuProcesos();
                break;
            case 3:
                //menuReportes();
                break;
            case 4:
                //menuConfiguracion();
                break;
            case 5:
                cout << "\n\n\t\tSaliendo del sistema...\n" << endl;
                break;
            default:
                cout << "n\t\tOpción no válida. Intente de nuevo" << endl;
        }
    } while (opciones != 5); // Repite el menú hasta que el usuario quiera salir

}
