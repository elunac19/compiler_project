#include <iostream>
#include <string>
#include <vector>

struct Materia {
    std::string nombre;
    int nota;
};

struct Alumno {
    std::string nombre;
    std::vector<Materia> materias;
};

void agregarMateria(Alumno &alumno, std::string nombreMateria, int nota) {
    Materia materia;
    materia.nombre = nombreMateria;
    materia.nota = nota;
    alumno.materias.push_back(materia);
}

int main() {
    Alumno alumno;
    alumno.nombre = "Juan";
    agregarMateria(alumno, "Matematicas", 90);
    agregarMateria(alumno, "Fisica", 85);
    
    for(Materia materia : alumno.materias) {
        std::cout << "Materia: " << materia.nombre << ", Nota: " << materia.nota << std::endl;
    }

    return 0;
}