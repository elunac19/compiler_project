#include <iostream>
#include <string>

struct Cancion {
  std::string nombre;
  int duracion;

  void setNombre(std::string n) {
    nombre = n;
  }

  void setDuracion(int d) {
    duracion = d;
  }

  std::string getNombre() {
    return nombre;
  }

  int getDuracion() {
    return duracion;
  }

  void play() {
    std::cout << "Reproduciendo " << nombre << " con duración de " << duracion << " minutos." << std::endl;
  }
};

int main() {
  Cancion unaCancion;
  unaCancion.setNombre("Bohemian Rhapsody");
  unaCancion.setDuracion(6);
  unaCancion.play();
  
  return 0;
}