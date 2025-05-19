int main() {
    int a = 5;
    float b = 3.14;
    char c = 'x';
    char* msg = "Hola mundo";

    // Variables nuevas
    int arreglo[3] = {1, 2, 3};
    double d = 9.81;
    long e = 123456789;

    // If-else
    if (a < 10) {
        b = b + 1.0;
    } else if (a == 10) {
        b = b * 2.0;
    } else {
        b = b - 1.0;
    }

    // While loop
    while (a > 0) {
        a = a - 1;
    }

    // For loop
    for (int i = 0; i < 10; i++) {
        arreglo[i % 3] = i;
    }

    // Función anidada (simulada)
    int suma(int x, int y) {
        return x + y;
    }

    int resultado = suma(3, 4);

    // Comentarios
    // Comentario de una línea

    /*
        Comentario
        de varias líneas
    */

    return 0;
}