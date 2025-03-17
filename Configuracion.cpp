#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include "Configuracion.h"
#include "Inicio.h"
using namespace sf;
using namespace std;

void clearFile(const std::string& filename) {
    std::ofstream ofs(filename, std::ofstream::trunc);
    ofs.close();
}

std::string loadFileContent(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Configuracion::run(){
	RenderWindow window(sf::VideoMode(400, 500), "Configuracion");
	
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error al cargar la fuente." << endl;
        return;
    }
    
    // imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("fondoConfig.png")) {
        cerr << "Error al cargar la imagen de fondo." << std::endl;
        return;
    }
    sf::Sprite fondo(fondoTexture);
    
    std::vector<std::string> imagePaths = {
        "C:/Users/compu/Pictures/archivos/Sand monster.jpg",
        "C:/Users/compu/Pictures/archivos/Cool cow.jpg",
        "C:/Users/compu/Pictures/archivos/A.jpg"
    };

    if (imagePaths.empty()) {
        std::cerr << "No se encontraron imágenes en la carpeta especificada." << std::endl;
        return ;
    }

    size_t currentImageIndex = 0;
    sf::Texture texture;
    sf::Sprite sprite;

    // Cargar la primera imagen
    if (!texture.loadFromFile(imagePaths[currentImageIndex])) {
        std::cerr << "Error al cargar la imagen: " << imagePaths[currentImageIndex] << std::endl;
        return ;
    }
    sprite.setTexture(texture);
    sprite.setPosition(100,100);
	 
	//boton de inicio
    sf::Texture logoT;
    if (!logoT.loadFromFile("logoSR.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }
    sf::Sprite logo;
    logo.setTexture(logoT);
    logo.setPosition(10, 10);	
	
	//boton de Manual
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
    
    //boton de configuraciones
	Text configTxt("Configuraciones", font, 20);
    configTxt.setPosition(200, 50);
    configTxt.setFillColor(Color::Black);
    sf::Texture configT;
    if (!configT.loadFromFile("config.png")) {
        cerr << "Error al cargar la imagen\n";
        return;
    }
    sf::Sprite config;
    config.setTexture(configT);
    config.setPosition(200, 10);
	
	 //boton de historial
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
	
	//Historial
    std::string fileContent = loadFileContent("historial.txt");
    sf::Text text(fileContent, font, 12);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10, 70);
    sf::RectangleShape button(sf::Vector2f(105, 30));
    button.setFillColor(sf::Color::Red);
    button.setPosition(290, 70);
    sf::Text buttonText("Eliminar historial", font, 13);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(295, 75);

	bool mostrarHistorial = false;
	bool mostrarManual = false;
	while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					//sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (logo.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                       	window.close();
                       	Inicio ventana;
                       	ventana.run();
                        return;
                    }
                    if (history.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
						mostrarHistorial = !mostrarHistorial;
					}
					 if (manual.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
						mostrarManual = !mostrarManual;
					}
                  	
					  if (button.getGlobalBounds().contains(mousePos)) {
                        clearFile("historial.txt");
                        fileContent = loadFileContent("historial.txt"); // Actualizar el contenido
                        text.setString(fileContent);
                    }  
                }
            }
        }
        
        // Cambiar la imagen cada 3 segundos
        std::this_thread::sleep_for(std::chrono::seconds(3));
        currentImageIndex = (currentImageIndex + 1) % imagePaths.size();

        // Cargar la nueva imagen
        if (!texture.loadFromFile(imagePaths[currentImageIndex])) {
            std::cerr << "Error al cargar la imagen: " << imagePaths[currentImageIndex] << std::endl;
            return ;
        }
        sprite.setTexture(texture);

        window.clear();
        window.draw(fondo);
        window.draw(logo);
        window.draw(config);
        window.draw(manual);
        window.draw(history);
        if (mostrarHistorial){
        	window.draw(text);
        	window.draw(button);
        	window.draw(buttonText);
		}
		if(mostrarManual){
			window.draw(sprite);
		}
        //window.draw(usoTxt);
        window.display();
    }
}


