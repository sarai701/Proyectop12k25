#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>

class Cliente {
private:
    std::string id;
    std::string nombre;
    std::string telefono;
    std::string email;

public:
    // Constructores
    Cliente();
    Cliente(const std::string& id, const std::string& nombre,
            const std::string& telefono, const std::string& email);

    // Setters
    void setId(const std::string& id);
    void setNombre(const std::string& nombre);
    void setTelefono(const std::string& telefono);
    void setEmail(const std::string& email);

    // Getters
    std::string getId() const;
    std::string getNombre() const;
    std::string getTelefono() const;
    std::string getEmail() const;

    // Mostrar datos
    void mostrar() const;
};

// Funciones relacionadas con almacenamiento y operaciones de cliente
void guardarClientes(const std::vector<Cliente>& clientes);
std::vector<Cliente> cargarClientes();
void ingresarCliente();
void consultarClientes();
void modificarCliente();
void borrarCliente();
std::string generarIdCliente();

#endif
