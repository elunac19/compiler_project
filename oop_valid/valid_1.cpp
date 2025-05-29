#include <iostream>
#include <vector>

class Estudiante {
private:
    std::string nombre;
    std::vector<double> notas;
public:
    Estudiante(std::string nombre) : nombre(nombre) {}

    void agregarNota(double nota) {
        notas.push_back(nota);
    }

    double calcularPromedio() {
        double suma = 0;
        for(double nota : notas) {
            suma += nota;
        }
        return suma / notas.size();
    }

    std::string getNombre() {
        return nombre;
    }
};

class Curso {
private:
    std::string nombre;
    std::vector<Estudiante> estudiantes;
public:
    Curso(std::string nombre) : nombre(nombre) {}

    void agregarEstudiante(Estudiante estudiante) {
        estudiantes.push_back(estudiante);
    }

    double promedioCurso() {
        double suma = 0;
        for(Estudiante estudiante : estudiantes) {
            suma += estudiante.calcularPromedio();
        }
        return suma / estudiantes.size();
    }
};

int main() {
    Estudiante estudiante1("Maria");
    estudiante1.agregarNota(4.0);
    estudiante1.agregarNota(3.5);

    Estudiante estudiante2("Carlos");
    estudiante2.agregarNota(3.7);
    estudiante2.agregarNota(4.2);

    Curso curso("Calculo");
    curso.agregarEstudiante(estudiante1);
    curso.agregarEstudiante(estudiante2);

    std::cout << "Promedio del curso: " << curso.promedioCurso() << std::endl;

    return 0;
}