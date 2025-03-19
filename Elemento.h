#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

template <class T>
struct Elemento {
    T dato;          
    Ciudad* ciudad;  

    Elemento(T datos, Ciudad* ciudadPtr) : dato(datos), ciudad(ciudadPtr) {}
};

#endif
