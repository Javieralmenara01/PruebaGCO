/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include "Data.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

/**
  * Constructor de la clase Data
  * @param file_name Nombre del archivo de entrada
  */
Data::Data(const std::string& file_name) {
  std::ifstream file(file_name);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo." << std::endl;
    return;
  }

  // Leer la primera línea: valor mínimo
  std::getline(file, line);
  std::stringstream ss_min(line);
  ss_min >> min_val;

  // Leer la segunda línea: valor máximo
  std::getline(file, line);
  std::stringstream ss_max(line);
  ss_max >> max_val;

  // Leer las líneas restantes: puntuaciones de los usuarios
  while (std::getline(file, line)) {
    std::vector<double> scores_row;
    std::stringstream ss(line);
    std::string valor;

    // Leer cada valor en la fila
    while (ss >> valor) {
      if (valor == "-") {
        /// Usamos el valor datos.min_val - 1.0 para representar una puntuación no observada
        scores_row.push_back(min_val - 1.0);
      } else {
        /// Comprobamos que el valor introducido sea válido
        if (std::stod(valor) < min_val || std::stod(valor) > max_val) {
          std::cerr << "Error: valor fuera de rango." << std::endl;
          exit(1);
        }
        scores_row.push_back(std::stod(valor));
      }
    }
    user_scores.push_back(scores_row);
  }
}

/**
  * Método para mostrar los datos leídos
  * @return void
  */
void Data::showData() const {
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Valor mínimo: " << min_val << std::endl;
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Valor máximo: " << max_val << std::endl;
  std::cout << "Puntuaciones de los usuarios:" << std::endl;

  for (const auto& row : user_scores) {
    for (const auto& score : row) {
      if (score == min_val - 1.0) {
        std::cout << "- ";
      } else {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << score << " ";
      }
    }
    std::cout << std::endl;
  }
}