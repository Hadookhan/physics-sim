#pragma once

#include <glm/vec2.hpp>

#include "data/State.hpp"

#include "physics/Electric.hpp"


class ElectricPanel
{
public:
    void createPanel(ElectricSystem& system, SimulationState& state);
};