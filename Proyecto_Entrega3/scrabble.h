#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include "arbol.h"

// Estructura que representa la interfaz del juego de Scrabble.
struct Interfaz_Scrabble {
private:
    // Atributos privados
    Arbol arbol; // Árbol principal para almacenar el diccionario de palabras
    Arbol arbolInverso; // Declaración de arbolInverso como miembro de la clase

    Arbol* diccionarioOriginal; // Puntero al diccionario original de palabras
    Arbol* diccionarioInvertido; // Puntero al diccionario invertido de palabras
    bool diccionarioOriginalInicializado; // Indicador de inicialización del diccionario original
    bool diccionarioInversoInicializado; // Indicador de inicialización del diccionario invertido
    bool arbolInicializado = false; // Indicador de inicialización del árbol principal
    bool arbolInvertidoInicializado = false; // Indicador de inicialización del árbol invertido

public:
    // Constructor por defecto
    Interfaz_Scrabble(): diccionarioOriginalInicializado(false), diccionarioInversoInicializado(false) {}

    // Métodos públicos

    // Entrega N°0 y N°1
    void mostrarListaComandos(); // Método para mostrar la lista de comandos disponibles
    void mostrarAyudaComando(std::string comando); // Método para mostrar la ayuda de un comando específico
    void procesarComando(std::string comando); // Método para procesar un comando ingresado por el usuario
    void inicializarDiccionario(std::string nombreArchivo); // Método para inicializar el diccionario de palabras
    void iniciarDiccionarioInverso(std::string nombreArchivo); // Método para inicializar el diccionario de palabras invertido
    int puntajePalabra(std::string palabraABuscar); // Método para calcular el puntaje de una palabra

    // Entrega N°2
    void inicializarArbol(std::string nombreArchivo = ""); // Método para inicializar el árbol principal
    void inicializarArbolInverso(std::string nombreArchivo = ""); // Método para inicializar el árbol invertido

    void buscarPalabrasPorPrefijo(Nodo* nodo, const std::string& prefijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas); // Método para buscar palabras por prefijo
    void palabrasPorPrefijo(std::string prefijo); // Método para obtener palabras que comienzan con un prefijo dado

    void buscarPalabrasPorSufijo(Nodo* nodo, const std::string& sufijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas); // Método para buscar palabras por sufijo
    void palabrasPorSufijo(std::string sufijo); // Método para obtener palabras que terminan con un sufijo dado

    // Última Entrega N°3
    void grafoDePalabras(); // Método para generar el grafo de palabras
    void posiblesPalabras(); // Método para encontrar todas las posibles palabras formadas a partir de un conjunto de letras

};

#endif
