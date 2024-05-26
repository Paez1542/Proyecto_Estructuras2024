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
#include "grafo.h"

struct Interfaz_Scrabble {
private:
    Arbol arbol;
    Arbol* diccionarioOriginal;
    Arbol* diccionarioInvertido;

    bool diccionarioOriginalInicializado;
    bool diccionarioInversoInicializado;
    bool arbolInicializado = false;
    bool arbolInvertidoInicializado = false;
    bool grafoInicializado = false;

    Grafo grafo;
    std::unordered_set<std::string> diccionario;

public:
    Interfaz_Scrabble() : diccionarioOriginalInicializado(false), diccionarioInversoInicializado(false), arbolInvertidoInicializado(false) {}
    
    // Funciones para la entrega N°0 y N°1
    void mostrarListaComandos();
    void mostrarAyudaComando(std::string comando);
    void procesarComando(std::string comando);
    void inicializarDiccionario(std::string nombreArchivo);
    void iniciarDiccionarioInverso(std::string nombreArchivo);
    int puntajePalabra(std::string palabraABuscar);

    // Funciones para la entrega N°2
    void inicializarArbol(std::string nombreArchivo );
    void inicializarArbolInverso(std::string nombreArchivo );
    void palabrasPorPrefijo(std::string prefijo);
    void palabrasPorSufijo(std::string sufijo);

    // Funciones auxiliares
    void buscarPalabrasPorPrefijo(Nodo* nodo, const std::string& prefijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas);
    void buscarPalabrasPorSufijo(Nodo* nodo, const std::string& sufijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas);

    // Funciones para la última entrega N°3
    void grafoDePalabras();
    void posiblesPalabras(std::string letras);

    // Funciones auxiliares
    bool esCadenaValida(const std::string& letras);
    void generarPermutaciones(const std::string& letras, std::string palabraActual, std::unordered_set<std::string>& resultados, Grafo& grafo, const std::unordered_set<std::string>& diccionario);
};

#endif
