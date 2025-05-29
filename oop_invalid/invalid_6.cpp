#include <iostream>
#include <string>

struct Vehiculo {
    std::string tipo;
    int velocidad;

    void setTipo(std::string t) {
        tipo = t;
    }

    void setVelocidad(int v) {
        velocidad = v;
    }

    std::string getTipo() {
        return tipo;
    }

    int getVelocidad() {
        return velocidad;
    }

    void acelera() {
        velocidad += 6;
    }

    void frena() {
        if (velocidad >= 6) {
            velocidad -= 6;
        }
    }
};

int main() {
    Vehiculo car;
    car.setTipo("Sedan");
    car.setVelocidad(0);

    std::cout << "Tipo de vehiculo: " << car.getTipo() << std::endl;
    std::cout << "Velocidad inicial: " << car.getVelocidad() << " mph" << std::endl;

    car.acelera();
    std::cout << "Velocidad despues de acelerar: " << car.getVelocidad() << " mph" << std::endl;

    car.frena();
    std::cout << "Velocidad despues de frenar: " << car.getVelocidad() << " mph" << std::endl;

    return 0;
}