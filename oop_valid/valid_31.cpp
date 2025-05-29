#include <iostream>
#include <string>

class Motor {
private:
    int potencia;
public:
    Motor(int potencia = 0): potencia(potencia) {}
    int getPotencia(){
        return this->potencia;
    }
};

class Vehiculo {
private:
    Motor motor;
    int velocidad;
public:
    Vehiculo(int potencia, int velocidad = 0)
        : motor(potencia), velocidad(velocidad) {}
        
    void setVelocidad(int velocidad) {
        this->velocidad = velocidad;
    }
    
    int getVelocidad() {
        return this->velocidad;
    }

    void acelerar() {
        this->velocidad += this->motor.getPotencia();
    }
};

int main() {
    Vehiculo coche(31, 0);
    coche.acelerar();
    std::cout << "La velocidad del coche es: " << coche.getVelocidad() << std::endl;
    return 0;
}