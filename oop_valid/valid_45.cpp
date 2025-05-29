#include <iostream>
#include <string>
#include <vector>

class Materia {
private:
    std::string nombre;
    int calificacion;

public:
    Materia(std::string nombre, int calificacion) {
        this->nombre = nombre;
        this->calificacion = calificacion;
    }

    std::string getNombre() {
        return this->nombre;
    }

    int getCalificacion() {
        return this->calificacion;
    }
};

class Alumno {
private:
    std::string nombre;
    std::vector<Materia> materias;

public:
    Alumno(std::string nombre) {
        this->nombre = nombre;
    }

    void agregarMateria(Materia materia) {
        this->materias.push_back(materia);
    }

    std::string getNombre() {
        return this->nombre;
    }

    void imprimirMaterias() {
        std::cout << "Materias de " << this->nombre << ":" << std::endl;
        for (Materia materia : this->materias) {
            std::cout << "- " << materia.getNombre() << ": " << materia.getCalificacion() << std::endl;
        }
    }
};

int main() {
    Alumno alumno("John Doe");
    alumno.agregarMateria(Materia("Matematicas", 85));
    alumno.agregarMateria(Materia("Programacion", 95));

    alumno.imprimirMaterias();

    return 0;
}