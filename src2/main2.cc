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

/**
  * Estructura para almacenar los datos leídos del archivo
  */
struct Data {
  double min_val;
  double max_val;
  std::vector<std::vector<double>> user_scores;  // Matriz de puntuaciones de los usuarios
};

/**
  * Función para obtener el archivo de salida
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return Nombre del archivo de salida
  */
std::string obtenerArchivoEntrada(int argc, char* argv[]) {
  std::string file_name = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-i") {
      if (i + 1 < argc) {
        file_name = argv[i + 1];
      } else {
        std::cerr << "Error: Falta el nombre del archivo de entrada." << std::endl;
        exit(1);
      }
    }
  }
  return file_name;
}

/** 
  * Función para obtener el archivo de salida
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return Nombre del archivo de salida
  */
std::string obtenerArchivoSalida(int argc, char* argv[]) {
  std::string file_name = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-o") {
      if (i + 1 < argc) {
        file_name = argv[i + 1];
      } else {
        std::cerr << "Error: Falta el nombre del archivo de salida." << std::endl;
        exit(1);
      }
    }
  }
  return file_name;
}

/**
  * Función para obtener el número de vecinos
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return Número de vecinos
  */
int obtenerNumeroVecinos(int argc, char* argv[]) {
  int k = 0;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-k") {
      if (i + 1 < argc) {
        k = std::stoi(argv[i + 1]);
        /// Comprobamos que el número de vecinos introducido sea válido
        if (k <= 0) {
          std::cerr << "Error: El número de vecinos debe ser mayor que cero." << std::endl;
          exit(1);
        }
      } else {
        std::cerr << "Error: Falta el número de vecinos." << std::endl;
        exit(1);
      }
    }
  }
  return k;
}

/**
  * Función para obtener la métrica a usar
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return 0 si la métrica es pearson, 1 si es coseno, 2 si es euclidea
  */
int obtenerMetrica(int argc, char* argv[]) {
  std::string metrica = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-m") {
      if (i + 1 < argc) {
        metrica = argv[i + 1];
        /// Comprobamos que la métrica introducida sea válida
        if (metrica != "pearson" && metrica != "coseno" && metrica != "euclidea") {
          std::cerr << "Error: La métrica introducida no es válida. Las métricas válidas son: pearson, coseno y euclidea." << std::endl;
          exit(1);
        }
      } else {
        std::cerr << "Error: Falta la métrica a usar." << std::endl;
        exit(1);
      }
    }
  }
  return (metrica == "pearson") ? 0 : (metrica == "coseno") ? 1 : 2;
}

/**
  * Función para obtener el método de predicción  
  * @param argc Número de argumentos
  * @param argv Argumentos
  * @return 0 si el método de predicción es la media, 1 si es ponderado
  */
int obtenerMetodoPrediccion(int argc, char* argv[]) {
  std::string metodo = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-p") {
      if (i + 1 < argc) {
        metodo = argv[i + 1];
        /// Comprobamos que el método de predicción introducido sea válido
        if (metodo != "simple" && metodo != "media") {
          std::cerr << "Error: El método de predicción introducido no es válido. Los métodos válidos son: simple y media." << std::endl;
          exit(1);
        }
      } else {
        std::cerr << "Error: Falta el método de predicción a usar." << std::endl;
        exit(1);
      }
    }
  }
  return (metodo == "simple") ? 0 : 1;
}

/**
  * Función para leer los datos del archivo de entrada
  * @param nombre_archivo Nombre del archivo de entrada
  * @return Estructura con los datos leídos
  */
Data leerDatos(const std::string& nombre_archivo) {
  std::ifstream archivo(nombre_archivo);
  Data datos;
  std::string linea;

  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo." << std::endl;
    return datos;
  }

  // Leer la primera línea: valor mínimo
  std::getline(archivo, linea);
  std::stringstream ss_min(linea);
  ss_min >> datos.min_val;

  // Leer la segunda línea: valor máximo
  std::getline(archivo, linea);
  std::stringstream ss_max(linea);
  ss_max >> datos.max_val;

  // Leer las líneas restantes: puntuaciones de los usuarios
  while (std::getline(archivo, linea)) {
    std::vector<double> fila_puntuaciones;
    std::stringstream ss(linea);
    std::string valor;

    // Leer cada valor en la fila
    while (ss >> valor) {
      if (valor == "-") {
        /// Usamos el valor datos.min_val - 1.0 para representar una puntuación no observada
        fila_puntuaciones.push_back(datos.min_val - 1.0);
      } else {
        /// Comprobamos que el valor introducido sea válido
        if (std::stod(valor) < datos.min_val || std::stod(valor) > datos.max_val) {
          std::cerr << "Error: El valor introducido no es válido. Debe estar en el rango [" << datos.min_val << ", " << datos.max_val << "]." << std::endl;
          return datos;
        }
        fila_puntuaciones.push_back(std::stod(valor));
      }
    }
    datos.user_scores.push_back(fila_puntuaciones);
  }

  archivo.close();
  return datos;
}

// Función temporal para mostrar los datos leídos
void mostrarDatos(const Data& datos) {
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Valor mínimo: " << datos.min_val << std::endl;
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "Valor máximo: " << datos.max_val << std::endl;
  std::cout << "Puntuaciones de los usuarios:" << std::endl;

  for (const auto& fila : datos.user_scores) {
    for (const auto& puntuacion : fila) {
      if (puntuacion == datos.min_val - 1.0) {
        std::cout << "- ";
      } else {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << puntuacion << " ";
      }
    }
    std::cout << std::endl;
  }
}

/**
  * Función para calcular la correlación de Pearson entre dos usuarios
  * @param x Usuario 1
  * @param y Usuario 2
  * @return Correlación de Pearson
  */
double correlacionPearson(const std::vector<double>& x, const std::vector<double>& y, double min_val) {
  int n = x.size();
  if (n != y.size()) {
    std::cerr << "Los vectores deben tener el mismo tamaño." << std::endl;
    return 0.0;
  }

  double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0;
  double sum_x2 = 0.0, sum_y2 = 0.0;
  int count = 0;

  for (int i = 0; i < n; ++i) {
    if (x[i] != (min_val - 1.0)  && y[i] != (min_val - 1.0)) {  // Ignorar puntuaciones no conocidas (min_val - 1.0)
      sum_x += x[i];
      sum_y += y[i];
      sum_xy += x[i] * y[i];
      sum_x2 += x[i] * x[i];
      sum_y2 += y[i] * y[i];
      ++count;
    }
  }

  // Evitar división por cero
  if (count == 0) return 0.0;

  double numerador = count * sum_xy - sum_x * sum_y;
  double denominador = std::sqrt((count * sum_x2 - sum_x * sum_x) * (count * sum_y2 - sum_y * sum_y));
    
  if (denominador == 0.0) return 0.0;

  return numerador / denominador;
}

/**
  * Función para calcular la similitud entre dos usuarios usando la distancia coseno
  * @param x Usuario 1
  * @param y Usuario 2
  * @return Similitud coseno
  */
double similitudCoseno(const std::vector<double>& x, const std::vector<double>& y, double min_val) {
  int n = x.size();
  if (n != y.size()) {
    std::cerr << "Los vectores deben tener el mismo tamaño." << std::endl;
    return 0.0;
  }

  double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0;
  double sum_x2 = 0.0, sum_y2 = 0.0;
  int count = 0;

  for (int i = 0; i < n; ++i) {
    if (x[i] != (min_val - 1.0) && y[i] != (min_val - 1.0)) {  // Ignorar puntuaciones no conocidas (min_val - 1.0)
      sum_x += x[i];
      sum_y += y[i];
      sum_xy += x[i] * y[i];
      sum_x2 += x[i] * x[i];
      sum_y2 += y[i] * y[i];
      ++count;
    }
  }

  // Evitar división por cero
  if (count == 0) return 0.0;

  double numerador = sum_xy;
  double denominador = std::sqrt(sum_x2) * std::sqrt(sum_y2);
    
  if (denominador == 0.0) return 0.0;

  return numerador / denominador;
}

/**
  * Función para calcular la similitud entre dos usuarios usando la distancia euclídea
  * @param x Usuario 1
  * @param y Usuario 2
  * @return Similitud euclídea
  */
double similitudEuclidea(const std::vector<double>& x, const std::vector<double>& y, double min_val) {
  int n = x.size();
  if (n != y.size()) {
    std::cerr << "Los vectores deben tener el mismo tamaño." << std::endl;
    return 0.0;
  }

  double sum = 0.0;
  int count = 0;

  for (int i = 0; i < n; ++i) {
    if (x[i] != (min_val - 1.0) && y[i] != (min_val - 1.0)) {  // Ignorar puntuaciones no conocidas (min_val - 1.0)
      sum += (x[i] - y[i]) * (x[i] - y[i]);
      ++count;
    }
  }

  // Evitar división por cero
  if (count == 0) return 0.0;

  return 1.0 / std::sqrt(sum);
}

/**
  * Función para calcular la similitud entre un usuario y el resto
  * @param datos Estructura con los datos
  * @param usuario Usuario para el que se calcula la similitud
  * @param metrica 0 si la métrica es pearson, 1 si es coseno, 2 si es euclidea
  * @return Vector con las similitudes
  */
std::vector<std::pair<int, double>> calcularSimilitudes(const Data& datos, int usuario, int metrica) {
  std::vector<std::pair<int, double>> similitudes;

  for (int i = 0; i < datos.user_scores.size(); ++i) {
    if (i != usuario) {
      double similitud = 0.0;

      switch (metrica) {
        case 0:
          similitud = correlacionPearson(datos.user_scores[usuario], datos.user_scores[i], datos.min_val);
          break;
        case 1:
          similitud = similitudCoseno(datos.user_scores[usuario], datos.user_scores[i], datos.min_val);
          break;
        case 2:
          similitud = similitudEuclidea(datos.user_scores[usuario], datos.user_scores[i], datos.min_val);
          break;
      }

      similitudes.push_back(std::make_pair(i, similitud));
    }
  }

  return similitudes;
}

/// Función que busca en la matriz los usuarios con valoraciones no observadas
std::vector<int> buscarUsuariosSinValoraciones(const Data& datos) {
  std::vector<int> usuarios_sin_valoraciones;
  for (int i = 0; i < datos.user_scores.size(); ++i) {
    for (int j = 0; j < datos.user_scores[i].size(); ++j) {
      if (datos.user_scores[i][j] == (datos.min_val - 1.0)) {
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
std::vector<std::pair<int, double>> vecinosCercanos(const std::vector<std::pair<int, double>>& similitudes, int k, const Data& datos, int item) {
  std::vector<std::pair<int, double>> vecinos;

  // Ordenar las similitudes de mayor a menor
  std::vector<std::pair<int, double>> similitudes_ordenadas = similitudes;
  std::sort(similitudes_ordenadas.begin(), similitudes_ordenadas.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
    return a.second > b.second;
  });

  // Selección de los k vecinos más cercanos que hayan valorado el ítem
  for (int i = 0; i < similitudes_ordenadas.size(); ++i) {
    if (vecinos.size() == k) break;
    int usuario_vecino = similitudes_ordenadas[i].first;
    if (datos.user_scores[usuario_vecino][item] != datos.min_val - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      vecinos.push_back(similitudes_ordenadas[i]);
    }
  }

  /// Question: ¿Qué pasa si no hay k vecinos que hayan valorado el ítem?

  return vecinos;
}

/// Función para predecir la valoración de un usuario para un ítem mediante el método de predicción simple
double prediccionSimple(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos) {
  double numerador = 0.0;
  double denominador = 0.0;

  for (const auto& vecino : vecinos) {
    int usuario_vecino = vecino.first;
    double similitud = vecino.second;

    if (datos.user_scores[usuario_vecino][item] != datos.min_val - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      numerador += similitud * datos.user_scores[usuario_vecino][item];
      denominador += std::abs(similitud);
    }
  }

  if (denominador == 0.0) return 0.0;

  return numerador / denominador;
}

/// Función para predecir la valoración de un usuario para un ítem mediante el método de predicción considerando la diferencia con la media
double prediccionMedia(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos) {
  double numerador = 0.0;
  double denominador = 0.0;
  double media_usuario = 0.0;

  int numero_valoraciones = 0;
  for (int i = 0; i < datos.user_scores[usuario].size(); ++i) {
    if (datos.user_scores[usuario][i] != (datos.min_val - 1.0)) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      media_usuario += datos.user_scores[usuario][i];
      numero_valoraciones++;
    }
  }

  media_usuario /= numero_valoraciones;

  for (const auto& vecino : vecinos) {
    int usuario_vecino = vecino.first;
    double similitud = vecino.second;
    double media_vecino = 0.0;

    int numero_valoraciones_vecino = 0;
    for (int i = 0; i < datos.user_scores[usuario_vecino].size(); ++i) {
      if (datos.user_scores[usuario_vecino][i] != (datos.min_val - 1.0)) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
        media_vecino += datos.user_scores[usuario_vecino][i];
        numero_valoraciones_vecino++;
      }
    }

    media_vecino /= numero_valoraciones_vecino;

    if (datos.user_scores[usuario_vecino][item] != datos.min_val - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
      numerador += similitud * (datos.user_scores[usuario_vecino][item] - media_vecino);
      denominador += std::abs(similitud);
    }
  }

  if (denominador == 0.0) return 0.0;

  return media_usuario + numerador / denominador;
}

/// Función para predecir la valoración de un usuario para un ítem
double predecirValoracion(const Data& datos, int usuario, int item, const std::vector<std::pair<int, double>>& vecinos, int metodo_prediccion) {
  if (metodo_prediccion == 0) {
    return prediccionSimple(datos, usuario, item, vecinos);
  } else {
    return prediccionMedia(datos, usuario, item, vecinos);
  }
}

/**
  * Función principal
  */
int main(int argc, char* argv[]) {

  // Inicio del cronómetro
  auto start = std::chrono::high_resolution_clock::now();

  /// Comprobamos que se han introducido los argumentos necesarios
  std::string archivo_entrada = obtenerArchivoEntrada(argc, argv);
  std::string archivo_salida = obtenerArchivoSalida(argc, argv);
  int k = obtenerNumeroVecinos(argc, argv);
  int metrica = obtenerMetrica(argc, argv);
  int metodo_prediccion = obtenerMetodoPrediccion(argc, argv);

  /// Leemos los datos del archivo de entrada
  Data datos = leerDatos(archivo_entrada);
  if (datos.user_scores.empty()) {
    std::cerr << "Error: No se han podido leer los datos del archivo." << std::endl;
    return 1;
  }

  /// Mostramos los datos leídos
  //mostrarDatos(datos);

  /// Buscamos los usuarios con valoraciones no observadas
  std::vector<int> usuarios_sin_valoraciones = buscarUsuariosSinValoraciones(datos);

  /// Calculamos las predicciones para los usuarios con valoraciones no observadas
  std::ofstream archivo(archivo_salida);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo de salida." << std::endl;
    return 1;
  }

  /// Calculamos las predicciones para los usuarios con valoraciones no observadas
  std::stringstream sim_usuarios_vecinos ("");
  sim_usuarios_vecinos << "Similitud entre usuarios y vecinos:\n";

  for (int usuario : usuarios_sin_valoraciones) {
   
    /// Question: ¿Qué pasa si el usuario no tiene ninguna valoración?
    std::vector<std::pair<int, double>> similitudes = calcularSimilitudes(datos, usuario, metrica);

    for (int item = 0; item < datos.user_scores[usuario].size(); ++item) {

      if (datos.user_scores[usuario][item] == datos.min_val - 1.0) { // Ignorar puntuaciones no conocidas (min_val - 1.0)
        
        std::vector<std::pair<int, double>> vecinos = vecinosCercanos(similitudes, k, datos, item);

        sim_usuarios_vecinos << "Usuario " << usuario << ": ";
        sim_usuarios_vecinos << "Vecinos [";
        for (const auto& vecino : vecinos) {
          sim_usuarios_vecinos << " " << vecino.first << " (" << std::fixed << std::setprecision(3) << vecino.second << ")";
        }
        sim_usuarios_vecinos << " ]\n";

        double valoracion = predecirValoracion(datos, usuario, item, vecinos, metodo_prediccion);
        std::cout << "Predicción para el usuario " << usuario << " e ítem " << item << ": " << std::fixed << std::setprecision(3) << valoracion << std::endl;

        if (valoracion < datos.min_val) {
          valoracion = datos.min_val;
        } else if (valoracion > datos.max_val) {
          valoracion = datos.max_val;
        }
        datos.user_scores[usuario][item] = valoracion;
      }
    }
  }

  /// Imprimimos la similaridad entre cada usuario y sus vecinos
  archivo << sim_usuarios_vecinos.str() << std::endl;
  
  /// Impresión de la matriz tras la predicción
  archivo << "Matriz de puntuaciones de los usuarios tras la predicción:" << std::endl;
  for (int i = 0; i < datos.user_scores.size(); ++i) {
    for (int j = 0; j < datos.user_scores[i].size(); ++j) {
      /// Este caso no debería darse
      if (datos.user_scores[i][j] == datos.min_val - 1.0) {
        archivo << "- ";
      } else {
        archivo << std::fixed << std::setprecision(3);
        archivo << datos.user_scores[i][j] << " ";
      }
    }
    archivo << std::endl;
  }

  // Fin del cronómetro
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> tiempo_transcurrido = end - start;
  std::cout << "Tiempo transcurrido: " << tiempo_transcurrido.count() << " segundos." << std::endl;

  return 0;
}