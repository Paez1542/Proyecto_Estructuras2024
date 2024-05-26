#include "scrabble.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Para compilar: g++ -o programa_main main.cpp scrabble.cpp arbol.cpp nodo.cpp
// Ejecutar con: ./programa_main

void mostrarCreditos() {
    std::cout << "\033[1;33m"; // Color amarillo
    std::cout << "Programa realizado por:\n";
    std::cout << "Juan Esteban Paez\n";
    std::cout << "Juliana Bejarano\n";
    std::cout << "Daniela Moreno\n\n";
    std::cout << "\033[0m"; // Restaurar color original
}

void imprimirMenu() {
    std::cout << "\033[1;36m"; // Color cyan
    std::cout << "========================= MENU =========================\n";
    std::cout << "  1. inicializar <nombre_archivo>\n";
    std::cout << "  2. inicializar_inverso <nombre_archivo>\n";
    std::cout << "  3. puntaje_palabra <palabra>\n";
    std::cout << "  4. inicializar_arbol <nombre_archivo>\n";
    std::cout << "  5. inicializar_arbol_inverso <nombre_archivo>\n";
    std::cout << "  6. palabras_por_prefijo\n";
    std::cout << "  7. palabras_por_sufijo\n";
    std::cout << "  8. grafo_de_palabras\n";
    std::cout << "  9. posibles_palabras\n";
    std::cout << "  10. salir\n";
    std::cout << "========================================================\n";
    std::cout << "Escriba 'ayuda <comando>' para obtener información sobre los comandos disponibles.\n";
    std::cout << "\033[0m"; // Restaurar color original
}

void mostrarBienvenidaAnimada() {
    std::string mensaje = 
        "                     SSSSS   CCCCC   RRRRR     A     BBBB   BBBB   L      EEEEE  \n"
        "                    S       C        R    R   A A    B   B  B   B  L      E      \n"
        "                      SSSS  C        RRRRR   A   A   BBBBB  BBBBB  L      EEEE   \n"
        "                          S C        R   R   AAAAAA  B   B  B   B  L      E      \n"
        "                     SSSSS   CCCCC   R    R  A     A BBBB   BBBB   LLLLL  EEEEE  \n";
    std::string colores[] = {"\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;34m", "\033[1;35m"};
    int num_colores = sizeof(colores) / sizeof(colores[0]);

    for (int i = 0; i < 3; ++i) {
        std::cout << colores[i % num_colores] << mensaje << "\033[0m" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "\r" << std::string(mensaje.length(), ' ') << "\r" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Mostrar mensaje final en color verde
    std::cout << "\033[1;32m" << mensaje << "\033[0m\n";
}

void ayuda() {
    std::cout << "\033[1;31mBienvenido jugador :D \033[0m\n";
    std::cout << "A continuación aparecen las funcionalidades del programa:\n";
    std::cout << "1). $inicializar diccionario.txt: Abre el archivo txt y extrae las palabras que tenga y las guarda en el programa\n";
    std::cout << "2). $inicializar_inverso diccionario.txt: Abre el archivo txt y extrae las palabras en sentido inverso y verifica que no tengan símbolos inválidos\n";
    std::cout << "3). $puntaje_palabra <palabra>: Calcula la puntuación de una palabra según la tabla de puntuaciones de letras\n";
    std::cout << "4). $salir: Termina la ejecución de la aplicación\n";
    std::cout << "5). $inicializar_arbol diccionario.txt: Inicializa el sistema con un diccionario desde el archivo diccionario.txt\n";
    std::cout << "6). $inicializar_arbol_inverso diccionario.txt: Inicializa el sistema con un diccionario en sentido inverso\n";
    std::cout << "7). $palabras_por_prefijo <prefijo>: Busca palabras en el diccionario que inicien con el prefijo dado\n";
    std::cout << "8). $palabras_por_sufijo <sufijo>: Busca palabras en el diccionario que terminen con el sufijo dado\n";
    std::cout << "9). $grafo_de_palabras: Construye un grafo de palabras con las palabras almacenadas en el diccionario\n";
    std::cout << "10). $posibles_palabras <letras>: Muestra palabras válidas que se pueden formar con las letras dadas\n";
}

int main() {
    Interfaz_Scrabble interfaz;
    std::string comando;

    mostrarCreditos();
    mostrarBienvenidaAnimada();
    imprimirMenu();

    while (true) {
        std::cout << "\033[1;35m$ \033[0m"; // Color magenta para el prompt
        std::getline(std::cin, comando);

        if (comando == "salir" || comando == "exit") {
            break;
        } else if (comando == "ayuda") {
            ayuda();
        } else {
            interfaz.procesarComando(comando);
        }
    }

    return 0;
}
