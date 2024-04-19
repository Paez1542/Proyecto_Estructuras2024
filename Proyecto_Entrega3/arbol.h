#ifndef ARBOL_H
#define ARBOL_H

#include "nodo.h"
#include <string>

class Arbol {
private:
    Nodo* raiz;

public:
    // Constructor: inicializa el árbol con una raíz nula
    Arbol();

    // Destructor: libera la memoria de la raíz y todos sus hijos
    ~Arbol();

    // Inserta una palabra en el árbol
    void insertarPalabra(const std::string& palabra);

    // Busca una palabra en el árbol y devuelve true si está presente, false si no
    bool buscarPalabra(const std::string& palabra) const;

    // Comprueba si el árbol está vacío (no tiene raíz)
    bool estaVacio() const;

    // Obtiene el hijo de la raíz con el caracter dado
    Nodo* getHijo(char c) const;

    // Getter para la raíz del árbol
    Nodo* getRaiz() const;
};

#endif // ARBOL_H
