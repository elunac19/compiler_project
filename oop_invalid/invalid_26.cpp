#include <iostream>
#include <vector>

struct Estudiante {
    std::string nombre;
    std::vector<int> notas;
    
    void agregarNota(int nota) {
        notas.push_back(nota);
    }
    
    double calcularPromedio() {
        double sum = 0;
        for(int i = 0; i < notas.size(); i++) {
            sum += notas[i];
        }
        return sum / notas.size();
    }
};

struct Curso {
    std::vector<Estudiante> estudiantes;
    
    void agregarEstudiante(Estudiante estudiante) {
        estudiantes.push_back(estudiante);
    }
    
    double calcularPromedioCurso() {
        double sum = 0;
        for(int i = 0; i < estudiantes.size(); i++) {
            sum += estudiantes[i].calcularPromedio();
        }
        return sum / estudiantes.size();
    }
};