/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include "auxFunctions.h"
 
/**
  * Función para calcular la similitud entre un usuario y el resto
  * @param datos Estructura con los datos
  * @param usuario Usuario para el que se calcula la similitud
  * @param metrica 0 si la métrica es pearson, 1 si es coseno, 2 si es euclidea
  * @return Vector con las similitudes
  */
std::vector<std::pair<int, double>> AuxFunctions::calcularSimilitudes(const Data& datos, int usuario, const Similarity& metrica) {
  std::vector<std::pair<int, double>> similitudes;

  for (int i = 0; i < (int)datos.getUserScores().size(); ++i) {
    if (i != usuario) {
      double similitud = 0.0;

      similitud = metrica.calculateSimilarities(datos.getUser(usuario), datos.getUser(i), datos.getMinVal());

      similitudes.push_back(std::make_pair(i, similitud));
    }
  }

  return similitudes;
}

/**
  * Función para buscar los usuarios que no han valorado ningún ítem
  * @param datos Estructura con los datos
  * @return Vector con los usuarios que no han valorado ningún ítem
  */
std::vector<int> AuxFunctions::buscarUsuariosSinValoraciones(const Data& datos) {
  std::vector<int> usuarios_sin_valoraciones;
  for (int i = 0; i < (int)datos.getUserScores().size(); ++i) {
    for (int j = 0; j < (int)datos.getUserScores()[i].size(); ++j) {
      if (datos.getValoration(i, j) == (datos.getMinVal() - 1.0)) {
        usuarios_sin_valoraciones.push_back(i);
        break;
      }
    }
  }
  return usuarios_sin_valoraciones;
}

/**
  * Función para seleccionar los k vecinos más cercanos que hayan valorado el ítem
  * @param similitudes Vector con las similitudes
  * @param k Número de vecinos a seleccionar
  * @return Vector con los k vecinos más cercanos
  */
std::vector<std::pair<int, double>> AuxFunctions::vecinosCercanos(const std::vector<std::pair<int, double>>& similitudes, int k, const Data& datos, int item) {
  std::vector<std::pair<int, double>> vecinos;

  // Ordenar las similitudes de mayor a menor
  std::vector<std::pair<int, double>> similitudes_ordenadas = similitudes;
  std::sort(similitudes_ordenadas.begin(), similitudes_ordenadas.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
    return a.second > b.second;
  });

  // Selección de los k vecinos más cercanos que hayan valorado el ítem
  for (int i = 0; i < (int)similitudes_ordenadas.size(); ++i) {
    if ((int)vecinos.size() == k) break;
    int usuario_vecino = similitudes_ordenadas[i].first;
    if (datos.getValoration(usuario_vecino, item) != datos.getMinVal() - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      vecinos.push_back(similitudes_ordenadas[i]);
    }
  }

  /// Question: ¿Qué pasa si no hay k vecinos que hayan valorado el ítem?

  return vecinos;
}
