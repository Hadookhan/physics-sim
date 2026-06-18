#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <math.h>

#include "physics/Electric.hpp"
#include "physics/Integrator.hpp"

#include "data/State.hpp"

void updateElectric(ElectricSystem& system, SimulationState& state)
{
    float softening = 0.01f;

    // Constant in Coulomb's law, k = 1 / (4 * pi * epsilon_0)
    float k = 1.0f / (4.0f * M_PI * system.spacePermittivity);

    for (size_t i = 0; i < system.charges.size(); ++i)
    {
        Charge& charge_i = system.charges[i];

        for (size_t j = 0; j < system.charges.size(); ++j)
        {
            if (i == j) continue;

            Charge& charge_j = system.charges[j];

            if (state.isStatic)
            {
                continue;
            }
            glm::vec2 r = charge_i.position - charge_j.position;
            float distanceSquared = glm::dot(r, r) + softening * softening;

            if (distanceSquared == 0.0f) continue;

            glm::vec2 forceDirection = glm::normalize(r);
            float forceMagnitude = k * (charge_i.charge * charge_j.charge) / distanceSquared;
            glm::vec2 force = forceMagnitude * forceDirection;

            charge_i.force += force;
        }

        charge_i.netForce = charge_i.force;

        if (!charge_i.isStatic)
        {
            integrateRK2(charge_i, state.dt);
        }
        else
        {
            charge_i.force = glm::vec2(0.0f);
            charge_i.velocity = glm::vec2(0.0f);
        }
    }
}

void renderElectric(const ElectricSystem& system, SimulationState& state)
{
    float velocityScale = 0.1f;
    float forceScale = 0.05f;


    for (const Charge& charge : system.charges)
    {
        glPointSize(12.0f);
        glBegin(GL_POINTS);
        glVertex2f(charge.position.x, charge.position.y);
        glEnd();

        // Lines below enable vectors of velocity and force acted on massed object
        if (state.showVelocityVector)
        {
            glBegin(GL_LINES);
            glVertex2f(charge.position.x, charge.position.y);
            glVertex2f(charge.position.x + charge.velocity.x * velocityScale, charge.position.y + charge.velocity.y * velocityScale);
            glEnd();
        }

        if (state.showForceVector)
        {
            glBegin(GL_LINES);
            glVertex2f(charge.position.x, charge.position.y);
            glVertex2f(charge.position.x + charge.netForce.x * forceScale, charge.position.y + charge.netForce.y * forceScale);
            glEnd();
        }
    }
}