#include <iostream>
#include <string>

struct CuentaBancaria {
    std::string nombrePropietario;
    double saldo;

    void establecerNombrePropietario(std::string np) {
        nombrePropietario = np;
    }

    void establecerSaldo(double s) {
        saldo = s;
    }

    std::string obtenerNombrePropietario() {
        return nombrePropietario;
    }

    double obtenerSaldo() {
        return saldo;
    }

    void depositar(double cantidad) {
        saldo += cantidad;
    }

    void retirar(double cantidad) {
        if (saldo >= cantidad)
            saldo -= cantidad;
        else
            std::cout << "Fondos insuficientes.\n";
    }
};

int main() {
    CuentaBancaria cuenta1;

    cuenta1.establecerNombrePropietario("Juan");
    cuenta1.establecerSaldo(5000.0);

    std::cout << "Nombre del propietario: " << cuenta1.obtenerNombrePropietario() << std::endl;
    std::cout << "Saldo: " << cuenta1.obtenerSaldo() << std::endl;

    cuenta1.depositar(2000.0);

    std::cout << "Saldo después del depósito: " << cuenta1.obtenerSaldo() << std::endl;

    cuenta1.retirar(7000.0);

    std::cout << "Saldo después del retiro: " << cuenta1.obtenerSaldo() << std::endl;

    return 0;
}