#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include "physics/Spring.hpp"
#include "physics/Integrator.hpp"

#include "data/State.hpp"

void updateSpringMass(SpringMass& mass, const Spring& spring, SimulationState& state)
{
    glm::vec2 displacement = mass.position - spring.anchor;
    float length = glm::length(displacement); // sqrt(x^2 + y^2)

    if (length == 0.0f) return;

    glm::vec2 direction = displacement / length;

    float extension = length - spring.restLength;

    // Hookes Law:
    glm::vec2 springForce =
        -spring.stiffness * extension * direction;

    glm::vec2 dampingForce =
        -spring.damping * mass.velocity;

    mass.force += springForce + dampingForce;

    if (state.useGravity)
    {
        mass.force += mass.mass * glm::vec2(0.0f, state.gravity); // Makes spring system obey gravity
    }

    mass.netForce = mass.force;

    integrateRK2(mass, state.dt);
}

void renderSpringMass(const SpringMass& mass, const Spring& spring, SimulationState& state)
{
    float velocityScale = 0.1f;
    float forceScale = 0.05f;

    glBegin(GL_LINES);
    glVertex2f(spring.anchor.x, spring.anchor.y);
    glVertex2f(mass.position.x, mass.position.y);
    glEnd();

    glPointSize(12.0f);
    glBegin(GL_POINTS);
    glVertex2f(mass.position.x, mass.position.y);
    glEnd();

    // Lines below enable vectors of velocity and force acted on massed object
    if (state.showVelocityVector)
    {
        glBegin(GL_LINES);
        glVertex2f(mass.position.x, mass.position.y);

        glVertex2f(
            mass.position.x + mass.velocity.x * velocityScale,
            mass.position.y + mass.velocity.y * velocityScale
        );

        glEnd();
    }

    if (state.showForceVector)
    {
        glBegin(GL_LINES);
        glVertex2f(mass.position.x, mass.position.y);
        glVertex2f(
            mass.position.x + mass.netForce.x * forceScale,
            mass.position.y + mass.netForce.y * forceScale
        );

        glEnd();
    }
}