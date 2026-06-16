#pragma once

#include <glm/vec2.hpp>

// Particle definition: Properties follow F=ma (Newtons second law)
// Takes in current position x, velocity v, force F, and mass m.
// Properties can be used to calculate acceleration of particle.

struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force;
    float mass;
};