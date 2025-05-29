#include <iostream>

struct CalculadoraSimple {
    double num1, num2;

    double suma() {
        return num1 + num2;
    }

    double resta() {
        return num1 - num2;
    }

    double multiplicacion() {
        return num1 * num2;
    }

    double division() {
        if(num2 != 0) 
            return num1 / num2;
        else {
            std::cout << "División por cero no es permitida." << std::endl;
            return 0;
        }
    }
};

int main() {
    CalculadoraSimple calc;
    calc.num1 = 10;
    calc.num2 = 5;

    std::cout << "Suma: " << calc.suma() << std::endl;
    std::cout << "Resta: " << calc.resta() << std::endl;
    std::cout << "Multiplicación: " << calc.multiplicacion() << std::endl;
    std::cout << "División: " << calc.division() << std::endl;

    return 0;
}