#ifndef SFML_ENGINE_GAMEBOARD_H
#define SFML_ENGINE_GAMEBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "EventManager.h"

unsigned int calculateCenterPadding(unsigned int areaWidth, int numElements, int elementWidth, int elementPadding);

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

class GameBoard : public DrawableEntity {
public:
    GameBoard(sf::RenderWindow &w, sf::Vector2i dims) : boardDims(dims), window(w)
    {
        auto windowSize = window.getSize();
        unsigned int leftPadding = calculateCenterPadding(windowSize.x, dims.y, 100, 50);
        unsigned int topPadding = calculateCenterPadding(windowSize.y, dims.x, 100, 50);

        for (int i = 0; i < dims.x; i++) {
            std::vector<SymbolSquare *> row;

            for (int j = 0; j < dims.y; j++) {
                auto s = new SymbolSquare(w, {static_cast<float>((j * 150) + leftPadding),
                                              static_cast<float>((i * 150) + topPadding)});
                row.push_back(s);
            }

            boardSquares.push_back(row);
        }
    }

    void draw() override;

    bool isPointInside(sf::Vector2f point) override;

private:
    sf::RenderWindow &window;
    std::vector<std::vector<SymbolSquare *>> boardSquares;
    sf::Vector2i boardDims;
};

#endif //SFML_ENGINE_GAMEBOARD_H
