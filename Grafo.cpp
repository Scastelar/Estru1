#include "Grafo.h"

void Grafo::agregarCiudad(Ciudad* ciudad) {
    if (listaAdyacencia.find(ciudad->nombre) == listaAdyacencia.end()) {
        listaAdyacencia[ciudad->nombre] = {};
    }
}

void Grafo::agregarRuta(Ciudad* origen, Ciudad* destino, float distancia) {
    listaAdyacencia[origen->nombre].push_back({destino, distancia});
    listaAdyacencia[destino->nombre].push_back({origen, distancia}); // grafo no dirigido
}

vector<pair<Ciudad*, float>> Grafo::obtenerAdyacentes(const string& nombre) {
    if (listaAdyacencia.find(nombre) != listaAdyacencia.end()) {
        return listaAdyacencia[nombre];
    }
    return {};
}

Ciudad* Grafo::buscarCiudad(const string& nombre) {
    for (auto& par : listaAdyacencia) {
        if (par.first == nombre) {
            //el primer elemento es la ciudad
            return par.second[0].first;
        }
    }
    return nullptr;
}


