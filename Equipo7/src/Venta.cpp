#include "Venta.h"

// Constructor de la clase Venta
// Inicializa una venta con un cliente, un producto y una cantidad.
Venta::Venta(Cliente c, Producto p, int cant) : cliente(c), producto(p), cantidad(cant) {}
