#include<iostream>
#include<string>

struct Empleado {
    std::string nombre;
    float salario;
    float aumento;

    void inicializar(std::string n, float s) {
        nombre = n;
        salario = s;
        aumento = 0;
    }

    void aumentarSalario(float monto) {
        aumento += monto;
    }

    void aplicarAumento() {
        salario += aumento;
        aumento = 0;
    }

    void imprimir() {
        std::cout << "Empleado: " << nombre << " Salario: " << salario << std::endl;
    }
};

int main() {
    Empleado empleado1;
    empleado1.inicializar("Juan", 1000);
    empleado1.aumentarSalario(200);
    empleado1.aplicarAumento();
    empleado1.imprimir(); 

    return 0;
}