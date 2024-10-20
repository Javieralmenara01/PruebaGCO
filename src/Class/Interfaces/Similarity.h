/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <vector>
#include <utility>
#include "../Data.h"

/**
  * Clase Abstracta Similarity
  * @brief Clase que define la interfaz de las similitudes 
  */
class Similarity {
 public:
  /**
    * Método virtual puro para calcular la similitud entre un usuario y el resto
    * @param datos Estructura con los datos
    * @param usuario Usuario para el que se calcula la similitud
    * @param metrica 0 si la métrica es pearson, 1 si es coseno, 2 si es euclidea
    * @return Vector con las similitudes
    */
  virtual double calculateSimilarities(const std::vector<double>& x, const std::vector<double>& y, double min_val) const = 0;
};

#endif