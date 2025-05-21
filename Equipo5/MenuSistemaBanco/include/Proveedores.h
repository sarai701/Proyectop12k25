// Boris de León 9959-24-6203
#ifndef PROVEEDORES_H
#define PROVEEDORES_H

#include <string>
#include <vector>

using namespace std;

class Proveedor {
public:
    void setUsuario(const string& u);//bitacora

    string codigo;     // Código del proveedor
    string nombre;     // Nombre del proveedor
    string telefono;   // Teléfono del proveedor
    string direccion;  // Dirección del proveedor

    void menuProveedor();               // Muestra el menú de opciones para proveedores
    void crearProveedor();              // Crea un nuevo proveedor
    void borrarProveedor();             // Borra un proveedor por código
    void buscarProveedor();             // Busca un proveedor por código
    void modificarProveedor();          // Modifica un proveedor existente
    void desplegarProveedores();        // Muestra todos los proveedores

private:
    string usuario;//bitacora

    void limpiarPantalla();             // Limpia la pantalla de la consola
    void pausar();                      // Pausa el programa hasta que se presione ENTER

    vector<Proveedor> cargarProveedores();      // Carga proveedores desde archivo binario
    void guardarProveedores(const vector<Proveedor>& proveedores);  // Guarda proveedores en archivo binario
    void ordenarProveedores(vector<Proveedor>& proveedores);       // Ordena proveedores por nombre
};

#endif
