/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Gestión del Conocimiento en las Organizaciones
  * Curso: 4º 
  * Prácticas de la asignatura GCO
  */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <utility>
#include <math.h>
#include <iomanip>    
#include <algorithm>
#include <chrono> 

#include "Functions/inputFunctions.h"
#include "Functions/auxFunctions.h"
#include "Class/Data.h"
#include "Class/Predictions/PredictionSimple.h"
#include "Class/Predictions/PredictionMedia.h"
#include "Class/Similarities/SimilarityEuclides.h"
#include "Class/Similarities/SimilarityPearson.h"
#include "Class/Similarities/SimilarityCoseno.h"

/**
  * Función principal
  */
int main(int argc, char* argv[]) {
  
  // Inicio del cronómetro
  auto start = std::chrono::high_resolution_clock::now();

  std::string archivo_entrada = InputFunctions::obtenerArchivoEntrada(argc, argv);
  std::string archivo_salida = InputFunctions::obtenerArchivoSalida(argc, argv);
  int k = InputFunctions::obtenerNumeroVecinos(argc, argv);
  int metrica = InputFunctions::obtenerMetrica(argc, argv);
  int metodo_prediccion = InputFunctions::obtenerMetodoPrediccion(argc, argv);

  Data datos = Data(archivo_entrada);
  std::vector<int> usuarios_sin_valoraciones = AuxFunctions::buscarUsuariosSinValoraciones(datos);
  std::cout << "Número de usuarios sin valoraciones: " << usuarios_sin_valoraciones.size() << std::endl;

  Prediction* prediccion = nullptr;
  if (metodo_prediccion == 0) {
    prediccion = new PredictionSimple();
  } else if (metodo_prediccion == 1) {
    prediccion = new PredictionMedia();
  }
  Similarity* similitud = nullptr;
  if (metrica == 0) {
    similitud = new SimilarityPearson();
  } else if (metrica == 1) {
    similitud = new SimilarityCoseno();
  } else if (metrica == 2) {
    similitud = new SimilarityEuclides();
  }

  std::ofstream archivo(archivo_salida);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo de salida." << std::endl;
    return 1;
  }

  std::stringstream sim_usuarios_vecinos (""), calculo_predicciones ("");
  sim_usuarios_vecinos << "# Similitud entre usuarios y vecinos:\n";
  calculo_predicciones << "# Calculo para las predicciones de las valoraciones:\n";

  for (int usuario : usuarios_sin_valoraciones) {
    std::vector<std::pair<int, double>> similitudes = AuxFunctions::calcularSimilitudes(datos, usuario, *similitud);
    for (int item = 0; item < (int)datos.getUser(usuario).size(); ++item) {
      if (datos.getValoration(usuario, item) == datos.getMinVal() - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
        std::vector<std::pair<int, double>> vecinos = AuxFunctions::vecinosCercanos(similitudes, k, datos, item);

        sim_usuarios_vecinos << "Usuario " << usuario << ": ";
        sim_usuarios_vecinos << "Vecinos [";
        for (const auto& vecino : vecinos) {
          sim_usuarios_vecinos << " " << vecino.first << " (" << std::fixed << std::setprecision(3) << vecino.second << ")";
        }
        sim_usuarios_vecinos << " ]\n";

        double valoracion = prediccion->predict(datos, usuario, item, vecinos, calculo_predicciones);
        if (valoracion < datos.getMinVal()) {
          valoracion = datos.getMinVal();
        } else if (valoracion > datos.getMaxVal()) {
          valoracion = datos.getMaxVal();
        }
        datos.setValoration(usuario, item, valoracion);
      }
    }
  }

  archivo << sim_usuarios_vecinos.str() << std::endl;
  archivo << "Matriz de puntuaciones de los usuarios tras la predicción:" << std::endl;
  for (int i = 0; i < (int)datos.getUserScores().size(); ++i) {
    for (int j = 0; j < (int)datos.getUser(i).size(); ++j) {
      if (datos.getValoration(i, j) == datos.getMinVal() - 1.0) {
        archivo << "- ";
      } else {
        archivo << std::fixed << std::setprecision(3);
        archivo << datos.getValoration(i, j) << " ";
      }
    }
    archivo << std::endl;
  }

  archivo << std::endl << calculo_predicciones.str() << std::endl;

  // Fin del cronómetro
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> tiempo_transcurrido = end - start;
  std::cout << "Tiempo transcurrido: " << tiempo_transcurrido.count() << " segundos." << std::endl;

  return 0; 
}