#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "physics/Particle.hpp"
#include "physics/Integrator.hpp"

int main()
{
    std::vector<Particle> particles;
    float dt = 0.016f;


    // First vec = position, second vec = velocity, third vec = force, float represents force.
    // These are the initial conditions to the equation F=ma
    particles.push_back({
        glm::vec2(0.0f, 0.5f), // (x pos, y pos)
        glm::vec2(0.2f, 0.4f), // (x velo, y velo)
        glm::vec2(0.0f),
        1.0f
    });

    if (!glfwInit())
    {
        std::cerr << "Failed to initialise GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
        "Physics Sim",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        for (Particle& p : particles)
        {
            // F=mg, manipulated gravitational field strength constant to a slower degree to show smoothly in window
            p.force += p.mass * glm::vec2(0.0f, -0.5f);
            integrateEuler(p, dt);

            if (p.position.y < -1.0f)
            {
                p.position = glm::vec2(0.0f, 0.5f);
                p.velocity = glm::vec2(0.2f, 0.4f);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(10.0f);
        glBegin(GL_POINTS);

        // Renders a particle x and y pos for every particle in particles vector
        for (const Particle& p : particles)
        {
            glVertex2f(p.position.x, p.position.y);
        }

        glEnd();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}