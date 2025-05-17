#include "aut.h"
#include "storage.h"
#include <string>
#include <functional>

AuthSystem::AuthSystem() : currentUser("") {}

std::string AuthSystem::hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

bool AuthSystem::validateUser(const std::string& user, const std::string& pass) {
    std::string storedHash = Storage::getUserPassword(user);
    if (storedHash.empty()) return false;

    return storedHash == hashPassword(pass);
}

bool AuthSystem::login(const std::string& user, const std::string& pass) {
    if (validateUser(user, pass)) {
        currentUser = user;
        return true;
    }
    return false;
}

bool AuthSystem::registerUser(const std::string& user, const std::string& pass) {
    if (Storage::userExists(user)) return false;

    Storage::saveUser(user, hashPassword(pass));
    return true;
}

void AuthSystem::logout() {
    currentUser = "";
}

bool AuthSystem::isLoggedIn() const {
    return !currentUser.empty();
}

std::string AuthSystem::getCurrentUser() const {
    return currentUser;
}
