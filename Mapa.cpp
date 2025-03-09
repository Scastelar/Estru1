#include "Mapa.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;


struct Ruta {
    Ciudad* origen;
    Ciudad* destino;
    vector<Vector2f> puntosMedios;
    float distancia;
};

vector<Ciudad> ciudades = {
    {"Tegucigalpa", {602, 373}, sf::CircleShape(4)},    //0
    {"Choluteca", {606, 500}, sf::CircleShape(4)},      //1
    {"Siguatepeque", {525, 300}, sf::CircleShape(4)},   //2
    {"Comayagua", {536, 319}, sf::CircleShape(4)},     //3
    {"Copan", {295, 250}, sf::CircleShape(4)},          //4
    {"San Pedro Sula", {479, 135}, sf::CircleShape(4)}, //5
    {"Puerto Cortes", {490, 85}, sf::CircleShape(4)},   //6
    {"Choloma", {483, 120}, sf::CircleShape(4)},        //7
    {"El Progreso", {510, 159}, sf::CircleShape(4)},    //8
    {"La Ceiba", {675, 100}, sf::CircleShape(4)},       //9
    {"Tela", {574, 99}, sf::CircleShape(4)}             //10
};

vector<Ruta> rutas;

void initializeCities() {
    for (auto& city : ciudades) {
        city.shape.setFillColor(sf::Color::Green);
        city.shape.setOrigin(city.shape.getRadius(), city.shape.getRadius());
        city.shape.setPosition(city.posicion);
    }
}

void initializeRutas() {

    // Ruta 1: San Pedro Sula -> Siguatepeque
    Ruta ruta5;
    ruta5.origen = &ciudades[5]; // San Pedro Sula
    ruta5.destino = &ciudades[2]; // Siguatepeque
    ruta5.distancia = 130.0f;
    ruta5.puntosMedios = {{475, 150}, {490, 250}, {490, 280}};
    rutas.push_back(ruta5);

    // Ruta 4: Siguatepeque -> Comayagua
    Ruta ruta4;
    ruta4.origen = &ciudades[2]; // Siguatepeque
    ruta4.destino = &ciudades[3]; // Comayagua
    ruta4.distancia = 42.0f;
    ruta4.puntosMedios = {{533, 313}};
    rutas.push_back(ruta4);

    // Ruta 6: Comayagua -> Tegucigalpa
    Ruta ruta6;
    ruta6.origen = &ciudades[3]; // Comayagua
    ruta6.destino = &ciudades[0]; // Tegucigalpa
    ruta6.distancia = 244.0f;
    ruta6.puntosMedios = {{542, 340}, {545, 345}, {570, 344}, {575, 356}};
    rutas.push_back(ruta6);

    // Ruta 2: San Pedro Sula -> El Progreso
    Ruta ruta2;
    ruta2.origen = &ciudades[5]; // San Pedro Sula
    ruta2.destino = &ciudades[8]; // El Progreso
    ruta2.distancia = 28.0f;
    ruta2.puntosMedios = {{480, 145}};
    rutas.push_back(ruta2);

    // Ruta 7: El Progreso -> Tela
    Ruta ruta7;
    ruta7.origen = &ciudades[8]; // El Progreso
    ruta7.destino = &ciudades[10]; // Tela
    ruta7.distancia = 71.0f;
    ruta7.puntosMedios = {{519, 141}, {540, 132}, {550, 104}};
    rutas.push_back(ruta7);

    // Ruta 8: Tela -> La Ceiba
    Ruta ruta8;
    ruta8.origen = &ciudades[10]; // Tela
    ruta8.destino = &ciudades[9]; // La Ceiba
    ruta8.distancia = 103.0f;
    ruta8.puntosMedios = {{590, 120}, {610, 125}, {640, 107}};
    rutas.push_back(ruta8);
    
    // Ruta 9: San Pedro Sula -> Choloma
    Ruta ruta9;
    ruta9.origen = &ciudades[5]; // San Pedro Sula
    ruta9.destino = &ciudades[7]; // Choloma
    ruta9.distancia = 15.0f; 
    ruta9.puntosMedios = {{485, 130}};
    rutas.push_back(ruta9);

    // Ruta 10: Choloma -> Puerto Cortés
    Ruta ruta10;
    ruta10.origen = &ciudades[7]; // Choloma
    ruta10.destino = &ciudades[6]; // Puerto Cortés
    ruta10.distancia = 55.0f; 
    ruta10.puntosMedios = {{494, 100},{505, 93}}; 
    rutas.push_back(ruta10);

    // Ruta 11: Tegucigalpa -> Choluteca
    Ruta ruta11;
    ruta11.origen = &ciudades[0]; // Tegucigalpa
    ruta11.destino = &ciudades[1]; // Choluteca
    ruta11.distancia = 139.0f; 
    ruta11.puntosMedios = {{600, 405},{597, 412}, {615, 434},{621, 483}};
    rutas.push_back(ruta11);

    // Ruta 12: San Pedro Sula -> Copán
    Ruta ruta12;
    ruta12.origen = &ciudades[5]; // San Pedro Sula
    ruta12.destino = &ciudades[4]; // Copán
    ruta12.distancia = 180.0f; 
    ruta12.puntosMedios = {{450, 170}, {400, 180}, {350, 220}}; 
    rutas.push_back(ruta12);
}

// Función para calcular la posición del carrito en la ruta
Vector2f calcularPosicionCarrito(const Ruta& ruta, float progreso) {
    // Unir todos los puntos de la ruta (origen + puntos intermedios + destino)
    vector<Vector2f> puntos = {ruta.origen->posicion};
    puntos.insert(puntos.end(), ruta.puntosMedios.begin(), ruta.puntosMedios.end());
    puntos.push_back(ruta.destino->posicion);

    // Calcular la distancia total de la ruta
    float distanciaTotal = 0.0f;
    for (size_t i = 1; i < puntos.size(); ++i) {
        distanciaTotal += std::hypot(puntos[i].x - puntos[i - 1].x, puntos[i].y - puntos[i - 1].y);
    }

    // Calcular la distancia actual basada en el progreso
    float distanciaActual = progreso * distanciaTotal;

    // Encontrar el segmento actual y la posición dentro de ese segmento
    for (size_t i = 1; i < puntos.size(); ++i) {
        float segmentoDistancia = std::hypot(puntos[i].x - puntos[i - 1].x, puntos[i].y - puntos[i - 1].y);
        if (distanciaActual <= segmentoDistancia) {
            float t = distanciaActual / segmentoDistancia;
            return Vector2f(
                puntos[i - 1].x + t * (puntos[i].x - puntos[i - 1].x),
                puntos[i - 1].y + t * (puntos[i].y - puntos[i - 1].y)
            );
        }
        distanciaActual -= segmentoDistancia;
    }

    return ruta.destino->posicion; // Si el progreso es 1, devolver el destino
}

void Mapa::run() {
    sf::RenderWindow window(sf::VideoMode(1250, 600), "Mapa de Honduras");

    initializeCities();
    initializeRutas();

    // Imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondo.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
        return;
    }
    sf::Sprite fondo(fondoTexture);

    // Textos
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return;
    }

    sf::Text origenTxt("Origen:", font, 17);
    origenTxt.setPosition(20, 90);
    origenTxt.setFillColor(sf::Color::Black);

    sf::Text destTxt("Destino:", font, 17);
    destTxt.setPosition(20, 180);
    destTxt.setFillColor(sf::Color::Black);

    sf::RectangleShape origenCampo(sf::Vector2f(200, 40));
    origenCampo.setPosition(20, 115);
    origenCampo.setFillColor(sf::Color::White);

    sf::Text nodoOrigen(" ", font, 17);
    nodoOrigen.setPosition(25, 120);
    nodoOrigen.setFillColor(sf::Color::Black);

    sf::RectangleShape destCampo(sf::Vector2f(200, 40));
    destCampo.setPosition(20, 205);
    destCampo.setFillColor(sf::Color::White);

    sf::Text nodoDestino(" ", font, 17);
    nodoDestino.setPosition(25, 210);
    nodoDestino.setFillColor(sf::Color::Black);

    sf::Texture refreshT;
    if (!refreshT.loadFromFile("refresh.png")) {
        std::cerr << "Error al cargar la imagen\n";
        return;
    }

    sf::Texture carT;
    if (!carT.loadFromFile("car.png")) {
        std::cerr << "Error al cargar la imagen\n";
        return;
    }

    // Botones
    sf::Sprite refresh;
    refresh.setTexture(refreshT);
    refresh.setPosition(180, 30);

    sf::Sprite car;
    car.setTexture(carT);
    car.setOrigin(car.getLocalBounds().width / 2, car.getLocalBounds().height / 2); // Centrar el carrito

    sf::RectangleShape calcularButton(sf::Vector2f(125, 30));
    calcularButton.setPosition(80, 262);
    calcularButton.setFillColor(sf::Color(176, 92, 85));
    sf::Text calcularTxt("Calcular ruta", font, 17);
    calcularTxt.setFillColor(sf::Color::White);
    calcularTxt.setPosition(85, 265);

    Ciudad* selectedOrigin = nullptr;
    Ciudad* selectedDestination = nullptr;
    Ruta* rutaSeleccionada = nullptr;
    float tiempoTranscurrido = 0.0f;
    const float duracionViaje = 10.0f; // 10 segundos para llegar al destino

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                    for (auto& city : ciudades) {
                        if (city.shape.getGlobalBounds().contains(mousePos)) {
                            if (!selectedOrigin) {
                                selectedOrigin = &city;
                                nodoOrigen.setString(city.nombre);
                            } else if (!selectedDestination) {
                                selectedDestination = &city;
                                nodoDestino.setString(city.nombre);

                                // Buscar la ruta seleccionada
                                for (auto& ruta : rutas) {
                                    if (ruta.origen == selectedOrigin && ruta.destino == selectedDestination) {
                                        rutaSeleccionada = &ruta;
                                        tiempoTranscurrido = 0.0f; // Reiniciar el tiempo
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }

                    if (refresh.getGlobalBounds().contains(mousePos)) {
                        selectedOrigin = nullptr;
                        selectedDestination = nullptr;
                        rutaSeleccionada = nullptr;
                        nodoOrigen.setString("");
                        nodoDestino.setString("");
                    }
                }
            }
        }

        // Actualizar la posición del carrito
        if (rutaSeleccionada && tiempoTranscurrido < duracionViaje) {
            tiempoTranscurrido += 0.016f; // Aproximadamente 1 frame (60 FPS)
            float progreso = tiempoTranscurrido / duracionViaje;
            car.setPosition(calcularPosicionCarrito(*rutaSeleccionada, progreso));
        }

        window.clear();
        window.draw(fondo);

        // Dibujar ciudades
        for (auto& city : ciudades) {
            window.draw(city.shape);
        }

        // Dibujar rutas con líneas gruesas
        for (auto& route : rutas) {
            vector<Vector2f> puntos = {route.origen->posicion};
            puntos.insert(puntos.end(), route.puntosMedios.begin(), route.puntosMedios.end());
            puntos.push_back(route.destino->posicion);

            for (size_t i = 1; i < puntos.size(); ++i) {
                sf::RectangleShape linea(Vector2f(std::hypot(puntos[i].x - puntos[i - 1].x, puntos[i].y - puntos[i - 1].y), 3));
                linea.setPosition(puntos[i - 1]);
                linea.setFillColor(sf::Color::Red);
                float angulo = std::atan2(puntos[i].y - puntos[i - 1].y, puntos[i].x - puntos[i - 1].x) * 180 / 3.14159265;
                linea.setRotation(angulo);
                window.draw(linea);
            }
        }

        // Dibujar el carrito si hay una ruta seleccionada
        if (rutaSeleccionada) {
            window.draw(car);
        }

        window.draw(refresh);
        window.draw(car);
        window.draw(calcularButton);
        window.draw(calcularTxt);
        window.draw(destTxt);
        window.draw(origenTxt);
        window.draw(origenCampo);
        window.draw(destCampo);
        window.draw(nodoOrigen);
        window.draw(nodoDestino);
        window.display();
    }
}
