/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include <vector>
#include <utility>
#include "../Class/Data.h"
#include "../Class/Interfaces/Similarity.h"


#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

/**
  * Funciones auxiliares
  */
namespace AuxFunctions {
  std::vector<std::pair<int, double>> calcularSimilitudes(const Data& datos, int usuario, const Similarity& metrica);
  std::vector<int> buscarUsuariosSinValoraciones(const Data& datos);
  std::vector<std::pair<int, double>> vecinosCercanos(const std::vector<std::pair<int, double>>& similitudes, int k, const Data& datos, int item);
} // namespace AuxFunctions

#endif // AUXFUNCTIONS_H