#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ==================== TYPEDEFS Y ALIASES ====================
typedef int entero;
typedef vector<string> StringVector;
typedef vector<vector<int>> Matrix2D;

// ==================== CONSTANTES Y VARIABLES GLOBALES ====================
const double PI = 3.14159265359;
const int MAX_SIZE = 100;
const int knightMoves[8][2] = {{-2,-1},{-2,1},{-1,2},{1,2},{2,-1},{2,1},{-1,-2},{1,-2}};

static int globalCounter = 0;
int h, w, k;
int gameBoard[6][6];
int tempBoard[6][6];

// ==================== ESTRUCTURAS Y CLASES ====================
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Persona {
    string nombre;
    int edad;
    double salario;
    
    void mostrarInfo() const {
        cout << "Nombre: " << nombre << ", Edad: " << edad << ", Salario: " << salario << endl;
    }
};

// Jerarquía de clases - Herencia
class Animal {
protected:
    string nombre;
    int edad;
    
public:
    Animal(const string& n, int e) : nombre(n), edad(e) {}
    virtual ~Animal() = default;
    virtual void hacerSonido() const = 0;
    virtual void mostrarInfo() const {
        cout << "Animal: " << nombre << ", Edad: " << edad << endl;
    }
};

class Perro : public Animal {
private:
    string raza;
    
public:
    Perro(const string& n, int e, const string& r) : Animal(n, e), raza(r) {}
    
    void hacerSonido() const override {
        cout << "¡Guau guau!" << endl;
    }
    
    void mostrarInfo() const override {
        cout << "Perro: " << nombre << ", Edad: " << edad << ", Raza: " << raza << endl;
    }
};

class Gato : public Animal {
private:
    bool esIndependiente;
    
public:
    Gato(const string& n, int e, bool ind = true) : Animal(n, e), esIndependiente(ind) {}
    
    void hacerSonido() const override {
        cout << "¡Miau miau!" << endl;
    }
    
    void mostrarInfo() const override {
        cout << "Gato: " << nombre << ", Edad: " << edad 
             << ", Independiente: " << (esIndependiente ? "Sí" : "No") << endl;
    }
};

// Template class
template <typename T>
class Contenedor {
private:
    vector<T> elementos;
    
public:
    void agregar(const T& elemento) {
        elementos.push_back(elemento);
    }
    
    T obtener(size_t index) const {
        if (index < elementos.size()) {
            return elementos[index];
        }
        throw out_of_range("Índice fuera de rango");
    }
    
    size_t tamaño() const {
        return elementos.size();
    }
    
    void mostrarTodos() const {
        for (const auto& elem : elementos) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

// ==================== TEMPLATE FUNCTIONS ====================
template <typename T>
inline bool actualizarMaximo(T& actual, const T& nuevo) {
    if (actual < nuevo) {
        actual = nuevo;
        return true;
    }
    return false;
}

template <typename T>
T encontrarMaximo(const vector<T>& vec) {
    if (vec.empty()) throw invalid_argument("Vector vacío");
    return *max_element(vec.begin(), vec.end());
}

// ==================== FUNCIONES UTILITARIAS ====================
void copiarTablero() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            tempBoard[i][j] = gameBoard[i][j];
        }
    }
}

int contarCeldasOcupadas() {
    int contador = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (tempBoard[i][j] == 1) contador++;
        }
    }
    return contador;
}

void pintarFilasYColumnas(int estadoFilas, int estadoColumnas) {
    // Pintar filas
    for (int i = 0; i < h; i++) {
        if ((1 << i) & estadoFilas) {
            for (int j = 0; j < w; j++) {
                tempBoard[i][j] = 2;
            }
        }
    }
    
    // Pintar columnas
    for (int i = 0; i < w; i++) {
        if ((1 << i) & estadoColumnas) {
            for (int j = 0; j < h; j++) {
                tempBoard[j][i] = 2;
            }
        }
    }
}

int resolverProblemaTablero() {
    int resultado = 0;
    for (int i = 0; i < (1 << h); i++) {
        for (int j = 0; j < (1 << w); j++) {
            copiarTablero();
            pintarFilasYColumnas(i, j);
            if (contarCeldasOcupadas() == k) {
                resultado++;
            }
        }
    }
    return resultado;
}

// ==================== FUNCIONES CON DIFERENTES MODIFICADORES ====================
static void funcionEstatica() {
    cout << "Función estática ejecutada" << endl;
    globalCounter++;
}

inline void mostrarMensaje(const string& mensaje) {
    cout << "Mensaje: " << mensaje << endl;
}

int suma(int a, int b = 10) {
    return a + b;
}

double calcularArea(double radio) {
    return PI * radio * radio;
}

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    cout << "=== EJEMPLO COMPLETO DE C++ ===" << endl;
    
    // Variables básicas
    int entero1 = 42;
    float decimal1 = 3.14f;
    double decimal2 = 2.71828;
    char caracter = 'A';
    string texto = "Hola, mundo!";
    bool esVerdadero = true;
    
    // Arrays y vectores
    int arrayEstatico[5] = {1, 2, 3, 4, 5};
    vector<int> vectorDinamico = {10, 20, 30, 40, 50};
    StringVector nombres = {"Ana", "Luis", "Carlos", "María"};
    
    // Estructuras
    Persona persona1 = {"Juan Pérez", 30, 50000.0};
    Point punto1(10, 20);
    
    // Objetos y polimorfismo
    vector<unique_ptr<Animal>> animales;
    animales.push_back(make_unique<Perro>("Max", 3, "Labrador"));
    animales.push_back(make_unique<Gato>("Whiskers", 2, true));
    
    // Templates
    Contenedor<int> contenedorEnteros;
    Contenedor<string> contenedorTextos;
    
    // ==================== DEMOSTRACIONES ====================
    
    // Control de flujo
    cout << "\n--- Control de flujo ---" << endl;
    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            cout << "Número par: " << i << endl;
        } else {
            cout << "Número impar: " << i << endl;
        }
    }
    
    // Uso de estructuras
    cout << "\n--- Estructuras ---" << endl;
    persona1.mostrarInfo();
    
    // Polimorfismo
    cout << "\n--- Polimorfismo ---" << endl;
    for (const auto& animal : animales) {
        animal->mostrarInfo();
        animal->hacerSonido();
    }
    
    // Templates
    cout << "\n--- Templates ---" << endl;
    contenedorEnteros.agregar(100);
    contenedorEnteros.agregar(200);
    contenedorEnteros.agregar(300);
    contenedorEnteros.mostrarTodos();
    
    contenedorTextos.agregar("Hola");
    contenedorTextos.agregar("Mundo");
    contenedorTextos.mostrarTodos();
    
    // Funciones con parámetros por defecto
    cout << "\n--- Funciones ---" << endl;
    cout << "Suma con parámetro por defecto: " << suma(5) << endl;
    cout << "Suma con ambos parámetros: " << suma(5, 15) << endl;
    
    // Template functions
    int maximo = 50;
    if (actualizarMaximo(maximo, 75)) {
        cout << "Nuevo máximo: " << maximo << endl;
    }
    
    // Funciones estáticas
    funcionEstatica();
    mostrarMensaje("Demostración completada");
    
    cout << "\n--- Problema del tablero ---" << endl;
    // Ejemplo simplificado del problema del tablero
    h = 3; w = 3; k = 2;
    
    // Inicializar tablero de ejemplo
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            gameBoard[i][j] = (i + j) % 2;
        }
    }
    
    int soluciones = resolverProblemaTablero();
    cout << "Número de soluciones encontradas: " << soluciones << endl;
    
    return 0;
}