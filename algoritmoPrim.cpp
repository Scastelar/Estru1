#include <iostream>
using namespace std;

void prim(int grafo[][4], int numVertices, int INF) {
    int padre[numVertices];
    int pesoMinimo[numVertices];
    bool visitado[numVertices];

    for (int i = 0; i < numVertices; i++) {
        pesoMinimo[i] = INF;
        visitado[i] = false;
    }

    pesoMinimo[0] = 0;
    padre[0] = -1;

    for (int i = 0; i < numVertices - 1; i++) {
        int verticeActual, minPeso = INF;
        for (int v = 0; v < numVertices; v++) {
            if (!visitado[v] && pesoMinimo[v] < minPeso) {
                minPeso = pesoMinimo[v];
                verticeActual = v;
            }
        }

        visitado[verticeActual] = true;

        for (int v = 0; v < numVertices; v++) {
            if (grafo[verticeActual][v] && !visitado[v] && grafo[verticeActual][v] < pesoMinimo[v]) {
                padre[v] = verticeActual;
                pesoMinimo[v] = grafo[verticeActual][v];
            }
        }
    }

    cout << "Algotitmo Prim" << endl;
    for (int i = 1; i < numVertices; i++) {
        cout << padre[i] << " -- " << grafo[i][padre[i]] << " --  " << i  << endl;
    }
}


int main() {
    int numVertices = 4;
    int INF = 99999;
    int grafo[4][4] = {
     {0, 1, 4, 3},
     {1, 0, 0, 2},
      {4, 0, 0, 5},
      {3, 2, 5, 0}
     };

    prim(grafo, numVertices, INF);
    return 0;
}