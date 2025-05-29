#include <iostream>
#include <string>

class Motor {
private:
    int velocidad;
public:
    Motor(int velocidad) : velocidad(velocidad) {}
    int getVelocidad() {
        return velocidad;
    }
    void setVelocidad(int velocidad) {
        this->velocidad = velocidad;
    }
};

class Vehiculo {
private:
    std::string tipo;
    Motor* motor;
public:
    Vehiculo(std::string tipo, int velocidad) : tipo(tipo) {
        motor = new Motor(velocidad);
    }
    ~Vehiculo() {
        delete motor;
    }
    void infoVehiculo() {
        std::cout << "Tipo: " << tipo << ", Velocidad: " << motor->getVelocidad() << std::endl;
    }
    void cambiarVelocidad(int nuevaVelocidad) {
        motor->setVelocidad(nuevaVelocidad);
    }
};

int main() {
    Vehiculo carro("Carro", 120);
    carro.infoVehiculo();
    carro.cambiarVelocidad(150);
    carro.infoVehiculo();
    return 0;
}