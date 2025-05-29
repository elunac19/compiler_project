#include<iostream>
#include<string>

struct Persona {
  std::string nombre;
  int edad;
};

struct Saludo {
  std::string frase;
};

void setNombre(Persona &p, std::string n) {
  p.nombre = n;
}

void setEdad(Persona &p, int e) {
  p.edad = e;
}

std::string getNombre(Persona &p) {
  return p.nombre;
}

int getEdad(Persona &p) {
  return p.edad;
}

void setFrase(Saludo &s, std::string f) {
  s.frase = f;
}

std::string getFrase(Saludo &s) {
  return s.frase;
}

void saludar(Persona &p, Saludo &s) {
  std::cout << getFrase(s) << ", " << getNombre(p) << "!\n";
}

int main() {
  Persona p;
  Saludo s;
  setNombre(p, "Juan");
  setEdad(p, 25);
  setFrase(s, "Hola");
  saludar(p, s);
  return 0;
}