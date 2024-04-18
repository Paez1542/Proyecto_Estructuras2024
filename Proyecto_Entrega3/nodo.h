#ifndef NODO_H
#define NODO_H

#include <string>
#include <unordered_map>

class Nodo {
private:
    char caracter;
    std::unordered_map<char, Nodo*> hijos;
    bool esFinal;

public:
    Nodo(char c);
    ~Nodo();

    char getCaracter() const;
    bool esHoja() const;
    bool tieneHijo(char c) const;
    Nodo* getHijo(char c) const;
    void agregarHijo(char c);
    void marcarComoFinal();
    bool esFinalDePalabra() const;
    bool esPalabra() const;

    const std::unordered_map<char, Nodo*>& getHijos() const;
};

#endif // NODO_H
