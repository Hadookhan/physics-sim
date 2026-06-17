#pragma once
#include <glm/vec2.hpp>
#include "physics/PhysicsBody.hpp"
#include "data/State.hpp"

struct SpringMass : public PhysicsBody
{
};

// Below struct is the actual spring, which is anchored at some (x,y) position

struct Spring
{
    glm::vec2 anchor;
    float restLength;
    float stiffness;
    float damping;
};

void updateSpringMass(SpringMass& mass, const Spring& spring, SimulationState& state);
void renderSpringMass(const SpringMass& mass, const Spring& spring, SimulationState& state);