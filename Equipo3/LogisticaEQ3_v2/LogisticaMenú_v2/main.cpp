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
    std::cout << "Inicio del programa..." << std::endl;

    // Inicializar todas las listas necesarias para almacenar datos del sistema
    std::vector<Clientes> listaClientes;
    std::vector<Proveedor> listaProveedores;
    std::vector<Producto> listaProductos;
    std::vector<Almacen> listaAlmacenes;
    std::vector<Administracion> listaAdministradores;
    std::vector<Transportistas> listaTransportistas;

    // Cargar los datos previamente guardados desde archivos a sus respectivas listas
    std::cout << "Cargando clientes..." << std::endl;
    Clientes::cargarDesdeArchivo(listaClientes);

    std::cout << "Cargando almacenes..." << std::endl;
    Almacen::cargarDesdeArchivo(listaAlmacenes);

    std::cout << "Cargando administradores..." << std::endl;
    Administracion::cargarDesdeArchivo(listaAdministradores);

    std::cout << "Cargando transportistas..." << std::endl;
    Transportistas::cargarDesdeArchivo(listaTransportistas);

    std::cout << "Cargando productos..." << std::endl;
    Producto::cargarDesdeArchivoBin(listaProductos);

    std::cout << "Cargando proveedores..." << std::endl;
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
    std::cout << "Guardando clientes..." << std::endl;
    Clientes::guardarEnArchivo(listaClientes);

    std::cout << "Guardando almacenes..." << std::endl;
    Almacen::guardarEnArchivo(listaAlmacenes);

    std::cout << "Guardando administradores..." << std::endl;
    Administracion::guardarEnArchivo(listaAdministradores);

    std::cout << "Guardando transportistas..." << std::endl;
    Transportistas::guardarEnArchivo(listaTransportistas);

    std::cout << "Guardando productos..." << std::endl;
    Producto::guardarEnArchivoBin(listaProductos);

    std::cout << "Guardando proveedores..." << std::endl;
    Proveedor::guardarEnArchivo(listaProveedores);

    // Pausa para ver mensajes antes de cerrar (solo Windows)
    system("pause");

    return 0;
}
