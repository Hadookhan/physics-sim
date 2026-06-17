#pragma once
#include <glm/vec2.hpp>

// Used for physical bodies to inherit from which have similar properties
// This allows them to share integrating methods

struct PhysicsBody
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force;
    glm::vec2 netForce;
    float mass;
};