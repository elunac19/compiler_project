#include <iostream>
#include <vector>

class Estudiante {
private:
    std::string nombre;
    std::vector<int> notas;
public:
    Estudiante(const std::string& nombre) : nombre(nombre) {}

    void agregarNota(int nota) {
        notas.push_back(nota);
    }

    const std::string& obtenerNombre() const {
        return nombre;
    }

    float calcularPromedio() const {
        int suma = 0;
        for(int nota : notas) {
            suma += nota;
        }
        return static_cast<float>(suma) / notas.size();
    }
};

class SalonDeClase {
private:
    std::vector<Estudiante> estudiantes;
public:
    void agregarEstudiante(const Estudiante& estudiante) {
        estudiantes.push_back(estudiante);
    }

    Estudiante& obtenerEstudiante(const std::string& nombre) {
        for(Estudiante& estudiante : estudiantes) {
            if(estudiante.obtenerNombre() == nombre) {
                return estudiante;
            }
        }
        throw std::runtime_error("Estudiante no encontrado");
    }
};

int main() {
    SalonDeClase salon;
    salon.agregarEstudiante(Estudiante("Juan"));
    salon.agregarEstudiante(Estudiante("Maria"));

    Estudiante& juan = salon.obtenerEstudiante("Juan");
    juan.agregarNota(95);
    juan.agregarNota(85);

    Estudiante& maria = salon.obtenerEstudiante("Maria");
    maria.agregarNota(90);
    maria.agregarNota(80);

    std::cout << "Promedio de Juan: " << juan.calcularPromedio() << '\n';
    std::cout << "Promedio de Maria: " << maria.calcularPromedio() << '\n';

    return 0;
}