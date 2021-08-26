#include "EventManager.h"

bool isPointInPolygon(sf::Vector2<float> point, const sf::RectangleShape &shape)
{
    const float xPos = shape.getPosition().x;
    const float yPos = shape.getPosition().y;

    const float x1 = shape.getPoint(0).x + xPos;
    const float x2 = shape.getPoint(1).x + xPos;

    const float y1 = shape.getPoint(0).y + yPos;
    const float y2 = shape.getPoint(2).y + yPos;

    if (point.x >= x1 && point.x <= x2 && point.y >= y1 && point.y <= y2)
        return true;

    return false;
}

void EventManager::registerEntity(DrawableEntity &entity)
{
    entities.push_back(&entity);
}

void EventManager::reportEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        handleMouseDown(event);
    } else if (event.type == sf::Event::MouseButtonReleased) {
        handleMouseUp();
    } else if (event.type == sf::Event::MouseMoved) {
        handleMouseMoved(event);
    }
}

void EventManager::handleMouseUp()
{
    if (lastClickedEntityIndex >= 0)
        entities[lastClickedEntityIndex]->onMouseUp();
    lastClickedEntityIndex = -1;
}

void EventManager::handleMouseDown(const sf::Event &event)
{
    for (int i = 0; i < entities.size(); i++) {
        auto &entity = entities[i];
        if (entity->isPointInside({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)})) {
            entity->onMouseDown();
            lastClickedEntityIndex = i;
        }
    }
}

void EventManager::handleMouseMoved(const sf::Event &event)
{
    for (auto &entity: entities) {
        if (entity->isPointInside({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)})) {
            if (lastHoveredEntity && lastHoveredEntity != entity) {
                lastHoveredEntity->onMouseLeave();
            }
            entity->onMouseEnter();
            lastHoveredEntity = entity;
            return;
        }
    }

    if (lastHoveredEntity) {
        lastHoveredEntity->onMouseLeave();
        lastHoveredEntity = nullptr;
    }
}

void EventManager::drawEntities()
{
    for (auto &entity: entities) {
        entity->draw();
    }
}
