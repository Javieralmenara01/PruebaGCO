/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

/**
  * Clase para almacenar los datos leídos del archivo
  * @param min_val Valor mínimo
  * @param max_val Valor máximo
  * @param user_scores Matriz de puntuaciones de los usuarios
  */
class Data {
 public:
  Data(const std::string& file_name);
  double getMinVal() const { return min_val; }
  double getMaxVal() const { return max_val; }
  std::vector<std::vector<double>> getUserScores() const { return user_scores; }
  void setUserScores(const std::vector<std::vector<double>>& user_scores) { this->user_scores = user_scores; }
  void setValoration(int user, int item, double valoration) { user_scores[user][item] = valoration; }
  double getValoration(int user, int item) const { return user_scores[user][item]; }
  void setUser(int user, const std::vector<double>& valoraciones) { user_scores[user] = valoraciones; }
  std::vector<double> getUser(int user) const { return user_scores[user]; }
  void showData() const;

 private:
  double min_val;
  double max_val;
  std::vector<std::vector<double>> user_scores;  // Matriz de puntuaciones de los usuarios
};

#endif