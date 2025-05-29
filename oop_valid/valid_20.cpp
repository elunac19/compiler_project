#include <iostream>
#include <vector>
#include <string>

class Materia {
private:
    std::string nombre;
public:
    Materia(std::string _nombre) : nombre(_nombre) {}
    
    std::string getNombre() {
        return nombre;
    }
};

class Alumno {
private:
    std::string nombre;
    std::vector<Materia> materias;
public:
    Alumno(std::string _nombre) : nombre(_nombre) {}

    void agregarMateria(Materia materia) {
        materias.push_back(materia);
    }

    void mostrarMaterias() {
        std::cout << "Materias de " << nombre << ":" << std::endl;
        for(int i = 0; i < materias.size(); ++i) {
            std::cout << i+1 << ". " << materias[i].getNombre() << std::endl;
        }
    }
};

int main() {
    Alumno alumno("Juan");
    alumno.agregarMateria(Materia("Matematicas"));
    alumno.agregarMateria(Materia("Fisica"));
    alumno.mostrarMaterias();
    return 0;
}