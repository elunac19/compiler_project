#include<iostream>
#include<string>

class Empleado {
private:
    std::string nombre;
    double salario;

public:
    Empleado(std::string nombre, double salario) : nombre(nombre), salario(salario) {}

    double obtenerSalario() {
        return salario;
    }

    std::string obtenerNombre() {
        return nombre;
    }

    void aumentarSalario(double porcentaje) {
        salario += (salario * porcentaje/100);
    }
};

class Empresa {
private:
    std::string nombreEmpresa;
    Empleado *empleados;
    int numEmpleados;

public:
    Empresa(std::string nombreEmpresa, int numEmpleados) : nombreEmpresa(nombreEmpresa), numEmpleados(numEmpleados) {
        empleados = new Empleado[numEmpleados];
    }

    void agregarEmpleado(Empleado empleado, int indice) {
        if(indice >= 0 && indice < numEmpleados) {
            empleados[indice] = empleado;
        }
    }

    void aumentarSalarios(double porcentaje) {
        for(int i = 0; i < numEmpleados; i++) {
            empleados[i].aumentarSalario(porcentaje);
        }
    }

    void imprimirSalarios() {
        for(int i = 0; i < numEmpleados; i++) {
            std::cout << "Nombre: " << empleados[i].obtenerNombre() << ", Salario: " << empleados[i].obtenerSalario() << std::endl;
        }
    }
};

int main() {
    Empresa empresa("XYZ", 3);
    Empleado empleado1("Juan", 1000);
    Empleado empleado2("Maria", 1500);
    Empleado empleado3("Pedro", 2000);

    empresa.agregarEmpleado(empleado1, 0);
    empresa.agregarEmpleado(empleado2, 1);
    empresa.agregarEmpleado(empleado3, 2);

    empresa.aumentarSalarios(10);

    empresa.imprimirSalarios();

    return 0;
}