/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include "inputFunctions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <utility>

/**
  * Función para obtener el archivo de salida
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return Nombre del archivo de salida
  */
std::string InputFunctions::obtenerArchivoEntrada(int argc, char* argv[]) {
  std::string file_name = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-i") {
      if (i + 1 < argc) {
        file_name = argv[i + 1];
      } else {
        std::cerr << "Error: Falta el nombre del archivo de entrada." << std::endl;
        exit(1);
      }
    }
  }
  return file_name;
}

/** 
  * Función para obtener el archivo de salida
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return Nombre del archivo de salida
  */
std::string InputFunctions::obtenerArchivoSalida(int argc, char* argv[]) {
  std::string file_name = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-o") {
      if (i + 1 < argc) {
        file_name = argv[i + 1];
      } else {
        std::cerr << "Error: Falta el nombre del archivo de salida." << std::endl;
        exit(1);
      }
    }
  }
  return file_name;
}

/**
  * Función para obtener el número de vecinos
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return Número de vecinos
  */
int InputFunctions::obtenerNumeroVecinos(int argc, char* argv[]) {
  int k = 0;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-k") {
      if (i + 1 < argc) {
        k = std::stoi(argv[i + 1]);
      } else {
        std::cerr << "Error: Falta el número de vecinos." << std::endl;
        exit(1);
      }
    }
  }
  return k;
}

/**
  * Función para obtener la métrica a usar
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return 0 si la métrica es pearson, 1 si es coseno, 2 si es euclidea
  */
int InputFunctions::obtenerMetrica(int argc, char* argv[]) {
  std::string metrica = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-m") {
      if (i + 1 < argc) {
        metrica = argv[i + 1];
        /// Comprobamos que la métrica introducida sea válida
        if (metrica != "pearson" && metrica != "coseno" && metrica != "euclidea") {
          std::cerr << "Error: La métrica introducida no es válida. Las métricas válidas son: pearson, coseno y euclidea." << std::endl;
          exit(1);
        }
      } else {
        std::cerr << "Error: Falta la métrica a usar." << std::endl;
        exit(1);
      }
    }
  }
  return (metrica == "pearson") ? 0 : (metrica == "coseno") ? 1 : 2;
}

/**
  * Función para obtener el método de predicción  
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return 0 si el método de predicción es la media, 1 si es ponderado
  */
int InputFunctions::obtenerMetodoPrediccion(int argc, char* argv[]) {
  std::string metodo = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-p") {
      if (i + 1 < argc) {
        metodo = argv[i + 1];
        /// Comprobamos que el método de predicción introducido sea válido
        if (metodo != "simple" && metodo != "media") {
          std::cerr << "Error: El método de predicción introducido no es válido. Los métodos válidos son: simple y media." << std::endl;
          exit(1);
        }
      } else {
        std::cerr << "Error: Falta el método de predicción a usar." << std::endl;
        exit(1);
      }
    }
  }
  return (metodo == "simple") ? 0 : 1;
}