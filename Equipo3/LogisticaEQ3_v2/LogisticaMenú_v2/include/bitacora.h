// LUIS ANGEL MENDEZ FUENTES 9959-24-6845
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <unordered_map>  // Necesario para std::unordered_map

class CodigosBitacora {
private:
    static std::unordered_map<std::string, int> rangos;
public:
    static int getCodigo(const std::string& modulo) {  // Cambiado a un solo parámetro
        // Asigna códigos incrementales dentro del rango del módulo
        if (rangos.find(modulo) == rangos.end()) {
            rangos[modulo] = 3000; // Inicializa el rango base según módulo
        }
        return rangos[modulo]++;
    }
};

// Inicialización de rangos (debe estar en el .cpp)
// std::unordered_map<std::string, int> CodigosBitacora::rangos = {
//     {"PEDIDOS", 3100}, {"ENVIOS", 3300}, {"INVENTARIO", 3200},
//     {"FACTURACION", 3350}, {"REPORTES", 3400}, {"USUARIOS", 3000}
// };

class bitacora {
public:
    // Método para registrar acciones (cambiar de static a método normal si es necesario)
    static void registrar(const std::string& usuario,
                        const std::string& modulo,
                        const std::string& descripcion);

    // Método alternativo para compatibilidad
    static void insertar(const std::string& usuario,
                       const std::string& modulo,
                       const std::string& descripcion) {
        registrar(usuario, modulo, descripcion);
    }

    // Método para generar backups
    static void generarBackup();

    // Método para mostrar la bitácora
    static void mostrarBitacora();

    // Método del menú de bitácora
    static void menuBitacora();

    // Método para reiniciar la bitácora
    static void reiniciarBitacora();

private:
    // Función interna para obtener fecha formateada
    static std::string obtenerFechaActual();
};

#endif // BITACORA_H
