#include "arbol.h"

// Constructor: Crea un nuevo árbol con una raíz que representa el caracter nulo
Arbol::Arbol() : raiz(new Nodo('\0')) {}

// Destructor: Libera la memoria de la raíz, lo que también liberará de forma recursiva todos los nodos del árbol
Arbol::~Arbol() {
    delete raiz;
}

// Inserta una palabra en el árbol
void Arbol::insertarPalabra(const std::string& palabra) {
    Nodo* nodoActual = raiz;
    for (char c : palabra) {
        if (!nodoActual->tieneHijo(c)) {
            nodoActual->agregarHijo(c);
        }
        nodoActual = nodoActual->getHijo(c);
    }
    nodoActual->marcarComoFinal(); // Marca el nodo actual como el final de una palabra
}

// Busca una palabra en el árbol
bool Arbol::buscarPalabra(const std::string& palabra) const {
    Nodo* nodoActual = raiz;
    for (char c : palabra) {
        if (!nodoActual->tieneHijo(c)) {
            return false; // Si no hay un hijo correspondiente al caracter, la palabra no está en el árbol
        }
        nodoActual = nodoActual->getHijo(c);
    }
    return nodoActual != nullptr && nodoActual->esFinalDePalabra(); // Devuelve true si el nodo actual es el final de una palabra
}

// Comprueba si el árbol está vacío
bool Arbol::estaVacio() const {
    return raiz == nullptr; // El árbol está vacío si no tiene raíz
}

// Obtiene el hijo de la raíz correspondiente al caracter dado
Nodo* Arbol::getHijo(char c) const {
    return raiz ? raiz->getHijo(c) : nullptr; // Devuelve el hijo correspondiente si la raíz existe, de lo contrario, devuelve nullptr
}

// Getter para la raíz del árbol
Nodo* Arbol::getRaiz() const {
    return raiz;
}
