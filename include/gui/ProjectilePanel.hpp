#pragma once

#include <glm/vec2.hpp>

#include "data/State.hpp"
#include "physics/Particle.hpp"


class ProjectilePanel
{
public:
    void createPanel(std::vector<Particle>& particles, SimulationState& state);
};