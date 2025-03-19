#include "Configuracion.h"
#include "Inicio.h"
#include "Manual.h"
#include "Historial.h"

using namespace sf;
using namespace std;

void eliminarTexto(const std::string& archivo) {
    std::ofstream ofs(archivo, std::ofstream::trunc);
    ofs.close();
}

std::string cargarArchivo(const std::string& archivo) {
    std::ifstream file(archivo);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Historial::run() {
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


	//Historial
	string archivo = cargarArchivo("historial.txt");
	Text text(archivo, font, 12);
	text.setFillColor(sf::Color::Black);
	text.setPosition(10, 70);
	RectangleShape button(sf::Vector2f(105, 30));
	button.setFillColor(sf::Color::Red);
	button.setPosition(290, 70);
	Text buttonText("Eliminar historial", font, 13);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(295, 75);

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
                    if (config.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
						window.close();
                        Configuracion ventana;
                        ventana.run();
                        return;
					}
					if (button.getGlobalBounds().contains(mousePos)) {
                    eliminarTexto("historial.txt");
                    archivo = cargarArchivo("historial.txt"); // Actualizar el contenido
                    text.setString(archivo);
                }  
					 if (manual.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
						window.close();
                        Manual ventana;
                        ventana.run();
                        return;
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
    	window.draw(text);
    	window.draw(button);
    	window.draw(buttonText);
	    window.display();
	}
}
