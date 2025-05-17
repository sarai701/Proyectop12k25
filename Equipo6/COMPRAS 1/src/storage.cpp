#include "storage.h"
#include <fstream>
#include <sstream>

const std::string Storage::USER_FILE = "users.dat";
const std::string Storage::PRODUCTS_FILE = "products.dat";

bool Storage::userExists(const std::string& user) {
    std::ifstream file(USER_FILE);
    std::string line;

    while(std::getline(file, line)) {
        size_t pos = line.find(':');
        if(pos != std::string::npos && line.substr(0, pos) == user) {
            return true;
        }
    }
    return false;
}

void Storage::saveUser(const std::string& user, const std::string& passHash) {
    std::ofstream file(USER_FILE, std::ios::app);
    file << user << ":" << passHash << "\n";
}

std::string Storage::getUserPassword(const std::string& user) {
    std::ifstream file(USER_FILE);
    std::string line;

    while(std::getline(file, line)) {
        size_t pos = line.find(':');
        if(pos != std::string::npos && line.substr(0, pos) == user) {
            return line.substr(pos + 1);
        }
    }
    return "";
}

std::vector<Producto> Storage::loadProducts() {
    std::vector<Producto> productos;
    std::ifstream file(PRODUCTS_FILE);
    std::string line;

    while(std::getline(file, line)) {
        std::stringstream ss(line);
        Producto p;
        std::getline(ss, p.nombre, '|');
        std::getline(ss, p.proveedor, '|');
        ss >> p.precio;
        ss.ignore();
        ss >> p.cantidad;
        ss.ignore();
        std::getline(ss, p.fecha);

        productos.push_back(p);
    }

    return productos;
}

void Storage::saveProducts(const std::vector<Producto>& prods) {
    std::ofstream file(PRODUCTS_FILE);

    for(const auto& p : prods) {
        file << p.nombre << "|" << p.proveedor << "|"
             << p.precio << "|" << p.cantidad << "|" << p.fecha << "\n";
    }
}
