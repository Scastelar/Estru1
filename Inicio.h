#ifndef INICIO_H
#define INICIO_H

#include <iostream>
#include "Configuracion.h"
#include "Mapa.h"

class Inicio {
	public:
	void run(){
	sf::RenderWindow window(sf::VideoMode(400, 400), "Bienvenido!");
	
     // imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondo1.png")) {
        return;
    }
    sf::Sprite fondo(fondoTexture);
        
    //boton de inicio
    sf::RectangleShape boton(sf::Vector2f(100, 50));
    boton.setPosition(150, 300); 
    boton.setFillColor(sf::Color(0, 0, 0, 0)); 
    boton.setOutlineColor(sf::Color::Blue);
    
    //boton configuracion
    sf::Texture t;
    if (!t.loadFromFile("car.png")) {
        return;
    }
    sf::Sprite config;
    config.setTexture(t);
    config.setPosition(10, 10);
        
        while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (boton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        window.close();
                        Mapa ventana;
                        ventana.run();
                        return;
                    }
                    
                    if (config.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                    	window.close();
                        Configuracion ventana;
                        ventana.run();
                        return;
					}
                }
            }
        }

        window.clear();
        window.draw(fondo);
        window.draw(config);
        window.draw(boton);
        window.display();
    }
}	
		
};

#endif
