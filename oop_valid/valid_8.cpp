#include<iostream>
using namespace std;

class Operando {
private:
    double value;
public:
    Operando(double v = 0) : value(v) {}
    double getValue() {
        return value;
    }
};

class Calculadora {
public:
    double sumar(Operando a, Operando b) {
        return a.getValue() + b.getValue();
    }
    
    double restar(Operando a, Operando b) {
        return a.getValue() - b.getValue();
    }
    
    double multiplicar(Operando a, Operando b) {
        return a.getValue() * b.getValue();
    }
    
    double dividir(Operando a, Operando b) {
        if (b.getValue() == 0) {
            cout << "Error: division por cero." << endl;
            return 0;
        } else {
            return a.getValue() / b.getValue();
        }
    }
};

int main() {
    Operando op1(10);
    Operando op2(5);
    Calculadora calc;

    cout << "Suma: " << calc.sumar(op1, op2) << endl;
    cout << "Resta: " << calc.restar(op1, op2) << endl;
    cout << "Multiplicacion: " << calc.multiplicar(op1, op2) << endl;
    cout << "Division: " << calc.dividir(op1, op2) << endl;

    return 0;
}