#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "GLOBAL_DATA.h"
#include "windows.h"
#include <iostream>
#include <vector>

class Composite : public Figure {
private:
	std::vector<Figure*> asset;
	bool withCollision = false;

public:
	Composite() {

	}

	Composite(Figure* const& figure) {
		asset.push_back(figure);
	}

	void AddShape(Composite* comp) {
		for (int i = 0; i < comp->asset.size(); i++) {
			asset.push_back(comp->asset[i]);
			comp->asset[i]->SetColor(color);
		}
	}

	void Hide() override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->Hide();
		}
		isHidden = true;
	}

	void ShowHidden() override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->ShowHidden();
		}
		isHidden = false;
	}

	bool IsHidden() override {
		return isHidden;
	}

	void AddBorder(sf::RenderWindow* window) override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->GetShape()->setOutlineThickness(BOLD_OUTLINE_THICKNESS);
		}
	}

	void DeleteBorder(sf::RenderWindow* window) override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->GetShape()->setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);
		}
	}

	void Draw(sf::RenderWindow* window) override {
		if (isHidden) {
			return;
		}

		for (int i = 0; i < asset.size(); i++) {
			asset[i]->Draw(window);
		}
	}

	void DrawOld(sf::RenderWindow* window) override {
		if (isHidden == true) {
			return;
		}
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->DrawOld(window);
		}
	}

	void Remove(sf::RenderWindow* window) override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->Remove(window);
		}
	}

	void Move(int x, int y) override {
		for (int i = 0; i < asset.size(); i++) {
			if ((asset[i]->Get_X() + x < 0) && (x < 0)) { //left
				return;
			}
			if ((asset[i]->Get_X() + x + asset[i]->GetRadius() * 2 > WINDOW_WIDTH) && (x > 0)) { //right
				return;
			}
			if ((asset[i]->Get_Y() + y < 0) && (y < 0)) { //up
				return;
			}
			if ((asset[i]->Get_Y() + y + asset[i]->GetRadius() * 2 > WINDOW_HEIGHT) && (y > 0)) { //down
				return;
			}
		}

		for (int i = 0; i < asset.size(); i++) {
			asset[i]->Move(x, y);
		}

		if (withCollision) {
			for (int k = 0; k < asset.size(); k++) {
				for (int i = 0; i < asset.size(); i++) {
					if (asset[k] != asset[i] && asset[i]->GetBounds().intersects(asset[k]->GetBounds())) {
						asset[i]->SetColor(asset[k]->GetColor());
					}
				}
			}
		}
	}

	void SwitchCollision() {
		withCollision = !withCollision;
		if (withCollision) {
			std::cout << "COLLISION ON!\n";
		} else {
			std::cout << "COLLISION OFF!\n";
		}
	}

	void MoveWithTrajectory(sf::RenderWindow* const& window, int x, int y) {
		for (int k = 0; k < asset.size(); k++) {
			for (int i = 0; i < WINDOW_HEIGHT; i++) {
				if ((asset[k]->Get_X() + x < 0) && (x < 0)) { //left
					return;
				}
				if ((asset[k]->Get_X() + x + asset[k]->GetRadius() * 2 > WINDOW_WIDTH) && (x > 0)) { //right
					return;
				}
				if ((asset[k]->Get_Y() + y < 0) && (y < 0)) { //up
					return;
				}
				if ((asset[k]->Get_Y() + y + asset[k]->GetRadius() * 2 > WINDOW_HEIGHT) && (y > 0)) { //down
					return;
				}

				for (int g = 0; g < asset.size(); g++) {
					if ((asset[g]->Get_X() + x < 0) && (x < 0)) { //left
						return;
					}
					if ((asset[g]->Get_X() + x + asset[g]->GetRadius() * 2 > WINDOW_WIDTH) && (x > 0)) { //right
						return;
					}
					if ((asset[g]->Get_Y() + y < 0) && (y < 0)) { //up
						return;
					}
					if ((asset[g]->Get_Y() + y + asset[g]->GetRadius() * 2 > WINDOW_HEIGHT) && (y > 0)) { //down
						return;
					}

					asset[g]->Move(x, y);
					asset[g]->Draw(window);
				}
				window->display();
				Sleep(1);
			}
		}
	}

	void SetColor(sf::Color color) override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->SetColor(color);
		}
	}

	void SetOuter(sf::Color color) override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->SetOuter(color);
		}
	}

	void SetRadius(int radius) override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->SetRadius(radius);
		}
	}

	void MakeBigger() override {
		for (int i = 0; i < asset.size(); i++) {
			asset[i]->MakeBigger();
		}
	}

	void MakeSmaller() override {
		for (int i = 0; i < asset.size(); i++) {
			if (asset[i]->GetRadius() - 5 <= 0) {
				return;
			}
			asset[i]->MakeSmaller();
		}
	}

	int ReturnSizeAsset() {
		return asset.size();
	}

	Figure* Entrails(int a) {
		if (a > asset.size() - 1) {
			return asset[0];
		} else {
			return asset[a];
		}
	}
};

