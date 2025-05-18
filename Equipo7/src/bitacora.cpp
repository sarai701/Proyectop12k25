#include "bitacora.h"//MEILYN JULEISY GARCIA LIMA
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>

void registrarEvento(const std::string& usuario, const std::string& evento) {
    std::ofstream archivo("bitacora.bin", std::ios::binary | std::ios::app);
    if (!archivo) return;

    // Obtener hora actual
    time_t now = time(0);
    std::string timestamp = std::string(ctime(&now));
    timestamp.pop_back(); // quitar salto de línea

    // Construir mensaje completo
    std::string mensaje = usuario + " [" + timestamp + "]: " + evento;

    // Escribir la longitud + contenido
    size_t longitud = mensaje.size();
    archivo.write(reinterpret_cast<char*>(&longitud), sizeof(longitud));
    archivo.write(mensaje.c_str(), longitud);
}
