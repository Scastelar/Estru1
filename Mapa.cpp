#include "Mapa.h"
#include "Inicio.h"
#include "Colores.h"
#include "Cola.h"
using namespace std;
using namespace sf;

vector<Ruta> rutas;
vector<Ruta> rutasCompletas;

vector<Ciudad> ciudades = {
    {"Tegucigalpa", {602, 373}, CircleShape(4)},	//0
    {"Choluteca", {607, 501}, CircleShape(4)},		//1
    {"Siguatepeque", {525, 300}, CircleShape(4)},	//2
    {"Comayagua", {536, 319}, CircleShape(4)},		//3
    {"Copan", {295, 250}, CircleShape(4)},			//4
    {"San Pedro Sula", {479, 135}, CircleShape(4)},	//5
    {"Puerto Cortes", {490, 85}, CircleShape(4)},	//6
    {"Choloma", {483, 120}, CircleShape(4)},		//7
    {"El Progreso", {510, 159}, CircleShape(4)},	//8
    {"La Ceiba", {675, 100}, CircleShape(4)},		//9
    {"Tela", {574, 99}, CircleShape(4)},			//10
    {"Santa Barbara", {487, 235}, CircleShape(4)},	//11
    {"La Entrada", {356, 220}, CircleShape(4)},		//12
    {"Omoa", {475, 103}, CircleShape(4)},			//13
    {"La Lima", {495, 152}, CircleShape(4)},		//14
    {"Santa Rosa de Copan", {355, 260}, CircleShape(4)},	//15
    {"Gracias", {387, 292}, CircleShape(4)},				//16
    {"La Esperanza", {450, 340}, CircleShape(4)},			//17
    {"Marcala", {474, 366}, CircleShape(4)},				//18
    {"La Paz", {530, 335}, CircleShape(4)},					//19
    {"Nuevo Ocotepeque", {290, 315}, CircleShape(4)},		//20
    {"San Lorenzo", {567, 484}, CircleShape(4)},			//21
    {"Yuscaran", {662, 397}, CircleShape(4)},				//22
    {"Talanga", {628, 325}, CircleShape(4)},				//23
    {"Guaimaca", {662, 300}, CircleShape(4)},				//24
    {"Santa Rita", {500, 185}, CircleShape(4)},				//25
    {"Morazan", {545, 170}, CircleShape(4)},				//26
    {"Yoro", {615, 203}, CircleShape(4)},					//27
    {"Olanchito", {710, 145}, CircleShape(4)},				//28
    {"Juticalpa", {811, 256}, CircleShape(4)},				//29
    {"Catacamas", {847, 237}, CircleShape(4)},				//30
    {"Sonaguera", {753, 125}, CircleShape(4)},				//31
    {"Tocoa", {790, 129}, CircleShape(4)},					//32
    {"Trujillo", {806, 78}, CircleShape(4)},				//33
    {"Nacaome", {561, 465}, CircleShape(4)}					//34
};

void initializeCities() {
    for (auto& city : ciudades) {
        city.shape.setFillColor(Color::Green);
        city.shape.setOrigin(city.shape.getRadius(), city.shape.getRadius());
        city.shape.setPosition(city.posicion);
    }
}

void initializeRutas() {
    auto agregarRuta = [](Ciudad* origen, Ciudad* destino, vector<Vector2f> puntosMedios, float distancia) {
        rutas.push_back({origen, destino, puntosMedios, distancia});
        rutasCompletas.push_back({origen, destino, puntosMedios, distancia});

        // Invertir los puntos medios para la ruta inversa
        vector<Vector2f> puntosMediosInversos(puntosMedios.rbegin(), puntosMedios.rend());
        rutasCompletas.push_back({destino, origen, puntosMediosInversos, distancia});
    };

    agregarRuta(&ciudades[5], &ciudades[11], {{475, 150}, {485, 180}}, 92.0f);
    agregarRuta(&ciudades[11], &ciudades[2], {{485, 270}, {490, 280}}, 100.0f);
    agregarRuta(&ciudades[2], &ciudades[3], {{533, 313}}, 42.0f);
    agregarRuta(&ciudades[3], &ciudades[0], {{542, 340}, {545, 345}, {570, 344}, {575, 356}}, 86.0f);
    agregarRuta(&ciudades[5], &ciudades[14], {{480, 145}}, 25.0f);
    agregarRuta(&ciudades[14], &ciudades[8], {}, 35.0f);
    agregarRuta(&ciudades[8], &ciudades[10], {{519, 141}, {540, 132}, {550, 104}}, 71.0f);
    agregarRuta(&ciudades[10], &ciudades[9], {{590, 120}, {610, 125}, {640, 107}}, 103.0f);
    agregarRuta(&ciudades[5], &ciudades[7], {{485, 130}}, 15.0f);
    agregarRuta(&ciudades[7], &ciudades[6], {{494, 100}, {505, 93}}, 55.0f);
    agregarRuta(&ciudades[6], &ciudades[13], {{484, 97}}, 24.0f);
    agregarRuta(&ciudades[5], &ciudades[12], {{476, 150}, {456, 156}, {445, 170}, {405, 170}, {350, 220}}, 110.0f);
    agregarRuta(&ciudades[12], &ciudades[4], {{350, 217}, {329, 237}}, 64.0f);
    agregarRuta(&ciudades[0], &ciudades[1], {{605, 377}, {600, 405}, {597, 412}, {615, 434}, {621, 483}}, 139.0f);
    agregarRuta(&ciudades[0], &ciudades[34], {{605, 377}, {600, 405}, {597, 412}, {579, 456}, {566, 465}}, 92.0f);
    agregarRuta(&ciudades[34], &ciudades[21], {{564, 464}, {567, 476}}, 92.0f);
    agregarRuta(&ciudades[21], &ciudades[1], {{579, 484}}, 76.0f);
    agregarRuta(&ciudades[12], &ciudades[15], {{358, 240}, {352, 250}}, 45.0f);
    agregarRuta(&ciudades[15], &ciudades[16], {{372, 263}, {377, 270}}, 51.0f);
    agregarRuta(&ciudades[16], &ciudades[17], {{400, 310}, {405, 320}, {415, 330}}, 96.0f);
    agregarRuta(&ciudades[17], &ciudades[18], {{465, 340}, {470, 345}}, 52.0f);
    agregarRuta(&ciudades[18], &ciudades[19], {{480, 366}, {505, 347}, {527, 345}}, 66.0f);
    agregarRuta(&ciudades[19], &ciudades[3], {}, 24.0f);
    agregarRuta(&ciudades[25], &ciudades[26], {{515, 190}, {530, 173}}, 38.0f);
    agregarRuta(&ciudades[26], &ciudades[27], {{585, 175}, {590, 197}, {595, 196}}, 40.0f);
    agregarRuta(&ciudades[26], &ciudades[23], {{585, 175}, {590, 197}, {587, 220}, {592, 235}, {615, 243}, {605, 273}, {628, 300}}, 52.0f);
    agregarRuta(&ciudades[27], &ciudades[23], {{605, 200}, {590, 197}, {587, 220}, {592, 235}, {615, 243}, {605, 273}, {628, 300}}, 110.0f);
    agregarRuta(&ciudades[8], &ciudades[25], {}, 20.0f);
    agregarRuta(&ciudades[25], &ciudades[11], {{500, 190}, {488, 214}}, 85.0f);
    agregarRuta(&ciudades[0], &ciudades[23], {{609, 355}, {609, 335}, {625, 320}}, 61.0f);
    agregarRuta(&ciudades[23], &ciudades[24], {{640, 310}}, 45.0f);
    agregarRuta(&ciudades[24], &ciudades[29], {{692, 297}, {791, 266}}, 85.0f);
    agregarRuta(&ciudades[29], &ciudades[30], {{827, 250}}, 43.0f);
    agregarRuta(&ciudades[21], &ciudades[34], {{565, 467}}, 18.0f);
    agregarRuta(&ciudades[0], &ciudades[22], {{638, 388}, {655, 382}}, 67.0f);
    agregarRuta(&ciudades[9], &ciudades[31], {{712, 100}, {720, 115}, {745, 135}}, 60.0f);
    agregarRuta(&ciudades[28], &ciudades[24], {{735, 150}, {730, 200}, {705, 218}, {708, 238}, {700, 258}, {715, 288}}, 150.0f);
    agregarRuta(&ciudades[28], &ciudades[29], {{735, 150}, {730, 200}, {705, 218}, {708, 238}, {700, 258}, {715, 288}, {760, 276}}, 120.0f);
    agregarRuta(&ciudades[28], &ciudades[32], {{735, 150}}, 90.0f);
    agregarRuta(&ciudades[31], &ciudades[32], {{748, 135}, {765, 137}}, 30.0f);
    agregarRuta(&ciudades[15], &ciudades[20], {{345, 275}, {335, 280}, {318, 315}, {311, 325}, {300, 315}}, 70.0f);
    agregarRuta(&ciudades[1], &ciudades[22], {{622, 492}, {658, 490}, {668, 480}, {673, 448}, {660, 432}, {670, 420}, {670, 410}}, 196.0f);
    agregarRuta(&ciudades[32], &ciudades[24], {{735, 150}, {730, 200}, {705, 218}, {708, 238}, {700, 258}, {715, 288}}, 130.0f);
    agregarRuta(&ciudades[32], &ciudades[29], {{830, 100}, {840, 107}, {845, 126}, {867, 150}, {830, 206}, {795, 220}, {780, 235}, {780, 253}, {795, 265}}, 160.0f);
    agregarRuta(&ciudades[32], &ciudades[33], {{830, 100}, {833, 90}, {830, 85}}, 50.0f);
    agregarRuta(&ciudades[27], &ciudades[28], {{637, 188}, {634, 183}, {656, 180}, {656, 175}, {645, 173}, {642, 163}, {645, 155}, {665, 160}}, 60.0f);
    agregarRuta(&ciudades[31], &ciudades[29], {{820, 93}, {826, 83}, {830, 85}, {833, 90}, {830, 100}, {840, 107}, {845, 126}, {867, 150}, {830, 206}, {795, 220}, {780, 235}, {780, 253}, {795, 265}}, 230.0f);
    agregarRuta(&ciudades[31], &ciudades[33], {{820, 93}, {826, 83}}, 80.0f);
    agregarRuta(&ciudades[33], &ciudades[29], {{830, 85}, {833, 90}, {830, 100}, {840, 107}, {845, 126}, {867, 150}, {830, 206}, {795, 220}, {780, 235}, {780, 253}, {795, 265}}, 200.0f);
}

Vector2f calcularPosicionCarrito(const vector<Vector2f>& puntos, float progreso) {
    float distanciaTotal = 0.0f;
    for (size_t i = 1; i < puntos.size(); ++i) {
        distanciaTotal += hypot(puntos[i].x - puntos[i - 1].x, puntos[i].y - puntos[i - 1].y);
    }

    float distanciaActual = progreso * distanciaTotal;

    for (size_t i = 1; i < puntos.size(); ++i) {
        float segmentoDistancia = hypot(puntos[i].x - puntos[i - 1].x, puntos[i].y - puntos[i - 1].y);
        if (distanciaActual <= segmentoDistancia) {
            float t = distanciaActual / segmentoDistancia;
            return Vector2f(
                puntos[i - 1].x + t * (puntos[i].x - puntos[i - 1].x),
                puntos[i - 1].y + t * (puntos[i].y - puntos[i - 1].y)
            );
        }
        distanciaActual -= segmentoDistancia;
    }

    return puntos.back();
}

vector<Ciudad*> dijkstra(Ciudad* origen, Ciudad* destino, const vector<Ruta>& rutasDisponibles) {
    unordered_map<Ciudad*, float> distancias;
    unordered_map<Ciudad*, Ciudad*> predecesores;
    for (auto& ciudad : ciudades) {
        distancias[&ciudad] = numeric_limits<float>::infinity();
    }
    distancias[origen] = 0.0f;

    auto comparar = [](pair<Ciudad*, float> a, pair<Ciudad*, float> b) {
        return a.second > b.second;
    };
   //Cola de Prioridad
	Cola<float> cola; 
	cola.insertar(0.0f, origen); 
	
	while (!cola.colaVacia()) {
	    Ciudad* actual = cola.desencolar().ciudad;
	
	    if (actual == destino) break;
	
	    for (auto& ruta : rutasDisponibles) {
	        if (ruta.origen == actual) {
	            float nuevaDistancia = distancias[actual] + ruta.distancia;
	            if (nuevaDistancia < distancias[ruta.destino]) {
	                distancias[ruta.destino] = nuevaDistancia;
	                predecesores[ruta.destino] = actual;
	                cola.insertar(nuevaDistancia, ruta.destino); 
	            }
	        }
	    }
	}

    vector<Ciudad*> ruta;
    for (Ciudad* ciudad = destino; ciudad != nullptr; ciudad = predecesores[ciudad]) {
        ruta.push_back(ciudad);
    }
    reverse(ruta.begin(), ruta.end());

    return ruta;
}

vector<vector<Ciudad*>> encontrarTresRutasMasCortas(Ciudad* origen, Ciudad* destino) {
    vector<vector<Ciudad*>> rutasMasCortas;
    vector<Ruta> rutasTemporales = rutasCompletas;

    for (int i = 0; i < 3; ++i) {
        vector<Ciudad*> ruta = dijkstra(origen, destino, rutasTemporales);
        if (ruta.empty()) break; // No hay mas rutas

        rutasMasCortas.push_back(ruta);

        for (size_t j = 1; j < ruta.size(); ++j) {
            auto it = remove_if(rutasTemporales.begin(), rutasTemporales.end(), [&](const Ruta& r) {
                return r.origen == ruta[j - 1] && r.destino == ruta[j];
            });
            rutasTemporales.erase(it, rutasTemporales.end());
        }
    }

    return rutasMasCortas;
}

vector<Vector2f> obtenerPuntosRuta(const vector<Ciudad*>& ruta) {
    vector<Vector2f> puntos;
    for (size_t i = 0; i < ruta.size(); ++i) {
        puntos.push_back(ruta[i]->posicion);
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

void guardarHistorial(const string& origen, const string& destino, float tiempoEstimado, bool esBus, const string& parada) {
    ofstream archivo("historial.txt", ios::app); 
    if (archivo.is_open()) {
        archivo << "Viaje de " << origen << " a " << destino << endl;
        if (esBus && !parada.empty()) {
            archivo << "Parada: " << parada << endl;
        }
        archivo << "Tiempo estimado: " << static_cast<int>(tiempoEstimado) << " minutos" << endl;
        archivo << "Transporte: " << (esBus ? "Bus" : "Carro") << endl;
        

        archivo << "-------------------------" << endl;
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo de historial." << endl;
    }
}

float calcularTiempoEstimado(const vector<Ciudad*>& rutaCalculada, float velocidadPromedio, bool tieneParada) {
    float distanciaTotal = 0.0f;

    // Sumar las distancias de las rutas 
    for (size_t i = 1; i < rutaCalculada.size(); ++i) {
        Ciudad* origen = rutaCalculada[i - 1];
        Ciudad* destino = rutaCalculada[i];

        for (const auto& ruta : rutasCompletas) {
            if (ruta.origen == origen && ruta.destino == destino) {
                distanciaTotal += ruta.distancia; // Sumar la distancia de la ruta
                break;
            }
        }
    }

    float tiempoEstimado = (distanciaTotal / velocidadPromedio) * 60.0f;

    // Si hay una parada, sumar 30 minutos
    if (tieneParada) {
        tiempoEstimado += 30.0f;
    }

    return tiempoEstimado;
}

void Mapa::run() {
    RenderWindow window(VideoMode(1250, 600), "Mapa de Honduras");

    initializeCities();
    initializeRutas();

    // Imagen de fondo
    Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondo.png")) {
        cerr << "Error al cargar la imagen de fondo." << endl;
        return;
    }
    Sprite fondo(fondoTexture);

    // Textos
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error al cargar la fuente." << endl;
        return;
    }

    Text origenTxt("Origen:", font, 17);
    origenTxt.setPosition(20, 90);
    origenTxt.setFillColor(Color::Black);

    Text destTxt("Destino:", font, 17);
    destTxt.setPosition(20, 180);
    destTxt.setFillColor(Color::Black);

    Text paradaTxt("Parada:", font, 17);
    paradaTxt.setPosition(20, 270);
    paradaTxt.setFillColor(Color::Black);

    Text tiempoEstimadoTxt("", font, 17);
    tiempoEstimadoTxt.setPosition(10, 400);
    tiempoEstimadoTxt.setFillColor(Color::Black);

    RectangleShape origenCampo(Vector2f(200, 40));
    origenCampo.setPosition(20, 115);
    origenCampo.setFillColor(Color::White);

    Text nodoOrigen(" ", font, 17);
    nodoOrigen.setPosition(25, 120);
    nodoOrigen.setFillColor(Color::Black);

    RectangleShape destCampo(Vector2f(200, 40));
    destCampo.setPosition(20, 205);
    destCampo.setFillColor(Color::White);

    Text nodoDestino(" ", font, 17);
    nodoDestino.setPosition(25, 210);
    nodoDestino.setFillColor(Color::Black);

    RectangleShape paradaCampo(Vector2f(200, 40));
    paradaCampo.setPosition(20, 295);
    paradaCampo.setFillColor(Color::White);

    Text nodoParada(" ", font, 17);
    nodoParada.setPosition(25, 300);
    nodoParada.setFillColor(Color::Black);

    Texture refreshT;
    if (!refreshT.loadFromFile("refresh.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }

    Texture carT;
    if (!carT.loadFromFile("car.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }

    Texture busT;
    if (!busT.loadFromFile("bus.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }

    // Botones
    sf::RectangleShape inicio(sf::Vector2f(50, 50));
    inicio.setPosition(25, 25);
    inicio.setFillColor(sf::Color(0,0,0,0));

    Sprite refresh;
    refresh.setTexture(refreshT);
    refresh.setPosition(180, 30);

    Sprite carroButton;
    carroButton.setTexture(carT);
    carroButton.setPosition(25, 350);

    Sprite car;
    car.setTexture(carT);
    car.setOrigin(car.getLocalBounds().width / 2, car.getLocalBounds().height / 2);

    RectangleShape calcularButton(Vector2f(125, 30));
    calcularButton.setPosition(80, 352);
    calcularButton.setFillColor(Color(176, 92, 85));
    Text calcularTxt("Calcular ruta", font, 17);
    calcularTxt.setFillColor(Color::White);
    calcularTxt.setPosition(85, 355);

    Ciudad* selectedOrigin = nullptr;
    Ciudad* selectedDestination = nullptr;
    Ciudad* selectedParada = nullptr;
    vector<Ciudad*> rutaCalculada;
    vector<Vector2f> puntosRuta;
    float tiempoTranscurrido = 0.0f;
    const float duracionViaje = 40.0f;

    vector<vector<Ciudad*>> rutasDisponibles;
    int rutaSeleccionada = -1;
    bool mostrandoMenu = false;
    vector<float> tiemposEstimados;

    bool paradaBus = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                    for (auto& city : ciudades) {
                        if (city.shape.getGlobalBounds().contains(mousePos)) {
                            if (!selectedOrigin) {
                                selectedOrigin = &city;
                                nodoOrigen.setString(city.nombre);
                            } else if (!selectedDestination) {
                                selectedDestination = &city;
                                nodoDestino.setString(city.nombre);

                                rutasDisponibles = encontrarTresRutasMasCortas(selectedOrigin, selectedDestination);
                                tiemposEstimados.clear();

                                for (const auto& ruta : rutasDisponibles) {
                                    float tiempoEstimado = calcularTiempoEstimado(ruta, 40.0f, paradaBus && selectedParada != nullptr);
                                    tiemposEstimados.push_back(tiempoEstimado);
                                }

                                mostrandoMenu = true;
                                rutaSeleccionada = (rutasDisponibles.size() == 1) ? 0 : -1; // Si solo hay una ruta, seleccionarla automáticamente
                            } else if (paradaBus && !selectedParada) {
                                selectedParada = &city;
                                nodoParada.setString(city.nombre);

                                // Recalcular el tiempo estimado con la parada
                                if (selectedOrigin && selectedDestination) {
                                    for (size_t i = 0; i < rutasDisponibles.size(); ++i) {
                                        tiemposEstimados[i] = calcularTiempoEstimado(rutasDisponibles[i], 40.0f, true);
                                    }
                                }
                            }
                            break;
                        }
                    }

                    if (inicio.getGlobalBounds().contains(mousePos)){
                        window.close();
                        Inicio ventana;
                        ventana.run();
                        return;
                    }

                    if (refresh.getGlobalBounds().contains(mousePos)) {
                        selectedOrigin = nullptr;
                        selectedDestination = nullptr;
                        selectedParada = nullptr;
                        rutaCalculada.clear();
                        puntosRuta.clear();
                        nodoOrigen.setString("");
                        nodoDestino.setString("");
                        nodoParada.setString("");
                        mostrandoMenu = false;
                        rutasCompletas.clear();
                        initializeRutas();
                        tiempoEstimadoTxt.setString("");
                    }

                    if (carroButton.getGlobalBounds().contains(mousePos)) {
                        paradaBus = !paradaBus;
                        carroButton.setTexture(paradaBus ? busT : carT);

                        // Limpiar la parada si se desactiva el modo bus
                        if (!paradaBus) {
                            selectedParada = nullptr;
                            nodoParada.setString("");
                        }
                    }

                    if (calcularButton.getGlobalBounds().contains(mousePos)) {
                        if (mostrandoMenu && (rutaSeleccionada != -1 || rutasDisponibles.size() == 1)) {
                            rutaCalculada = rutasDisponibles[(rutasDisponibles.size() == 1) ? 0 : rutaSeleccionada];
                            puntosRuta = obtenerPuntosRuta(rutaCalculada);
                            tiempoTranscurrido = 0.0f;
                            mostrandoMenu = false;

                            float velocidadPromedio = 40.0f; // Velocidad en km/h
                            float tiempoEstimado = calcularTiempoEstimado(rutaCalculada, velocidadPromedio, paradaBus && selectedParada != nullptr);
                            tiempoEstimadoTxt.setString("\nTiempo estimado: " + to_string(static_cast<int>(tiempoEstimado)) + " minutos");

                            // Guardar el historial
                           guardarHistorial(selectedOrigin->nombre, selectedDestination->nombre, tiempoEstimado, paradaBus, selectedParada ? selectedParada->nombre : "");
                        }
                    }
                }
            }

            if (event.type == Event::KeyPressed && mostrandoMenu) {
                if (event.key.code >= Keyboard::Num0 && event.key.code <= Keyboard::Num2) {
                    int seleccion = event.key.code - Keyboard::Num0;
                    if (seleccion < rutasDisponibles.size()) {
                        rutaSeleccionada = seleccion;
                        if (rutaSeleccionada >= 0 && rutaSeleccionada < tiemposEstimados.size()) {
                            tiempoEstimadoTxt.setString("\nTiempo estimado: " + to_string(static_cast<int>(tiemposEstimados[rutaSeleccionada])) + " minutos");
                        }
                    }
                }
            }
        }

        if (!puntosRuta.empty() && tiempoTranscurrido < duracionViaje) {
            tiempoTranscurrido += 0.016f;
            float progreso = tiempoTranscurrido / duracionViaje;
            car.setPosition(calcularPosicionCarrito(puntosRuta, progreso));
        }

        window.clear();
        window.draw(fondo);

        for (auto& city : ciudades) {
		    city.shape.setFillColor(colorCiudades); 
		    window.draw(city.shape);
		}
		
		for (auto& route : rutas) {
		    VertexArray lines(LineStrip, 2 + route.puntosMedios.size());
		    lines[0].position = route.origen->posicion;
		    lines[0].color = colorRutas; 
		
		    for (size_t i = 0; i < route.puntosMedios.size(); ++i) {
		        lines[i + 1].position = route.puntosMedios[i];
		        lines[i + 1].color = colorRutas; 
		    }
		
		    lines[lines.getVertexCount() - 1].position = route.destino->posicion;
		    lines[lines.getVertexCount() - 1].color = colorRutas; 
		
		    window.draw(lines);
		}

        if (mostrandoMenu) {
            for (size_t i = 0; i < rutasDisponibles.size(); ++i) {
                vector<Vector2f> puntos = obtenerPuntosRuta(rutasDisponibles[i]);
                VertexArray lines(LineStrip, puntos.size());
                for (size_t j = 0; j < puntos.size(); ++j) {
                    lines[j].position = puntos[j];
                    lines[j].color = (i == rutaSeleccionada) ? Color::Green : Color::Blue;
                }
                window.draw(lines);
            }
        }

       if (!puntosRuta.empty()) {
    static float distanciaTotal = 0.0f;
    if (distanciaTotal == 0.0f) {
        for (size_t i = 1; i < puntosRuta.size(); ++i) {
            distanciaTotal += hypot(puntosRuta[i].x - puntosRuta[i - 1].x, puntosRuta[i].y - puntosRuta[i - 1].y);
        }
    }

    // Calcular la distancia recorrida por el carrito
    float distanciaRecorrida = (tiempoTranscurrido / duracionViaje) * distanciaTotal;

    // Dibujar la parte ya recorrida en negro
    VertexArray lineaRecorrida(LineStrip, 0);
    float distanciaAcumulada = 0.0f;

    for (size_t i = 1; i < puntosRuta.size(); ++i) {
        float segmentoDistancia = hypot(puntosRuta[i].x - puntosRuta[i - 1].x, puntosRuta[i].y - puntosRuta[i - 1].y);

        if (distanciaAcumulada + segmentoDistancia >= distanciaRecorrida) {
            float t = (distanciaRecorrida - distanciaAcumulada) / segmentoDistancia;
            Vector2f puntoIntermedio = puntosRuta[i - 1] + t * (puntosRuta[i] - puntosRuta[i - 1]);

            lineaRecorrida.append(Vertex(puntosRuta[i - 1], Color::Black));
            lineaRecorrida.append(Vertex(puntoIntermedio, Color::Black));
            break;
        } else {
            lineaRecorrida.append(Vertex(puntosRuta[i - 1], Color::Black));
            lineaRecorrida.append(Vertex(puntosRuta[i], Color::Black));
            distanciaAcumulada += segmentoDistancia;
        }
    }
    window.draw(lineaRecorrida);

    // Dibujar la parte por recorrer en verde
    VertexArray lineaPorRecorrer(LineStrip, 0);
    bool carritoEncontrado = false;

    // Reiniciar la distancia acumulada
    distanciaAcumulada = 0.0f;

    for (size_t i = 1; i < puntosRuta.size(); ++i) {
        float segmentoDistancia = hypot(puntosRuta[i].x - puntosRuta[i - 1].x, puntosRuta[i].y - puntosRuta[i - 1].y);

        if (!carritoEncontrado && distanciaAcumulada + segmentoDistancia >= distanciaRecorrida) {
            float t = (distanciaRecorrida - distanciaAcumulada) / segmentoDistancia;
            Vector2f puntoIntermedio = puntosRuta[i - 1] + t * (puntosRuta[i] - puntosRuta[i - 1]);

            lineaPorRecorrer.append(Vertex(puntoIntermedio, Color::Green));
            lineaPorRecorrer.append(Vertex(puntosRuta[i], Color::Green));
            carritoEncontrado = true;
        } else if (carritoEncontrado) {
            lineaPorRecorrer.append(Vertex(puntosRuta[i - 1], Color::Green));
            lineaPorRecorrer.append(Vertex(puntosRuta[i], Color::Green));
        }
        distanciaAcumulada += segmentoDistancia;
    }
    window.draw(lineaPorRecorrer);

    // Dibujar el carrito
    Vector2f posicionCarrito = calcularPosicionCarrito(puntosRuta, tiempoTranscurrido / duracionViaje);
    car.setPosition(posicionCarrito);
    window.draw(car);            
}

        window.draw(refresh);
        window.draw(inicio);
        window.draw(carroButton);
        window.draw(calcularButton);
        window.draw(calcularTxt);
        window.draw(destTxt);
        window.draw(origenTxt);
        window.draw(origenCampo);
        window.draw(destCampo);
        window.draw(nodoOrigen);
        window.draw(nodoDestino);

        if (paradaBus) {
            window.draw(paradaTxt);
            window.draw(paradaCampo);
            window.draw(nodoParada);
        }

        window.draw(tiempoEstimadoTxt);

        if (mostrandoMenu) {
            string textoMenu = (rutasDisponibles.size() == 1) ? "Ruta disponible: 0" : "Seleccione una ruta (0-" + to_string(rutasDisponibles.size() - 1) + "):";
            Text menuTxt(textoMenu, font, 20);
            menuTxt.setPosition(10, 380);
            menuTxt.setFillColor(Color::Black);
            window.draw(menuTxt);
        }

        window.display();
    }
}
