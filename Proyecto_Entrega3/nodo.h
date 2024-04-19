#ifndef NODO_H
#define NODO_H

#include <string>
#include <unordered_map>

// Clase que representa un nodo en el árbol trie
class Nodo {
private:
    char caracter; // Caracter asociado al nodo
    std::unordered_map<char, Nodo*> hijos; // Mapa de caracteres a nodos hijos
    bool esFinal; // Indicador de si el nodo representa el final de una palabra

public:
    // Constructor
    Nodo(char c);

    // Destructor
    ~Nodo();

    // Métodos públicos

    // Getter para el caracter del nodo
    char getCaracter() const;

    // Comprueba si el nodo es una hoja
    bool esHoja() const;

    // Comprueba si el nodo tiene un hijo con el caracter dado
    bool tieneHijo(char c) const;

    // Obtiene el hijo del nodo con el caracter dado
    Nodo* getHijo(char c) const;

    // Agrega un hijo al nodo con el caracter dado
    void agregarHijo(char c);

    // Marca el nodo como el final de una palabra
    void marcarComoFinal();

    // Comprueba si el nodo es el final de una palabra
    bool esFinalDePalabra() const;

    // Comprueba si el nodo representa una palabra completa
    bool esPalabra() const;

    // Getter para los hijos del nodo
    const std::unordered_map<char, Nodo*>& getHijos() const;
};

#endif // NODO_H
