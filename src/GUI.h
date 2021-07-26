#ifndef SFML_ENGINE_GUI_H
#define SFML_ENGINE_GUI_H

#include "EventManager.h"
#include <SFML/Graphics.hpp>
#include <utility>

class Button : public DrawableEntity {
public:
    Button(sf::RenderWindow &w, sf::Vector2f size, sf::Vector2i pos) : window(w), shape(sf::RectangleShape({size}))
    {
        shape.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
    };

    bool isPointInside(sf::Vector2f point) override;

protected:
    sf::RectangleShape shape;
    sf::RenderWindow &window;
};

class MenuButton : public Button {
public:
    MenuButton(sf::RenderWindow &w, sf::Vector2i pos, std::string t) : Button(w, {200, 70}, pos)
    {
        font.loadFromFile("../res/MenuButtonFont.ttf");
        text.setFont(font);
        text.setPosition(pos.x, pos.y);
        text.setString(t);
        text.setFillColor(sf::Color::Black);
    };

    void draw() override;

    void onMouseUp() override;

    void onMouseDown() override;

    void onMouseEnter() override;

    void onMouseLeave() override;

private:
    sf::Text text;
    sf::Font font;
};

#endif //SFML_ENGINE_GUI_H
