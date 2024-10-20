/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include "../Interfaces/Similarity.h"
#include "../../Functions/similarityFunctions.h"
#include <vector>

#ifndef SIMILARITYEUCLIDES_H
#define SIMILARITYEUCLIDES_H

/**
  * Clase SimilarityEuclides
  * @brief Clase que calcula la similitud euclídea entre un usuario y el resto
  */
class SimilarityEuclides : public Similarity {
 public:
  /**
    * Método para calcular la similitud entre un usuario y el resto
    * @param datos Estructura con los datos
    * @param usuario Usuario para el que se calcula la similitud
    * @param metrica 0 si la métrica es pearson, 1 si es coseno, 2 si es euclidea
    * @return Vector con las similitudes
    */
  double calculateSimilarities(const std::vector<double>& x, const std::vector<double>& y, double min_val) const override { return SimilarityFunctions::similitudEuclidea(x, y, min_val); }
};

#endif