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
    {"Tegucigalpa", {602, 373}, sf::CircleShape(4)},   					//0
    {"Choluteca", {607, 501}, sf::CircleShape(4)},      				//1
    {"Siguatepeque", {525, 300}, sf::CircleShape(4)},  					//2
    {"Comayagua", {536, 319}, sf::CircleShape(4)},     					//3
    {"Copan", {295, 250}, sf::CircleShape(4)},          				//4
    {"San Pedro Sula", {479, 135}, sf::CircleShape(4)},					//5
    {"Puerto Cortes", {490, 85}, sf::CircleShape(4)},   				//6
    {"Choloma", {483, 120}, sf::CircleShape(4)},        				//7
    {"El Progreso", {510, 159}, sf::CircleShape(4)},   				    //8
    {"La Ceiba", {675, 100}, sf::CircleShape(4)},       				//9
    {"Tela", {574, 99}, sf::CircleShape(4)},           				    //10
    {"Santa Barbara", {487, 235}, sf::CircleShape(4)},					//11
    {"La Entrada", {356, 220}, sf::CircleShape(4)},						//12
    {"Omoa", {475, 103}, sf::CircleShape(4)},							//13
    {"La Lima", {495, 152}, sf::CircleShape(4)},						//14
    {"Santa Rosa de Copan", {355, 260}, sf::CircleShape(4)},			//15
    {"Gracias", {387, 292}, sf::CircleShape(4)},						//16
    {"La Esperanza", {450, 340}, sf::CircleShape(4)},					//17
    {"Marcala", {474, 366}, sf::CircleShape(4)},						//18
    {"La Paz", {530, 335}, sf::CircleShape(4)},							//19
    {"Nuevo Ocotepeque", {290, 315}, sf::CircleShape(4)},				//20
    {"San Lorenzo", {567, 484}, sf::CircleShape(4)},					//21
    {"Yuscaran", {662, 397}, sf::CircleShape(4)},						//22
    {"Talanga", {628, 325}, sf::CircleShape(4)},						//23
    {"Guaimaca", {662, 300}, sf::CircleShape(4)},						//24
    {"Santa Rita", {500, 185}, sf::CircleShape(4)},						//25
    {"Morazan", {545, 170}, sf::CircleShape(4)},						//26
    {"Yoro", {615, 203}, sf::CircleShape(4)},							//27
    {"Olanchito", {710, 145}, sf::CircleShape(4)},						//28
    {"Juticalpa", {811, 256}, sf::CircleShape(4)},						//29
    {"Catacamas", {847, 237}, sf::CircleShape(4)},						//30
    {"Sonaguera", {753, 125}, sf::CircleShape(4)},						//31
    {"Tocoa", {790, 129}, sf::CircleShape(4)},							//32
    {"Trujillo", {806, 78}, sf::CircleShape(4)},						//33
	{"Nacaome", {561, 465}, sf::CircleShape(4)},						//34
};

vector<Ruta> rutas; //rutas
vector<Ruta> rutasCompletas; // Rutas completas (originales + inversas, para Dijkstra)

void initializeCities() {
    for (auto& city : ciudades) {
        city.shape.setFillColor(sf::Color::Green);
        city.shape.setOrigin(city.shape.getRadius(), city.shape.getRadius());
        city.shape.setPosition(city.posicion);
    }
}

void initializeRutas() {
    auto agregarRuta = [](Ciudad* origen, Ciudad* destino, vector<Vector2f> puntosMedios, float distancia) {
        rutas.push_back({origen, destino, puntosMedios, distancia}); //rutas en pantalla
        rutasCompletas.push_back({origen, destino, puntosMedios, distancia}); // ruta original para Dijkstra

        // Invertir los puntos medios para la ruta inversa
        vector<Vector2f> puntosMediosInversos(puntosMedios.rbegin(), puntosMedios.rend());
        rutasCompletas.push_back({destino, origen, puntosMediosInversos, distancia}); // Ruta inversa para Dijkstra
    };

    // Definir todas las rutas originales
    agregarRuta(&ciudades[5], &ciudades[11], {{475, 150},{485, 180}},83.0f); // San Pedro Sula -> Santa Barbara
    agregarRuta(&ciudades[11], &ciudades[2], {{485, 270}, {490, 280}}, 100.0f); // Santa Barbara -> Siguatepeque
    agregarRuta(&ciudades[2], &ciudades[3], {{533, 313}}, 42.0f); // Siguatepeque -> Comayagua
    agregarRuta(&ciudades[3], &ciudades[0], {{542, 340}, {545, 345}, {570, 344}, {575, 356}}, 86.0f); // Comayagua -> Tegucigalpa
    agregarRuta(&ciudades[5], &ciudades[14], {{480, 145}}, 11.0f); // San Pedro Sula -> La Lima
    agregarRuta(&ciudades[14], &ciudades[8], {}, 21.0f); // La Lima -> El Progreso
    agregarRuta(&ciudades[8], &ciudades[10], {{519, 141}, {540, 132}, {550, 104}}, 71.0f); // El Progreso -> Tela
    agregarRuta(&ciudades[10], &ciudades[9], {{590, 120}, {610, 125}, {640, 107}}, 103.0f); // Tela -> La Ceiba
    agregarRuta(&ciudades[5], &ciudades[7], {{485, 130}}, 15.0f); // San Pedro Sula -> Choloma
    agregarRuta(&ciudades[7], &ciudades[6], {{494, 100},{505, 93}}, 55.0f); // Choloma -> Puerto Cortés
    agregarRuta(&ciudades[6], &ciudades[13], {{484, 97}}, 24.0f); // Puerto Cortés -> Omoa
    agregarRuta(&ciudades[5], &ciudades[12], {{476, 150},{456, 156},{445, 170}, {405, 170}, {350, 220}}, 110.0f); // San Pedro Sula -> La Entrada
    agregarRuta(&ciudades[12], &ciudades[4], {{350, 217},{329, 237}}, 64.0f); // La Entrada -> Copán
    agregarRuta(&ciudades[0], &ciudades[1], {{605, 377},{600, 405},{597, 412}, {615, 434},{621, 483}}, 139.0f); // Tegucigalpa -> Choluteca
	agregarRuta(&ciudades[0], &ciudades[34], {{605, 377},{600, 405},{597, 412}, {579, 456},{566, 465}}, 92.0f); // Tegucigalpa -> Nacaome
	agregarRuta(&ciudades[34], &ciudades[21], {{564, 464},{567, 476}}, 92.0f); // Nacaome -> San Lorenzo
    agregarRuta(&ciudades[21], &ciudades[1], {{579, 484}}, 76.0f); // San Lorenzo -> Choluteca
    agregarRuta(&ciudades[12], &ciudades[15], {{358, 240},{352, 250}}, 45.0f); // La Entrada -> Santa Rosa de Copan
    agregarRuta(&ciudades[15], &ciudades[16], {{372, 263},{377, 270}}, 51.0f); // Santa Rosa de Copan -> Gracias
    agregarRuta(&ciudades[16], &ciudades[17], {{400, 310},{405, 320},{415, 330}}, 96.0f); //Gracias -> La Esperanza
	agregarRuta(&ciudades[17], &ciudades[18], {{465, 340},{470, 345}}, 52.0f); //La Esperanza -> Marcala
	agregarRuta(&ciudades[18], &ciudades[19], {{480, 366},{505, 347},{527, 345}}, 36.0f); // Marcala -> La Paz
	agregarRuta(&ciudades[19], &ciudades[3], {}, 35.0f); // La Paz -> Comayagua
	agregarRuta(&ciudades[25], &ciudades[26], {{515, 190},{530, 173}}, 20.0f); // Santa Rita -> Morazan
	agregarRuta(&ciudades[26], &ciudades[27], {{585, 175},{590, 197},{595, 196}}, 40.0f); // Morazan -> Yoro
	agregarRuta(&ciudades[26], &ciudades[23], {{585, 175},{590, 197},{587, 220},{592, 235},{615, 243},{605, 273},{628, 300}}, 65.0f); // Morazan -> Talanga
	agregarRuta(&ciudades[27], &ciudades[23], {{605, 200},{590, 197},{587, 220},{592, 235},{615, 243},{605, 273},{628, 300}}, 110.0f); // Yoro -> Talanga
	agregarRuta(&ciudades[8], &ciudades[25], {}, 12.0f); // El Progreso -> Santa Rita
	agregarRuta(&ciudades[25], &ciudades[11], {{500, 190},{488, 214}}, 85.0f); // Santa Rita -> Santa Barbara
	agregarRuta(&ciudades[0], &ciudades[23], {{609, 355},{609, 335},{625, 320}}, 52.0f); // Tegucigalpa -> Talanga
	agregarRuta(&ciudades[23], &ciudades[24], {{640, 310}}, 45.0f); // Talanga -> Guaimaca
	agregarRuta(&ciudades[24], &ciudades[29], {{692, 297},{791, 266}}, 85.0f); // Guaimaca -> Juticalpa
	agregarRuta(&ciudades[29], &ciudades[30], {{827, 250}}, 43.0f); // Juticalpa -> Catacamas
	agregarRuta(&ciudades[21], &ciudades[34], {{565, 467}}, 18.0f); // San Lorenzo -> Nacaome
	agregarRuta(&ciudades[0], &ciudades[22], {{638, 388},{655, 382}}, 67.0f); // Tegucigalpa -> Yuscaran
	agregarRuta(&ciudades[9], &ciudades[31], {{712, 100},{720, 115},{745, 135}}, 60.0f); // La Ceiba -> Sonaguera
	agregarRuta(&ciudades[28], &ciudades[24], {{735, 150},{730, 200},{705, 218},{708, 238},{700, 258},{715, 288}}, 150.0f); // Olanchito -> Guaimaca
	agregarRuta(&ciudades[28], &ciudades[29], {{735, 150},{730, 200},{705, 218},{708, 238},{700, 258},{715, 288},{760, 276}}, 120.0f); // Olanchito -> Juticalpa
	agregarRuta(&ciudades[28], &ciudades[32], {{735, 150}}, 90.0f); // Olanchito -> Tocoa
	agregarRuta(&ciudades[31], &ciudades[32], {{748, 135},{765, 137}}, 30.0f); // Sonaguera -> Tocoa
    agregarRuta(&ciudades[15], &ciudades[20], {{345, 275},{335, 280},{318, 315},{311, 325},{300, 315}}, 70.0f); // Santa Rosa de Copan -> Nuevo Ocotepeque
	agregarRuta(&ciudades[1], &ciudades[22], {{622, 492},{658, 490},{668, 480},{673, 448},{660, 432},{670, 420},{670, 410}}, 196.0f); // Choluteca -> Yuscaran
	agregarRuta(&ciudades[32], &ciudades[24], {{735, 150},{730, 200},{705, 218},{708, 238},{700, 258},{715, 288}}, 130.0f); // Tocoa -> Guaimaca
	agregarRuta(&ciudades[32], &ciudades[29], {{830, 100},{840, 107},{845, 126},{867, 150},{830, 206},{795, 220},{780, 235},{780, 253},{795, 265}}, 160.0f); // Tocoa -> Juticalpa
	agregarRuta(&ciudades[32], &ciudades[33], {{830, 100},{833, 90},{830, 85}}, 50.0f); // Tocoa -> Trujillo
	agregarRuta(&ciudades[27], &ciudades[28], {{637, 188},{634, 183},{656, 180},{656, 175},{645, 173},{642, 163},{645, 155},{665, 160}}, 60.0f); // Yoro -> Olanchito
	agregarRuta(&ciudades[31], &ciudades[29], {{820, 93},{826, 83},{830, 85},{833, 90},{830, 100},{840, 107},{845, 126},{867, 150},{830, 206},{795, 220},{780, 235},{780, 253},{795, 265}}, 230.0f); // Sonaguera -> Juticalpa
	agregarRuta(&ciudades[31], &ciudades[33], {{820, 93},{826, 83}}, 80.0f); // Sonaguera -> Trujillo
	agregarRuta(&ciudades[33], &ciudades[29], {{830, 85},{833, 90},{830, 100},{840, 107},{845, 126},{867, 150},{830, 206},{795, 220},{780, 235},{780, 253},{795, 265}}, 200.0f); // Trujillo -> Juticalpa

}


// Funcion para calcular la posicion del carrito en la ruta
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

// Funcion para obtener todos los puntos de una ruta (origen + puntos medios + destino)
vector<Vector2f> obtenerPuntosRuta(const vector<Ciudad*>& ruta) {
    vector<Vector2f> puntos;
    for (size_t i = 0; i < ruta.size(); ++i) {
        puntos.push_back(ruta[i]->posicion); // Agregar la posicion de la ciudad

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
    car.setOrigin(car.getLocalBounds().width / 2, car.getLocalBounds().height / 2); // centrar el carrito

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
    const float duracionViaje = 40.0f; // 40 segundos para llegar al destino

    // Variables para el menú de selección de rutas
    vector<vector<Ciudad*>> rutasDisponibles;
    int rutaSeleccionada = -1;
    bool mostrandoMenu = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                    // Seleccionar origen y destino
                    for (auto& city : ciudades) {
                        if (city.shape.getGlobalBounds().contains(mousePos)) {
                            if (!selectedOrigin) {
                                selectedOrigin = &city;
                                nodoOrigen.setString(city.nombre);
                            } else if (!selectedDestination) {
                                selectedDestination = &city;
                                nodoDestino.setString(city.nombre);

                                // Calcular todas las rutas disponibles usando Dijkstra
                                rutasDisponibles.clear();
                                rutasDisponibles.push_back(dijkstra(selectedOrigin, selectedDestination));
                                mostrandoMenu = true; // Mostrar el menú de selección
                            }
                            break;
                        }
                    }

                    // Botón de refresh
                    if (refresh.getGlobalBounds().contains(mousePos)) {
                        selectedOrigin = nullptr;
                        selectedDestination = nullptr;
                        rutaCalculada.clear();
                        puntosRuta.clear();
                        nodoOrigen.setString("");
                        nodoDestino.setString("");
                        mostrandoMenu = false;
                    }

                    // Botón de calcular ruta
                    if (calcularButton.getGlobalBounds().contains(mousePos)) {
                        if (mostrandoMenu && rutaSeleccionada != -1) {
                            rutaCalculada = rutasDisponibles[rutaSeleccionada];
                            puntosRuta = obtenerPuntosRuta(rutaCalculada);
                            tiempoTranscurrido = 0.0f; // Reinicia el tiempo
                            mostrandoMenu = false; // Ocultar el menú
                        }
                    }
                }
            }

            // Manejar la selección de rutas desde el menú
            if (event.type == sf::Event::KeyPressed && mostrandoMenu) {
                if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                    int seleccion = event.key.code - sf::Keyboard::Num0;
                    if (seleccion < rutasDisponibles.size()) {
                        rutaSeleccionada = seleccion;
                    }
                }
            }
        }

        // Actualizar la posición del carrito
        if (!puntosRuta.empty() && tiempoTranscurrido < duracionViaje) {
            tiempoTranscurrido += 0.016f;
            float progreso = tiempoTranscurrido / duracionViaje;
            car.setPosition(calcularPosicionCarrito(puntosRuta, progreso));
        }

        window.clear();
        window.draw(fondo);

        // Dibujar ciudades
        for (auto& city : ciudades) {
            window.draw(city.shape);
        }

        // Dibujar rutas
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

        // Dibujar rutas disponibles en azul
        if (mostrandoMenu) {
            for (size_t i = 0; i < rutasDisponibles.size(); ++i) {
                vector<Vector2f> puntos = obtenerPuntosRuta(rutasDisponibles[i]);
                sf::VertexArray lines(sf::LineStrip, puntos.size());
                for (size_t j = 0; j < puntos.size(); ++j) {
                    lines[j].position = puntos[j];
                    lines[j].color = (i == rutaSeleccionada) ? sf::Color::Green : sf::Color::Blue;
                }
                window.draw(lines);
            }
        }

        // Dibujar el carrito si hay una ruta seleccionada
        if (!puntosRuta.empty()) {
            window.draw(car);
        }

        // Dibujar interfaz de usuario
        window.draw(refresh);
        window.draw(carroButton);
        window.draw(calcularButton);
        window.draw(calcularTxt);
        window.draw(destTxt);
        window.draw(origenTxt);
        window.draw(origenCampo);
        window.draw(destCampo);
        window.draw(nodoOrigen);
        window.draw(nodoDestino);

        // Mostrar el menú de selección de rutas
        if (mostrandoMenu) {
            sf::Text menuTxt("Seleccione una ruta (0-" + to_string(rutasDisponibles.size() - 1) + "):", font, 20);
            menuTxt.setPosition(20, 300);
            menuTxt.setFillColor(sf::Color::Black);
            window.draw(menuTxt);
        }

        window.display();
    }
}
