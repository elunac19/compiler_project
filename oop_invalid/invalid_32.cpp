#include<iostream>
#include<string>

struct Persona {
    std::string nombre;
    int edad;

    void establecerNombre(std::string n) {
        nombre = n;
    }

    void establecerEdad(int e) {
        edad = e;
    }

    std::string obtenerNombre() {
        return nombre;
    }

    int obtenerEdad() {
        return edad;
    }
};

struct Saludo {
    std::string saludo;

    void establecerSaludo(std::string s) {
        saludo = s;
    }

    std::string obtenerSaludo() {
        return saludo;
    }
};

int main() {
    Persona p;
    p.establecerNombre("Juan");
    p.establecerEdad(32);

    Saludo s;
    s.establecerSaludo("Hola");

    std::cout << s.obtenerSaludo() << ", " << p.obtenerNombre() << ". Tienes " << p.obtenerEdad() << " años." << std::endl;

    return 0;
}