#include<iostream>

struct FiguraGeometrica {
    double ancho;
    double altura;

    FiguraGeometrica(double anchoInicial, double alturaInicial) {
        ancho = anchoInicial;
        altura = alturaInicial;
    }

    double obtenerArea() {
        return ancho * altura;
    }

    double obtenerPerimetro() {
        return 2 * (ancho + altura);
    }
};

struct Cuadrado : FiguraGeometrica {
    Cuadrado(double lado) : FiguraGeometrica(lado, lado) {}
};

struct Rectangulo : FiguraGeometrica {
    Rectangulo(double ancho, double altura) : FiguraGeometrica(ancho, altura) {}
};

int main() {
    Rectangulo miRectangulo(10, 5);
    std::cout << "El área del rectángulo es: " << miRectangulo.obtenerArea() << std::endl;
    std::cout << "El perímetro del rectángulo es: " << miRectangulo.obtenerPerimetro() << std::endl;

    Cuadrado miCuadrado(5);
    std::cout << "El área del cuadrado es: " << miCuadrado.obtenerArea() << std::endl;
    std::cout << "El perímetro del cuadrado es: " << miCuadrado.obtenerPerimetro() << std::endl;

    return 0;
}