#include<iostream>

class Rectangulo {
private:
    double largo;
    double ancho;

public:
    Rectangulo(double l = 1.0, double a = 1.0) : largo(l), ancho(a) {}

    double calcularArea() {
        return largo * ancho;
    }

    double getLargo() {
        return largo;
    }

    double getAncho() {
        return ancho;
    }

    void setLargo(double l) {
        this->largo = l;
    }

    void setAncho(double a) {
        this->ancho = a;
    }
};

class Test {
public:
    static void ejecutarPruebas() {
        Rectangulo r1;
        std::cout << "Area del rectangulo por defecto: " << r1.calcularArea() << std::endl;

        Rectangulo r2(5.0, 3.0);
        std::cout << "Area del rectangulo con largo 5 y ancho 3: " << r2.calcularArea() << std::endl;

        r2.setLargo(7.0);
        r2.setAncho(4.0);
        std::cout << "Area del rectangulo con largo 7 y ancho 4: " << r2.calcularArea() << std::endl;
    }
};

int main() {
    Test::ejecutarPruebas();
    return 0;
}