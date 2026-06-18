#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <GLFW/glfw3.h>
#include <vector>

#include "physics/Orbit.hpp"
#include "physics/Integrator.hpp"

#include "data/State.hpp"

void updateOrbit(OrbitSystem& system, SimulationState& state)
{
    for (auto& satellite : system.satellites)
    {
        glm::vec2 displacement = (system.central.position - satellite.position);
        float distance = glm::length(displacement);
        if (distance < 0.001f)
        {
            continue; // Avoid division by zero or extremely large forces
        }
        glm::vec2 direction = displacement / distance;

        
        float softening = 0.01f;
        float distanceSquared = distance * distance + softening * softening;

        // Newtons law of gravitation
        glm::vec2 gravityForce = system.G * system.central.mass * satellite.mass / distanceSquared * direction;
        satellite.force += gravityForce;
        satellite.netForce = gravityForce;

        integrateRK2(satellite, state.dt);
    }
}

void renderOrbit(const OrbitSystem& system, SimulationState& state)
{
    float velocityScale = 0.1f;
    float forceScale = 0.05f;

    glPointSize(25.0f);
    glBegin(GL_POINTS);
    glVertex2f(system.central.position.x, system.central.position.y);
    glEnd();

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (const auto& satellite : system.satellites)
    {
        glVertex2f(satellite.position.x, satellite.position.y);
    }
    glEnd();

    if (state.showVelocityVector)
    {
        glBegin(GL_LINES);
        for (const auto& satellite : system.satellites)
        {
            glVertex2f(satellite.position.x, satellite.position.y);
            glVertex2f(
                satellite.position.x + satellite.velocity.x * velocityScale,
                satellite.position.y + satellite.velocity.y * velocityScale
            );
        }
        glEnd();
    }

    if (state.showForceVector)
    {
        glBegin(GL_LINES);
        for (const auto& satellite : system.satellites)
        {
            glVertex2f(satellite.position.x, satellite.position.y);
            glVertex2f(
                satellite.position.x + satellite.netForce.x * forceScale,
                satellite.position.y + satellite.netForce.y * forceScale
            );
        }
        glEnd();
    }

    if (state.showOrbitLine)
    {
        glBegin(GL_LINES);
        for (const auto& satellite : system.satellites)
        {
            glVertex2f(system.central.position.x, system.central.position.y);
            glVertex2f(satellite.position.x, satellite.position.y);
        }
        glEnd();
    }
}