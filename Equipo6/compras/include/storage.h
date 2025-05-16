#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "compras.h"

class Storage {
public:
    // Usuarios
    static bool userExists(const std::string& user);
    static void saveUser(const std::string& user, const std::string& passHash);
    static std::string getUserPassword(const std::string& user);

    // Productos
    static std::vector<Producto> loadProducts();
    static void saveProducts(const std::vector<Producto>& prods);

private:
    static const std::string USER_FILE;
    static const std::string PRODUCTS_FILE;
};

#endif // STORAGE_H
