#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"
#include "Vendedores.h"

class SistemaVentas {
private:
    std::vector<Cliente> clientes;
    std::vector<Producto> productos;
    std::vector<Vendedores> vendedores;

    void limpiarPantalla();
    Cliente* buscarCliente(const std::string& codigo);
    Vendedores* buscarVendedor(const std::string& codigo);




    std::vector<Venta> ventas;
    int contadorCodigoVenta = 300;

    // Funciones internas para persistencia
    void guardarVentaEnArchivo(const Venta& venta);
    void eliminarVentaEnArchivo(int codigoVenta); // ← Declarada aquí

public:
    void menuVenta();
    void nuevaVenta();
    void registroVenta();
    void EliminarVenta();
    void cargarVentasDesdeArchivo(); // ← MOVER AQUÍ

    Venta* obtenerVentaPorCodigo(int codigo);
    Cliente* obtenerClientePorCodigo(const std::string& codCliente);

};

#endif // SISTEMAVENTAS_H
