/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include "similarityFunctions.h"

#include <iostream>
#include <vector>
#include <utility>

/**
  * Función para calcular la correlación de Pearson entre dos usuarios
  * @param x Usuario 1
  * @param y Usuario 2
  * @return Correlación de Pearson
  */
double SimilarityFunctions::correlacionPearson(const std::vector<double>& x, const std::vector<double>& y, double min_val) {
  int n = x.size();
  if (n != (int)y.size()) {
    std::cerr << "Los vectores deben tener el mismo tamaño." << std::endl;
    return 0.0;
  }

  double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0;
  double sum_x2 = 0.0, sum_y2 = 0.0;
  int count = 0;

  for (int i = 0; i < n; ++i) {
    if (x[i] != (min_val - 1.0)  && y[i] != (min_val - 1.0)) {  // Ignorar puntuaciones no conocidas (min_val - 1.0)
      sum_x += x[i];
      sum_y += y[i];
      sum_xy += x[i] * y[i];
      sum_x2 += x[i] * x[i];
      sum_y2 += y[i] * y[i];
      ++count;
    }
  }

  // Evitar división por cero
  if (count == 0) return 0.0;

  double numerador = count * sum_xy - sum_x * sum_y;
  double denominador = std::sqrt((count * sum_x2 - sum_x * sum_x) * (count * sum_y2 - sum_y * sum_y));
    
  if (denominador == 0.0) return 0.0;

  return numerador / denominador;
}

/**
  * Función para calcular la similitud entre dos usuarios usando el coseno
  * @param x Usuario 1
  * @param y Usuario 2
  * @return Similitud coseno
  */
double SimilarityFunctions::similitudCoseno(const std::vector<double>& x, const std::vector<double>& y, double min_val) {
  int n = x.size();
  if (n != (int)y.size()) {
    std::cerr << "Los vectores deben tener el mismo tamaño." << std::endl;
    return 0.0;
  }

  double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0;
  double sum_x2 = 0.0, sum_y2 = 0.0;
  int count = 0;

  for (int i = 0; i < n; ++i) {
    if (x[i] != (min_val - 1.0) && y[i] != (min_val - 1.0)) {  // Ignorar puntuaciones no conocidas (min_val - 1.0)
      sum_x += x[i];
      sum_y += y[i];
      sum_xy += x[i] * y[i];
      sum_x2 += x[i] * x[i];
      sum_y2 += y[i] * y[i];
      ++count;
    }
  }

  // Evitar división por cero
  if (count == 0) return 0.0;

  double numerador = sum_xy;
  double denominador = std::sqrt(sum_x2) * std::sqrt(sum_y2);
    
  if (denominador == 0.0) return 0.0;

  return numerador / denominador;
}

/**
  * Función para calcular la similitud entre dos usuarios usando la distancia euclídea
  * @param x Usuario 1
  * @param y Usuario 2
  * @return Similitud euclídea
  */
double SimilarityFunctions::similitudEuclidea(const std::vector<double>& x, const std::vector<double>& y, double min_val) {
  int n = x.size();
  if (n != (int)y.size()) {
    std::cerr << "Los vectores deben tener el mismo tamaño." << std::endl;
    return 0.0;
  }

  double sum = 0.0;
  int count = 0;

  for (int i = 0; i < n; ++i) {
    if (x[i] != (min_val - 1.0) && y[i] != (min_val - 1.0)) {  // Ignorar puntuaciones no conocidas (min_val - 1.0)
      sum += (x[i] - y[i]) * (x[i] - y[i]);
      ++count;
    }
  }

  // Evitar división por cero
  if (count == 0) return 0.0;

  return 1.0 / std::sqrt(sum);
}

