#include "Mapa.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <limits>

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

vector<Ruta> rutas; // Rutas originales (solo para dibujar)
vector<Ruta> rutasCompletas; // Rutas completas (originales + inversas, para Dijkstra)

void initializeCities() {
    for (auto& city : ciudades) {
        city.shape.setFillColor(sf::Color::Green);
        city.shape.setOrigin(city.shape.getRadius(), city.shape.getRadius());
        city.shape.setPosition(city.posicion);
    }
}

void initializeRutas() {
    // Rutas originales (solo para dibujar)
    auto agregarRuta = [](Ciudad* origen, Ciudad* destino, vector<Vector2f> puntosMedios, float distancia) {
        rutas.push_back({origen, destino, puntosMedios, distancia});
        rutasCompletas.push_back({origen, destino, puntosMedios, distancia}); // Para Dijkstra
        rutasCompletas.push_back({destino, origen, puntosMedios, distancia}); // Ruta inversa para Dijkstra
    };

    // Definir todas las rutas originales
    agregarRuta(&ciudades[5], &ciudades[2], {{475, 150}, {490, 250}, {490, 280}}, 130.0f); // San Pedro Sula -> Siguatepeque
    agregarRuta(&ciudades[2], &ciudades[3], {{533, 313}}, 42.0f); // Siguatepeque -> Comayagua
    agregarRuta(&ciudades[3], &ciudades[0], {{542, 340}, {545, 345}, {570, 344}, {575, 356}}, 244.0f); // Comayagua -> Tegucigalpa
    agregarRuta(&ciudades[5], &ciudades[8], {{480, 145}}, 28.0f); // San Pedro Sula -> El Progreso
    agregarRuta(&ciudades[8], &ciudades[10], {{519, 141}, {540, 132}, {550, 104}}, 71.0f); // El Progreso -> Tela
    agregarRuta(&ciudades[10], &ciudades[9], {{590, 120}, {610, 125}, {640, 107}}, 103.0f); // Tela -> La Ceiba
    agregarRuta(&ciudades[5], &ciudades[7], {{485, 130}}, 15.0f); // San Pedro Sula -> Choloma
    agregarRuta(&ciudades[7], &ciudades[6], {{494, 100},{505, 93}}, 55.0f); // Choloma -> Puerto Cortés
    agregarRuta(&ciudades[0], &ciudades[1], {{600, 405},{597, 412}, {615, 434},{621, 483}}, 139.0f); // Tegucigalpa -> Choluteca
    agregarRuta(&ciudades[5], &ciudades[4], {{450, 170}, {400, 180}, {350, 220}}, 180.0f); // San Pedro Sula -> Copán
}

// Función para calcular la posición del carrito en la ruta
Vector2f calcularPosicionCarrito(const vector<Vector2f>& puntos, float progreso) {
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

    return puntos.back(); // Si el progreso es 1, devolver el último punto
}

// Algoritmo de Dijkstra para encontrar la ruta más corta
vector<Ciudad*> dijkstra(Ciudad* origen, Ciudad* destino) {
    // Estructuras para almacenar distancias y predecesores
    unordered_map<Ciudad*, float> distancias;
    unordered_map<Ciudad*, Ciudad*> predecesores;
    for (auto& ciudad : ciudades) {
        distancias[&ciudad] = numeric_limits<float>::infinity();
    }
    distancias[origen] = 0.0f;

    // Cola de prioridad para seleccionar el nodo con la menor distancia
    auto comparar = [](pair<Ciudad*, float> a, pair<Ciudad*, float> b) {
        return a.second > b.second;
    };
    priority_queue<pair<Ciudad*, float>, vector<pair<Ciudad*, float>>, decltype(comparar)> cola(comparar);
    cola.push({origen, 0.0f});

    while (!cola.empty()) {
        Ciudad* actual = cola.top().first;
        cola.pop();

        if (actual == destino) break; // Llegamos al destino

        // Explorar vecinos (rutas desde la ciudad actual)
        for (auto& ruta : rutasCompletas) {
            if (ruta.origen == actual) {
                float nuevaDistancia = distancias[actual] + ruta.distancia;
                if (nuevaDistancia < distancias[ruta.destino]) {
                    distancias[ruta.destino] = nuevaDistancia;
                    predecesores[ruta.destino] = actual;
                    cola.push({ruta.destino, nuevaDistancia});
                }
            }
        }
    }

    // Reconstruir la ruta desde el destino hasta el origen
    vector<Ciudad*> ruta;
    for (Ciudad* ciudad = destino; ciudad != nullptr; ciudad = predecesores[ciudad]) {
        ruta.push_back(ciudad);
    }
    reverse(ruta.begin(), ruta.end()); // Invertir para obtener origen -> destino

    return ruta;
}

// Función para obtener todos los puntos de una ruta (origen + puntos medios + destino)
vector<Vector2f> obtenerPuntosRuta(const vector<Ciudad*>& ruta) {
    vector<Vector2f> puntos;
    for (size_t i = 0; i < ruta.size(); ++i) {
        puntos.push_back(ruta[i]->posicion); // Agregar la posición de la ciudad

        // Si hay una ruta entre esta ciudad y la siguiente, agregar los puntos medios
        if (i < ruta.size() - 1) {
            for (auto& r : rutasCompletas) {
                if (r.origen == ruta[i] && r.destino == ruta[i + 1]) {
                    puntos.insert(puntos.end(), r.puntosMedios.begin(), r.puntosMedios.end());
                    break;
                }
            }
        }
    }
    return puntos;
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
    
    sf::Sprite carroButton;
    carroButton.setTexture(carT);
    carroButton.setPosition(25, 260);

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
    vector<Ciudad*> rutaCalculada;
    vector<Vector2f> puntosRuta;
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

                                // Calcular la ruta usando Dijkstra
                                rutaCalculada = dijkstra(selectedOrigin, selectedDestination);
                                puntosRuta = obtenerPuntosRuta(rutaCalculada);
                                tiempoTranscurrido = 0.0f; // Reiniciar el tiempo
                            }
                            break;
                        }
                    }

                    if (refresh.getGlobalBounds().contains(mousePos)) {
                        selectedOrigin = nullptr;
                        selectedDestination = nullptr;
                        rutaCalculada.clear();
                        puntosRuta.clear();
                        nodoOrigen.setString("");
                        nodoDestino.setString("");
                    }
                }
            }
        }

        // Actualizar la posición del carrito
        if (!puntosRuta.empty() && tiempoTranscurrido < duracionViaje) {
            tiempoTranscurrido += 0.016f; // Aproximadamente 1 frame (60 FPS)
            float progreso = tiempoTranscurrido / duracionViaje;
            car.setPosition(calcularPosicionCarrito(puntosRuta, progreso));
        }

        window.clear();
        window.draw(fondo);

        // Dibujar ciudades
        for (auto& city : ciudades) {
            window.draw(city.shape);
        }

        // Dibujar solo las rutas originales
        for (auto& route : rutas) {
            sf::VertexArray lines(sf::LineStrip, 2 + route.puntosMedios.size());
            lines[0].position = route.origen->posicion;
            lines[0].color = sf::Color::Red;

            for (size_t i = 0; i < route.puntosMedios.size(); ++i) {
                lines[i + 1].position = route.puntosMedios[i];
                lines[i + 1].color = sf::Color::Red;
            }

            lines[lines.getVertexCount() - 1].position = route.destino->posicion;
            lines[lines.getVertexCount() - 1].color = sf::Color::Red;

            window.draw(lines);
        }

        // Dibujar el carrito si hay una ruta calculada
        if (!puntosRuta.empty()) {
            window.draw(car);
        }

        window.draw(refresh);
        window.draw(car);
        window.draw(carroButton);
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
