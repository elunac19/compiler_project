#include<iostream>
#include<string>

struct Usuario {
    std::string nombreUsuario;
    std::string password;
};

struct Login {
    Usuario usuario;
    bool esUsuarioLogeado;

    void ingresarUsuario(std::string nombreUsuario, std::string password) {
        usuario.nombreUsuario = nombreUsuario;
        usuario.password = password;
        esUsuarioLogeado = true;
    }

    void deslogearUsuario() {
        esUsuarioLogeado = false;
    }

    void verificarUsuarioLogeado() {
        if (esUsuarioLogeado) {
            std::cout << "Usuario " << usuario.nombreUsuario << " está logeado." << std::endl;
        } else {
            std::cout << "No hay ningún usuario logeado." << std::endl;
        }
    }
};

int main() {
    Login login;
    login.ingresarUsuario("testUser", "testPassword");
    login.verificarUsuarioLogeado();
    login.deslogearUsuario();
    login.verificarUsuarioLogeado();
    return 0;
}