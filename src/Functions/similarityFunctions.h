/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#ifndef SIMILARITYFUNCTIONS_H
#define SIMILARITYFUNCTIONS_H

#include "../Class/Data.h"
#include <vector>

/**
  * Funciones para calcular la similitud entre dos usuarios
  */
namespace SimilarityFunctions {
  double correlacionPearson(const std::vector<double>& x, const std::vector<double>& y, double min_val);
  double similitudCoseno(const std::vector<double>& x, const std::vector<double>& y, double min_val);
  double similitudEuclidea(const std::vector<double>& x, const std::vector<double>& y, double min_val);
}

#endif