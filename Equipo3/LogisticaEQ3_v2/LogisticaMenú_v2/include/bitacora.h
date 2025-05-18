#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <unordered_map>

/**
 * Estructura que representa un registro en la bitácora.
 */
struct RegistroBitacora {
    int id_accion;
    char usuario[30];
    char modulo[30];
    char descripcion[100];
    char fecha_hora[20];
};

/**
 * Clase encargada de manejar los códigos únicos para cada módulo en la bitácora.
 */
class CodigosBitacora {
private:
    static std::unordered_map<std::string, int> rangos;

public:
    static int getCodigo(const std::string& modulo);
};

/**
 * Clase encargada de registrar y administrar acciones del sistema en una bitácora binaria.
 */
class bitacora {
public:
    static void registrar(const std::string& usuario, const std::string& modulo, const std::string& descripcion);

    static void insertar(const std::string& usuario, const std::string& modulo, const std::string& descripcion) {
        registrar(usuario, modulo, descripcion);
    }

    static void mostrarBitacora();
    static void generarBackup();
    static void reiniciarBitacora();
    static void buscarPorNombreUsuario();
    static void buscarPorFecha();
    static void menuBitacora();

private:
    static std::string obtenerFechaActual();
};

#endif // BITACORA_H
