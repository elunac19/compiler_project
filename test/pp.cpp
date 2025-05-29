#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

// ==================== CONSTANTES GLOBALES ====================
const int MAX_ESTUDIANTES = 100;
const int MAX_MATERIAS = 10;
const double PI = 3.14159265359;
const double NOTA_APROBATORIA = 6.0;

// ==================== ESTRUCTURAS DE DATOS ====================
struct Estudiante {
    std::string nombre;
    int id;
    double notas[MAX_MATERIAS];
    int numeroMaterias;
    double promedio;
};

struct Materia {
    std::string nombre;
    std::string codigo;
    int creditos;
    double notaMinima;
};

struct RegistroAcademico {
    Estudiante estudiantes[MAX_ESTUDIANTES];
    Materia materias[MAX_MATERIAS];
    int totalEstudiantes;
    int totalMaterias;
};

// ==================== VARIABLES GLOBALES ====================
RegistroAcademico sistemaAcademico;
int contadorOperaciones = 0;

// ==================== FUNCIONES DE INICIALIZACIÓN ====================
void inicializarSistema() {
    sistemaAcademico.totalEstudiantes = 0;
    sistemaAcademico.totalMaterias = 0;
    contadorOperaciones = 0;
    std::cout << "Sistema académico inicializado." << std::endl;
}

void cargarMateriasDefault() {
    sistemaAcademico.materias[0] = {"Matemáticas I", "MAT101", 4, 6.0};
    sistemaAcademico.materias[1] = {"Programación I", "PRG101", 5, 6.0};
    sistemaAcademico.materias[2] = {"Física I", "FIS101", 4, 6.0};
    sistemaAcademico.materias[3] = {"Química General", "QUI101", 3, 6.0};
    sistemaAcademico.materias[4] = {"Inglés I", "ING101", 2, 7.0};
    
    sistemaAcademico.totalMaterias = 5;
    std::cout << "Materias por defecto cargadas: " << sistemaAcademico.totalMaterias << std::endl;
}

// ==================== FUNCIONES DE ENTRADA DE DATOS ====================
void ingresarEstudiante() {
    if (sistemaAcademico.totalEstudiantes >= MAX_ESTUDIANTES) {
        std::cout << "Error: Límite de estudiantes alcanzado." << std::endl;
        return;
    }
    
    int indice = sistemaAcademico.totalEstudiantes;
    
    std::cout << "Ingrese nombre del estudiante: ";
    std::cin.ignore();
    std::getline(std::cin, sistemaAcademico.estudiantes[indice].nombre);
    
    std::cout << "Ingrese ID del estudiante: ";
    std::cin >> sistemaAcademico.estudiantes[indice].id;
    
    std::cout << "¿Cuántas materias cursará? (máx " << MAX_MATERIAS << "): ";
    std::cin >> sistemaAcademico.estudiantes[indice].numeroMaterias;
    
    if (sistemaAcademico.estudiantes[indice].numeroMaterias > MAX_MATERIAS) {
        sistemaAcademico.estudiantes[indice].numeroMaterias = MAX_MATERIAS;
    }
    
    std::cout << "Ingrese las notas:" << std::endl;
    for (int i = 0; i < sistemaAcademico.estudiantes[indice].numeroMaterias; i++) {
        std::cout << "Nota " << (i + 1) << ": ";
        std::cin >> sistemaAcademico.estudiantes[indice].notas[i];
    }
    
    sistemaAcademico.totalEstudiantes++;
    contadorOperaciones++;
    std::cout << "Estudiante registrado exitosamente." << std::endl;
}

void ingresarNotasAleatorias(int numeroEstudiantes) {
    for (int i = 0; i < numeroEstudiantes && sistemaAcademico.totalEstudiantes < MAX_ESTUDIANTES; i++) {
        int indice = sistemaAcademico.totalEstudiantes;
        
        sistemaAcademico.estudiantes[indice].nombre = "Estudiante_" + std::to_string(indice + 1);
        sistemaAcademico.estudiantes[indice].id = 1000 + indice;
        sistemaAcademico.estudiantes[indice].numeroMaterias = 5;
        
        // Generar notas aleatorias entre 0 y 10
        for (int j = 0; j < sistemaAcademico.estudiantes[indice].numeroMaterias; j++) {
            sistemaAcademico.estudiantes[indice].notas[j] = (rand() % 101) / 10.0; // 0.0 a 10.0
        }
        
        sistemaAcademico.totalEstudiantes++;
    }
    
    std::cout << numeroEstudiantes << " estudiantes con notas aleatorias generados." << std::endl;
}

// ==================== FUNCIONES DE CÁLCULO ====================
double calcularPromedio(const Estudiante& estudiante) {
    if (estudiante.numeroMaterias == 0) return 0.0;
    
    double suma = 0.0;
    for (int i = 0; i < estudiante.numeroMaterias; i++) {
        suma += estudiante.notas[i];
    }
    return suma / estudiante.numeroMaterias;
}

void calcularPromedios() {
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        sistemaAcademico.estudiantes[i].promedio = calcularPromedio(sistemaAcademico.estudiantes[i]);
    }
    std::cout << "Promedios calculados para " << sistemaAcademico.totalEstudiantes << " estudiantes." << std::endl;
}

double calcularPromedioGeneral() {
    if (sistemaAcademico.totalEstudiantes == 0) return 0.0;
    
    double sumaTotal = 0.0;
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        sumaTotal += sistemaAcademico.estudiantes[i].promedio;
    }
    return sumaTotal / sistemaAcademico.totalEstudiantes;
}

double encontrarNotaMaxima() {
    double maxima = 0.0;
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        if (sistemaAcademico.estudiantes[i].promedio > maxima) {
            maxima = sistemaAcademico.estudiantes[i].promedio;
        }
    }
    return maxima;
}

double encontrarNotaMinima() {
    if (sistemaAcademico.totalEstudiantes == 0) return 0.0;
    
    double minima = sistemaAcademico.estudiantes[0].promedio;
    for (int i = 1; i < sistemaAcademico.totalEstudiantes; i++) {
        if (sistemaAcademico.estudiantes[i].promedio < minima) {
            minima = sistemaAcademico.estudiantes[i].promedio;
        }
    }
    return minima;
}

// ==================== FUNCIONES DE BÚSQUEDA Y FILTRADO ====================
int buscarEstudiantePorId(int id) {
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        if (sistemaAcademico.estudiantes[i].id == id) {
            return i;
        }
    }
    return -1; // No encontrado
}

void buscarEstudiantesPorNombre(const std::string& nombre) {
    bool encontrado = false;
    std::cout << "Estudiantes que contienen '" << nombre << "':" << std::endl;
    
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        if (sistemaAcademico.estudiantes[i].nombre.find(nombre) != std::string::npos) {
            std::cout << "- " << sistemaAcademico.estudiantes[i].nombre 
                     << " (ID: " << sistemaAcademico.estudiantes[i].id 
                     << ", Promedio: " << sistemaAcademico.estudiantes[i].promedio << ")" << std::endl;
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        std::cout << "No se encontraron estudiantes." << std::endl;
    }
}

void obtenerEstudiantesAprobados() {
    std::cout << "Estudiantes aprobados (promedio >= " << NOTA_APROBATORIA << "):" << std::endl;
    int contador = 0;
    
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        if (sistemaAcademico.estudiantes[i].promedio >= NOTA_APROBATORIA) {
            std::cout << "- " << sistemaAcademico.estudiantes[i].nombre 
                     << " (Promedio: " << sistemaAcademico.estudiantes[i].promedio << ")" << std::endl;
            contador++;
        }
    }
    
    std::cout << "Total de aprobados: " << contador << std::endl;
}

void obtenerEstudiantesReprobados() {
    std::cout << "Estudiantes reprobados (promedio < " << NOTA_APROBATORIA << "):" << std::endl;
    int contador = 0;
    
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        if (sistemaAcademico.estudiantes[i].promedio < NOTA_APROBATORIA) {
            std::cout << "- " << sistemaAcademico.estudiantes[i].nombre 
                     << " (Promedio: " << sistemaAcademico.estudiantes[i].promedio << ")" << std::endl;
            contador++;
        }
    }
    
    std::cout << "Total de reprobados: " << contador << std::endl;
}

// ==================== FUNCIONES DE ORDENAMIENTO ====================
void intercambiarEstudiantes(int indice1, int indice2) {
    Estudiante temp = sistemaAcademico.estudiantes[indice1];
    sistemaAcademico.estudiantes[indice1] = sistemaAcademico.estudiantes[indice2];
    sistemaAcademico.estudiantes[indice2] = temp;
}

void ordenarPorPromedio(bool ascendente = true) {
    // Algoritmo de burbuja
    for (int i = 0; i < sistemaAcademico.totalEstudiantes - 1; i++) {
        for (int j = 0; j < sistemaAcademico.totalEstudiantes - i - 1; j++) {
            bool condicion = ascendente ? 
                (sistemaAcademico.estudiantes[j].promedio > sistemaAcademico.estudiantes[j + 1].promedio) :
                (sistemaAcademico.estudiantes[j].promedio < sistemaAcademico.estudiantes[j + 1].promedio);
            
            if (condicion) {
                intercambiarEstudiantes(j, j + 1);
            }
        }
    }
    std::cout << "Estudiantes ordenados por promedio " 
             << (ascendente ? "ascendente" : "descendente") << std::endl;
}

void ordenarPorNombre() {
    // Algoritmo de selección
    for (int i = 0; i < sistemaAcademico.totalEstudiantes - 1; i++) {
        int minimo = i;
        for (int j = i + 1; j < sistemaAcademico.totalEstudiantes; j++) {
            if (sistemaAcademico.estudiantes[j].nombre < sistemaAcademico.estudiantes[minimo].nombre) {
                minimo = j;
            }
        }
        if (minimo != i) {
            intercambiarEstudiantes(i, minimo);
        }
    }
    std::cout << "Estudiantes ordenados por nombre alfabéticamente." << std::endl;
}

// ==================== FUNCIONES DE VISUALIZACIÓN ====================
void mostrarEstudiante(int indice) {
    if (indice < 0 || indice >= sistemaAcademico.totalEstudiantes) {
        std::cout << "Índice de estudiante inválido." << std::endl;
        return;
    }
    
    const Estudiante& est = sistemaAcademico.estudiantes[indice];
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Nombre: " << est.nombre << std::endl;
    std::cout << "ID: " << est.id << std::endl;
    std::cout << "Número de materias: " << est.numeroMaterias << std::endl;
    std::cout << "Notas: ";
    for (int i = 0; i < est.numeroMaterias; i++) {
        std::cout << est.notas[i];
        if (i < est.numeroMaterias - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Promedio: " << std::fixed << std::setprecision(2) << est.promedio << std::endl;
    std::cout << "Estado: " << (est.promedio >= NOTA_APROBATORIA ? "APROBADO" : "REPROBADO") << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void mostrarTodosLosEstudiantes() {
    if (sistemaAcademico.totalEstudiantes == 0) {
        std::cout << "No hay estudiantes registrados." << std::endl;
        return;
    }
    
    std::cout << "\n=== LISTA DE TODOS LOS ESTUDIANTES ===" << std::endl;
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        mostrarEstudiante(i);
    }
}

void mostrarEstadisticas() {
    if (sistemaAcademico.totalEstudiantes == 0) {
        std::cout << "No hay estudiantes para mostrar estadísticas." << std::endl;
        return;
    }
    
    calcularPromedios();
    
    std::cout << "\n=== ESTADÍSTICAS GENERALES ===" << std::endl;
    std::cout << "Total de estudiantes: " << sistemaAcademico.totalEstudiantes << std::endl;
    std::cout << "Promedio general: " << std::fixed << std::setprecision(2) 
             << calcularPromedioGeneral() << std::endl;
    std::cout << "Nota máxima: " << encontrarNotaMaxima() << std::endl;
    std::cout << "Nota mínima: " << encontrarNotaMinima() << std::endl;
    
    int aprobados = 0, reprobados = 0;
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        if (sistemaAcademico.estudiantes[i].promedio >= NOTA_APROBATORIA) {
            aprobados++;
        } else {
            reprobados++;
        }
    }
    
    std::cout << "Estudiantes aprobados: " << aprobados << std::endl;
    std::cout << "Estudiantes reprobados: " << reprobados << std::endl;
    std::cout << "Porcentaje de aprobación: " 
             << (aprobados * 100.0 / sistemaAcademico.totalEstudiantes) << "%" << std::endl;
}

void mostrarMaterias() {
    std::cout << "\n=== MATERIAS DISPONIBLES ===" << std::endl;
    for (int i = 0; i < sistemaAcademico.totalMaterias; i++) {
        std::cout << i + 1 << ". " << sistemaAcademico.materias[i].nombre 
                 << " (" << sistemaAcademico.materias[i].codigo << ")" << std::endl;
        std::cout << "   Créditos: " << sistemaAcademico.materias[i].creditos 
                 << ", Nota mínima: " << sistemaAcademico.materias[i].notaMinima << std::endl;
    }
}

// ==================== FUNCIONES DE UTILIDAD MATEMÁTICA ====================
double calcularDesviacionEstandar() {
    if (sistemaAcademico.totalEstudiantes == 0) return 0.0;
    
    double promedio = calcularPromedioGeneral();
    double sumaCuadrados = 0.0;
    
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        double diferencia = sistemaAcademico.estudiantes[i].promedio - promedio;
        sumaCuadrados += diferencia * diferencia;
    }
    
    return std::sqrt(sumaCuadrados / sistemaAcademico.totalEstudiantes);
}

void calcularEstadisticasAvanzadas() {
    if (sistemaAcademico.totalEstudiantes == 0) return;
    
    std::cout << "\n=== ESTADÍSTICAS AVANZADAS ===" << std::endl;
    std::cout << "Desviación estándar: " << std::fixed << std::setprecision(2) 
             << calcularDesviacionEstandar() << std::endl;
    
    // Mediana
    std::vector<double> promedios;
    for (int i = 0; i < sistemaAcademico.totalEstudiantes; i++) {
        promedios.push_back(sistemaAcademico.estudiantes[i].promedio);
    }
    
    std::sort(promedios.begin(), promedios.end());
    double mediana;
    if (promedios.size() % 2 == 0) {
        mediana = (promedios[promedios.size()/2 - 1] + promedios[promedios.size()/2]) / 2.0;
    } else {
        mediana = promedios[promedios.size()/2];
    }
    
    std::cout << "Mediana: " << mediana << std::endl;
}

// ==================== FUNCIÓN DE MENÚ PRINCIPAL ====================
void mostrarMenu() {
    std::cout << "\n=== SISTEMA DE GESTIÓN ACADÉMICA ===" << std::endl;
    std::cout << "1. Ingresar estudiante manualmente" << std::endl;
    std::cout << "2. Generar estudiantes con notas aleatorias" << std::endl;
    std::cout << "3. Mostrar todos los estudiantes" << std::endl;
    std::cout << "4. Buscar estudiante por ID" << std::endl;
    std::cout << "5. Buscar estudiantes por nombre" << std::endl;
    std::cout << "6. Mostrar estudiantes aprobados" << std::endl;
    std::cout << "7. Mostrar estudiantes reprobados" << std::endl;
    std::cout << "8. Ordenar por promedio (ascendente)" << std::endl;
    std::cout << "9. Ordenar por promedio (descendente)" << std::endl;
    std::cout << "10. Ordenar por nombre" << std::endl;
    std::cout << "11. Mostrar estadísticas generales" << std::endl;
    std::cout << "12. Mostrar estadísticas avanzadas" << std::endl;
    std::cout << "13. Mostrar materias" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    inicializarSistema();
    cargarMateriasDefault();
    
    // Generar algunos datos de ejemplo
    ingresarNotasAleatorias(10);
    calcularPromedios();
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        switch (opcion) {
            case 1:
                ingresarEstudiante();
                break;
            case 2: {
                int cantidad;
                std::cout << "¿Cuántos estudiantes generar? ";
                std::cin >> cantidad;
                ingresarNotasAleatorias(cantidad);
                calcularPromedios();
                break;
            }
            case 3:
                mostrarTodosLosEstudiantes();
                break;
            case 4: {
                int id;
                std::cout << "Ingrese ID del estudiante: ";
                std::cin >> id;
                int indice = buscarEstudiantePorId(id);
                if (indice != -1) {
                    mostrarEstudiante(indice);
                } else {
                    std::cout << "Estudiante no encontrado." << std::endl;
                }
                break;
            }
            case 5: {
                std::string nombre;
                std::cout << "Ingrese nombre o parte del nombre: ";
                std::cin.ignore();
                std::getline(std::cin, nombre);
                buscarEstudiantesPorNombre(nombre);
                break;
            }
            case 6:
                obtenerEstudiantesAprobados();
                break;
            case 7:
                obtenerEstudiantesReprobados();
                break;
            case 8:
                ordenarPorPromedio(true);
                break;
            case 9:
                ordenarPorPromedio(false);
                break;
            case 10:
                ordenarPorNombre();
                break;
            case 11:
                mostrarEstadisticas();
                break;
            case 12:
                calcularEstadisticasAvanzadas();
                break;
            case 13:
                mostrarMaterias();
                break;
            case 0:
                std::cout << "¡Hasta luego!" << std::endl;
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
        }
        
        contadorOperaciones++;
        
    } while (opcion != 0);
    
    std::cout << "Total de operaciones realizadas: " << contadorOperaciones << std::endl;
    
    return 0;
}