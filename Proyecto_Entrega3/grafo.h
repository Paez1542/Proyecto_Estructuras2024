#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Grafo {
private:
    std::unordered_map<std::string, std::vector<std::string>> adyacencias;

    bool patronCoincide(const std::string& patron, const std::string& palabra);

public:
    void construirGrafo(const std::vector<std::string>& diccionario);
    std::vector<std::string> obtenerVecinos(const std::string& palabra) const;
};

#endif
