#include "nodo.h"

// Constructor: inicializa el nodo con el caracter dado y lo marca como no final
Nodo::Nodo(char c) : caracter(c), esFinal(false) {}

// Destructor: libera la memoria de todos los nodos hijos
Nodo::~Nodo() {
    for (auto& par : hijos) {
        delete par.second;
    }
}

// Getter para el caracter del nodo
char Nodo::getCaracter() const {
    return caracter;
}

// Comprueba si el nodo es una hoja (no tiene hijos)
bool Nodo::esHoja() const {
    return hijos.empty();
}

// Comprueba si el nodo tiene un hijo con el caracter dado
bool Nodo::tieneHijo(char c) const {
    return hijos.find(c) != hijos.end();
}

// Obtiene el hijo del nodo con el caracter dado, si no existe devuelve nullptr
Nodo* Nodo::getHijo(char c) const {
    auto it = hijos.find(c);
    return it != hijos.end() ? it->second : nullptr;
}

// Getter para los hijos del nodo
const std::unordered_map<char, Nodo*>& Nodo::getHijos() const { 
    return hijos; 
}

// Agrega un hijo al nodo con el caracter dado
void Nodo::agregarHijo(char c) {
    hijos[c] = new Nodo(c);
}

// Marca el nodo como el final de una palabra
void Nodo::marcarComoFinal() {
    esFinal = true;
}

// Comprueba si el nodo es el final de una palabra
bool Nodo::esFinalDePalabra() const {
    return esFinal;
}
