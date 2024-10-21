/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include "predictionFunctions.h"
#include "../Class/Data.h"
#include <algorithm>

/** 
 * Función para predecir la valoración de un usuario para un ítem
 * @param datos Datos de entrada
 * @param usuario Usuario
 * @param item Ítem
 * @param vecinos Vecinos más cercanos
 * @param metodo_prediccion Método de predicción
 * @return Valoración predicha
 */
double PredictionFunctions::prediccionSimple(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos, std::stringstream& output) {
  double numerador = 0.0;
  double denominador = 0.0;

  output << "Predicción para el usuario " << usuario << " e ítem " << item << ":\n";

  for (const auto& vecino : vecinos) {
    int usuario_vecino = vecino.first;
    double similitud = vecino.second;

    if (datos.getValoration(usuario_vecino,item) != datos.getMinVal() - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      output << "Vecino: " << usuario_vecino << " - Similitud: " << similitud << " - Valoración: " << datos.getValoration(usuario_vecino,item) << "\n";
      numerador += similitud * datos.getValoration(usuario_vecino,item);
      denominador += std::abs(similitud);
    }
  }

  if (denominador == 0.0) return 0.0;

  output << "Predicción Final: " << numerador / denominador << "\n\n";

  return numerador / denominador;
}

/** 
 * Función para predecir la valoración de un usuario para un ítem mediante el método de predicción considerando la diferencia con la media
 * @param datos Datos de entrada
 * @param usuario Usuario
 * @param item Ítem
 * @param vecinos Vecinos más cercanos
 * @return Valoración predicha
 */
double PredictionFunctions::prediccionMedia(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos, std::stringstream& output) {
  double numerador = 0.0;
  double denominador = 0.0;
  double media_usuario = 0.0;

  output << "Predicción para el usuario " << usuario << " e ítem " << item << ":\n";

  int numero_valoraciones = 0;
  for (int i = 0; i < (int)datos.getUser(usuario).size(); ++i) {
    if (datos.getUser(usuario)[i] != (datos.getMinVal() - 1.0)) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      media_usuario += datos.getUser(usuario)[i];
      numero_valoraciones++;
    }
  }

  output << "Media del usuario: " << media_usuario / numero_valoraciones << "\n";

  media_usuario /= numero_valoraciones;

  for (const auto& vecino : vecinos) {
    int usuario_vecino = vecino.first;
    double similitud = vecino.second;
    double media_vecino = 0.0;

    output << "Vecino: " << usuario_vecino << " - Similitud: " << similitud << "\n";

    int numero_valoraciones_vecino = 0;
    for (int i = 0; i < (int)datos.getUser(usuario_vecino).size(); ++i) {
      if (datos.getUser(usuario_vecino)[i] != (datos.getMinVal() - 1.0)) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
        media_vecino += datos.getUser(usuario_vecino)[i];
        numero_valoraciones_vecino++;
      }
    }

    media_vecino /= numero_valoraciones_vecino;

    output << "Media del vecino: " << media_vecino << "\n";

    if (datos.getValoration(usuario_vecino,item) != datos.getMinVal() - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      numerador += similitud * (datos.getValoration(usuario_vecino,item) - media_vecino);
      denominador += std::abs(similitud);
    }
  }

  if (denominador == 0.0) return 0.0;

  output << "Predicción Final: " << media_usuario + numerador / denominador << "\n\n";

  return media_usuario + numerador / denominador;
}