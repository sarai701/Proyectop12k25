#include <iostream>
#include "Usuario.h"
#include "Menu.h"
#include "Inventario.h"
#include "Facturacion.h"
using namespace std;

usuarios usuarioRegistrado;
Menu menu;

int main() {
    bool accesoUsuarios = usuarioRegistrado.loginUsuarios();

    if (accesoUsuarios) {
        Inventario inventario;  // Instanciar Inventario
        Facturacion factura;    // Instanciar Facturacion
        string nombreUsuario = usuarioRegistrado.getNombre();
        menu.mostrarOpciones(inventario, factura, nombreUsuario); // Llamar menú pasando los objetos
    }

    system("cls");
    cout << "* Hasta la próxima *" << endl;
    return 0;
}
