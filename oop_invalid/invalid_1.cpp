#include<iostream>
using namespace std;

struct Estudiante{
    string nombre;
    double notas[3];
};

double calcularPromedio(Estudiante estudiante){
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += estudiante.notas[i];
    }
    return sum / 3;
}

int main() {
    Estudiante estudiante1;
    estudiante1.nombre = "Juan";
    estudiante1.notas[0] = 80.5;
    estudiante1.notas[1] = 90.4;
    estudiante1.notas[2] = 89.67;
    
    cout << "El promedio de " << estudiante1.nombre << " es " << calcularPromedio(estudiante1) << endl;
    return 0;
}