struct FiguraGeometrica {
    int lados;
    double largo;
};

struct Poligono {
    FiguraGeometrica figura;

    void setLados(int l) {
        figura.lados = l;
    }

    void setLargo(double l) {
        figura.largo = l;
    }

    int getLados() {
        return figura.lados;
    }

    double getLargo() {
        return figura.largo;
    }

    double calcularPerimetro() {
        return figura.lados * figura.largo;
    }
};

struct Circulo {
    FiguraGeometrica figura;

    void setRadio(double r) {
        figura.largo = r;
    }

    double getRadio() {
        return figura.largo;
    }

    double calcularCircunferencia() {
        return 2 * 3.14159 * figura.largo;
    }
};

struct Triangulo {
    FiguraGeometrica figura;

    void setLados(int l) {
        figura.lados = l;
    }

    void setLargo(double l) {
        figura.largo = l;
    }

    int getLados() {
        return figura.lados;
    }

    double getLargo() {
        return figura.largo;
    }

    double calcularPerimetro() {
        return figura.lados * figura.largo;
    }
};

int main() {
    Poligono poligono;
    poligono.setLados(3);
    poligono.setLargo(5.0);
    double perimetroPoligono = poligono.calcularPerimetro();

    Circulo circulo;
    circulo.setRadio(5.0);
    double circunferenciaCirculo = circulo.calcularCircunferencia();

    Triangulo triangulo;
    triangulo.setLados(3);
    triangulo.setLargo(5.0);
    double perimetroTriangulo = triangulo.calcularPerimetro();

    return 0;
}