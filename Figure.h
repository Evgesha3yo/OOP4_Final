#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Figure {
protected:
	int _x;
	int _y;
	sf::Color color;
	int _radius;
	sf::Color outlineColor;

	int _xOld;
	int _yOld;
	sf::Color colorOld;
	int _radiusOld;
	sf::Color outlineColorOld;

	bool isSelected;
	bool isHidden = false;

	sf::CircleShape* shape;

public:
	Figure(int move_x, int move_y, int radius) {
		this->_x = move_x;
		this->_y = move_y;
		this->color = sf::Color::Magenta;
		this->_radius = radius;
		this->outlineColor = sf::Color::White;

		this->_xOld = _x;
		this->_yOld = _y;
		this->colorOld = color;
		this->_radiusOld = _radius;
		this->outlineColorOld = sf::Color::White;
	}

	Figure() {
		this->_x = 0;
		this->_y = 0;
		this->color = sf::Color::Magenta;
		this->_radius = 150;
		this->outlineColor = sf::Color::White;

		this->_xOld = 0;
		this->_yOld = 0;
		this->colorOld = sf::Color::Magenta;
		this->_radiusOld = 150;
		this->outlineColorOld = sf::Color::White;
	}

	sf::CircleShape* GetShape() {
		return shape;
	}

	void Set_xAnd_y(int x, int y) {
		_x = x;
		_y = y;
	}

	sf::Color GetOldColor() {
		return colorOld;
	}

	virtual void SetColor(sf::Color color) {
		this->color = color;
	}

	virtual void SetOuter(sf::Color color) {
		this->outlineColor = color;
	}

	virtual sf::Color GetColor() {
		return this->color;
	}

	virtual sf::Color GetOuter() {
		return this->outlineColor;
	}

	virtual int GetOldRadius() {
		return _radiusOld;
	}

	virtual int GetRadius() {
		return this->_radius;
	}

	virtual void SetRadius(int r) {
		_radius = r;
	}

	virtual int Get_xOld() {
		return _xOld;
	}

	virtual int Get_yOld() {
		return _yOld;
	}

	virtual int Get_X() {
		return _x;
	}

	virtual int Get_Y() {
		return _y;
	}

	virtual void Hide() {
		isHidden = true;
	}

	virtual void ShowHidden() {
		isHidden = false;
	}

	virtual bool IsHidden() {
		return isHidden;
	}

	virtual void AddBorder(sf::RenderWindow* window) {

	}

	virtual void DeleteBorder(sf::RenderWindow* window) {

	}

	virtual void Draw(sf::RenderWindow* window) {

	}

	virtual void DrawOld(sf::RenderWindow* window) {
		_x = _xOld;
		_y = _yOld;
		color = colorOld;
		_radius = _radiusOld;
		outlineColor = outlineColorOld;
	}

	virtual void Remove(sf::RenderWindow* window) {

	}

	virtual void Move(int x, int y) {

	}

	virtual void MakeBigger() {
		_radius += 5;
	}

	virtual void MakeSmaller() {
		_radius -= 5;
	}

	virtual sf::Vector2f GetPosition() {
		return shape->getPosition();
	}

	virtual sf::FloatRect GetBounds() {
		return sf::FloatRect();
	}

	virtual Figure* Clone() {
		return nullptr;
	}
};