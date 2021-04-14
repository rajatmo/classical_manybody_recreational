#include "InteractingParticles.h"
float dist(float x1, float y1, float z1, float x2, float y2, float z2) {
    return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

/*
//Coulomb global
float globalforcex(float x, float y, float z, float vx, float vy, float vz) {
    float d = dist(x, y, z, 1280.0f / 2.0f, 720.0f / 2.0f, 1000.0f / 2.0f);
    if (d < 5.0f) {
        return 0;
    }
    return -1000000.0f * (x - 1280.0f / 2.0f) / powf(dist(x, y, z, 1280.0f / 2.0f, 720.0f / 2.0f, 1000.0f / 2.0f), 3);
}
float globalforcey(float x, float y, float z, float vx, float vy, float vz) {
    float d = dist(x, y, z, 1280.0f / 2.0f, 720.0f / 2.0f, 1000.0f / 2.0f);
    if (d < 5.0f) {
        return 0;
    }
    return -1000000.0f * (y - 720.0f / 2.0f) / powf(dist(x, y, z, 1280.0f / 2.0f, 720.0f / 2.0f, 1000.0f / 2.0f), 3);
}
float globalforcez(float x, float y, float z, float vx, float vy, float vz) {
    float d = dist(x, y, z, 1280.0f / 2.0f, 720.0f / 2.0f, 1000.0f / 2.0f);
    if (d < 5.0f) {
        return 0;
    }
    return -1000000.0f * (z - 1000.0f / 2.0f) / powf(dist(x, y, z, 1280.0f / 2.0f, 720.0f / 2.0f, 1000.0f / 2.0f), 3);
}

*/

//Coulomb mutual
float mutualforcex(float x1, float y1, float z1, float x2, float y2, float z2) {
    return -100.0f * (x1 - x2) / float(pow(dist(x1, y1, z1, x2, y2, z2),3));
}
float mutualforcey(float x1, float y1, float z1, float x2, float y2, float z2) {
    return -100.0f * (y1 - y2) / float(pow(dist(x1, y1, z1, x2, y2, z2), 3));
}
float mutualforcez(float x1, float y1, float z1, float x2, float y2, float z2) {
    return -100.0f * (z1 - z2) / float(pow(dist(x1, y1, z1, x2, y2, z2), 3));
}


/*
//Yukawa
float mutualforcex(float x1, float y1, float z1, float x2, float y2, float z2) {
    return -(x1 - x2) * exp(-dist(x1, y1, z1, x2, y2, z2))/ dist(x1, y1, z1, x2, y2, z2);
}
float mutualforcey(float x1, float y1, float z1, float x2, float y2, float z2) {
    return - (y1 - y2) * exp(-dist(x1, y1, z1, x2, y2, z2)) / dist(x1, y1, z1, x2, y2, z2);
}
float mutualforcez(float x1, float y1, float z1, float x2, float y2, float z2) {
    return - (z1 - z2) * exp(-dist(x1, y1, z1, x2, y2, z2)) / dist(x1, y1, z1, x2, y2, z2);
}
*/

/*
//Van der Waal's
float mutualforcex(float x1, float y1, float z1, float x2, float y2, float z2) {
    return 1000.0f * (x1 - x2) / float(pow(dist(x1, y1, z1, x2, y2, z2), 7));
}
float mutualforcey(float x1, float y1, float z1, float x2, float y2, float z2) {
    return 1000.0f * (y1 - y2) / float(pow(dist(x1, y1, z1, x2, y2, z2), 7));
}
float mutualforcez(float x1, float y1, float z1, float x2, float y2, float z2) {
    return 1000.0f * (z1 - z2) / float(pow(dist(x1, y1, z1, x2, y2, z2), 7));
}

*/

void my_system(const state_type& x, state_type& dxdt, const float t, state_type& mass) {
    for (size_t i = 0; i < x.size() / 6; i++) {
        float localsumx = 0;
        float localsumy = 0;
        float localsumz = 0;
        float globalfx = 0;
        float globalfy = 0;
        float globalfz = 0;
        /*
        globalfx = globalforcex(x[6 * i + 0], x[6 * i + 1], x[6 * i + 2], x[6 * i + 3], x[6 * i + 4], x[6 * i + 5]);
        globalfy = globalforcey(x[6 * i + 0], x[6 * i + 1], x[6 * i + 2], x[6 * i + 3], x[6 * i + 4], x[6 * i + 5]);
        globalfz = globalforcez(x[6 * i + 0], x[6 * i + 1], x[6 * i + 2], x[6 * i + 3], x[6 * i + 4], x[6 * i + 5]);
        */
        
        for (size_t j = 0; j < x.size() / 6; j++) {
            if (i != j) {
                localsumx += mass[j] * mutualforcex(x[6 * i + 0], x[6 * i + 1], x[6 * i + 2], x[6 * j + 0], x[6 * j + 1], x[6 * j + 2]);
                localsumy += mass[j] * mutualforcey(x[6 * i + 0], x[6 * i + 1], x[6 * i + 2], x[6 * j + 0], x[6 * j + 1], x[6 * j + 2]);
                localsumz += mass[j] * mutualforcez(x[6 * i + 0], x[6 * i + 1], x[6 * i + 2], x[6 * j + 0], x[6 * j + 1], x[6 * j + 2]);
            }
        }
        
        dxdt[6 * i + 0] = x[6 * i + 3];
        dxdt[6 * i + 1] = x[6 * i + 4];
        dxdt[6 * i + 2] = x[6 * i + 5];
        dxdt[6 * i + 3] = localsumx + (globalfx);
        dxdt[6 * i + 4] = localsumy + (globalfy);
        dxdt[6 * i + 5] = localsumz + (globalfz);
    }
}

//elastic reflection

void checkBounds(float& x, float& y, float& z, float& vx, float& vy, float& vz) {
    if (x < 0 || x > 1280 || y < 0 || y > 720 || z < 0 || z > 1000) {
        if (x < 0 || x > 1280) {
            vx = -vx;
        }
        if (y < 0 || y > 720) {
            vy = -vy;
        }
        if (z < 0 || z > 1000) {
            vz = -vz;
        }
    }
}

/*
//inelastic reflection
void checkBounds(float& x, float& y, float& z, float& vx, float& vy, float& vz) {
    if (x < 0 || x > 1280 || y < 0 || y > 720 || z < 0 || z > 1000) {
        if (x < 0 || x > 1280) {
            vx = -0.7f * vx;
            
        }
        if (y < 0 || y > 720) {
            vy = -0.7f * vy;
            
        }
        if (z < 0 || z > 1000) {
            vz = -0.5f * vz;
            
        }
    }
}
*/



void euler_solver(void (*System)(const state_type& x, state_type& dxdt, const float t, state_type& mass), state_type& x, float t, float dt, state_type& mass) {
    size_t dim = x.size();
    state_type result(dim);
    result = x;
    state_type k(dim);
    System(x, k, t, mass);
    for (int i = 0; i < dim; i++) {
        x[i] += dt * k[i];
    }
}


InteractingParticles::InteractingParticles(size_t k) {
    n = 0;
    for (size_t i = 0; i < k; i++) {
        spawn_new(10.0f, 0, 0, 0, 0, 0, 0);
    }
}

void InteractingParticles::onUpdate(float t, float dt, sf::RenderWindow& window) {
    euler_solver(my_system, x, t, dt * TIMESCALE, mass);
    for (size_t i = 0; i < n; i++) {
        checkBounds(x[6 * i + 0], x[6 * i + 1], x[6 * i + 2], x[6 * i + 3], x[6 * i + 4], x[6 * i + 5]);
        circ[i].setPosition(x[6 * i + 0], x[6 * i + 1]);
        window.draw(circ[i]);
    }
}

void InteractingParticles::spawn_new(float r, float xm, float ym, float zm, float vx, float vy, float vz) {
    n += 1;
    std::cout << "Ball no. " << n << "being spawned at ("<<xm<<", "<<ym<<").\n";
    x.push_back(xm);
    x.push_back(ym);
    x.push_back(zm);
    x.push_back(vx);
    x.push_back(vy);
    x.push_back(vz);
    mass.push_back(r * r * r/10000.0f);
    sf::CircleShape tmp(r);
    tmp.setOrigin(r, r);
    tmp.setPosition(xm, ym);
    tmp.setFillColor(sf::Color::Blue);
    circ.push_back(tmp);
}

