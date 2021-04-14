#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>   

constexpr float PI = 3.141;
constexpr float TIMESCALE = 50.0;

using namespace std;

typedef std::vector<float> state_type;

class InteractingParticles
{

    size_t n;
    state_type x;
    state_type mass;
    std::vector<sf::CircleShape> circ;
public:
    InteractingParticles(size_t k);
    void onUpdate(float t, float dt, sf::RenderWindow& window);
    void spawn_new(float r, float xm, float ym, float zm, float vx, float vy, float vz);
};

