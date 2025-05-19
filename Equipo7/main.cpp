#include <iostream>
#include "SistemaVentas.h"
#include "Login.h"
#include "bitacora.h"
#include "Cliente.h"
#include "Facturacion.h"
#include "Producto.h"
#include "vendedores.h"
#include "venta.h"

using namespace std;


string usuarioActual; // Para guardar el nombre del usuario bitacora

void mostrarMenuPrincipal();
void MenuCatalogo();
void MenuProcesos();

int main() {
    int opcion;
    bool accesoPermitido = false;

    do {

        system ("cls");
        cout << "\n--- Bienvenido al Sistema ---\n";
        cout << "1. Iniciar Sesion\n";
        cout << "2. Registrarse\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Para evitar errores con getline

        switch (opcion) {
            case 1:
                accesoPermitido = iniciarSesion(usuarioActual);
                break;
            case 2:
                registrarUsuario();
                break;
            case 3:
                cout << "\n\nSaliendo del sistema...\n";
                return 0;
            default:
                cout << "Opci n invalida.\n";
        }
    } while (!accesoPermitido);

    mostrarMenuPrincipal();
     registrarEvento(usuarioActual, "Cerr  sesi n desde men  principal");
    return 0;
}




void mostrarMenuPrincipal() {
    int opcion;
    do {
        system ("cls");
        cout << "n\t\t\t|------------------------ \n" ;
        cout << "\t\t\t|     MENU PRINCIPAL     | \n";
        cout << "\t\t\t|------------------------- \n" ;
        cout << "\t\t\t|1. Archivo\n";
        cout << "\t\t\t|2. Catalogos\n";
        cout << "\t\t\t|3. Procesos\n";
        cout << "\t\t\t|4. Informes\n";
        cout << "\t\t\t|5. Salir del sistema\n";
        cout << "\t\t\t|Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarEvento(usuarioActual, "Entro a la opcion Archivo");
                cout << "Archivo (sin funciones aun).\n";
                break;
            case 2:
                registrarEvento(usuarioActual, "Entro a la opcion Catalogos");
                MenuCatalogo();
                break;
            case 3:
                registrarEvento(usuarioActual, "Entro a la opcion Procesos");
                MenuProcesos();
                break;
            case 4:
                registrarEvento(usuarioActual, "Entro a la opcion Informes");
                break;
            case 5:
                registrarEvento(usuarioActual, "Salio del menu general");
                cout << "Cerrando sesion...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}

void MenuProcesos() {
    SistemaVentas sistemaVentas;
    int opcion;
    do {
        system ("cls");
        cout << "n\t\t\t|------------------------- \n" ;
        cout << "\t\t\t|      MENU PROCESOS     | \n";
        cout << "\t\t\t|------------------------- \n" ;
        cout << "\t\t\t|1. CLIENTES \n";
        cout << "\t\t\t|2. VENDEDORES\n";
        cout << "\t\t\t|3. PRODUCTOS\n";
        cout << "\t\t\t|4. VENTAS\n";
        cout << "\t\t\t|5. FACTURACION\n";
        cout << "\t\t\t|6. REGRESAR AL MENU PRINCIPAL\n";
        cout << "\t\t\t| Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarEvento(usuarioActual, "Entro a la opcion CLIENTES");
                {
                    Cliente Cliente;
                    Cliente.MenuClientes();
                }
                break;
            case 2:
                registrarEvento(usuarioActual, "Entro a la opcion VENDEDORES");
                {
                    Vendedores Vendedores;
                    Vendedores.MenuVendedores();
                }
                break;
            case 3:
                registrarEvento(usuarioActual, "Entro a la opcion PRODUCTOS");
                {
                    Producto Producto;
                    Producto.MenuProducto();
                }
                break;
            case 4:
                registrarEvento(usuarioActual, "Entro a la opcion VENTAS");
                {
                    SistemaVentas SistemaVentas;
                    SistemaVentas.menuVenta();
                }
                break;
            case 5:
                registrarEvento(usuarioActual, "Entro a la opcion FACTURACION");
                {
                    Facturacion Facturacion;
                    Facturacion.menuFacturacion(sistemaVentas);
                }
                break;
            case 6:
                registrarEvento(usuarioActual, "Salio del menu de catalogos");
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);
}

void MenuCatalogo() {
    SistemaVentas sistema;
    int opcion;
    do {
        system ("cls");
        cout << "n\t\t\t|--------------------------- \n" ;
        cout << "\t\t\t|      MENU CATALOGOS      | \n";
        cout << "\t\t\t|--------------------------- \n" ;
        cout << "\t\t\t|1. REGISTRO CLIENTES \n";
        cout << "\t\t\t|2. REGISTRO VENDEDORES\n";
        cout << "\t\t\t|3. REGISTRO PRODUCTOS\n";
        cout << "\t\t\t|4. REGISTRO VENTAS\n";
        cout << "\t\t\t|5. REGRESAR AL MENU PRINCIPAL\n";
        cout << "\t\t\t| Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarEvento(usuarioActual, "Entro a la opcion REGISTRO CLIENTES");
                {
                    Cliente Cliente;
                    Cliente.MostrarClientes();
                }
                break;
            case 2:
                registrarEvento(usuarioActual, "Entro a la opcion REGISTRO VENDEDORES");
                {
                    Vendedores Vendedores;
                    Vendedores.MostrarVendedores();
                }
                break;
            case 3:
                registrarEvento(usuarioActual, "Entro a la opcion REGISTRO PRODUCTOS");
                {

                    Producto Producto;
                    Producto.MostrarProductos();
                }
                break;
            case 4:
                registrarEvento(usuarioActual, "Entro a la opcion  REGISTRO VENTAS");
                {
                    SistemaVentas SistemaVentas;
                    SistemaVentas.registroVenta();
                }
                break;
            case 5:
                registrarEvento(usuarioActual, "Salio del menu de procesos");
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}
