#ifndef SFML_ENGINE_GAMEBOARD_H
#define SFML_ENGINE_GAMEBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "EventManager.h"

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

unsigned int calculateCenterPadding(unsigned int areaWidth, int numElements, int elementWidth, int elementPadding);

class GameBoard;

class SymbolSquare : public DrawableEntity {
public:
    SymbolSquare(sf::RenderWindow &w, sf::Vector2f pos) : shape({100, 100}), window(w)
    {
        shape.setFillColor(sf::Color::White);
        shape.setPosition(pos.x, pos.y);
    }

    void draw() override;

    bool isPointInside(sf::Vector2f point) override;

private:
    sf::RenderWindow &window;
    sf::RectangleShape shape;
};

class PathVertex : public DrawableEntity {
public:
    explicit PathVertex(sf::RenderWindow &w, sf::Vector2f pos, GameBoard *gb) : shape(15.), window(w), gameBoard(gb)
    {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(pos.x, pos.y);
    }

    void draw() override;

    void onMouseUp() override;

    bool isPointInside(sf::Vector2f point) override;

    void connect(enum Direction direction);

    bool isConnected();

private:
    bool connected = false;
    GameBoard *gameBoard;
    sf::RenderWindow &window;
    sf::CircleShape shape;
    sf::RectangleShape connectionLine;
};

class GameBoard : public DrawableEntity {
public:
    GameBoard(sf::RenderWindow &w, sf::Vector2i dims, EventManager *em) : boardDims(dims), window(w), eventManager(em)
    {
        initSquares();
        initVertices();
    }

    void initSquares();

    void initVertices();

    void draw() override;

    bool isPointInside(sf::Vector2f point) override;

    sf::Vector2i getVertexCoordinates(PathVertex *vertex);

    void handleVertexClick(PathVertex *vertex);

private:
    EventManager *eventManager;
    sf::RenderWindow &window;
    std::vector<std::vector<SymbolSquare *>> boardSquares;
    std::vector<std::vector<PathVertex *>> pathVertices;
    sf::Vector2i boardDims;
    sf::Vector2i headVertex = {0, 0};
};

#endif //SFML_ENGINE_GAMEBOARD_H
