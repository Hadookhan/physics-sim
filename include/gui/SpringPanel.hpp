#pragma once

#include "data/State.hpp"

#include "physics/Spring.hpp"

class SpringPanel
{
public:
    void createPanel(SpringMass& springMass, Spring& spring, SimulationState& state);
};