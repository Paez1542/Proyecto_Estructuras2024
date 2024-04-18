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

struct Interfaz_Scrabble {
private:
    Arbol arbol;
    Arbol* diccionarioOriginal;
    Arbol* diccionarioInvertido;

    bool diccionarioOriginalInicializado;
    bool diccionarioInversoInicializado;
    bool arbolInicializado = false;
    bool arbolInvertidoInicializado = false;

public:
Interfaz_Scrabble(): diccionarioOriginalInicializado(false), diccionarioInversoInicializado(false) {}
    void mostrarListaComandos();
    void mostrarAyudaComando(std::string comando);
    void procesarComando(std::string comando);
    void inicializarDiccionario(std::string nombreArchivo);
    void iniciarDiccionarioInverso(std::string nombreArchivo);
    int puntajePalabra(std::string palabraABuscar);
    void inicializarArbol(std::string nombreArchivo = "");
    void inicializarArbolInverso(std::string nombreArchivo = "");
    void palabrasPorPrefijo(std::string prefijo);
    void buscarPalabrasPorPrefijo(Nodo* nodo, const std::string& prefijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas);
    void palabrasPorSufijo(std::string sufijo);
    void grafoDePalabras();
    void posiblesPalabras();

    
};

#endif
