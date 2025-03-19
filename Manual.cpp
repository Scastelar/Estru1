#include "Inicio.h"
#include "Configuracion.h"
#include "Historial.h"
#include "Manual.h"

using namespace sf;
using namespace std;



void Manual::run() {
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

    // Cargar imágenes
    std::vector<std::string> imagePaths = {
        "C:/Users/compu/Pictures/archivos/Sand monster.jpg",
        "C:/Users/compu/Pictures/archivos/Cool cow.jpg",
        "C:/Users/compu/Pictures/archivos/A.jpg"
    };

    if (imagePaths.empty()) {
        std::cerr << "No se encontraron imágenes en la carpeta especificada." << std::endl;
        return;
    }

    size_t currentImageIndex = 0;
    sf::Texture texture;
    sf::Sprite sprite;

    // Cargar la primera imagen
    if (!texture.loadFromFile(imagePaths[currentImageIndex])) {
        std::cerr << "Error al cargar la imagen: " << imagePaths[currentImageIndex] << std::endl;
        return;
    }
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);

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
	                    // Mostrar/ocultar componentes de configuración
	                    if (config.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
	                         window.close();
                        Configuracion ventana;
                        ventana.run();
                        return;
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
            return;
        }
        sprite.setTexture(texture);

       window.clear();
	    window.draw(fondo);
	    window.draw(logo);
	    window.draw(config);
	    window.draw(manual);
	    window.draw(history);
	    window.draw(sprite);
	    window.display();
	}
}
