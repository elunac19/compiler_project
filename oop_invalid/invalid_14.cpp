#include <iostream>
#include <string>

struct Animal {
    std::string tipo;
    std::string sonido;

    void setTipo(std::string t) {
        tipo = t;
    }

    void setSonido(std::string s) {
        sonido = s;
    }

    void imprimir() {
        std::cout << "El " << tipo << " hace " << sonido << std::endl;
    }
};

int main() {
    Animal perro;
    perro.setTipo("Perro");
    perro.setSonido("Guau");

    perro.imprimir();

    return 0;
}