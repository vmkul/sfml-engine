#include "GameBoard.h"

unsigned int calculateCenterPadding(unsigned int areaWidth, int numElements, int elementWidth, int elementPadding)
{
    unsigned int boardWidth = numElements * elementWidth + (elementPadding * (numElements - 1));
    unsigned int padding = (areaWidth - boardWidth) / 2;
    return padding;
}

void SymbolSquare::draw()
{
    window.draw(shape);
}

bool SymbolSquare::isPointInside(sf::Vector2f point)
{
    return false;
}

void GameBoard::draw()
{
    for (auto& row : boardSquares) {
        for (auto& square : row) {
            square->draw();
        }
    }
}

bool GameBoard::isPointInside(sf::Vector2f point)
{
    return false;
}
