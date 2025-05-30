#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

struct Persona {
    std::string nombre;
    int edad;
};

// ==================== CLASE BASE ABSTRACTA ====================
class Vehiculo{
protected:
    string marca;
    string modelo;
    int año;
    double precio;
    
public:
    Vehiculo(const string& m, const string& mod, int a, double p) 
        : marca(m), modelo(mod), año(a), precio(p) {}
    
    virtual ~Vehiculo() = default;
    
    // Métodos virtuales puros (abstractos)
    virtual void encender() = 0;
    virtual void apagar() = 0;
    virtual double calcularImpuesto() const = 0;
    
    // Métodos virtuales con implementación por defecto
    virtual void mostrarInfo() const {
        cout << "Vehículo: " << marca << " " << modelo 
             << " (" << año << ") - $" << precio << endl;
    }
    
    // Getters y setters
    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    int getAño() const { return año; }
    double getPrecio() const { return precio; }
    
    void setPrecio(double nuevoPrecio) {
        if (nuevoPrecio > 0) precio = nuevoPrecio;
    }
};

// ==================== CLASES DERIVADAS ====================
class Automovil : Vehiculo {
private:
    int numeroPuertas;
    string tipoTransmision;
    bool esElectrico;
    
public:
    Automovil(const string& m, const string& mod, int a, double p, 
              int puertas, const string& trans, bool electrico = false)
        : Vehiculo(m, mod, a, p), numeroPuertas(puertas), 
          tipoTransmision(trans), esElectrico(electrico) {}
    
    void encender() override {
        cout << "Automóvil " << marca << " " << modelo << " encendido." << endl;
        if (esElectrico) {
            cout << "Motor eléctrico silencioso activado." << endl;
        } else {
            cout << "Motor de combustión rugiendo." << endl;
        }
    }
    
    void apagar() override {
        cout << "Automóvil apagado." << endl;
    }
    
    double calcularImpuesto() const override {
        double impuesto = precio * 0.15; // 15% base
        if (esElectrico) {
            impuesto *= 0.5; // 50% descuento para eléctricos
        }
        return impuesto;
    }
    
    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "  Puertas: " << numeroPuertas 
             << ", Transmisión: " << tipoTransmision
             << ", Eléctrico: " << (esElectrico ? "Sí" : "No") << endl;
    }
    
    void activarAireAcondicionado() {
        cout << "Aire acondicionado activado en " << marca << " " << modelo << endl;
    }
};

class Motocicleta : public Vehiculo, private Vehiculo {
private:
    int cilindrada;
    string tipoMotor;
    bool tieneSidecar;
    
public:
    Motocicleta(const string& m, const string& mod, int a, double p,
                int cc, const string& motor, bool sidecar = false)
        : Vehiculo(m, mod, a, p), cilindrada(cc), tipoMotor(motor), tieneSidecar(sidecar) {}
    
    void encender() override {
        cout << "Motocicleta " << marca << " " << modelo << " rugiendo a la vida." << endl;
        cout << "Motor de " << cilindrada << "cc resonando." << endl;
    }
    
    void apagar() override {
        cout << "Motocicleta silenciada." << endl;
    }
    
    double calcularImpuesto() const override {
        return precio * 0.08; // 8% para motocicletas
    }
    
    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "  Cilindrada: " << cilindrada << "cc"
             << ", Motor: " << tipoMotor
             << ", Sidecar: " << (tieneSidecar ? "Sí" : "No") << endl;
    }
    
    void hacerWheellie() {
        cout << "¡Haciendo wheellie con la " << marca << " " << modelo << "!" << endl;
    }
};

class Camion : public Vehiculo {
private:
    double capacidadCarga;
    int numeroEjes;
    string tipoCombustible;
    
public:
    Camion(const string& m, const string& mod, int a, double p,
           double carga, int ejes, const string& combustible)
        : Vehiculo(m, mod, a, p), capacidadCarga(carga), numeroEjes(ejes), tipoCombustible(combustible) {}
    
    void encender() override {
        cout << "Camión " << marca << " " << modelo << " arrancando con potencia." << endl;
        cout << "Motor diésel rugiendo, listo para cargar " << capacidadCarga << " toneladas." << endl;
    }
    
    void apagar() override {
        cout << "Camión apagado, frenos de aire liberados." << endl;
    }
    
    double calcularImpuesto() const override {
        return precio * 0.20 + (capacidadCarga * 100); // Base + por capacidad
    }
    
    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "  Capacidad: " << capacidadCarga << " ton"
             << ", Ejes: " << numeroEjes
             << ", Combustible: " << tipoCombustible << endl;
    }
    
    void cargar(double peso) {
        if (peso <= capacidadCarga) {
            cout << "Cargando " << peso << " toneladas en el camión." << endl;
        } else {
            cout << "¡Sobrecarga! El camión solo puede cargar " << capacidadCarga << " toneladas." << endl;
        }
    }
};

// ==================== CLASE PARA GESTIÓN DE FLOTA ====================
class Concesionario {
private:
    string nombre;
    vector<unique_ptr<Vehiculo>> inventario;
    double ventasTotales;
    
public:
    Concesionario(const string& n) : nombre(n), ventasTotales(0.0) {}
    
    void agregarVehiculo(unique_ptr<Vehiculo> vehiculo) {
        inventario.push_back(move(vehiculo));
        cout << "Vehículo agregado al inventario de " << nombre << endl;
    }
    
    void mostrarInventario() const {
        cout << "\n=== INVENTARIO DE " << nombre << " ===" << endl;
        for (const auto& vehiculo : inventario) {
            vehiculo->mostrarInfo();
            cout << "Impuesto: $" << vehiculo->calcularImpuesto() << endl;
            cout << "------------------------" << endl;
        }
    }
    
    void probarVehiculos() {
        cout << "\n=== PRUEBA DE VEHÍCULOS ===" << endl;
        for (auto& vehiculo : inventario) {
            vehiculo->encender();
            vehiculo->apagar();
            cout << "---" << endl;
        }
    }
    
    double calcularValorInventario() const {
        double total = 0.0;
        for (const auto& vehiculo : inventario) {
            total += vehiculo->getPrecio();
        }
        return total;
    }
    
    void venderVehiculo(size_t indice) {
        if (indice < inventario.size()) {
            double precio = inventario[indice]->getPrecio();
            cout << "Vendiendo: ";
            inventario[indice]->mostrarInfo();
            ventasTotales += precio;
            inventario.erase(inventario.begin() + indice);
            cout << "¡Venta realizada! Total de ventas: $" << ventasTotales << endl;
        }
    }
    
    vector<unique_ptr<Vehiculo>> buscarPorMarca(const string& marca) const {
        vector<unique_ptr<Vehiculo>> resultados;
        for (const auto& vehiculo : inventario) {
            if (vehiculo->getMarca() == marca) {
                // Nota: En un caso real, clonarías los objetos
                cout << "Encontrado: " << vehiculo->getMarca() << " " << vehiculo->getModelo() << endl;
            }
        }
        return resultados;
    }
};

// ==================== CLASE TEMPLATE ====================
template<typename T>
class Garage {
private:
    vector<T> vehiculos;
    string ubicacion;
    
public:
    Garage(const string& loc) : ubicacion(loc) {}
    
    void estacionar(const T& vehiculo) {
        vehiculos.push_back(vehiculo);
        cout << "Vehículo estacionado en garage de " << ubicacion << endl;
    }
    
    void listarVehiculos() const {
        cout << "\n=== VEHÍCULOS EN GARAGE - " << ubicacion << " ===" << endl;
        for (size_t i = 0; i < vehiculos.size(); ++i) {
            cout << i + 1 << ". ";
            vehiculos[i]->mostrarInfo();
        }
    }
    
    size_t cantidadVehiculos() const {
        return vehiculos.size();
    }
};

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    cout << "=== SISTEMA DE GESTIÓN DE VEHÍCULOS - OOP ===" << endl;
    
    // Crear concesionario
    Concesionario miConcesionario("AutoMax Plus");
    
    // Crear vehículos usando polimorfismo
    auto auto1 = make_unique<Automovil>("Toyota", "Prius", 2023, 35000, 4, "Automática", true);
    auto auto2 = make_unique<Automovil>("BMW", "M3", 2024, 65000, 2, "Manual", false);
    auto moto1 = make_unique<Motocicleta>("Harley-Davidson", "Street 750", 2023, 8500, 750, "V-Twin", false);
    auto moto2 = make_unique<Motocicleta>("Yamaha", "YZF-R1", 2024, 17000, 1000, "4 cilindros", false);
    auto camion1 = make_unique<Camion>("Volvo", "FH16", 2023, 150000, 40.0, 6, "Diésel");
    
    // Agregar al inventario
    miConcesionario.agregarVehiculo(move(auto1));
    miConcesionario.agregarVehiculo(move(auto2));
    miConcesionario.agregarVehiculo(move(moto1));
    miConcesionario.agregarVehiculo(move(moto2));
    miConcesionario.agregarVehiculo(move(camion1));
    
    // Mostrar inventario
    miConcesionario.mostrarInventario();
    
    // Probar vehículos
    miConcesionario.probarVehiculos();
    
    // Mostrar valor total
    cout << "\nValor total del inventario: $" << miConcesionario.calcularValorInventario() << endl;
    
    // Crear garage con template
    Garage<shared_ptr<Vehiculo>> garagePrivado("Mi Casa");
    
    // Crear más vehículos para el garage
    auto autoPersonal = make_shared<Automovil>("Honda", "Civic", 2022, 25000, 4, "CVT", false);
    auto motoPersonal = make_shared<Motocicleta>("Kawasaki", "Ninja 300", 2021, 5500, 300, "2 cilindros", false);
    
    garagePrivado.estacionar(autoPersonal);
    garagePrivado.estacionar(motoPersonal);
    garagePrivado.listarVehiculos();
    
    // Demostrar funcionalidades específicas
    cout << "\n=== FUNCIONALIDADES ESPECÍFICAS ===" << endl;
    
    // Downcasting seguro para acceder a métodos específicos
    auto autoEspecifico = make_unique<Automovil>("Tesla", "Model S", 2024, 80000, 4, "Automática", true);
    autoEspecifico->mostrarInfo();
    autoEspecifico->activarAireAcondicionado();
    
    auto motoEspecifica = make_unique<Motocicleta>("Ducati", "Panigale V4", 2024, 25000, 1100, "V4", false);
    motoEspecifica->mostrarInfo();
    motoEspecifica->hacerWheellie();
    
    auto camionEspecifico = make_unique<Camion>("Mercedes", "Actros", 2024, 120000, 35.0, 4, "Diésel");
    camionEspecifico->mostrarInfo();
    camionEspecifico->cargar(30.0);
    camionEspecifico->cargar(40.0); // Sobrecarga
    
    cout << "\n=== DEMOSTRACIÓN COMPLETADA ===" << endl;
    
    return 0;
}