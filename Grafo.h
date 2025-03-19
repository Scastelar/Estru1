#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include "Cola.h"

using namespace std;
using namespace sf;




class Grafo {
private:
    unordered_map<string, vector<pair<Ciudad*, float>>> listaAdyacencia;

public:
    void agregarCiudad(Ciudad* ciudad);
    void agregarRuta(Ciudad* origen, Ciudad* destino, float distancia); 
    vector<pair<Ciudad*, float>> obtenerAdyacentes(const string& nombre);
    Ciudad* buscarCiudad(const string& nombre);
    vector<Ciudad*> dijkstra(const string& origenNombre, const string& destinoNombre); 
};

#endif 
