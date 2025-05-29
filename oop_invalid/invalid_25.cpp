#include <iostream>
#include <string>

struct Pantalla {
  int ancho;
  int alto;
  std::string tipo;

  void SetResolucion(int a, int b){
    ancho = a;
    alto = b;
  }

  void SetTipo(std::string t){
    tipo = t;
  }

  void ImprimirInfo(){
    std::cout << "Tipo: " << tipo << ", Resolución: " << ancho << "x" << alto << std::endl;
  }
};

struct Pantalla4K : Pantalla {
  Pantalla4K(){
    ancho = 3840;
    alto = 2160;
    tipo = "4K";
  }
};

struct Pantalla1080p : Pantalla {
  Pantalla1080p(){
    ancho = 1920;
    alto = 1080;
    tipo = "1080p";
  }
};

int main() {
  Pantalla4K p4k;
  p4k.ImprimirInfo();
  
  Pantalla1080p p1080;
  p1080.ImprimirInfo();

  return 0;
}