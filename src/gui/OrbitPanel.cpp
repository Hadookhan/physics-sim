#include <string>

#include "physics/Orbit.hpp"

#include "gui/OrbitPanel.hpp"

#include "data/State.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void OrbitPanel::createPanel(OrbitSystem& system, SimulationState& state)
{
    int satelliteIndex = 0;
    int satelliteCount = static_cast<int>(system.satellites.size());
    ImGui::Text("Number of Satellites: %d", satelliteCount);

    ImGui::SliderFloat("G", &state.G, 0.001f, 0.1f);
    ImGui::SliderFloat("Central Mass", &system.central.mass, 1.0f, 1000.0f);
    ImGui::SliderFloat("Initial Tangential Velocity", &state.orbitVelocity, 0.0f, 5.0f);

    for (int i = 0; i < satelliteCount; i++)
    {
        std::string label = "Satellite Mass " + std::to_string(i+1);
        ImGui::SliderFloat(label.c_str(), &system.satellites[i].mass, 0.1f, 100.0f);
    }

    if (ImGui::Button("Reset Orbit"))
    {
         system.satellites.resize(1); // Destroys all satellites except the first one

        system.central.position = glm::vec2(0.0f, 0.0f);
        system.central.velocity = glm::vec2(0.0f);
        system.central.force = glm::vec2(0.0f);
        system.central.netForce = glm::vec2(0.0f);
        system.central.isStatic = true;

        // Only resets the first satellite to the initial position and velocity
        for (auto& satellite : system.satellites)
        {
            satellite.position = glm::vec2(0.6f, 0.0f);
            satellite.velocity = glm::vec2(0.0f, state.orbitVelocity);
            satellite.force = glm::vec2(0.0f);
            satellite.netForce = glm::vec2(0.0f);
            satellite.isStatic = false;
        }
    }

    if (ImGui::Button("Add Satellite"))
    {
        OrbitBody newSatellite{
            glm::vec2(0.6f, 0.0f),
            glm::vec2(0.0f, state.orbitVelocity),
            glm::vec2(0.0f),
            glm::vec2(0.0f),
            1.0f,
            false
        };
        system.satellites.push_back(newSatellite);
    }

    ImGui::Checkbox("Show Orbit line", &state.showOrbitLine);
}