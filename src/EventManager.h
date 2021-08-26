#ifndef SFML_ENGINE_EVENTMANAGER_H
#define SFML_ENGINE_EVENTMANAGER_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

bool isPointInPolygon(sf::Vector2<float> point, const sf::RectangleShape &shape);

bool isPointInPolygon(sf::Vector2<float> point, const sf::CircleShape &shape);

class DrawableEntity {
public:
    virtual void draw() = 0;

    virtual bool isPointInside(sf::Vector2f point) = 0;

    virtual void onMouseDown()
    {};

    virtual void onMouseUp()
    {};

    virtual void onMouseEnter()
    {};

    virtual void onMouseLeave()
    {};
};

class EventManager {
public:
    void registerEntity(DrawableEntity &entity);

    void reportEvent(const sf::Event &event);

    void drawEntities();

private:
    void handleMouseUp();

    void handleMouseDown(const sf::Event &event);

    void handleMouseMoved(const sf::Event &event);

    std::vector<DrawableEntity *> entities;
    DrawableEntity *lastHoveredEntity = nullptr;
    int lastClickedEntityIndex = -1;
};

#endif //SFML_ENGINE_EVENTMANAGER_H
