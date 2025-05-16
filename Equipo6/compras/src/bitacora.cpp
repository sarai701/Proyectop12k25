#include "bitacora.h"
#include <fstream>
#include <ctime>
#include <iostream>

void Bitacora::registrarEvento(const std::string& usuario, const std::string& accion) {
    std::ofstream archivo("bitacora.txt", std::ios::app);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de bitacora." << std::endl;
        return;
    }

    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);

    archivo << "[" << (tiempoLocal->tm_year + 1900) << "-"
            << (tiempoLocal->tm_mon + 1) << "-"
            << tiempoLocal->tm_mday << " "
            << tiempoLocal->tm_hour << ":"
            << tiempoLocal->tm_min << ":"
            << tiempoLocal->tm_sec << "] "
            << accion << " usuario: " << usuario << std::endl;

    archivo.close();
}
