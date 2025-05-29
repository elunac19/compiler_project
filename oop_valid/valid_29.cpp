#include <iostream>
#include <string>

class Empleado {
private:
    std::string nombre;
    double salario;

public:
    Empleado(const std::string& nom, double sal): nombre(nom), salario(sal) {}

    std::string getNombre() const {
        return nombre;
    }

    double getSalario() const {
        return salario;
    }
  
    void aumentarSalario(double porcentaje) {
        salario += salario * (porcentaje / 100);
    }
};

class Departamento {
private:
    std::string nombre;
    Empleado* empleado;

public:
    Departamento(const std::string& nom, Empleado* emp): nombre(nom), empleado(emp) {}

    void aumentarSalarioEmpleado(double porcentaje) {
        empleado->aumentarSalario(porcentaje);
    }

    void mostrarInfo() const {
        std::cout << "Departamento: " << nombre << std::endl;
        std::cout << "Empleado: " << empleado->getNombre() << std::endl;
        std::cout << "Salario: " << empleado->getSalario() << std::endl;
    }
};

int main() {
    Empleado empleado1("Juan", 5000);
    Departamento departamento1("Ventas", &empleado1);

    departamento1.mostrarInfo();
    departamento1.aumentarSalarioEmpleado(29);
    departamento1.mostrarInfo();

    return 0;
}