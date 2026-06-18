#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "physics/PhysicsBody.hpp"

#include "data/State.hpp"

struct OrbitBody : public PhysicsBody
{
    bool isStatic;
};

struct OrbitSystem
{
    OrbitBody central;
    std::vector<OrbitBody> satellites;
    float G;
};

void updateOrbit(OrbitSystem& system, SimulationState& state);
void renderOrbit(const OrbitSystem& system, SimulationState& state);