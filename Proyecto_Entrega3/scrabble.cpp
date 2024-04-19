#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "arbol.h"
#include "nodo.h" 
#include "scrabble.h"


// Funcion para leer un archivo y obtener un vector de palabras
std::vector<std::string> leerArchivo(const std::string &nombreArchivo) {
  //// Vector para almacenar las palabras
  std::vector<std::string> palabras;
  // abre el archivo
  std::ifstream archivo(nombreArchivo);
  std::string palabra;

  // Lee cada palabra del archivo y la agrega al vector
  if (archivo.is_open()) {
    while (getline(archivo, palabra)) {
       std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
      // Verifica que la palabra contenga caracteres especiales y o invalidos
      bool contieneCaracteresInvalidos = false;
      // recorrer cada caracter de la palabra
      for (char c : palabra) {
        // Si no es una letra marca que hay caracteres invalidos
        if (!isalpha(c)) {
          contieneCaracteresInvalidos = true;
          break;
        }
      }
      // Si no hay caracteres invalidos la agrega al vector
      if (!contieneCaracteresInvalidos) {
        palabras.push_back(palabra);
      }
    }
    archivo.close();
  } else {
    std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
  }
  // Retorna el vecto de palabras
  return palabras;
}

// Funcion para verificar si una palabra se encuentra en dos archivos
bool palabraEnArchivos(const std::string &palabra, const std::string &archivo1,
                       const std::string &archivo2) {
  // Lee los vectores de palabras de los archivos
  auto palabrasArchivo1 = leerArchivo(archivo1);
  auto palabrasArchivo2 = leerArchivo(archivo2);

  // Busca la palabra en ambos vectores
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
  std::cout << "4. inicializar_arbol" << std::endl;
  std::cout << "5. palabras_por_prefijo" << std::endl;
  std::cout << "6. palabras_por_sufijo" <<std::endl;
  std::cout << "7. grafo_de_palabras" << std::endl;
  std::cout << "8. posibles_palabras" << std::endl;
  std::cout << "9. salir" << std::endl;
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
  } else if (comando == "inicializar_arbol") {
    std::cout << "Comando 'inicializar_arbol': Inicializa la estructura de "
                 "datos para almacenar las palabras del diccionario."
              << std::endl;
    std::cout << "Uso: inicializar_arbol" << std::endl;
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
    inicializarArbol();
  } else if (primerPalabra == "palabras_por_prefijo") {
    std::string prefijo = comando.substr(comando.find(' ') + 1);
    palabrasPorPrefijo(prefijo);
  }else if (primerPalabra == "palabras_por_sufijo") {
    std::string sufijo = comando.substr(comando.find(' ') + 1);
    palabrasPorSufijo(sufijo);
  } else if (primerPalabra == "grafo_de_palabras") {
    grafoDePalabras();
  } else if (primerPalabra == "posibles_palabras") {
    posiblesPalabras();
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
void Interfaz_Scrabble::inicializarDiccionario(std::string nombreArchivo) {
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
  std::cout << "---------------------------------" << std::endl;

  inicializarArbol(nombreArchivo);
  arbolInicializado = true;

  std::cout << "---------------------------------" << std::endl;

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
  std::cout << "---------------------------------" << std::endl;
  inicializarArbolInverso(nombreArchivo);
    arbolInvertidoInicializado = true;
  std::cout << "---------------------------------" << std::endl;

}

// Funcion para calcular el puntaje de una palabra

  int Interfaz_Scrabble::puntajePalabra(std::string palabraABuscar) {
    std::transform(palabraABuscar.begin(), palabraABuscar.end(), palabraABuscar.begin(), ::tolower);

    if (!diccionarioOriginalInicializado && !diccionarioInversoInicializado) {
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
  
    if (arbolInicializado) {
        std::cout << "(Árbol ya inicializado) El árbol del diccionario ya ha sido inicializado." << std::endl;
        return;
    }

    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "(Archivo no existe) El archivo " << nombreArchivo << " no existe o no puede ser leído." << std::endl;
        return;
    }

    std::string palabra;
    while (std::getline(archivo, palabra)) {
        //std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        bool contieneCaracteresInvalidos = false;
        for (char c : palabra) {
            if (!isalpha(c)) {
                contieneCaracteresInvalidos = true;
                break;
            }
        }
        if (!contieneCaracteresInvalidos) {
            arbol.insertarPalabra(palabra);
        }
    }

    archivo.close();

    if (!arbol.estaVacio()) {
        std::cout << "(Resultado exitoso) El árbol del diccionario se ha inicializado correctamente." << std::endl;
        arbolInicializado = true;
    } else {
        std::cerr << "Error: No se pudo inicializar el árbol del diccionario." << std::endl;
    }
}

void Interfaz_Scrabble::inicializarArbolInverso(std::string nombreArchivo) {
    if (!diccionarioInversoInicializado) {
        std::ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            std::string palabra;
            Arbol arbolInverso;
            while (std::getline(archivo, palabra)) {
                bool esValida = std::all_of(palabra.begin(), palabra.end(), [](char c) {
                    return std::isalpha(c);
                });
                if (esValida) {
                    //std::reverse(palabra.begin(), palabra.end()); // Invertir la palabra
                    arbolInverso.insertarPalabra(palabra);
                }
            }
            diccionarioInversoInicializado = true;
            std::cout << "(Resultado exitoso) El árbol del diccionario inverso se ha inicializado correctamente.\n";
        } else {
            std::cout << "(Archivo no existe) El archivo " << nombreArchivo << " no existe o no puede ser leído.\n";
        }
    } else {
        std::cout << "(Árbol ya inicializado) El árbol del diccionario inverso ya ha sido inicializado.\n";
    }
}

void Interfaz_Scrabble::buscarPalabrasPorPrefijo(Nodo* nodo, const std::string& prefijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas) {
    if (!nodo) {
        return;
    }

    if (palabra.length() >= prefijo.length() && palabra.substr(0, prefijo.length()) == prefijo) {
        palabrasEncontradas.push_back(palabra);
    }

    for (char c = 'a'; c <= 'z'; ++c) {
        if (nodo->tieneHijo(c)) {
            Nodo* hijo = nodo->getHijo(c);
            buscarPalabrasPorPrefijo(hijo, prefijo, palabra + c, palabrasEncontradas);
        }
    }
}

void Interfaz_Scrabble::palabrasPorPrefijo(std::string prefijo) {
    if (!arbolInicializado) {
        std::cerr << "(Árbol no inicializado) Debe inicializar el árbol primero." << std::endl;
        return;
    }

    std::cout << "Buscando palabras que comienzan con el prefijo '" << prefijo << "'..." << std::endl;

    std::vector<std::string> palabrasEncontradas;
    buscarPalabrasPorPrefijo(arbol.getRaiz(), prefijo, "", palabrasEncontradas);

    if (palabrasEncontradas.empty()) {
        std::cerr << "(Prefijo inválido) No se encontraron palabras que comiencen con el prefijo '" << prefijo << "'." << std::endl;
        return;
    }
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    std::cout << "(Resultado exitoso) Las palabras que inician con el prefijo '" << prefijo << "' son:" << std::endl;
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    for (const auto& palabra : palabrasEncontradas) {
        int puntaje = puntajePalabra(palabra);
        if (puntaje == -1) {
            std::cerr << "Error: No se pudo calcular el puntaje para la palabra '" << palabra << "'." << std::endl;
        } else {
          std::cout << "........................." << std::endl;
            std::cout << palabra << " - Longitud: " << palabra.length() << " - Puntaje: " << puntaje << std::endl;
        }
    }
}

void Interfaz_Scrabble::buscarPalabrasPorSufijo(Nodo* nodo, const std::string& sufijo, const std::string& palabra, std::vector<std::string>& palabrasEncontradas) {
    if (!nodo) {
        return;
    }

    // Si la palabra actual tiene una longitud igual o mayor al sufijo
    // y el sufijo coincide con el final de la palabra, entonces la palabra es una coincidencia.
    if (palabra.length() >= sufijo.length() && palabra.substr(palabra.length() - sufijo.length()) == sufijo) {
        palabrasEncontradas.push_back(palabra);
    }

    // Recorremos todos los hijos del nodo actual.
    for (const auto& par : nodo->getHijos()) {
        char caracter = par.first;
        Nodo* hijo = par.second;
        
        // Llamamos recursivamente a la función para cada hijo del nodo.
        buscarPalabrasPorSufijo(hijo, sufijo, palabra + caracter, palabrasEncontradas);
    }
}


void Interfaz_Scrabble::palabrasPorSufijo(std::string sufijo) {
    std::vector<std::string> palabrasEncontradas;
    
    // Llamamos a la función buscarPalabrasPorSufijo con el nodo raíz del árbol y el sufijo dado.
    buscarPalabrasPorSufijo(arbol.getRaiz(), sufijo, "", palabrasEncontradas); // Suponiendo que 'arbol' es el árbol del diccionario
    
    // Mostramos las palabras encontradas en la salida estándar.
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    std::cout << "(Resultado exitoso) Las palabras que inician con el sufijo '" << sufijo << "' son:" << std::endl;
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;

    
    for (const auto& palabra : palabrasEncontradas) {
       int puntaje = puntajePalabra(palabra);
       if (puntaje == -1) {
        std::cerr << "Error: No se pudo calcular el puntaje para la palabra '" << palabra << "'." << std::endl;
        } else {
          std::cout << "................................." << std::endl;
            std::cout << palabra << " - Longitud: " << palabra.length() << " - Puntaje: " << puntaje << std::endl;
      }
  }
}



void Interfaz_Scrabble::grafoDePalabras() {
  // Implementación de construcción de grafo de palabras
  std::cout << "Falta implementar la construccion del grafo de palabras\n"
            << std::endl;
}

void Interfaz_Scrabble::posiblesPalabras() {
  // Implementación de búsqueda de posibles palabras
  std::cout << "Falta implementar la busqueda de posibles palabras\n"
            << std::endl;
}