#include "Mapa.h"
#include <iostream>
using namespace std;


void run();

int main() {
    Mapa ventana;
    ventana.run();
	//run();
    return 0;
}

void run(){
	sf::RenderWindow window(sf::VideoMode(400, 400), "Bienvenido!");
	
     // imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondo1.png")) {
        cerr << "Error al cargar la imagen de fondo." << std::endl;
        return;
    }
    sf::Sprite fondo(fondoTexture);
        
     // Crear botón invisible
    sf::RectangleShape boton(sf::Vector2f(100, 50));
    boton.setPosition(150, 300); 
    boton.setFillColor(sf::Color(0, 0, 0, 0)); 
    boton.setOutlineColor(sf::Color::Blue);
        
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
                        cout << "Boton!" << std::endl;
                        return;
                    }
                }
            }
        }

        window.clear();
        window.draw(fondo);
        window.draw(boton);
        window.display();
    }
}
