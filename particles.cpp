#include <iostream>
#include <SFML/Graphics.hpp>

#include "InteractingParticles.h"

using namespace std;

typedef std::vector<float> state_type;

int WinMain() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Window", sf::Style::Default);
    window.setFramerateLimit(60);

    InteractingParticles parts(0);

    sf::Clock clock;
    float t = 0.0f;
    float dt = 0.0f;

    sf::Vector2f mPos;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == 2) {
                    mPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    float theta = PI * float(rand() % 100) / 100.0f;
                    float phi = PI * float(rand() % 100) / 100.0f;
                    parts.spawn_new(20 + rand() % 40, mPos.x, mPos.y, rand()%1000, 1.0f * sinf(theta) * cosf(phi), 1.0f * sinf(theta) * sinf(phi), 1.0f * cosf(theta));
                }
                break;
            }
        }
        
        

        dt = clock.restart().asSeconds();
        std::cout << int(1.0f / dt) << std::endl;
        t += dt;

        window.clear();

        parts.onUpdate(t, dt, window);

        window.display();
        
    }
    return 0;
}