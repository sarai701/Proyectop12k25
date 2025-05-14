#ifndef AUT_H
#define AUT_H

#include <string>

class AuthSystem {
private:
    std::string currentUser;

    std::string hashPassword(const std::string& password);
    bool validateUser(const std::string& user, const std::string& pass);

public:
    AuthSystem();

    bool login(const std::string& user, const std::string& pass);
    bool registerUser(const std::string& user, const std::string& pass);
    void logout();
    bool isLoggedIn() const;
    std::string getCurrentUser() const;
};

#endif // AUTH_H
