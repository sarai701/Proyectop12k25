//Programaddo por Boris Ivan de Leon Santos 9959-24-6203
#ifndef PROVEEDORES_H
#define PROVEEDORES_H

#include <string>
#include <vector>

using namespace std;
class Proveedor {
private:
    vector<Proveedor> proveedores; // Lista de proveedores en memoria
    void cargarProveedores();           // Carga desde proveedores.txt
    void guardarProveedores();          // Guarda toda la lista en proveedores.txt
    void ordenarProveedores();          // Ordena alfabéticamente por nombre

public:
    string codigo;                 // Código del proveedor
    string nombre;                 // Nombre del proveedor
    string telefono;               // Teléfono del proveedor
    string direccion;              // Dirección del proveedor

    void menuProveedor();               // Muestra el menú de opciones para proveedores
    void crearProveedor();              // Crea un nuevo proveedor
    void borrarProveedor();             // Borra un proveedor por código
    void buscarProveedor();             // Busca un proveedor por código
    void modificarProveedor();          // Modifica un proveedor existente
    void desplegarProveedores();        // Muestra todos los proveedores

    void limpiarPantalla();             // Limpia la pantalla de la consola
    void pausar();                      // Pausa el programa hasta que se presione ENTER
};

#endif

