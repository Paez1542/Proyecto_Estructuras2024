#include "arbol.h"



Arbol::Arbol() : raiz(new Nodo('\0')) {}
//Arbol::Arbol() : raiz(nullptr), contador(0) {}

Arbol::~Arbol() {
    delete raiz; // Esto liberará recursivamente toda la estructura del árbol
}

int Arbol::size() const {
    return contador;
}

void Arbol::insertarPalabra(const std::string& palabra) {
    Nodo* nodoActual = raiz;
    for (char c : palabra) {
        if (!nodoActual->tieneHijo(c)) {
            nodoActual->agregarHijo(c);
        }
        nodoActual = nodoActual->getHijo(c);
    }
    nodoActual->marcarComoFinal();
}

bool Arbol::buscarPalabra(const std::string& palabra) const {
    Nodo* nodoActual = raiz;
    for (char c : palabra) {
        if (!nodoActual->tieneHijo(c)) {
            return false;
        }
        nodoActual = nodoActual->getHijo(c);
    }
    return nodoActual!= nullptr && nodoActual->esFinalDePalabra();
}

bool Arbol::estaVacio() const {
    return raiz == nullptr;
}

Nodo* Arbol::getHijo(char c) const {
    return raiz? raiz->getHijo(c) : nullptr;
}

Nodo* Arbol::getRaiz() const {
    return raiz;
}
