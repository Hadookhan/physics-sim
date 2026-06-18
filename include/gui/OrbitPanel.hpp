#pragma once

#include <glm/vec2.hpp>

#include "data/State.hpp"

#include "physics/Orbit.hpp"


class OrbitPanel
{
public:
    void createPanel(OrbitSystem& system, SimulationState& state);
};