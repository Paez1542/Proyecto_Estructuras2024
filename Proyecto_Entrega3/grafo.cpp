#include "grafo.h"
#include <iostream>
#include <unordered_set>

bool Grafo::patronCoincide(const std::string& patron, const std::string& palabra) {
    if (patron.size() != palabra.size()) return false;
    for (size_t i = 0; i < patron.size(); ++i) {
        if (patron[i] != '?' && patron[i] != palabra[i]) {
            return false;
        }
    }
    return true;
}

void Grafo::construirGrafo(const std::vector<std::string>& diccionario) {
    adyacencias.clear();
    std::unordered_set<std::string> diccionarioSet(diccionario.begin(), diccionario.end());

    for (const auto& palabra : diccionario) {
        for (size_t i = 0; i < palabra.size(); ++i) {
            std::string patron = palabra.substr(0, i) + '?' + palabra.substr(i + 1);
            for (const auto& otra_palabra : diccionario) {
                if (otra_palabra != palabra && patronCoincide(patron, otra_palabra)) {
                    adyacencias[palabra].push_back(otra_palabra);
                }
            }
        }
    }

    // Depuración: Mostrar el grafo
    std::cout << "Grafo construido:" << std::endl;
    for (const auto& par : adyacencias) {
        std::cout << "Palabra: " << par.first << " -> ";
        for (const auto& vecino : par.second) {
            std::cout << vecino << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> Grafo::obtenerVecinos(const std::string& palabra) const {
    auto it = adyacencias.find(palabra);
    if (it != adyacencias.end()) {
        return it->second;
    }
    return {};
}
