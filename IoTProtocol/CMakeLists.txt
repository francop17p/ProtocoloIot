cmake_minimum_required(VERSION 3.10)
project(IoTProtocol)

# Especificamos el estándar de C++
set(CMAKE_CXX_STANDARD 11)

# Agregar el directorio de encabezados
include_directories(include)

# Crear la librería estática
add_library(IoTProtocol STATIC src/IoTProtocol.cpp)

# Crear el ejecutable de prueba
add_executable(example src/main.cpp)

# Enlazar la librería con el ejecutable
target_link_libraries(example IoTProtocol)
