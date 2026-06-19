#pragma once
#include <glm/vec2.hpp>

#include <data/State.hpp>

// Used for visualising vector fields. Describes a vector at a given position in space, with a field strength value associated with it.

struct FieldVector
{
    glm::vec2 position;
    glm::vec2 value;
};

void renderFieldVectors(const std::vector<FieldVector>& field, SimulationState& state);