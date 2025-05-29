#include <iostream>
#include <string>

class Persona {
private:
    std::string nombre;
    int edad;

public:
    Persona(std::string nom, int ed) : nombre(nom), edad(ed) {}

    std::string obtenerNombre() {
        return nombre;
    }

    int obtenerEdad() {
        return edad;
    }
};

class Saludo {
private:
    std::string saludo;

public:
    Saludo(std::string sal) : saludo(sal) {}

    void darSaludo(Persona p) {
        std::cout << saludo << ", " << p.obtenerNombre() << ". Tienes " << p.obtenerEdad() << " años." << std::endl;
    }
};

int main() {
    Persona p1("Juan", 25);
    Saludo s1("Hola");

    s1.darSaludo(p1);

    return 0;
}