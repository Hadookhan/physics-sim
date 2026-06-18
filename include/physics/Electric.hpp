#pragma once

#include <vector>

#include "physics/PhysicsBody.hpp"
#include "data/State.hpp"

struct Charge : public PhysicsBody
{
    float charge;
    bool isStatic;
};

struct ElectricSystem
{
    std::vector<Charge> charges;
    float spacePermittivity;
};

void updateElectric(ElectricSystem& system, SimulationState& state);
void renderElectric(const ElectricSystem& system, SimulationState& state);