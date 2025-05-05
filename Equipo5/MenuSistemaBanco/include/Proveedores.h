#ifndef PROVEEDORES_H
#define PROVEEDORES_H

#include <string>
#include <vector>
#include "Bitacora.h"

using namespace std;
class Proveedor {
private:
    vector<Proveedor> proveedores; // Lista de proveedores en memoria
    void cargarProveedores();           // Carga desde proveedores.txt
    void guardarProveedores();          // Guarda toda la lista en proveedores.txt
    void ordenarProveedores();          // Ordena alfab�ticamente por nombre

public:
    string codigo;                 // C�digo del proveedor
    string nombre;                 // Nombre del proveedor
    string telefono;               // Tel�fono del proveedor
    string direccion;              // Direcci�n del proveedor

    void menuProveedor();               // Muestra el men� de opciones para proveedores
    void crearProveedor();              // Crea un nuevo proveedor
    void borrarProveedor();             // Borra un proveedor por c�digo
    void buscarProveedor();             // Busca un proveedor por c�digo
    void modificarProveedor();          // Modifica un proveedor existente
    void desplegarProveedores();        // Muestra todos los proveedores

    void limpiarPantalla();             // Limpia la pantalla de la consola
    void pausar();                      // Pausa el programa hasta que se presione ENTER
};

#endif

