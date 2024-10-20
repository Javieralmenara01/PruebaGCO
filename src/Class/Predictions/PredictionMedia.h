/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include "../Interfaces/Prediction.h"
#include "../../Functions/predictionFunctions.h"

#ifndef PREDICTIONMEDIA_H
#define PREDICTIONMEDIA_H

/**
  * Clase PredictionMedia
  * @brief Clase que implementa la predicción considerando la diferencia con la media
  */
class PredictionMedia : public Prediction {
 public:
  /**
    * Método para predecir la valoración de un usuario para un ítem
    * @param datos Estructura con los datos
    * @param usuario Usuario para el que se predice la valoración
    * @param item Ítem para el que se predice la valoración
    * @param vecinos Vecinos más cercanos
    * @return Valoración predicha
    */
  double predict(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos, std::stringstream& output) const override { return PredictionFunctions::prediccionMedia(datos, usuario, item, vecinos, output); }
};

#endif