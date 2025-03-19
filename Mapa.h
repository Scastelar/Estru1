#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

struct Ciudad {
    std::string nombre;
    sf::Vector2f posicion;
    sf::CircleShape shape;
    std::vector<std::pair<int, float>> neighbors; 
};

struct Ruta {
    Ciudad* origen;
    Ciudad* destino;
    std::vector<sf::Vector2f> puntosMedios;
    float distancia;
};

class Mapa {
public:
    void run(); 
};

void initializeCities(); 
std::vector<int> dijkstra(int start, int end); 

extern std::vector<Ciudad> ciudades; 
//extern Grafo grafoCiudades;

#endif 

