#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "GUI.h"
#include "GameBoard.h"

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
    auto eventManager = new EventManager();

    GameBoard gb(window, {3, 3}, eventManager);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            eventManager->reportEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        gb.draw();
        window.display();
    }

    return 0;
}
