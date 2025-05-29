#include <iostream>
#include <cmath>

class FiguraGeometrica {
private:
    std::string nombre;
public:
    FiguraGeometrica(std::string n) : nombre(n) {}

    std::string getNombre() {
        return nombre;
    }
};

class Circulo : public FiguraGeometrica {
private:
    double radio;
public:
    Circulo(std::string n, double r) : FiguraGeometrica(n), radio(r) {}

    double getRadio() {
        return radio;
    }

    double calcularArea() {
        return M_PI * std::pow(radio, 2);
    }

    double calcularPerimetro() {
        return 2 * M_PI * radio;
    }
};

class Rectangulo : public FiguraGeometrica {
private:
    double largo, ancho;
public:
    Rectangulo(std::string n, double l, double a) : FiguraGeometrica(n), largo(l), ancho(a) {}

    double getLargo() {
        return largo;
    }

    double getAncho() {
        return ancho;
    }

    double calcularArea() {
        return largo * ancho;
    }

    double calcularPerimetro() {
        return 2 * (largo + ancho);
    }
};

int main() {
    Circulo c1("Circulo", 5.0);
    Rectangulo r1("Rectangulo", 10.0, 5.0);

    std::cout << "Figura: " << c1.getNombre() 
              << "\nArea: " << c1.calcularArea() 
              << "\nPerimetro: " << c1.calcularPerimetro() << "\n";

    std::cout << "Figura: " << r1.getNombre() 
              << "\nArea: " << r1.calcularArea() 
              << "\nPerimetro: " << r1.calcularPerimetro() << "\n";

    return 0;
}