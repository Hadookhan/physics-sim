#include "physics/Orbit.hpp"

#include "gui/OrbitPanel.hpp"

#include "data/State.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void OrbitPanel::createPanel(OrbitSystem& system, SimulationState& state)
{
    ImGui::SliderFloat("G", &state.G, 0.001f, 0.1f);
    ImGui::SliderFloat("Central Mass", &system.central.mass, 1.0f, 1000.0f);
    ImGui::SliderFloat("Satellite Mass", &system.satellite.mass, 0.1f, 100.0f);
    ImGui::SliderFloat("Initial Tangential Velocity", &state.orbitVelocity, 0.0f, 5.0f);

    if (ImGui::Button("Reset Orbit"))
    {
        system.central.position = glm::vec2(0.0f, 0.0f);
        system.central.velocity = glm::vec2(0.0f);
        system.central.force = glm::vec2(0.0f);
        system.central.netForce = glm::vec2(0.0f);
        system.central.isStatic = true;

        system.satellite.position = glm::vec2(0.6f, 0.0f);
        system.satellite.velocity = glm::vec2(0.0f, 1.29f);
        system.satellite.force = glm::vec2(0.0f);
        system.satellite.netForce = glm::vec2(0.0f);
        system.satellite.isStatic = false;
    }
    ImGui::Checkbox("Show Orbit line", &state.showOrbitLine);
}