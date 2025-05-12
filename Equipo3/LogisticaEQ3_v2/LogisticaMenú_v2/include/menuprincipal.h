#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <vector>
#include "Clientes.h"
#include "Proveedor.h"
#include "Producto.h"
#include "Almacen.h"
#include "Administracion.h"
#include "transportistas.h"
#include "usuarios.h"

class MenuPrincipal {
public:
    static void mostrar(
        std::vector<Clientes>& clientes,
        std::vector<Proveedor>& proveedores,
        std::vector<Producto>& productos,
        std::vector<Almacen>& almacenes,
        std::vector<Administracion>& administradores,
        std::vector<Transportistas>& transportistas,
        usuarios& usuarioActual
    );
};

#endif // MENUPRINCIPAL_H
