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
    {"Santa Barbara", {441, 235}, sf::CircleShape(4)},  //5
    {"San Pedro Sula", {479, 135}, sf::CircleShape(4)}, //6
    {"Puerto Cortes", {490, 85}, sf::CircleShape(4)},   //7
    {"Choloma", {483, 120}, sf::CircleShape(4)},        //8
    {"El Progreso", {510, 159}, sf::CircleShape(4)},    //9
    {"La Ceiba", {675, 100}, sf::CircleShape(4)},       //10
    {"Tela", {574, 99}, sf::CircleShape(4)}             //11
};

vector<Ruta> rutas;

void initializeCities() {
    for (auto& city : ciudades) {
        city.shape.setFillColor(sf::Color::Green);
        city.shape.setOrigin(city.shape.getRadius(), city.shape.getRadius());
        city.shape.setPosition(city.position);
    }
}

void initializeRutas() {
    // Ruta 1: San Pedro Sula -> Tegucigalpa
    
    Ruta ruta1;
    ruta1.origen = &ciudades[6]; // San Pedro Sula
    ruta1.destino = &ciudades[0]; // Tegucigalpa
    ruta1.distancia = 244.0f;
    ruta1.puntosMedios = {{470, 150},{490, 250},{490, 280},{525, 300}, {540, 340}, {570, 350}}; 
    rutas.push_back(ruta1);
    

    // Ruta 2: San Pedro Sula -> El Progreso
	 
    Ruta ruta2;
    ruta2.origen = &ciudades[6]; // San Pedro Sula
    ruta2.destino = &ciudades[9]; // El Progreso
    ruta2.distancia = 28.0f;
    ruta2.puntosMedios = {{480, 145}}; 
    rutas.push_back(ruta2);
    
    
    // Ruta 3: San Pedro Sula -> La Ceiba
    Ruta ruta3;
    ruta3.origen = &ciudades[6]; // San Pedro Sula
    ruta3.destino = &ciudades[10]; // La Ceiba
    ruta3.distancia = 203.0f;
    ruta3.puntosMedios = {{480, 145},{510, 159},{540, 129},{550, 109}, {574, 99},{590, 120},{610, 125}, {640, 107}}; 
    rutas.push_back(ruta3);
	
}

void Mapa::run() {
    sf::RenderWindow window(sf::VideoMode(1250, 600), "Mapa de Honduras");

    initializeCities();
    initializeRutas();

    // imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondo.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
        return;
    }
    sf::Sprite fondo(fondoTexture);

    // textos
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
    car.setPosition(25, 260);

    sf::RectangleShape calcularButton(sf::Vector2f(125, 30));
    calcularButton.setPosition(80, 262);
    calcularButton.setFillColor(sf::Color(176, 92, 85));
    sf::Text calcularTxt("Calcular ruta", font, 17);
    calcularTxt.setFillColor(sf::Color::White);
    calcularTxt.setPosition(85, 265);

    Ciudad* selectedOrigin = nullptr;
    Ciudad* selectedDestination = nullptr;

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
                                nodoOrigen.setString(city.name);
                            } else if (!selectedDestination) {
                                selectedDestination = &city;
                                nodoDestino.setString(city.name);
                            }
                            break;
                        }
                    }

                    if (refresh.getGlobalBounds().contains(mousePos)) {
                        selectedOrigin = nullptr;
                        selectedDestination = nullptr;
                        nodoOrigen.setString("");
                        nodoDestino.setString("");
                    }
                }
            }
        }

        window.clear();
        window.draw(fondo);

        for (auto& city : ciudades) {
            window.draw(city.shape);
        }

        for (auto& route : rutas) {
            // origen a primer punto intermedio
            sf::VertexArray lines(sf::LineStrip, 2 + route.puntosMedios.size());
            lines[0].position = route.origen->position;
            lines[0].color = sf::Color::Red;

            // puntos intermedios
            for (size_t i = 0; i < route.puntosMedios.size(); ++i) {
                lines[i + 1].position = route.puntosMedios[i];
                lines[i + 1].color = sf::Color::Green;
            }

            // punto intermedio hasta destino
            lines[lines.getVertexCount() - 1].position = route.destino->position;
            lines[lines.getVertexCount() - 1].color = sf::Color::Red;

            window.draw(lines);
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
