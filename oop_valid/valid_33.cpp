#include<iostream>

class Numero {
private:
    double valor;
public:
    Numero(double val) {
        valor = val;
    }
    double getValor() {
        return valor;
    }
};

class Calculadora {
public:
    double suma(Numero n1, Numero n2) {
        return n1.getValor() + n2.getValor();
    }
    double resta(Numero n1, Numero n2) {
        return n1.getValor() - n2.getValor();
    }
    double multiplica(Numero n1, Numero n2) {
        return n1.getValor() * n2.getValor();
    }
    double divide(Numero n1, Numero n2) {
        if(n2.getValor() != 0) {
            return n1.getValor() / n2.getValor();
        } else {
            std::cout << "Error: Division por cero." << std::endl;
            return 0;
        }
    }
};

int main() {
    Numero num1(10.0);
    Numero num2(5.0);

    Calculadora calc;

    std::cout << "Suma: " << calc.suma(num1, num2) << std::endl;
    std::cout << "Resta: " << calc.resta(num1, num2) << std::endl;
    std::cout << "Multiplicacion: " << calc.multiplica(num1, num2) << std::endl;
    std::cout << "Division: " << calc.divide(num1, num2) << std::endl;

    return 0;
}