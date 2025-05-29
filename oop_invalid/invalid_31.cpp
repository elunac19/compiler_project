#include <iostream>

struct Vehiculo {
    int velocidad;

    void setVelocidad(int v) {
        velocidad = v;
    }

    int getVelocidad() {
        return velocidad;
    }

    void acelerar() {
        velocidad++;
    }

    void frenar() {
        if(velocidad > 0) velocidad--;
    }
};

struct Coche : Vehiculo {
    int puertas;

    void setPuertas(int p) {
        puertas = p;
    }

    int getPuertas() {
        return puertas;
    }
};

int main() {
    Coche coche;
    coche.setVelocidad(31);
    coche.setPuertas(4);

    std::cout << "Velocidad del coche: " << coche.getVelocidad() << std::endl;
    std::cout << "Puertas del coche: " << coche.getPuertas() << std::endl;

    return 0;
}