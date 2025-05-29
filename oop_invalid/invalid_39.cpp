#include <iostream>
#include <string>

struct Animal {
    std::string name;
    std::string sound;
    
    void setName(std::string n) {
        name = n;
    }
    
    void setSound(std::string s) {
        sound = s;
    }
    
    void makeSound() {
        std::cout << name << " hace " << sound << std::endl;
    }
};

int main() {
    Animal dog;
    dog.setName("Perro");
    dog.setSound("Guau");
    dog.makeSound();

    Animal cat;
    cat.setName("Gato");
    cat.setSound("Miau");
    cat.makeSound();

    return 0;
}