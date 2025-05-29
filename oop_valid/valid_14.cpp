#include <iostream>
#include <string>

class Animal {
private:
    std::string name;
    std::string sound;
public:
    // Constructor
    Animal(std::string name, std::string sound) : name(name), sound(sound) {}

    // Getter for name
    std::string getName() {
        return this->name;
    }

    // Getter for sound
    std::string getSound() {
        return this->sound;
    }
};

class Zoo {
private:
    Animal* animals[14];
    int animalCount;
public:
    // Constructor
    Zoo() : animalCount(0) {}

    // Add animal to zoo
    void addAnimal(Animal* animal) {
        if (animalCount < 14) {
            animals[animalCount] = animal;
            animalCount++;
        } else {
            std::cout << "Zoo is full!" << std::endl;
        }
    }

    // Make all animals make sound
    void makeNoise() {
        for(int i = 0; i < animalCount; i++) {
            std::cout << animals[i]->getName() << " says " << animals[i]->getSound() << std::endl;
        }
    }
};

int main() {
    Zoo myZoo;
    Animal dog("Dog", "Bark");
    Animal cat("Cat", "Meow");
    myZoo.addAnimal(&dog);
    myZoo.addAnimal(&cat);

    myZoo.makeNoise();

    return 0;
}