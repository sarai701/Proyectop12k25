// Maria Celeste Mayen Ibarra 9959-23-3775

#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <vector>
#include <string>
#include "Cliente.h"

// Clase que representa a un cliente dentro del sistema
class Cliente {
public:
    // Atributos públicos del cliente
    std::string nombre;     // Nombre del cliente
    std::string telefono;   // Número telefónico del cliente
    std::string nit;        // Número de Identificación Tributaria (NIT)
    std::string codigo;     // Código único del cliente

    // Constructor por defecto
    Cliente();

    // Constructor con parámetros para inicializar los datos del cliente
    Cliente(std::string n, std::string t, std::string nit, std::string cod);

    // Menú principal de opciones para gestionar clientes
    static void MenuClientes();

    // Función para agregar un nuevo cliente
    static void AgregarCliente();

    // Función para modificar los datos de un cliente existente
    static void ModificarCliente();

    // Función para eliminar un cliente del registro
    static void EliminarCliente();

    // Función para mostrar el listado completo de clientes
    static void MostrarClientes();

    // Retorna la lista completa de clientes registrados
    static std::vector<Cliente>& obtenerClientes();

private:
    // Lista estática que almacena todos los clientes registrados
    static std::vector<Cliente> clientes;

    // Contador estático utilizado para generar códigos únicos para los clientes
    static int contadorClientes;
};

#endif // CLIENTE_H
