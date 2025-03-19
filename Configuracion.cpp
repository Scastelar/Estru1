#include "Configuracion.h"
#include "Inicio.h"
#include "Manual.h"
#include "Historial.h"
#include "Colores.h"

using namespace sf;
using namespace std;

void Configuracion::run() {
    RenderWindow window(sf::VideoMode(400, 500), "Configuracion");

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error al cargar la fuente." << endl;
        return;
    }

    // Imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondoConfig.png")) {
        cerr << "Error al cargar la imagen de fondo." << std::endl;
        return;
    }
    sf::Sprite fondo(fondoTexture);

    // Botón de inicio
    sf::Texture logoT;
    if (!logoT.loadFromFile("logoSR.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }
    sf::Sprite logo;
    logo.setTexture(logoT);
    logo.setPosition(10, 10);

    // Botón de configuraciones
    sf::Texture configT;
    if (!configT.loadFromFile("config.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }
    sf::Sprite config;
    config.setTexture(configT);
    config.setPosition(200, 10);
    
    // Botón de Manual
    Text usoTxt("Manual de Uso", font, 20);
    usoTxt.setPosition(100, 50);
    usoTxt.setFillColor(Color::Black);
    sf::Texture manualT;
    if (!manualT.loadFromFile("manual.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }
    sf::Sprite manual;
    manual.setTexture(manualT);
    manual.setPosition(100, 10);
    
    // Botón de historial
    Text historyTxt("Historial", font, 20);
    historyTxt.setPosition(200, 50);
    historyTxt.setFillColor(Color::Black);
    sf::Texture historyT;
    if (!historyT.loadFromFile("history.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }
    sf::Sprite history;
    history.setTexture(historyT);
    history.setPosition(300, 10);    

    sf::Text opcionesRutas("Priorizar rutas cortas", font, 14);
    opcionesRutas.setPosition(50, 80);
    opcionesRutas.setFillColor(Color::Black);

    sf::Text ajustesTrafic("Simular condiciones de tráfico", font, 14);
    ajustesTrafic.setPosition(50, 120);
    ajustesTrafic.setFillColor(Color::Black);

    sf::RectangleShape botonRutas(sf::Vector2f(20, 20));
    botonRutas.setPosition(10, 80);
    botonRutas.setFillColor(Color::Red); 

    sf::RectangleShape botonTrafic(sf::Vector2f(20, 20));
    botonTrafic.setPosition(10, 120);
    botonTrafic.setFillColor(Color::Red);
    
    sf::Text colorRutas("Color de Rutas: ", font, 14);
    colorRutas.setPosition(10, 160);
    colorRutas.setFillColor(Color::Black);
    
    sf::RectangleShape botonColorRutas(sf::Vector2f(20, 20));
    botonColorRutas.setPosition(130, 160);
    botonColorRutas.setFillColor(Color::Red);

    sf::Text colorNodos("Color de Nodos:", font, 14);
    colorNodos.setPosition(10, 200);
    colorNodos.setFillColor(Color::Black);
    
    sf::RectangleShape botonColorNodos(sf::Vector2f(20, 20));
    botonColorNodos.setPosition(130, 200);
    botonColorNodos.setFillColor(Color::Green);

    // Colores para los botones de color
    Color coloresRutas[3] = { Color::Red, Color::Blue, Color::Yellow };
    Color coloresNodos[3] = { Color::Green, Color::Cyan, Color::Magenta };
    int indexColorRutas = 0;
    int indexColorNodos = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    if (logo.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        window.close();
                        Inicio ventana;
                        ventana.run();
                        return;
                    }
                    if (history.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        window.close();
                        Historial ventana;
                        ventana.run();
                        return;
                    }
                    if (manual.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        window.close();
                        Manual ventana;
                        ventana.run();
                        return;
                    } 
                    if (botonRutas.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        botonRutas.setFillColor(botonRutas.getFillColor() == Color::Red ? Color::Green : Color::Red);
                    }
                    if (botonTrafic.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        botonTrafic.setFillColor(botonTrafic.getFillColor() == Color::Red ? Color::Green : Color::Red);
                    }
                   if (botonColorRutas.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					    indexColorRutas = (indexColorRutas + 1) % 2;
					    botonColorRutas.setFillColor(coloresRutas[indexColorRutas]);
					    setColorRutas(coloresRutas[indexColorRutas]); 
					}
					if (botonColorNodos.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					    indexColorNodos = (indexColorNodos + 1) % 4;
					    botonColorNodos.setFillColor(coloresNodos[indexColorNodos]);
					    setColorCiudades(coloresNodos[indexColorNodos]); 
					}
                }
            }
        }

        window.clear();
        window.draw(fondo);
        window.draw(logo);
        window.draw(config);
        window.draw(manual);
        window.draw(history);
        window.draw(colorRutas);
        window.draw(opcionesRutas);
        window.draw(ajustesTrafic);
        window.draw(botonRutas);
        window.draw(botonTrafic);
        window.draw(colorRutas);
        window.draw(colorNodos);
        window.draw(botonColorRutas);
        window.draw(botonColorNodos);
        window.display();
    }
}
