#include <iostream>
#include <string>

using namespace std;

struct Usuario {
    string nombre;
    string password;

    void setNombre(string usuario_nombre) {
        nombre = usuario_nombre;
    }

    void setPassword(string usuario_password) {
        password = usuario_password;
    }

    bool login(string login_nombre, string login_password) {
        if(nombre == login_nombre && password == login_password) {
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    Usuario miUsuario;
    miUsuario.setNombre("admin");
    miUsuario.setPassword("1234");

    if(miUsuario.login("admin", "1234")) {
        cout << "Login exitoso!" << endl;
    } else {
        cout << "Login fallido!" << endl;
    }

    return 0;
}