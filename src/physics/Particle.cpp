#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "physics/Particle.hpp"
#include "physics/Integrator.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

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

void updateProjectile(std::vector<Particle>& particles, float dt, float gravity, float horizontalForce, float dragCoeff, float particleMass, glm::vec2 velocity, glm::vec2 pos, glm::vec2 force)
{
    for (Particle& p : particles)
    {
        p.mass = particleMass;
        // F=mg=ma, uses gravity slider to change gravitational strength
        // Implements a constant horizontal force, which when non-zero, brings mass back into the equation
        // Implements drag (example: air resistance) to simulate real physics motion - drag always pushes against direction of force by a 'dragCoeff' constant
        p.force += p.mass * glm::vec2(0.0f, gravity);
        p.force += glm::vec2(horizontalForce, 0.0f);
        p.force += -dragCoeff * p.velocity;
        integrateRK2(p, dt);

        resetProjectile(p, pos, velocity, force, particleMass);
    }
}

void renderParticles(std::vector<Particle>& particles)
{
    // Renders a particle x and y pos for every particle in particles vector
    for (const Particle& p : particles)
    {
        glVertex2f(p.position.x, p.position.y);
    }
}