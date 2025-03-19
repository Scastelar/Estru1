#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <vector>
#include "Elemento.h"
#include <utility> 

using namespace std;

template <class T>
class Cola {
private:
    vector<Elemento<T>> elementos;  

public:
    bool colaVacia() {
        return elementos.size() == 0; 
    }
    
    void insertar(T dato, Ciudad* ciudad) {
        Elemento<T> nuevo(dato, ciudad);
        int i = 0;

        while (i < elementos.size() && elementos[i].dato < nuevo.dato) {
            i++; 
        }

        elementos.insert(elementos.begin() + i, nuevo); 
    }

    // Desencolar el primer elemento (menor prioridad)
    Elemento<T> desencolar() {
        if (colaVacia()) { 
            return Elemento<T>(-1, nullptr);
        }
        Elemento<T> primero = elementos.front();  
        elementos.erase(elementos.begin());     
        return primero;
    }

};

#endif
