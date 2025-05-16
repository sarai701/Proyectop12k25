#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>

struct Cliente {
    std::string id;
    std::string nombre;
    std::string telefono;
    std::string email;
};

void guardarClientes(const std::vector<Cliente>& clientes);
std::vector<Cliente> cargarClientes();
void ingresarCliente();
void consultarClientes();
void modificarCliente();
void borrarCliente();
std::string generarIdCliente();

#endif
