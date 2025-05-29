#include <iostream>
#include <string>

class User {
private:
    std::string username;
    std::string password;
public:
    User(std::string username, std::string password) : username(username), password(password) {}
    std::string getUsername() { return username; }
    std::string getPassword() { return password; }
};

class LoginSystem {
private:
    User user;
public:
    LoginSystem(User user) : user(user) {}
    bool authenticate(std::string username, std::string password) {
        if (username == user.getUsername() && password == user.getPassword()) {
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    User user("admin", "password");
    LoginSystem loginSystem(user);

    std::cout << "Enter username: ";
    std::string username;
    std::cin >> username;

    std::cout << "Enter password: ";
    std::string password;
    std::cin >> password;

    if (loginSystem.authenticate(username, password)) {
        std::cout << "Access granted.\n";
    } else {
        std::cout << "Access denied.\n";
    }

    return 0;
}