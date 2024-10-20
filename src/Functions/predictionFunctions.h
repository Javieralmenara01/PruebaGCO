/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#ifndef PREDICTIONFUNCTIONS_H
#define PREDICTIONFUNCTIONS_H

#include "../Class/Data.h"
#include <vector>
#include <utility>

/**
  * Funciones para predecir la valoración de un usuario para un ítem
  */
namespace PredictionFunctions {
  double prediccionSimple(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos, std::stringstream& output);
  double prediccionMedia(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos, std::stringstream& output);
}

#endif