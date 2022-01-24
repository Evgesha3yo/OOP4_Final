#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Circle.h"
#include "Octagon.h"
#include "Scene.h"
#include "GLOBAL_DATA.h"
#include "windows.h"

int main()
{
    bool withShadow = false;
    bool withRememberedTrajectory = false;
    int counter = 0;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML");
    Scene* scene = new Scene(&window);
    Circle* circle = new Circle(80, 360, 300);
    Octagon* octagon = new Octagon(90, 300, 400);
    Circle* circle1 = new Circle(70, 100, 300);
    Octagon* octagon1 = new Octagon(35, 250, 100);
    Circle* circle2 = new Circle(20, 100, 100);
    Circle* circle3 = new Circle(20, 200, 200);

    scene->AddShape(new Composite(circle));
    scene->AddShape(new Composite(octagon));
    scene->AddShape(new Composite(circle1));
    scene->AddShape(new Composite(octagon1));
    scene->AddShape(new Composite(circle2));
    scene->AddShape(new Composite(circle3));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::N) {
                    scene->SelectForward();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    scene->Move(0, -15);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    scene->Move(0, 15);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    scene->Move(-15, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    scene->Move(15, 0);
                }
                if (event.key.code == sf::Keyboard::C) {
                    scene->ChangeColor();
                }
                if (event.key.code == sf::Keyboard::B) {
                    scene->ChangeOutlineBorderColor();
                }
                if (event.key.code == sf::Keyboard::H) {
                    scene->HideOneElement();
                }
                if (event.key.code == sf::Keyboard::Comma) {
                    scene->MakeSmaller();
                }
                if (event.key.code == sf::Keyboard::Period) {
                    scene->MakeBigger();
                }
                if (event.key.code == sf::Keyboard::O) {
                    scene->DrawOld();
                }
                if (event.key.code == sf::Keyboard::S) { //Shadow mode swithcer
                    withShadow = !withShadow;
                    if (withShadow) {
                        std::cout << "SHADOW ON!\n";
                    } else {
                        std::cout << "SHADOW OFF!\n";
                    }
                }
                if (event.key.code == sf::Keyboard::A) {
                    scene->MoveWithTrajectory(&window, 0, 2);
                }
                if (event.key.code == sf::Keyboard::Tab) {
                    scene->SwitchCollision();
                }
                if (event.key.code == sf::Keyboard::T) {
                    scene->NewCombine();
                }
                if (event.key.code == sf::Keyboard::U) {
                    scene->Combine();
                }
            }
        }

        counter++;
        if (counter > 700) {
            counter = 0;
            window.clear();
        }

        if (!withShadow) {
            window.clear();
        }

        scene->Draw();
        window.display();
    }
}
