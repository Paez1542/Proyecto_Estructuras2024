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

    bool esFinalDePalabra() const { return esFinal; }
    const std::unordered_map<char, Nodo*>& getHijos() const { return hijos; }
    char getCaracter() const;
    bool esHoja() const;
    bool tieneHijo(char c) const;
    Nodo* getHijo(char c) const;
    void agregarHijo(char c);
    void marcarComoFinal();
    bool esPalabra() const;
};

#endif // NODO_H

