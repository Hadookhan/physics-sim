#pragma once
#include <glm/vec2.hpp>
#include "physics/PhysicsBody.hpp"

struct SpringMass : public PhysicsBody
{
};

struct Spring
{
    glm::vec2 anchor;
    float restLength;
    float stiffness;
    float damping;
};

void updateSpringMass(SpringMass& mass, const Spring& spring, float dt, float gravity, bool useGravity);
void renderSpringMass(const SpringMass& mass, const Spring& spring, bool showVelocityVector, bool showForceVector);