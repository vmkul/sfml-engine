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
    for (auto &row: boardSquares) {
        for (auto &square: row) {
            square->draw();
        }
    }

    for (auto &row: pathVertices) {
        for (auto &vertex: row) {
            vertex->draw();
        }
    }
}

bool GameBoard::isPointInside(sf::Vector2f point)
{
    return false;
}

void GameBoard::initSquares()
{
    auto windowSize = window.getSize();
    unsigned int leftPadding = calculateCenterPadding(windowSize.x, boardDims.y, 100, 50);
    unsigned int topPadding = calculateCenterPadding(windowSize.y, boardDims.x, 100, 50);

    for (int i = 0; i < boardDims.x; i++) {
        std::vector<SymbolSquare *> row;

        for (int j = 0; j < boardDims.y; j++) {
            auto s = new SymbolSquare(window, {static_cast<float>((j * 150) + leftPadding),
                                               static_cast<float>((i * 150) + topPadding)});
            row.push_back(s);
        }

        boardSquares.push_back(row);
    }
}

void GameBoard::initVertices()
{
    auto windowSize = window.getSize();
    unsigned int leftPadding = calculateCenterPadding(windowSize.x, boardDims.y, 100, 50);
    unsigned int topPadding = calculateCenterPadding(windowSize.y, boardDims.x, 100, 50);

    for (int i = 0; i < boardDims.x + 1; i++) {
        std::vector<PathVertex *> row;

        for (int j = 0; j < boardDims.y + 1; j++) {
            auto v = new PathVertex(window, {static_cast<float>((j * 150) + leftPadding - 36),
                                             static_cast<float>((i * 150) + topPadding - 36)}, this);
            eventManager->registerEntity(*v);
            row.push_back(v);
        }

        pathVertices.push_back(row);
    }
}

void GameBoard::handleVertexClick(PathVertex *vertex)
{
    if (vertex->isConnected()) return;
    auto vertexCoordinates = getVertexCoordinates(vertex);
    auto head = pathVertices[headVertex.x][headVertex.y];

    if (headVertex.x == vertexCoordinates.x) {
        if (headVertex.y == (vertexCoordinates.y - 1)) {
            head->connect(RIGHT);
            headVertex = {vertexCoordinates.x, vertexCoordinates.y};
            return;
        }
        if (headVertex.y == (vertexCoordinates.y + 1)) {
            head->connect(LEFT);
            headVertex = {vertexCoordinates.x, vertexCoordinates.y};
            return;
        }
    }

    if (headVertex.y == vertexCoordinates.y) {
        if (headVertex.x == (vertexCoordinates.x - 1)) {
            head->connect(DOWN);
            headVertex = {vertexCoordinates.x, vertexCoordinates.y};
            return;
        }
        if (headVertex.x == (vertexCoordinates.x + 1)) {
            head->connect(UP);
            headVertex = {vertexCoordinates.x, vertexCoordinates.y};
            return;
        }
    }
}

sf::Vector2i GameBoard::getVertexCoordinates(PathVertex *vertex)
{
    for (int i = 0; i < pathVertices.size(); i++) {
        for (int j = 0; j < pathVertices[0].size(); j++) {
            if (pathVertices[i][j] == vertex) return sf::Vector2i({i, j});
        }
    }
    return sf::Vector2i({});
}

void PathVertex::draw()
{
    window.draw(shape);
    if (connected) window.draw(connectionLine);
}

bool PathVertex::isPointInside(sf::Vector2f point)
{
    return isPointInPolygon(point, shape);
}

void PathVertex::connect(enum Direction direction)
{
    if (connected) return;
    auto pos = shape.getPosition();

    connectionLine = sf::RectangleShape({150, 5});
    connectionLine.setFillColor(sf::Color::Blue);
    connectionLine.setPosition({static_cast<float>(pos.x + 11), static_cast<float>(pos.y + 11)});

    if (direction == Direction::UP) {
        connectionLine.rotate(-90);
    } else if (direction == Direction::DOWN) {
        connectionLine.rotate(90);
    } else if (direction == Direction::LEFT) {
        connectionLine.rotate(180);
    }

    connected = true;
}

bool PathVertex::isConnected()
{
    return connected;
}

void PathVertex::onMouseUp()
{
    gameBoard->handleVertexClick(this);
}
