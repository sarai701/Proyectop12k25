// LUIS ANGEL MENDEZ FUENTES 9959-24-6845
#include "bitacora.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

// Inicialización de los rangos
std::unordered_map<std::string, int> CodigosBitacora::rangos = {
    {"AUTENTICACION", 3000}, {"USUARIOS", 3050}, {"PEDIDOS", 3100},
    {"CLIENTES", 3150}, {"PROVEEDORES", 3200}, {"PRODUCTOS", 3250},
    {"ALMACENES", 3300}, {"TRANSPORTISTAS", 3350}, {"FACTURACION", 3400},
    {"REPORTES", 3450}, {"INVENTARIO", 3500}, {"ENVIOS", 3550}
};

void bitacora::registrar(const std::string& usuario,
                         const std::string& modulo,
                         const std::string& descripcion) {
    std::ifstream check("bitacora.txt");
    bool isEmpty = check.peek() == std::ifstream::traits_type::eof();
    check.close();

    std::ofstream file("bitacora.txt", std::ios::app);
    int codigo = CodigosBitacora::getCodigo(modulo);

    std::time_t now = std::time(nullptr);
    char fecha[100];
    std::strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", std::localtime(&now));

    if (file.is_open()) {
        if (isEmpty) {
            file << "-------------------------- BITÁCORA DEL SISTEMA --------------------------\n";
            file << std::left
                 << std::setw(12) << "ID_ACCION"
                 << std::setw(15) << "USUARIO"
                 << std::setw(20) << "MODULO"
                 << std::setw(35) << "DESCRIPCION"
                 << std::setw(20) << "FECHA_HORA" << "\n";
            file << "---------------------------------------------------------------------------\n";
        }

        file << std::left
             << std::setw(12) << codigo
             << std::setw(15) << usuario
             << std::setw(20) << modulo
             << std::setw(35) << descripcion
             << std::setw(20) << fecha << "\n";
    }
}

std::string bitacora::obtenerFechaActual() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

void bitacora::mostrarBitacora() {
    system("cls");
    std::ifstream file("bitacora.txt");

    std::cout << "\t\t========================================================\n";
    std::cout << "\t\t|                      BITÁCORA                        |\n";
    std::cout << "\t\t========================================================\n";
    std::cout << "\t\t" << std::left
              << std::setw(10) << "CÓDIGO"
              << std::setw(15) << "USUARIO"
              << std::setw(30) << "DESCRIPCIÓN"
              << std::setw(15) << "FECHA" << "\n";
    std::cout << "\t\t---------------------------------------------------------------\n";

    if (file.is_open()) {
        std::string linea;
        while (std::getline(file, linea)) {
            std::cout << "\t\t" << linea << "\n";
        }
        file.close();
    } else {
        std::cout << "\t\tNo hay registros en la bitácora.\n";
    }
    std::cout << "\t\t===============================================================\n";
    system("pause");
}

void bitacora::generarBackup() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << "backup_bitacora_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".txt";

    std::ifstream src("bitacora.txt", std::ios::binary);
    std::ofstream dst(oss.str(), std::ios::binary);

    if (src && dst) {
        dst << src.rdbuf();
        registrar("SISTEMA", "3106", "Backup de bitácora generado: " + oss.str());
        std::cout << "\n\t\tBackup generado exitosamente: " << oss.str() << "\n";
    } else {
        std::cerr << "\n\t\tError al generar backup!\n";
    }
}

void bitacora::reiniciarBitacora() {
    std::ofstream file("bitacora.txt", std::ios::trunc); // trunc = borra todo el contenido
    if (file.is_open()) {
        file.close();
        std::cout << "Bitácora reiniciada con éxito.\n";
    } else {
        std::cout << "Error al reiniciar la bitácora.\n";
    }
}

void bitacora::menuBitacora() {
    int opcion;
    do {
        system("cls");
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t|      ADMINISTRACIÓN DE BITÁCORA     |\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\t 1. Ver registros completos\n";
        std::cout << "\t\t 2. Generar backup\n";
        std::cout << "\t\t 3. Buscar por código de usuario\n";
        std::cout << "\t\t 4. Buscar por fecha\n";
        std::cout << "\t\t 5. Reiniciar bitácora\n"; // Nueva opción
        std::cout << "\t\t 6. Volver al menú principal\n";
        std::cout << "\t\t=======================================\n";
        std::cout << "\t\tOpción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: mostrarBitacora(); break;
            case 2: generarBackup(); break;
            case 3:
                // Implementar búsqueda por código
                break;
            case 4:
                // Implementar búsqueda por fecha
                break;
            case 5: reiniciarBitacora(); break; // Llamar a la función para reiniciar la bitácora
            case 6: break;
            default:
                std::cout << "\n\t\tOpción inválida!";
                std::cin.ignore();
                std::cin.get();
        }
    } while(opcion != 6);
}
