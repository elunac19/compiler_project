#include<iostream>
#include<string>

class Cliente {
    private:
        std::string nombre;

    public:
        Cliente(std::string nombre) {
            this->nombre = nombre;
        }

        std::string getNombre() {
            return this->nombre;
        }
};

class CuentaBancaria {
    private:
        double saldo;
        Cliente *propietario;

    public:
        CuentaBancaria(Cliente *propietario, double saldoInicial) {
            this->propietario = propietario;
            this->saldo = saldoInicial;
        }

        void depositar(double monto) {
            this->saldo += monto;
        }

        void retirar(double monto) {
            if(monto > this->saldo) {
                std::cout << "Saldo insuficiente para realizar la transacción" << std::endl;
            } else {
                this->saldo -= monto;
            }
        }

        void mostrarSaldo() {
            std::cout << "El saldo de " << this->propietario->getNombre() << " es: " << this->saldo << std::endl;
        }
};

int main() {
    Cliente cliente1("Juan");
    CuentaBancaria cuenta1(&cliente1, 500.0);

    cuenta1.mostrarSaldo();
    cuenta1.depositar(100.0);
    cuenta1.mostrarSaldo();
    cuenta1.retirar(200.0);
    cuenta1.mostrarSaldo();

    return 0;
}