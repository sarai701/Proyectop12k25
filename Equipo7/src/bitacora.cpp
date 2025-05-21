#include "bitacora.h"//MEILYN JULEISY GARCIA LIMA
#include <fstream>
#include <ctime>
#include <cstring>

void registrarEvento(const std::string& usuario, const std::string& evento) {
    std::ofstream archivo("bitacora.txt", std::ios::app);

    // Obtener hora actual
    std::time_t ahora = std::time(nullptr);
    char* tiempo = std::ctime(&ahora);
    tiempo[strcspn(tiempo, "\n")] = '\0'; // Eliminar salto de línea

    archivo << "[" << tiempo << "] Usuario: " << usuario << " - " << evento << "\n";
    archivo.close();
}
