#include<iostream>

struct Operaciones {
    int suma(int a, int b) {
        return a + b;
    }

    int resta(int a, int b) {
        return a - b;
    }

    int multiplicacion(int a, int b) {
        return a * b;
    }

    float division(int a, int b) {
        if(b == 0) {
            return 0;
        }
        return (float)a / b;
    }
};

int main() {
    Operaciones op;
    int a = 10;
    int b = 5;

    std::cout << "Suma: " << op.suma(a, b) << std::endl;
    std::cout << "Resta: " << op.resta(a, b) << std::endl;
    std::cout << "Multiplicacion: " << op.multiplicacion(a, b) << std::endl;
    std::cout << "Division: " << op.division(a, b) << std::endl;

    return 0;
}