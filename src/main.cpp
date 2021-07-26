#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "GUI.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML!");
    window.setFramerateLimit(60);

    MenuButton menuButtons[]{
            MenuButton{window, {500, 100}, "Button1"},
            MenuButton{window, {500, 200}, "Button2"},
            MenuButton{window, {500, 300}, "Button3"},
            MenuButton{window, {500, 400}, "Button4"},
    };
    EventManager eventManager;

    for (auto &b : menuButtons) {
        eventManager.registerEntity(b);
    }

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            eventManager.reportEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        eventManager.drawEntities();
        window.display();
    }

    return 0;
}
