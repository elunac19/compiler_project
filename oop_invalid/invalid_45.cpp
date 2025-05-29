#include <iostream>
#include <vector>
#include <string>

struct Materia{
    std::string nombre;
    int calificacion;
};

struct Alumno{
    std::string nombre;
    std::vector<Materia> materias;
};

void asignarMateria(Alumno& alumno, Materia materia){
    alumno.materias.push_back(materia);
}

void asignarCalificacion(Materia& materia, int calificacion){
    materia.calificacion = calificacion;
}

void imprimirAlumno(Alumno& alumno){
    std::cout << "Alumno: " << alumno.nombre << "\n";
    for(auto& materia : alumno.materias){
        std::cout << "Materia: " << materia.nombre << " Calificacion: " << materia.calificacion << "\n";
    }
}

int main(){
    Alumno alumno;
    alumno.nombre = "Juan";

    Materia matematicas;
    matematicas.nombre = "Matematicas";

    asignarMateria(alumno, matematicas);
    asignarCalificacion(alumno.materias[0], 85);

    imprimirAlumno(alumno);

    return 0;
}