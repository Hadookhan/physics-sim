#pragma once
#include <glm/vec2.hpp>

struct SpringMass
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force;
    float mass;
};

struct Spring
{
    glm::vec2 anchor;
    float restLength;
    float stiffness;
    float damping;
};

void updateSpringMass(SpringMass& mass, const Spring& spring, float dt);
void renderSpringMass(const SpringMass& mass, const Spring& spring);