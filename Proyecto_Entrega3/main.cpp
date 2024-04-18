#include "scrabble.h"
#include <iostream>
#include <stdio.h>

// para compilar en g++ -o programa_main main.cpp scrabble.cpp arbol.cpp nodo.cpp

// ejecutarlo con ./programa_main

int main() {
  // Crear una instancia de la structura Interfaz_Scrabble
  Interfaz_Scrabble interfaz;

  std::string comando;
  // Bucle principal del programa
  interfaz.mostrarListaComandos();

  do {

    std::cout << "$ ";
    // Leer el comando ingresado por el usuario
    std::getline(std::cin, comando);
    // Ejecutar el comando ingresado
    interfaz.procesarComando(comando);
  } while (comando != "salir" && comando != "exit");

  return 0;
}