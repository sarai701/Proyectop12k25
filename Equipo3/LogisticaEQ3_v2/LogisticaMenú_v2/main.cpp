// 9959 24 11603 GE
#include <iostream>
#include <vector>
#include <string>
#include "usuarios.h"
#include "MenuPrincipal.h"
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
#include "Almacen.h"
#include "Administracion.h"
#include "transportistas.h"
#include "globals.h"

int main() {
    // Inicializar todas las listas necesarias para almacenar datos del sistema
    std::vector<Clientes> listaClientes;
    std::vector<Proveedor> listaProveedores;
    std::vector<Producto> listaProductos;
    std::vector<Almacen> listaAlmacenes;
    std::vector<Administracion> listaAdministradores;
    std::vector<Transportistas> listaTransportistas;

    // Cargar los datos previamente guardados desde archivos a sus respectivas listas
    Clientes::cargarDesdeArchivo(listaClientes);
    Almacen::cargarDesdeArchivo(listaAlmacenes);
    Administracion::cargarDesdeArchivo(listaAdministradores);
    Transportistas::cargarDesdeArchivo(listaTransportistas);
    Producto::cargarDesdeArchivoBin(listaProductos);
    Proveedor::cargarDesdeArchivo(listaProveedores);

    std::cout << "Datos cargados correctamente.\n";

    // Iniciar sistema de login (verifica si el usuario puede ingresar)
    if (usuarioRegistrado.loginUsuarios()) {
        std::cout << "Login exitoso.\n";
        // Si el login es exitoso, se muestra el menú principal con todas las listas necesarias
        MenuPrincipal::mostrar(
            listaClientes,
            listaProveedores,
            listaProductos,
            listaAlmacenes,
            listaAdministradores,
            listaTransportistas,
            usuarioRegistrado
        );
    } else {
        std::cout << "Login fallido. Saliendo del programa.\n";
    }

    // Mensaje de salida cuando el programa termina
    std::cout << "\n\t\t** Sistema de Logística - Hasta pronto **\n";

    // Guardar todos los datos actualizados en sus respectivos archivos antes de finalizar
    Clientes::guardarEnArchivo(listaClientes);
    Almacen::guardarEnArchivo(listaAlmacenes);
    Administracion::guardarEnArchivo(listaAdministradores);
    Transportistas::guardarEnArchivo(listaTransportistas);
    Producto::guardarEnArchivoBin(listaProductos);
    Proveedor::guardarEnArchivo(listaProveedores);

    // Pausa para ver mensajes antes de cerrar (solo Windows)
    system("pause");

    return 0;
}
