/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#ifndef PREDICTION_H
#define PREDICTION_H

#include "../Data.h"
#include <vector>
#include <sstream>

/**
  * Clase Abstracta Prediction
  * @brief Clase que define la interfaz de las predicciones 
  */
class Prediction {
 public:
  /**
    * Método virtual puro para predecir la valoración de un usuario para un ítem
    * @param datos Estructura con los datos
    * @param usuario Usuario para el que se predice la valoración
    * @param item Ítem para el que se predice la valoración
    * @param vecinos Vecinos más cercanos
    * @return Valoración predicha
    */
  virtual double predict(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos, std::stringstream& output) const = 0;
};

#endif