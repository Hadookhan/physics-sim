#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "physics/Particle.hpp"
#include "physics/Integrator.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

int main()
{
    std::vector<Particle> particles;
    float dt = 0.016f;
    float gravity = -0.5f;
    float particleMass = 1.0f;
    float horizontalForce = 1.0f;
    float dragCoeff = 0.5f;


    // First vec = position, second vec = velocity, third vec = force, float represents force.
    // These are the initial conditions to the equation F=ma
    particles.push_back({
        glm::vec2(0.0f, 0.2f), // (x pos, y pos)
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
        1000,
        1000,
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

    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Simulation Controls");

        ImGui::SliderFloat("Gravity", &gravity, -10.0f, 0.0f);
        ImGui::SliderFloat("Time step", &dt, 0.001f, 0.05f);
        ImGui::SliderFloat("Mass", &particleMass, 0.1f, 10.0f);
        ImGui::SliderFloat("Horizontal force", &horizontalForce, -10.0f, 10.0f);

        if (ImGui::Button("Reset Particle"))
        {
            particles[0].position = glm::vec2(0.0f, 0.2f);
            particles[0].velocity = glm::vec2(0.2f, 0.4f);
            particles[0].force = glm::vec2(0.0f);
            particles[0].mass = particleMass;
        }

        ImGui::End();

        for (Particle& p : particles)
        {
            p.mass = particleMass;
            // F=mg=ma, uses gravity slider to change gravitational strength
            // Implements a constant horizontal force, which when non-zero, brings mass back into the equation
            // Implements drag (example: air resistance) to simulate real physics motion - drag always pushes against direction of force by a 'dragCoeff' constant
            p.force += p.mass * glm::vec2(0.0f, gravity);
            p.force += glm::vec2(horizontalForce, 0.0f);
            p.force += -dragCoeff * p.velocity;
            integrateEuler(p, dt);

            if (p.position.y < -1.0f)
            {
                p.position = glm::vec2(0.0f, 0.2f);
                p.velocity = glm::vec2(0.2f, 0.4f);
                p.force = glm::vec2(0.0f);
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

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}