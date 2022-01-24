#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Composite.h"
#include "GLOBAL_DATA.h"
#include "windows.h"
#include <vector>

class Scene : public Figure {
private:
	std::vector<Composite*> figures;
	sf::RenderWindow* window;
	Composite* SelectedFigure;

	int _currentElement = 0;
	bool allIsShown = true;
	bool withCollision = false;
	Composite* combinedFigure;

public:
	Scene(sf::RenderWindow* const& window) {
		this->window = window;
	}

	void AddShape(Composite* figure) {
		figures.push_back(figure);
		if (figures.size() == 1) {
			figure->ShowHidden();
			figure->AddBorder(window);
			SelectedFigure = figure;
		}
	}

	void DeleteFromFigures(Figure* figure) {
		SelectedFigure->DeleteBorder(window);
		for (int i = 0; i < figures.size(); i++) {
			if (figures[i] == SelectedFigure) {
				figures.erase(figures.begin() + i);
			}
		}
		_currentElement--;
		if (_currentElement < 0) {
			_currentElement = 0;
		}
	}

	void NewCombine() {
		combinedFigure = SelectedFigure;
	}

	void Combine() {
		combinedFigure->AddShape((Composite*)SelectedFigure);
		DeleteFromFigures(SelectedFigure);
		SelectedFigure = combinedFigure;
		SelectedFigure->AddBorder(window);
	}

	void Draw() {
		for (int i = 0; i < figures.size(); i++) {
			figures[i]->Draw(window);
		}
	}

	virtual void DrawOld() {
		SelectedFigure->DrawOld(window);
	}

	void Move(int x, int y) {
		SelectedFigure->Move(x, y);

		if (withCollision) {
			for (int i = 0; i < figures.size(); i++) {
				if (figures[i]->ReturnSizeAsset() < 2) {
					for (int j = 0; j < figures[i]->ReturnSizeAsset(); j++) {
						for (int k = 0; k < figures[j]->ReturnSizeAsset(); k++) {
							if (figures[i]->Entrails(k) != SelectedFigure->Entrails(k) && figures[i]->Entrails(k)->GetBounds().intersects(SelectedFigure->Entrails(k)->GetBounds())) {
								figures[i]->SetRadius(SelectedFigure->Entrails(k)->GetRadius());
							}
						}
					}
				} else {
					for (int k = 0; k < figures[i]->ReturnSizeAsset(); k++) {
						if (figures[i]->Entrails(k) != SelectedFigure->Entrails(k) && figures[i]->Entrails(k)->GetBounds().intersects(SelectedFigure->Entrails(k)->GetBounds())) {
							figures[i]->SetRadius(SelectedFigure->Entrails(k)->GetRadius());
						}
					}
				}
			}
		}
	}

	void SwitchCollision() {
		withCollision = !withCollision;
		if (withCollision) {
			std::cout << "MODE: COLLISION (ENABLED)\n";
		} else {
			std::cout << "MODE: COLLISION (DISABLED)\n";
		}
	}

	void MoveWithTrajectory(sf::RenderWindow* const& window, int x, int y) {
		SelectedFigure->MoveWithTrajectory(window, x, y);
	}

	void HideOneElement() {
		if (allIsShown) {
			if (SelectedFigure->IsHidden()) {
				std::cout << "ELEMENT IS SHOWN!\n";
				SelectedFigure->ShowHidden();
			} else {
				std::cout << "ELEMENT IS HIDDEN!\n";
				SelectedFigure->Hide();
			}
		}
	}

	void MakeBigger() {
		SelectedFigure->MakeBigger();
	}

	void MakeSmaller() {
		if (SelectedFigure->GetRadius() - 5 <= 0) {
			return;
		}
		SelectedFigure->MakeSmaller();
	}

	void ChangeColor() {
		color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
		SelectedFigure->SetColor(color);
		std::cout << "Color is changed!\n";
	}

	void ChangeOutlineBorderColor() {
		color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
		SelectedFigure->SetOuter(color);
		std::cout << "OuterColor is changed!\n";
	}

	void SelectForward() {
		if (!allIsShown) {
			if (figures.size() == 0) {
				return;
			}

			if (_currentElement == 0) {
				figures[figures.size() - 1]->Hide();
				figures[figures.size() - 1]->DeleteBorder(window);

				figures[_currentElement]->ShowHidden();
				figures[_currentElement]->AddBorder(window);
				SelectedFigure = figures[_currentElement];
			} else {
				figures[_currentElement]->ShowHidden();
				figures[_currentElement]->AddBorder(window);
				SelectedFigure = figures[_currentElement];

				figures[_currentElement - 1]->Hide();
				figures[_currentElement - 1]->DeleteBorder(window);
			}
			_currentElement++;
			if (_currentElement >= figures.size()) {
				_currentElement = 0;
			}
		} else {
			if (figures.size() == 0) {
				return;
			}
			if (_currentElement == 0) {
				figures[figures.size() - 1]->DeleteBorder(window);
				figures[_currentElement]->AddBorder(window);
				SelectedFigure = figures[_currentElement];
			} else {
				figures[_currentElement]->AddBorder(window);
				SelectedFigure = figures[_currentElement];
				figures[_currentElement - 1]->DeleteBorder(window);
			}
			_currentElement++;
			if (_currentElement >= figures.size())  {
				_currentElement = 0;
			}
		}
	}
};