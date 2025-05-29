#include<iostream>

class Sensor {
private:
    int id;
    float temperatura;

public:
    Sensor(int id, float temperatura): id(id), temperatura(temperatura) { }

    int getId() {
        return this->id;
    }

    float getTemperatura() {
        return this->temperatura;
    }

    void setTemperatura(float temperatura) {
        this->temperatura = temperatura;
    }
};

class MonitorTemperatura {
private:
    Sensor* sensor;

public:
    MonitorTemperatura(Sensor* sensor): sensor(sensor) { }

    void mostrarTemperatura() {
        std::cout << "La temperatura del sensor " << sensor->getId() << " es: " << sensor->getTemperatura() << std::endl;
    }
};

int main() {
    Sensor sensor1(11, 23.5);
    MonitorTemperatura monitor(&sensor1);
    monitor.mostrarTemperatura();
    sensor1.setTemperatura(24.7);
    monitor.mostrarTemperatura();
    return 0;
}