#include "GUI.h"

void MenuButton::draw()
{
    window.draw(shape);
    window.draw(text);
}

void MenuButton::onMouseDown()
{
    shape.setFillColor(sf::Color::Magenta);
}

void MenuButton::onMouseUp()
{
    shape.setFillColor(sf::Color::White);
}

void MenuButton::onMouseEnter()
{
    text.setFillColor(sf::Color::Yellow);
}

void MenuButton::onMouseLeave()
{
    text.setFillColor(sf::Color::Black);
}

bool Button::isPointInside(sf::Vector2f point)
{
    return isPointInPolygon(point, shape);
}
