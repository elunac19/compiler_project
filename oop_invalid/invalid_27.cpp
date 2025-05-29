#include <iostream>

struct CuentaBancaria {
    int saldo;

    void depositar(int cantidad) {
        saldo += cantidad;
    }

    void retirar(int cantidad) {
        if(saldo >= cantidad)
            saldo -= cantidad;
        else
            std::cout << "Fondos insuficientes" << std::endl;
    }

    void mostrarSaldo() {
        std::cout << "Saldo: " << saldo << std::endl;
    }
};

int main() {
    CuentaBancaria cuenta1;
    cuenta1.saldo = 100;
    cuenta1.depositar(300);
    cuenta1.mostrarSaldo(); 
    cuenta1.retirar(50); 
    cuenta1.mostrarSaldo(); 

    return 0;
}