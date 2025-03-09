#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Ciudad {
    std::string nombre;
    sf::Vector2f posicion;
    sf::CircleShape shape;
    std::vector<std::pair<int, float>> neighbors; 
};

class Mapa {
public:
    void run(); 
};

void initializeCities(); 
std::vector<int> dijkstra(int start, int end); 

extern std::vector<Ciudad> ciudades; 

#endif 

