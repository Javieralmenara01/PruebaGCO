/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <utility>

/**
 * Funciones para obtener los argumentos de entrada
 */
namespace InputFunctions {
  int obtenerNumeroVecinos(int argc, char* argv[]);
  int obtenerMetrica(int argc, char* argv[]);
  std::string obtenerArchivoEntrada(int argc, char* argv[]);
  std::string obtenerArchivoSalida(int argc, char* argv[]);
  int obtenerMetodoPrediccion(int argc, char* argv[]);
}

#endif