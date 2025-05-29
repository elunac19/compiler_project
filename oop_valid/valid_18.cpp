#include <iostream>
#include <string>

class Usuario {
private:
    std::string nombreUsuario;
    std::string contrasenia;

public:
    Usuario(std::string nombreUsuario, std::string contrasenia) {
        this->nombreUsuario = nombreUsuario;
        this->contrasenia = contrasenia;
    }

    std::string getNombreUsuario() {
        return this->nombreUsuario;
    }

    bool verificarContrasenia(std::string contrasenia) {
        return this->contrasenia == contrasenia;
    }
};

class Login {
private:
    Usuario* usuarioActual;

public:
    Login() {
        this->usuarioActual = nullptr;
    }

    bool iniciarSesion(Usuario* usuario, std::string contrasenia) {
        if (usuario->verificarContrasenia(contrasenia)) {
            this->usuarioActual = usuario;
            return true;
        }
        return false;
    }

    void cerrarSesion() {
        this->usuarioActual = nullptr;
    }

    bool sesionIniciada() {
        return this->usuarioActual != nullptr;
    }

    std::string getNombreUsuarioActual() {
        if (this->sesionIniciada()) {
            return this->usuarioActual->getNombreUsuario();
        } else {
            return "";
        }
    }
};

int main() {
    Usuario usuario1("usuario1", "contrasenia1");
    Login login;

    if (login.iniciarSesion(&usuario1, "contrasenia1")) {
        std::cout << "Sesión iniciada con el usuario: " << login.getNombreUsuarioActual() << "\n";
    } else {
        std::cout << "Error al iniciar sesión\n";
    }
    
    login.cerrarSesion();
    std::cout << "Sesión cerrada\n";

    return 0;
}