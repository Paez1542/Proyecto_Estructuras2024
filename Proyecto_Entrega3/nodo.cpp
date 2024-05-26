#include "nodo.h"

Nodo::Nodo(char c) : caracter(c), esFinal(false) {}

Nodo::~Nodo() {
    for (auto& par : hijos) {
        delete par.second;
    }
}

char Nodo::getCaracter() const {
    return caracter;
}

bool Nodo::esHoja() const {
    return hijos.empty();
}

bool Nodo::tieneHijo(char c) const {
    return hijos.find(c) != hijos.end();
}

Nodo* Nodo::getHijo(char c) const {
    auto it = hijos.find(c);
    return it != hijos.end() ? it->second : nullptr;
}

void Nodo::agregarHijo(char c) {
    if (!tieneHijo(c)) {
        hijos[c] = new Nodo(c);
    }
}

void Nodo::marcarComoFinal() {
    esFinal = true;
}
