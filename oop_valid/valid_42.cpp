#include<iostream>
#include<cmath>

class Punto {
private:
    double x, y;

public:
    Punto(double x = 0, double y = 0) : x(x), y(y) {}

    double obtenerX() const {
        return x;
    }

    double obtenerY() const {
        return y;
    }

    void mover(double dx, double dy) {
        x += dx;
        y += dy;
    }
};

class Circulo {
private:
    Punto centro;
    double radio;

public:
    Circulo(double x = 0, double y = 0, double radio = 0)
        : centro(x, y), radio(radio) {}

    double obtenerRadio() const {
        return radio;
    }

    Punto obtenerCentro() const {
        return centro;
    }

    void moverCentro(double dx, double dy) {
        centro.mover(dx, dy);
    }

    double calcularArea() const {
        return M_PI * radio * radio;
    }
};

int main() {
    Circulo c1(1, 2, 3);
    std::cout << "Centro del circulo: (" << c1.obtenerCentro().obtenerX() << ", " << c1.obtenerCentro().obtenerY() << ")" << std::endl;
    std::cout << "Radio del circulo: " << c1.obtenerRadio() << std::endl;
    std::cout << "Area del circulo: " << c1.calcularArea() << std::endl;

    c1.moverCentro(3, 3);
    std::cout << "Nuevo centro del circulo: (" << c1.obtenerCentro().obtenerX() << ", " << c1.obtenerCentro().obtenerY() << ")" << std::endl;

    return 0;
}