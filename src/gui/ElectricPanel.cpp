#include <string>
#include <vector>

#include "physics/Electric.hpp"

#include "gui/ElectricPanel.hpp"

#include "data/State.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void ElectricPanel::createPanel(ElectricSystem& system, SimulationState& state)
{
    std::vector<glm::vec2> chargePos{state.chargePos1, state.chargePos2};

    ImGui::SliderFloat("Space Permittivity", &system.spacePermittivity, 0.001f, 0.1f);
    ImGui::Checkbox("Enable Static Charges", &state.isStatic);
    for (auto& charge : system.charges)
    {
        charge.isStatic = state.isStatic;
    }

    // if (ImGui::Button("Add Charge"))
    // {
    //     Charge newCharge{
    //         glm::vec2(0.5f, 0.0f),
    //         glm::vec2(0.0f),
    //         glm::vec2(0.0f),
    //         glm::vec2(0.0f),
    //         1.0f,
    //         1.0f,
    //         false
    //     };
    //     system.charges.push_back(newCharge);
    // }

    int chargeCount = static_cast<int>(system.charges.size());
    for (int i = 0; i < chargeCount; i++)
    {
        std::string label = "Charge " + std::to_string(i+1) + " Value";
        ImGui::SliderFloat(label.c_str(), &system.charges[i].charge, -10.0f, 10.0f);
    }

    if (ImGui::Button("Reset Charges"))
    {
        for (int i = 0; i < chargeCount; i++)
        {
            system.charges[i].position = chargePos[i];
            system.charges[i].velocity = glm::vec2(0.0f);
            system.charges[i].force = glm::vec2(0.0f);
            system.charges[i].netForce = glm::vec2(0.0f);
            system.charges[i].isStatic = true;
        }
        state.elapsed = 0.0f;
        state.logTimer = 0.0f;
    }
}