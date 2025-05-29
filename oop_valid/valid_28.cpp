#include <iostream>

class Punto {
private:
    double x, y;

public:
    Punto(double x = 0, double y = 0) : x(x), y(y) {}
    
    double getX() const { return x; }
    double getY() const { return y; }
};

class Rectangulo {
private:
    Punto superiorIzquierdo;
    Punto inferiorDerecho;

public:
    Rectangulo(Punto superiorIzquierdo = Punto(), Punto inferiorDerecho = Punto())
        : superiorIzquierdo(superiorIzquierdo), inferiorDerecho(inferiorDerecho) { }

    double calcularArea() const {
        double ancho = inferiorDerecho.getX() - superiorIzquierdo.getX();
        double alto = superiorIzquierdo.getY() - inferiorDerecho.getY();
        return ancho * alto;
    }
};

int main() {
    Punto p1(1, 5);
    Punto p2(6, 1);
    Rectangulo rect(p1, p2);
    std::cout << "El área del rectángulo es: " << rect.calcularArea() << std::endl;
    return 0;
}