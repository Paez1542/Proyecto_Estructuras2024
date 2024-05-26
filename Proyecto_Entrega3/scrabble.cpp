#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "arbol.h"
#include "scrabble.h"


std::vector<std::string> leerArchivo(const std::string &nombreArchivo) {
    std::vector<std::string> palabras;
    std::ifstream archivo(nombreArchivo);
    std::string palabra;

    if (archivo.is_open()) {
        while (getline(archivo, palabra)) {
            std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            bool contieneCaracteresInvalidos = false;
            for (char c : palabra) {
                if (!isalpha(c)) {
                    contieneCaracteresInvalidos = true;
                    break;
                }
            }
            if (!contieneCaracteresInvalidos) {
                palabras.push_back(palabra);
            }
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
    return palabras;
}

bool palabraEnArchivos(const std::string &palabra, const std::string &archivo1,
                       const std::string &archivo2) {
    auto palabrasArchivo1 = leerArchivo(archivo1);
    auto palabrasArchivo2 = leerArchivo(archivo2);

    return std::find(palabrasArchivo1.begin(), palabrasArchivo1.end(), palabra) !=
             palabrasArchivo1.end() ||
         std::find(palabrasArchivo2.begin(), palabrasArchivo2.end(), palabra) !=
             palabrasArchivo2.end();
}


// Funcion para mostar los comandos disponibles
void Interfaz_Scrabble::mostrarListaComandos() {
  std::cout << "---------------------------------" << std::endl;
  std::cout << "* SISTEMA DE APOYO DE SCRABBLE *" << std::endl;
  std::cout << "---------------------------------" << std::endl;

  std::cout << "\n** LISTA DE COMANDOS **\n" << std::endl;
  std::cout << "1. inicializar <nombre_archivo>" << std::endl;
  std::cout << "2. inicializar_inverso <nombre_archivo>" << std::endl;
  std::cout << "3. puntaje_palabra <palabra>" << std::endl;
  std::cout << "4. inicializar_arbol <nombre_archivo>"<< std::endl;
  std::cout << "5. inicializar_arbol_inverso <nombre_archivo>"<< std::endl;
  std::cout << "6. palabras_por_prefijo" << std::endl;
  std::cout << "7. palabras_por_sufijo" <<std::endl;
  std::cout << "8. grafo_de_palabras" << std::endl;
  std::cout << "9. posibles_palabras" << std::endl;
  std::cout << "10. salir" << std::endl;
  std::cout << "---------------------------------\n" << std::endl;
  std::cout << "** Escriba 'ayuda <comando>' para obtener información sobre "
               "los comandos disponibles. **"
            << std::endl;
}

// Funcion para mostrar la ayuda de un comando especifico
void Interfaz_Scrabble::mostrarAyudaComando(std::string comando) {
  if (comando == "inicializar") {
    std::cout << "Comando 'inicializar': Inicializa el diccionario a partir "
                 "del archivo especificado."
              << std::endl;
    std::cout << "Uso: inicializar <nombre_archivo>" << std::endl;
  } else if (comando == "inicializar_inverso") {
    std::cout << "Comando 'inicializar_inverso': Inicializa el diccionario "
                 "inverso a partir del archivo especificado."
              << std::endl;
    std::cout << "Uso: inicializar_inverso <nombre_archivo>" << std::endl;
  } else if (comando == "puntaje_palabra") {
    std::cout << "Comando 'puntaje_palabra': Calcula el puntaje de la palabra "
                 "especificada."
              << std::endl;
    std::cout << "Uso: puntaje_palabra <palabra>" << std::endl;
  } else if (comando == "inicializar_arbol <nombre_archivo>") {
    std::cout << "Comando 'inicializar_arbol': Inicializa la estructura de "
                 "datos para almacenar las palabras del diccionario."
              << std::endl;
    std::cout << "Uso: inicializar_arbol <nombre_archivo>" << std::endl;
  }else if (comando == "inicializar_arbol_inverso <nombre_archivo>") {
    std::cout << "Comando 'inicializar_arbol_inverso': Inicializa la estructura de "
                 "datos para almacenar las palabras del diccionario inverso."
              << std::endl;
    std::cout << "Uso: inicializar_arbol <nombre_archivo>" << std::endl;
  } else if (comando == "palabras_por_prefijo") {
    std::cout << "Comando 'palabras_por_prefijo': Muestra todas las palabras "
                 "posibles a construir a partir de un prefijo dado."
              << std::endl;
    std::cout << "Uso: palabras_por_prefijo <prefijo>" << std::endl;
   } else if (comando == "palabras_por_sufijo") {
    std::cout << "Comando 'palabras_por_sufijo': Muestra todas las palabras "
                 "posibles a construir a partir de un sufijo dado."
              << std::endl;
    std::cout << "Uso: palabras_por_sufijo <sufijo>" << std::endl;
  } else if (comando == "grafo_de_palabras") {
    std::cout << "Comando 'grafo_de_palabras': Construye un grafo de palabras "
                 "a partir del diccionario."
              << std::endl;
    std::cout << "Uso: grafo_de_palabras" << std::endl;
  } else if (comando == "posibles_palabras") {
    std::cout
        << "Comando 'posibles_palabras': Muestra todas las posibles palabras "
           "válidas a construir a partir de un conjunto de letras."
        << std::endl;
    std::cout << "Uso: posibles_palabras" << std::endl;
  } else if (comando == "ayuda" || comando == "help") {
    std::cout
        << "Comando 'ayuda/help': Muestra la ayuda para un comando específico."
        << std::endl;
    std::cout << "Uso: ayuda <nombre_comando>" << std::endl;
  } else {
    std::cerr << "Error: Comando no reconocido. Use 'ayuda' para ver la lista "
                 "de comandos disponibles."
              << std::endl;
  }
}

// Funcion para procesar un comando introducido por el usuario
void Interfaz_Scrabble::procesarComando(std::string comando) {
  if (comando.empty()) {
    std::cerr << "Error: No se proporcionó ningún comando." << std::endl;
    return;
  }

  // Divide el comando en palabras separadas por espacios
  std::string primerPalabra = comando.substr(0, comando.find(' '));
  if (primerPalabra == "ayuda" || primerPalabra == "help") {
    std::string comandoAyuda = comando.substr(comando.find(' ') + 1);
    // Si el comando es "ayuda" o "help", muestra la ayuda para el comando
    // especificado
    mostrarAyudaComando(comandoAyuda);
  } else if (primerPalabra == "inicializar") {
    // Si el comando es inicializar , inicializa el diccionario a partir del
    // archivo especificado
    std::string nombreArchivo = comando.substr(comando.find(' ') + 1);
    inicializarDiccionario(nombreArchivo);
  } else if (primerPalabra == "inicializar_inverso") {
    // Si el comando es inicializar_inverso, inicializa el diccionario inverso a
    // partir del archivo especificado
    std::string nombreArchivo = comando.substr(comando.find(' ') + 1);
    iniciarDiccionarioInverso(nombreArchivo);

  } else if (primerPalabra == "puntaje_palabra") {
    std::string palabraABuscar = comando.substr(comando.find(' ') + 1);
    puntajePalabra(palabraABuscar);

  } else if (primerPalabra == "inicializar_arbol") {
    std::string nombreArchivo = comando.substr(comando.find(' ') + 1);
    inicializarArbol(nombreArchivo);

  } else if (primerPalabra == "inicializar_arbol_inverso") {
    std::string nombreArchivo = comando.substr(comando.find(' ') + 1);
    inicializarArbolInverso(nombreArchivo);

  } else if (primerPalabra == "palabras_por_prefijo") {
    std::string prefijo = comando.substr(comando.find(' ') + 1);
    palabrasPorPrefijo(prefijo);
  }else if (primerPalabra == "palabras_por_sufijo") {
    std::string sufijo = comando.substr(comando.find(' ') + 1);
    palabrasPorSufijo(sufijo);
  } else if (primerPalabra == "grafo_de_palabras") {
    grafoDePalabras();
  } else if (primerPalabra == "posibles_palabras") {
    std::string letras = comando.substr(comando.find(' ') + 1); 
    posiblesPalabras(letras); 
  } else if (primerPalabra == "salir" || primerPalabra == "exit") {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Gracias por usar el programa, la buena" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    return;

  } else {
    std::cerr << "Error: Comando no reconocido. Use 'ayuda' para ver la lista "
                 "de comandos disponibles."
              << std::endl;
  }
}

// Funcion para inicializar el diccionario a partir de un archivo
/*void Interfaz_Scrabble::inicializarDiccionario(std::string nombreArchivo) {
  std::cout << "Inicializando diccionario desde el archivo: " << nombreArchivo
            << std::endl;

  // Leer el archivo y cargar las palabras en el diccionario
  std::vector<std::string> palabras = leerArchivo(nombreArchivo);
  if (!palabras.empty()) {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "El diccionario fue inicializado correctamente." << std::endl;
    diccionarioOriginalInicializado = true;
  } else {
    std::cerr << "El diccionario no fue inicializado correctamente."
              << std::endl;
  }
}
*/

void Interfaz_Scrabble::inicializarDiccionario(std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::string palabra;

    if (archivo.is_open()) {
        while (archivo >> palabra) {
            // Convertir palabra a minúsculas
            std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            diccionario.insert(palabra);
        }
        archivo.close();
        diccionarioOriginalInicializado = true;
        std::cout << "El diccionario fue inicializado correctamente." << std::endl;

        // Depuración: Mostrar el contenido del diccionario
        std::cout << "Contenido del diccionario:" << std::endl;
        for (const auto& palabra : diccionario) {
            std::cout << palabra << std::endl;
        }
    } else {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
    }
}


// Funcion para inicializar el diccionario inverso a partir de un archivo
void Interfaz_Scrabble::iniciarDiccionarioInverso(std::string nombreArchivo) {

  std::cout << "Inicializando diccionario inverso desde el archivo: "
            << nombreArchivo << std::endl;

  // Leer el archivo y cargar las palabras en un vector
  std::vector<std::string> palabras = leerArchivo(nombreArchivo);

  // Invertir cada palabra y guardarla en un nuevo archivo
  std::ofstream archivoInverso(nombreArchivo + "_inverso.txt");
  if (archivoInverso.is_open()) {
    for (const std::string &palabra : palabras) {

      std::string palabraInversa = palabra;

      std::reverse(palabraInversa.begin(), palabraInversa.end());
      archivoInverso << palabraInversa << std::endl;
    }
    archivoInverso.close();
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Diccionario inverso inicializado correctamente." << std::endl;
    diccionarioInversoInicializado = true;
  } else {
    std::cerr << "Error: No se pudo abrir el archivo para escribir el "
                 "diccionario inverso."
              << std::endl;
  }
}

// Funcion para calcular el puntaje de una palabra

  int Interfaz_Scrabble::puntajePalabra(std::string palabraABuscar) {
    std::transform(palabraABuscar.begin(), palabraABuscar.end(), palabraABuscar.begin(), ::tolower);

    if ((!diccionarioOriginalInicializado && !diccionarioInversoInicializado) && (!arbolInicializado && !arbolInvertidoInicializado)) {
        std::cerr << "Error: Los archivos no han sido inicializados correctamente." << std::endl;
        return -1; // Retornar un valor inválido para indicar un error
    }

    if (palabraABuscar.empty()) {
        std::cerr << "Error: La palabra ingresada está vacía." << std::endl;
        return -1; // Retornar un valor inválido para indicar un error
    }

    for (char c : palabraABuscar) {
        if (!isalpha(c)) {
            std::cerr << "Error: La palabra contiene caracteres no alfabéticos." << std::endl;
            return -1; // Retornar un valor inválido para indicar un error
        }
    }

    int puntaje = 0;
    for (char c : palabraABuscar) {
        switch (tolower(c)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'n':
        case 'r':
        case 't':
        case 'l':
        case 's':
        case 'u':
            puntaje += 1;
            break;
        case 'd':
        case 'g':
            puntaje += 2;
            break;
        case 'b':
        case 'c':
        case 'm':
        case 'p':
            puntaje += 3;
            break;
        case 'f':
        case 'h':
        case 'v':
        case 'w':
        case 'y':
            puntaje += 4;
            break;
        case 'k':
            puntaje += 5;
            break;
        case 'j':
        case 'x':
            puntaje += 8;
            break;
        case 'q':
        case 'z':
            puntaje += 10;
            break;
        default:
            break;
        }
    }

    std::cout << "El puntaje de la palabra " << palabraABuscar << " es: " << puntaje << std::endl;
    return puntaje; // Devolver el puntaje calculado
}

void Interfaz_Scrabble::inicializarArbol(std::string nombreArchivo) {
    std::cout << "Inicializando árbol desde el archivo: " << nombreArchivo << std::endl;
    std::vector<std::string> palabras = leerArchivo(nombreArchivo);
    for (const std::string &palabra : palabras) {
        arbol.insertarPalabra(palabra);
    }
    arbolInicializado = true;
    std::cout << "Árbol inicializado correctamente." << std::endl;
}

void Interfaz_Scrabble::inicializarArbolInverso(std::string nombreArchivo) {
    std::cout << "Inicializando árbol inverso desde el archivo: " << nombreArchivo << std::endl;
    std::vector<std::string> palabras = leerArchivo(nombreArchivo);
    for (std::string palabra : palabras) {
        std::reverse(palabra.begin(), palabra.end());
        arbol.insertarPalabra(palabra);
    }
    arbolInvertidoInicializado = true;
    std::cout << "Árbol inverso inicializado correctamente." << std::endl;
}


void Interfaz_Scrabble::buscarPalabrasPorPrefijo(Nodo* nodo, const std::string& prefijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas) {
    if (nodo->esFinalDePalabra()) {
        palabrasEncontradas.push_back(palabra);
    }
    for (const auto& par : nodo->getHijos()) {
        buscarPalabrasPorPrefijo(par.second, prefijo, palabra + par.first, palabrasEncontradas);
    }
}

void Interfaz_Scrabble::palabrasPorPrefijo(std::string prefijo) {
  if (!arbolInicializado) {
        std::cerr << "Error: El árbol inverso no ha sido inicializado." << std::endl;
        return;
    }

    Nodo* nodoActual = arbol.getRaiz();
    for (char c : prefijo) {
        if (!nodoActual->tieneHijo(c)) {
            std::cerr << "No se encontraron palabras con el prefijo: " << prefijo << std::endl;
            return;
        }
        nodoActual = nodoActual->getHijo(c);
    }
    std::vector<std::string> palabrasEncontradas;
    buscarPalabrasPorPrefijo(nodoActual, prefijo, prefijo, palabrasEncontradas);
    if (!palabrasEncontradas.empty()) {
        std::cout << "Palabras encontradas con el prefijo '" << prefijo << "':" << std::endl;
        int indice = 1;
        for (const std::string& palabra : palabrasEncontradas) {
            int puntaje = puntajePalabra(palabra);
            std::cout << indice << ". " << palabra << " (Longitud: " << palabra.size() << ", Puntaje: " << puntaje << ")" << std::endl;
            indice++;
        }
    } else {
        std::cerr << "No se encontraron palabras con el prefijo: " << prefijo << std::endl;
    }
}



void Interfaz_Scrabble::buscarPalabrasPorSufijo(Nodo* nodo, const std::string& sufijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas) {
    if (nodo->esFinalDePalabra()) {
        std::string palabraOriginal = palabra;
        std::reverse(palabraOriginal.begin(), palabraOriginal.end());
        palabrasEncontradas.push_back(palabraOriginal);
    }
    for (const auto& par : nodo->getHijos()) {
        buscarPalabrasPorSufijo(par.second, sufijo, palabra + par.first, palabrasEncontradas);
    }
}

void Interfaz_Scrabble::palabrasPorSufijo(std::string sufijo) {
    if (!arbolInvertidoInicializado) {
        std::cerr << "Error: El árbol inverso no ha sido inicializado." << std::endl;
        return;
    }

    // Invertir el sufijo para buscar en el árbol inverso
    std::reverse(sufijo.begin(), sufijo.end());
    
    Nodo* nodoActual = arbol.getRaiz();
    for (char c : sufijo) {
        if (!nodoActual->tieneHijo(c)) {
            std::cerr << "Sufijo inválido: Sufijo " << sufijo << " no pudo encontrarse en el diccionario." << std::endl;
            return;
        }
        nodoActual = nodoActual->getHijo(c);
    }
    
    std::vector<std::string> palabrasEncontradas;
    buscarPalabrasPorSufijo(nodoActual, sufijo, sufijo, palabrasEncontradas);
    
    if (!palabrasEncontradas.empty()) {
        std::cout << "Las palabras que terminan con este sufijo son:" << std::endl;
        int indice = 1;
        for (const std::string& palabra : palabrasEncontradas) {
            int puntaje = puntajePalabra(palabra);
            std::cout << indice << ". " << palabra << " (Longitud: " << palabra.size() << ", Puntaje: " << puntaje << ")" << std::endl;
            indice++;
        }
    } else {
        std::cerr << "Sufijo inválido: Sufijo " << sufijo << " no pudo encontrarse en el diccionario." << std::endl;
    }
}


void Interfaz_Scrabble::grafoDePalabras() {
    if (!diccionarioOriginalInicializado) {
        std::cerr << "Error: El diccionario  no ha sido inicializado." << std::endl;
        return;
    }
    
    grafo.construirGrafo(std::vector<std::string>(diccionario.begin(), diccionario.end()));
    grafoInicializado = true;
    std::cout << "Grafo construido correctamente." << std::endl;
    /*if(grafoInicializado == true){
      std::cout << "Si se puso en true" << std::endl;
    }else{
      std::cout << "No" << std::endl;
    }*/
}

bool Interfaz_Scrabble::esCadenaValida(const std::string& letras) {
    for (char c : letras) {
        if (!isalpha(c) && c != '?') {
            return false;
        }
    }
    return true;
}

/*void Interfaz_Scrabble::generarPermutaciones(const std::string& letras, std::string palabraActual, std::unordered_set<std::string>& resultados, Grafo& grafo, const std::unordered_set<std::string>& diccionario) {
    // Depuración: Mostrar la palabra actual y el conjunto de resultados
    std::cout << "Generando permutaciones para la palabra actual: " << palabraActual << std::endl;

    if (diccionario.find(palabraActual) != diccionario.end()) {
        resultados.insert(palabraActual);
        for (const auto& vecino : grafo.obtenerVecinos(palabraActual)) {
            resultados.insert(vecino);
        }
    }

    if (palabraActual.size() < letras.size()) {
        for (size_t i = 0; i < letras.size(); ++i) {
            if (letras[i] != '?') {
                std::string nuevaPalabraActual = palabraActual + letras[i];
                std::string nuevaLetras = letras.substr(0, i) + letras.substr(i + 1);
                generarPermutaciones(nuevaLetras, nuevaPalabraActual, resultados, grafo, diccionario);
            } else {
                for (char c = 'a'; c <= 'z'; ++c) {
                    std::string nuevaPalabraActual = palabraActual + c;
                    std::string nuevaLetras = letras.substr(0, i) + letras.substr(i + 1);
                    generarPermutaciones(nuevaLetras, nuevaPalabraActual, resultados, grafo, diccionario);
                }
            }
        }
    }
}
*/

void Interfaz_Scrabble::generarPermutaciones(const std::string& letras, std::string palabraActual, std::unordered_set<std::string>& resultados, Grafo& grafo, const std::unordered_set<std::string>& diccionario) {
    // Depuración: Mostrar la palabra actual
    std::cout << "Generando permutaciones para la palabra actual: " << palabraActual << std::endl;

    // Generar todas las permutaciones primero
    if (!palabraActual.empty()) {
        resultados.insert(palabraActual);
    }

    // Generar permutaciones recursivamente
    for (size_t i = 0; i < letras.size(); ++i) {
        char letraActual = letras[i];

        // Si es un comodín, generar todas las posibles letras del alfabeto
        if (letraActual == '?') {
            for (char c = 'a'; c <= 'z'; ++c) {
                std::string nuevaPalabra = palabraActual + c;
                std::string nuevasLetras = letras.substr(0, i) + letras.substr(i + 1);
                generarPermutaciones(nuevasLetras, nuevaPalabra, resultados, grafo, diccionario);
            }
        } else { // Si es una letra normal, simplemente agregarla a la palabra actual
            std::string nuevaPalabra = palabraActual + letraActual;
            std::string nuevasLetras = letras.substr(0, i) + letras.substr(i + 1);
            generarPermutaciones(nuevasLetras, nuevaPalabra, resultados, grafo, diccionario);
        }
    }

    // Verificar si la palabra actual es válida y está en el diccionario
    if (!palabraActual.empty() && diccionario.find(palabraActual) != diccionario.end()) {
        resultados.insert(palabraActual);
    }
}


void Interfaz_Scrabble::posiblesPalabras(std::string letras) {
    std::transform(letras.begin(), letras.end(), letras.begin(), ::tolower);
    if (!esCadenaValida(letras)) {
        std::cerr << "Letras inválidas: La cadena letras contiene símbolos inválidos." << std::endl;
        return;
    }

    // Verificar que los diccionarios y el grafo estén inicializados
    if (!diccionarioOriginalInicializado || !grafoInicializado) {
        std::cerr << "Error: Los archivos no han sido inicializados correctamente." << std::endl;
        return;
    }

    std::unordered_set<std::string> resultados;
    generarPermutaciones(letras, "", resultados, grafo, diccionario);

    std::vector<std::string> palabrasValidas;
    for (const auto& palabra : resultados) {
        if (diccionario.find(palabra) != diccionario.end()) {
            palabrasValidas.push_back(palabra);
        }
    }

    if (!palabrasValidas.empty()) {
        std::cout << "Las posibles palabras a construir con las letras " << letras << " son:" << std::endl;
        for (const auto& palabra : palabrasValidas) {
            int puntaje = puntajePalabra(palabra);
            int indice = 1;
            std::cout<<indice <<"." << palabra << " (Longitud: " << palabra.size() << ", Puntaje: " << puntaje << ")" << std::endl;
            indice ++;
        }
    } else {
        std::cout << "No se encontraron palabras válidas con las letras proporcionadas." << std::endl;
    }
}
