#ifndef ARBOL_H
#define ARBOL_H

#include "nodo.h"
#include <string>

class Arbol {
private:
  Nodo *raiz;

public:
  Arbol();
  ~Arbol();

  void insertarPalabra(const std::string &palabra);
  bool buscarPalabra(const std::string &palabra) const;
  bool estaVacio() const;
  Nodo* getHijo(char c) const;
  Nodo* getRaiz() const;


};
//#include "arbol.cpp"
#endif // ARBOL_H

