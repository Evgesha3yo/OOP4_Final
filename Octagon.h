#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include "GLOBAL_DATA.h"

class Octagon : public Figure {
private:
    bool isRemoved;

public:
    Octagon(int r, int posX, int posY) {
        shape = new sf::CircleShape(_radius, 8);
        _radius = r;
        _x = posX;
        _y = posY;

        _xOld = posX;
        _yOld = posY;
        colorOld = sf::Color::Magenta;
        _radiusOld = r;
    }

    void SetRadius(int r) {
        _radius = r;
    }
    
    void Draw(sf::RenderWindow* window) override {
        if (isHidden == true || isRemoved == true) {
            return;
        } else {
            shape->setFillColor(color);
            shape->setOutlineColor(outlineColor);
            shape->setPosition(_x, _y);
            shape->setRadius(_radius);
            window->draw(*shape);
        }
    }

    void AddBorder(sf::RenderWindow* window) override {
        shape->setOutlineThickness(BOLD_OUTLINE_THICKNESS);
    }

    void DeleteBorder(sf::RenderWindow* window) override {
        shape->setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);
    }

    void Remove(sf::RenderWindow* window) override {
        isRemoved = true;
    }

    void Move(int xMove, int yMove) {
        _x += xMove;
        _y += yMove;
    }

    sf::FloatRect GetBounds() override {
        return shape->getGlobalBounds();
    }
};