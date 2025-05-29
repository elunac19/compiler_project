#include <iostream>
#include <string>

class Persona {
private:
    std::string nombre;
    int edad;

public:
    Persona(std::string nombre, int edad) {
        this->nombre = nombre;
        this->edad = edad;
    }

    std::string getNombre() {
        return nombre;
    }

    int getEdad() {
        return edad;
    }
};

class Saludo {
private:
    std::string mensaje;

public:
    Saludo(std::string mensaje) {
        this->mensaje = mensaje;
    }

    void darSaludo(Persona persona) {
        std::cout << mensaje << " " << persona.getNombre() << ". Tu edad es " << persona.getEdad() << "." << std::endl;
    }
};

int main() {
    Persona persona1("Juan", 32);
    Saludo saludo1("Hola");

    saludo1.darSaludo(persona1);

    return 0;
}