#include <vector>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/norm.hpp>

#include "physics/Field.hpp"

#include "data/State.hpp"

void renderFieldVectors(const std::vector<FieldVector>& field, SimulationState& state)
{
    float maxLength = 0.08f;

    glBegin(GL_LINES);

    for (const FieldVector& f : field)
    {
        glm::vec2 arrow = f.value * state.fieldScale;

        if (glm::length(arrow) > maxLength)
        {
            arrow = glm::normalize(arrow) * maxLength;
        }

        glm::vec2 end = f.position + arrow;

        glVertex2f(f.position.x, f.position.y);
        glVertex2f(end.x, end.y);
    }

    glEnd();
}