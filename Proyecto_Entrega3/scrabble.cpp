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
  std::cout << "** SISTEMA DE APOYO DE SCRABBLE **" << std::endl;
  std::cout << "---------------------------------" << std::endl;

  std::cout << "\n** LISTA DE COMANDOS **\n" << std::endl;
  std::cout << "1. inicializar <nombre_archivo>" << std::endl;
  std::cout << "2. inicializar_inverso <nombre_archivo>" << std::endl;
  std::cout << "3. puntaje_palabra <palabra>" << std::endl;
  std::cout << "4. inicializar_arbol" << std::endl;
  std::cout << "5. palabras_por_prefijo" << std::endl;
  std::cout << "6. grafo_de_palabras" << std::endl;
  std::cout << "7. posibles_palabras" << std::endl;
  std::cout << "8. salir" << std::endl;
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
    std::cout << "Uso: palabras_por_prefijo" << std::endl;
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
    int puntajeCalculado = puntajePalabra(palabraABuscar);
    std::cout << "El puntaje de la palabra " << palabraABuscar
                << " es: " << puntajeCalculado << std::endl;
  } else if (primerPalabra == "inicializar_arbol") {
    inicializarArbol();
  } else if (primerPalabra == "palabras_por_prefijo") {
    std::string prefijo = comando.substr(comando.find(' ') + 1);
    palabrasPorPrefijo(prefijo);
    std::cout << "holatu" << std::endl;
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

    std::cout << "Estado de inicialización - Diccionario Original: "
              << diccionarioOriginalInicializado << std::endl;
    std::cout << "Estado de inicialización - Diccionario Inverso: "
              << diccionarioInversoInicializado << std::endl;

    if (!diccionarioOriginalInicializado && !diccionarioInversoInicializado) {
        std::cerr << "Error: Los archivos no han sido inicializados correctamente."
                  << std::endl;
        return 0; // Retorna un valor predeterminado o que tenga sentido en tu programa
    } else {
        std::cout << "Calculando puntaje para la palabra: " << palabraABuscar
                  << std::endl;
    }

    if (palabraABuscar.empty()) {
        std::cerr << "Error: La palabra ingresada está vacía." << std::endl;
        return 0; // Retorna un valor predeterminado o que tenga sentido en tu programa
    }

    for (char c : palabraABuscar) {
        if (!isalpha(c)) {
            std::cerr << "Error: La palabra contiene caracteres no alfabéticos."
                      << std::endl;
            return 0; // Retorna un valor predeterminado o que tenga sentido en tu programa
        }
    }

    bool enDiccionarioOriginal =
        palabraEnArchivos(palabraABuscar, "words1.txt", "words2.txt");

    bool enDiccionarioInverso = palabraEnArchivos(
        palabraABuscar, "words1.txt_inverso.txt", "words2.txt_inverso.txt");

    if (!enDiccionarioOriginal && !enDiccionarioInverso) {
        std::cerr
            << "Error: La palabra no se encuentra en ninguno de los diccionarios."
            << std::endl;
        return 0; // Retorna un valor predeterminado o que tenga sentido en tu programa
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

    return puntaje; // Devuelve el puntaje calculado
}



void Interfaz_Scrabble::inicializarArbol(std::string nombreArchivo) {
    // Verificar si el árbol ya está inicializado
    if (arbolInicializado) {
        std::cout << "(Árbol ya inicializado) El árbol del diccionario ya ha sido inicializado." << std::endl;
        return;
    }

    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "(Archivo no existe) El archivo " << nombreArchivo << " no existe o no puede ser leído." << std::endl;
        return;
    }
    Arbol arbol;
    std::string palabra;
    while (std::getline(archivo, palabra)) {
        // Transformar la palabra a minúsculas
        std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);

        // Verificar que la palabra no contenga caracteres inválidos
        bool contieneCaracteresInvalidos = false;
        for (char c : palabra) {
            if (!isalpha(c)) {
                contieneCaracteresInvalidos = true;
                break;
            }
        }

        if (!contieneCaracteresInvalidos) {
            // Insertar la palabra en el árbol
            arbol.insertarPalabra(palabra);
        }
    }

    archivo.close();

    // Verificar si el árbol se inicializó correctamente
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
            Arbol arbolInverso; // Crear un objeto Arbol para el diccionario inverso
            while (std::getline(archivo, palabra)) {
                // Verificar si la palabra contiene solo caracteres válidos
                bool esValida = std::all_of(palabra.begin(), palabra.end(), [](char c) {
                    return std::isalpha(c);
                });
                if (esValida) {
                    // Invertir la palabra antes de insertarla en el árbol
                    //std::reverse(palabra.begin(), palabra.end());
                    arbolInverso.insertarPalabra(palabra); // Llamar a insertarPalabra en el objeto arbolInverso
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

void Interfaz_Scrabble::buscarPalabrasPorPrefijo(Nodo* nodoActual, const std::string& prefijo, std::string palabra, std::vector<std::string>& palabrasEncontradas) {
    // Verifica si el nodo actual es nulo
    if (!nodoActual) {
        return;
    }
    // Agrega el caracter del nodo actual a la palabra en construcción
    palabra += nodoActual->getCaracter();
    // Si el nodo actual marca el final de una palabra, la agrega al vector de palabras encontradas
    if (nodoActual->esFinalDePalabra()) {
        palabrasEncontradas.push_back(palabra);
    }
    // Recorre todos los hijos del nodo actual
    for (const auto& par : nodoActual->getHijos()) {
        buscarPalabrasPorPrefijo(par.second, prefijo, palabra, palabrasEncontradas);
    }
}

void Interfaz_Scrabble::palabrasPorPrefijo(const std::string& prefijo) {
    // Convierte el prefijo a minúsculas
    //std::transform(prefijo.begin(), prefijo.end(), prefijo.begin(), ::tolower);
    std::cout << "Tamano del prefijo: " << prefijo.size() << std::endl;
    if (arbol->size() > 0) {
    std::cout << "El árbol tiene nodos." << std::endl;
    } else {
    std::cout << "El árbol está vacío." << std::endl;
  }
    std::vector<std::string> palabrasEncontradas;

    if (!arbolInicializado) {
        std::cerr << "Error: El árbol del diccionario no ha sido inicializado." << std::endl;
        return;
    }
    
    Nodo* nodoActual = arbol->getRaiz();
    std::cout << "Nodo raíz: " << nodoActual->getCaracter() << std::endl;
    if (nodoActual->esHoja()) {
    std::cerr << "El nodo actual no tiene hijos." << std::endl;
    return;
    }
    // Recorre el árbol buscando el nodo correspondiente del prefijo
    for (char c : prefijo) {
    std::cout << "Carácter actual: " << c << std::endl;
    std::cout << "hola" << std::endl;
        nodoActual = nodoActual->getHijo(c);
        if (!nodoActual) {
            std::cerr << "(Prefijo inválido) El prefijo '" << prefijo << "' no pudo encontrarse en el diccionario." << std::endl;
            return;
        }
    }
    std::cout << "Después del bucle for" << std::endl;
    // Llama a la función para buscar palabras por prefijo a partir del nodo encontrado
    buscarPalabrasPorPrefijo(nodoActual, prefijo, "", palabrasEncontradas);

    if (palabrasEncontradas.empty()) {
        std::cerr << "(Prefijo no encontrado) No hay palabras en el diccionario que inicien con el prefijo '" << prefijo << "'." << std::endl;
    } else {
        std::cout << "(Resultado exitoso) Las palabras que inician con el prefijo '" << prefijo << "' son:" << std::endl;
        for (const std::string& palabra : palabrasEncontradas) {
            std::cout << palabra << " - Longitud: " << palabra.length() << " - Puntaje: " << puntajePalabra(palabra) << std::endl;
        }
    }
}

/*void Interfaz_Scrabble::palabrasPorPrefijo(std::string prefijo) {
    if (!arbolInicializado) {
        std::cerr << "(Árbol no inicializado) Debe inicializar el árbol primero." << std::endl;
        return;
    }

    std::cout << "Buscando palabras que comienzan con el prefijo '" << prefijo << "'..." << std::endl;

    std::vector<std::string> palabrasEncontradas;
    buscarPalabrasPorPrefijo(arbol->getRaiz(), prefijo, "", palabrasEncontradas);

    if (palabrasEncontradas.empty()) {
        std::cerr << "(Prefijo inválido) Prefijo '" << prefijo << "' no pudo encontrarse en el diccionario." << std::endl;
        return;
    }

    std::cout << "(Resultado exitoso) Las palabras que inician con el prefijo '" << prefijo << "' son:" << std::endl;
    for (const auto& palabra : palabrasEncontradas) {
        std::cout << palabra << " - Longitud: " << palabra.length() << std::endl;
        puntajePalabra(palabra);
    }
}*/





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