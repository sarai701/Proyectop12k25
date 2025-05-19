//STEVEN ANDRE VASQUEZ CHAVEZ 9959 24 11528

#ifndef SISTEMAVENTAS_H
#define SISTEMAVENTAS_H

#include <vector>
#include <string>
#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"
#include "Vendedores.h"

// Clase que representa el sistema de ventas, gestionando clientes, productos, vendedores y ventas.
class SistemaVentas {
private:
    // Vectores que almacenan los registros de clientes, productos y vendedores.
    std::vector<Cliente> clientes;      // Lista de clientes registrados.
    std::vector<Producto> productos;    // Lista de productos disponibles para la venta.
    std::vector<Vendedores> vendedores; // Lista de vendedores registrados.

    // Funciones privadas para gestionar la interacción con el sistema
    void limpiarPantalla(); // Limpia la pantalla de la terminal.
    Cliente* buscarCliente(const std::string& codigo); // Busca un cliente por su código.
    Vendedores* buscarVendedor(const std::string& codigo); // Busca un vendedor por su código.

    // Vectores y variables internas para el manejo de ventas.
    std::vector<Venta> ventas;         // Lista de ventas realizadas.
    int contadorCodigoVenta = 300;     // Contador para generar el código de ventas a partir de 300.

    // Funciones internas para la persistencia de datos.
    void guardarVentaEnArchivo(const Venta& venta); // Guarda una venta en un archivo.
    void cargarVentasDesdeArchivo(); // Carga las ventas previamente guardadas desde un archivo.
    void eliminarVentaEnArchivo(int codigoVenta); // Elimina una venta de un archivo por su código.

public:
    // Funciones públicas disponibles para el sistema de ventas.

    // Menú principal de ventas donde se puede gestionar el flujo de ventas.
    void menuVenta();

    // Función que permite realizar una nueva venta en el sistema.
    void nuevaVenta();

    // Función para registrar una venta ya realizada.
    void registroVenta();

    // Función que permite eliminar una venta por su código.
    void EliminarVenta();

    // Funciones públicas para obtener datos específicos de una venta o cliente.
    Venta* obtenerVentaPorCodigo(int codigo); // Obtiene una venta por su código.
    Cliente* obtenerClientePorCodigo(const std::string& codCliente); // Obtiene un cliente por su código.

};

#endif // SISTEMAVENTAS_H

