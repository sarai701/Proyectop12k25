#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <unordered_map>  // Necesario para usar std::unordered_map

/**
 * Clase encargada de manejar los códigos únicos para cada módulo en la bitácora.
 */
class CodigosBitacora {
private:
    // Mapa que contiene los rangos base de códigos por módulo
    static std::unordered_map<std::string, int> rangos;

public:
    /**
     * Devuelve un código único para cada acción según el módulo.
     * Si el módulo no existe en el mapa, se inicializa en 3000.
     * @param modulo Nombre del módulo (ej. "USUARIOS", "PEDIDOS", etc.)
     * @return Código único para la bitácora.
     */
    static int getCodigo(const std::string& modulo);
};

/**
 * Clase encargada de registrar y administrar acciones del sistema en una bitácora.
 */
class bitacora {
public:
    /**
     * Registra una acción en la bitácora con los datos del usuario, módulo y descripción.
     * @param usuario Nombre o ID del usuario que realiza la acción.
     * @param modulo Módulo del sistema (ej. "USUARIOS", "PRODUCTOS", etc.).
     * @param descripcion Descripción de la acción realizada.
     */
    static void registrar(const std::string& usuario, const std::string& modulo, const std::string& descripcion);

    /**
     * Alias del método registrar. Permite registrar acciones de forma más intuitiva en algunos contextos.
     */
    static void insertar(const std::string& usuario, const std::string& modulo, const std::string& descripcion) {
        registrar(usuario, modulo, descripcion);
    }

    /**
     * Muestra el contenido actual del archivo de bitácora en consola.
     */
    static void mostrarBitacora();

    /**
     * Crea una copia de seguridad de la bitácora con nombre basado en la fecha y hora actual.
     */
    static void generarBackup();

    /**
     * Borra todo el contenido del archivo de bitácora.
     */
    static void reiniciarBitacora();

    /**
     * Busca registros en la bitácora por nombre o ID de usuario.
     */
    static void buscarPorCodigoUsuario();

    /**
     * Busca registros en la bitácora por fecha específica (formato DD/MM/AAAA).
     */
    static void buscarPorFecha();

    /**
     * Muestra el menú interactivo para administrar la bitácora desde la consola.
     */
    static void menuBitacora();

private:
    /**
     * Obtiene la fecha actual en formato DD/MM/AAAA.
     * @return Cadena con la fecha actual.
     */
    static std::string obtenerFechaActual();
};

#endif // BITACORA_H
