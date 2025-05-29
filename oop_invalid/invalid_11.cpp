#include<iostream>

struct SensorTemperatura {
    int id;
    float temperatura;

    void inicializar(int id, float temperatura) {
        this->id = id;
        this->temperatura = temperatura;
    }

    void mostrar(){
        std::cout << "ID: " << id << " Temperatura: " << temperatura << std::endl;
    }
};

int main(){
    SensorTemperatura sensor1, sensor2;
    sensor1.inicializar(1, 35.5);
    sensor2.inicializar(2, 36.5);
    
    sensor1.mostrar();
    sensor2.mostrar();
    
    return 0;
}

