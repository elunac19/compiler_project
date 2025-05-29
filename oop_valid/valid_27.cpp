#include <iostream>
#include <string>

class Cliente {
private:
    std::string nombre;
public:
    Cliente(std::string nombre) : nombre(nombre) {}

    std::string getNombre() {
        return nombre;
    }
};

class CuentaBancaria {
private:
    Cliente cliente;
    double saldo;
public:
    CuentaBancaria(Cliente cliente, double saldo) : cliente(cliente), saldo(saldo) {}

    void depositar(double cantidad) {
        saldo += cantidad;
    }

    bool retirar(double cantidad) {
        if (saldo >= cantidad) {
            saldo -= cantidad;
            return true;
        }
        return false;
    }

    double getSaldo() {
        return saldo;
    }

    std::string getNombreCliente() {
        return cliente.getNombre();
    }
};

int main() {
    Cliente cliente1("John Doe");
    CuentaBancaria cuenta1(cliente1, 1000.0);

    std::cout << cuenta1.getNombreCliente() << " tiene un saldo de $" << cuenta1.getSaldo() << std::endl;

    cuenta1.depositar(500.0);
    std::cout << "Después de depositar $500, " << cuenta1.getNombreCliente() << " ahora tiene un saldo de $" << cuenta1.getSaldo() << std::endl;

    if (cuenta1.retirar(1500.0)) {
        std::cout << "Después de retirar $1500, " << cuenta1.getNombreCliente() << " ahora tiene un saldo de $" << cuenta1.getSaldo() << std::endl;
    } else {
        std::cout << "No es posible retirar más de lo que " << cuenta1.getNombreCliente() << " tiene en su cuenta." << std::endl;
    }

    return 0;
}