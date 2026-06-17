#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "physics/Particle.hpp"
#include "physics/Integrator.hpp"

#include "data/State.hpp"

void resetProjectile(Particle& p, glm::vec2 position, glm::vec2 velocity, glm::vec2 force, float mass)
{
    if (p.position.y < -1.0f)
    { 
        p.position = position;
        p.velocity = velocity;
        p.force = force;
        p.mass = mass;
    }
}

glm::vec2 calcGravityForce(Particle& p, float gravity)
{
    return p.mass * glm::vec2(0.0f, gravity);
}
glm::vec2 calcHorizontalForce(float horizontalForce)
{
    return glm::vec2(horizontalForce, 0.0f);
}
glm::vec2 calcDragForce(Particle& p, float dragCoeff)
{
    return -dragCoeff * p.velocity;
}

void updateProjectile(std::vector<Particle>& particles, float particleMass, const glm::vec2& velocity, const glm::vec2& pos, glm::vec2 force, SimulationState& state)
{
    for (Particle& p : particles)
    {
        p.mass = particleMass;
        // F=mg=ma, uses gravity slider to change gravitational strength
        // Implements a constant horizontal force, which when non-zero, brings mass back into the equation
        // Implements drag (example: air resistance) to simulate real physics motion - drag always pushes against direction of force by a 'dragCoeff' constant
        p.force += calcGravityForce(p, state.gravity);
        p.force += calcHorizontalForce(state.horizontalForce);

        if (state.useDrag)
        {
            p.force += calcDragForce(p, state.dragCoeff);
        }

        // Net force is used to store total force acted on the particle, before integrate function resets force to 0.
        p.netForce = p.force;

        integrateEuler(p, state.dt);

        resetProjectile(p, pos, velocity, force, particleMass);
    }
}

void renderParticles(const std::vector<Particle>& particles, SimulationState& state)
{
    float velocityScale = 0.1f;
    float forceScale = 0.05f;

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    // Renders a particle x and y pos for every particle in particles vector
    for (const Particle& p : particles)
    {
        glVertex2f(p.position.x, p.position.y);
    }
    glEnd();

    // Lines below enable vectors of velocity and force acted on particle
    if (state.showVelocityVector)
    {
        glBegin(GL_LINES);
        for (const Particle& p : particles)
        {
            glVertex2f(p.position.x, p.position.y);

            glVertex2f(
                p.position.x + p.velocity.x * velocityScale,
                p.position.y + p.velocity.y * velocityScale
            );
        }

        glEnd();
    }

    if (state.showForceVector)
    {
        glBegin(GL_LINES);
        for (const Particle& p : particles)
        {
            glVertex2f(p.position.x, p.position.y);
            glVertex2f(
                p.position.x + p.netForce.x * forceScale,
                p.position.y + p.netForce.y * forceScale
            );
        }
        glEnd();
    }

}