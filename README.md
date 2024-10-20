# Sistema Recomendador: Métodos de Filtrado Colaborativo

### Autores

- Javier Almenara Herrera
- Ithaisa Morales Arbelo
- Antonio Ramos Castilla
- Guillermo Plaza Gayán

### Descripción

Este proyecto implementa un sistema recomendador basado en métodos de filtrado colaborativo, utilizando algoritmos como el coeficiente de Pearson, la similitud de coseno y la distancia euclidiana. Está diseñado para analizar valoraciones de usuarios y generar recomendaciones personalizadas, permitiendo seleccionar diferentes métodos de predicción y cálculo de similitud.

### Instalación de Dependencias

1. **Clonar el repositorio**:  

   ```bash
   git clone git@github.com:IthaisaMoralesArbelo/SistemaRecomendador.git
   cd SistemaRecomendador
   ```

2. **Instalar las dependencias necesarias** (si las hubiera). En este caso, se requiere tener un compilador de C++ y `make` instalado:

   - **En Ubuntu**:  

     ```bash
     sudo apt-get update
     sudo apt-get install g++
     sudo apt-get install make
     ```

   - **En otros sistemas operativos**: Consultar la documentación específica para instalar `g++` y `make`.

### Compilación y Despliegue

Para compilar y desplegar el sistema recomendador, ejecute los siguientes comandos en la carpeta del proyecto:

1. **Compilar el proyecto**:  
  
   ```bash
   make
   ```
  
   Esto generará un ejecutable llamado `main` en la carpeta del proyecto.

2. **Ejecutar el sistema recomendador**:  

   ```bash
   ./main -i <fichero_entrada> -o <fichero_salida> -m <método> -k <numero de vecinos> -p <metodo de prediccion>
   ```

   Donde:
   - `<fichero_entrada>`: Archivo con las valoraciones de los usuarios.
   - `<fichero_salida>`: Archivo donde se almacenarán las recomendaciones generadas.
   - `<método>`: Método de filtrado colaborativo (`pearson`, `coseno`, `euclidiana`).
   - `<numero de vecinos>`: Número de vecinos a considerar para la recomendación.
   - `<metodo de prediccion>`: Método de predicción (`media`, `simple`).

### Ejemplo de Uso

Para ejecutar el sistema recomendador con el archivo `ratings.txt`, utilizando el método de filtrado colaborativo `pearson`, considerando 10 usuarios, y empleando el método de predicción `media`, use el siguiente comando:

```bash
./main -i ratings.txt -o recomendaciones.txt -m pearson -k 10 -p media
```

Este comando leerá las valoraciones del archivo `ratings.txt`, generará las recomendaciones basadas en el método de Pearson y guardará los resultados en `recomendaciones.txt`.

### Descripción del Código

El código del sistema se divide en varios archivos para facilitar su mantenimiento y comprensión:

- **main.cc**: Punto de entrada del programa, maneja la lógica principal y la interacción con el usuario.
- **auxFunctions.cc/h**: Funciones auxiliares utilizadas para manipular datos y realizar cálculos secundarios.
- **inputFunctions.cc/h**: Funciones para la lectura de archivos de entrada y procesamiento de datos.
- **predictionFunctions.cc/h**: Implementa los métodos de predicción de valoraciones.
- **similarityFunctions.cc/h**: Contiene los métodos de cálculo de similitud, como Pearson, coseno y euclidiana.
- **Data.cc/h**: Clase encargada de almacenar y gestionar las valoraciones de los usuarios.
- **Prediction.h y Similarity.h**: Archivos de cabecera que definen las interfaces para métodos específicos de predicción y similitud.
- **PredictionSimple.h**: Implementación concreta de un método de predicción simple.
- **PredictionMedia.h**: Implementación concreta de un método de predicción basado en la media.
- **SimilarityPearson.h**: Implementación concreta del cálculo de similitud de Pearson.
- **SimilarityCoseno.h**: Implementación concreta del cálculo de similitud de coseno.
- **SimilarityEuclidiana.h**: Implementación concreta del cálculo de similitud euclidiana.

Cada archivo está organizado para facilitar la modificación y extensión de los métodos de recomendación y predicción.

### Notas Adicionales

- Asegúrese de que los archivos de entrada estén en el formato adecuado, con las valoraciones estructuradas por usuario.
- Puede consultar la documentación de cada método dentro del código para entender mejor su funcionamiento.
