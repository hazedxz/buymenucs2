#include "liquid_menu.h"
#include "../vendor/imgui/imgui.h"
#include <iostream>

// Global vectors to store our categories
std::vector<BuyMenuItem> categoryPistols;
std::vector<BuyMenuItem> categoryRifles;

// Helper function to populate items and load textures efficiently
void AddWeapon(std::vector<BuyMenuItem>& category, const std::string& name, const std::string& cmd, int price) {
    BuyMenuItem item;
    item.displayName = name;
    item.command = cmd;
    item.price = price;
    
    std::string path = "assets/icons/" + cmd + ".svg";
    item.textureID = LoadSVGTexture(path.c_str(), 128, 45); // Standardized resolution
    
    category.push_back(item);
}

void InitializeBuyMenu() {
    // Vertical logging format for terminal clarity
    std::cout << "[SYSTEM] Starting UI Initialization..." << std::endl;
    std::cout << "[SYSTEM] Allocating memory for textures..." << std::endl;
    
    // --- PISTOLS ---
    std::cout << "[DATA] Loading category: Pistols" << std::endl;
    AddWeapon(categoryPistols, "Glock-18", "glock", 400);
    AddWeapon(categoryPistols, "USP-S", "usp", 500);
    AddWeapon(categoryPistols, "P250", "p228", 300);
    AddWeapon(categoryPistols, "Desert Eagle", "deagle", 650);

    // --- RIFLES ---
    std::cout << "[DATA] Loading category: Rifles" << std::endl;
    AddWeapon(categoryRifles, "Galil AR", "galil", 2000);
    AddWeapon(categoryRifles, "FAMAS", "famas", 2250);
    AddWeapon(categoryRifles, "AK-47", "ak47", 2700);
    AddWeapon(categoryRifles, "M4A1", "m4a1", 3100);
    AddWeapon(categoryRifles, "AWP", "awp", 4750);

    std::cout << "[SYSTEM] Buy Menu initialized successfully." << std::endl;
}

void ApplyDarkCinematicStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Dark Cinematic / Liquid styling
    colors[ImGuiCol_WindowBg]       = ImVec4(0.06f, 0.06f, 0.06f, 0.94f); // Translucent dark
    colors[ImGuiCol_Border]         = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
    colors[ImGuiCol_Button]         = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_ButtonHovered]  = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive]   = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_Text]           = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled]   = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

    style.WindowRounding    = 8.0f; // Soft Apple-like corners
    style.FrameRounding     = 4.0f;
    style.ItemSpacing       = ImVec2(8, 8);
}

void RenderBuyMenu(bool* pOpen) {
    if (!*pOpen) return;

    ApplyDarkCinematicStyle();

    // Setup main window, removing native titlebars and making it unmovable to simulate an overlay
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
                                   ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

    // Center the menu perfectly
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(1000, 600), ImGuiCond_Once);

    ImGui::Begin("CS2_BuyMenu", pOpen, windowFlags);

    // Grid Layout using ImGui Tables (Replicating the 5-column layout)
    if (ImGui::BeginTable("BuyGrid", 5, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingFixedFit)) {
        
        // Table Headers
        ImGui::TableSetupColumn("Equipment");
        ImGui::TableSetupColumn("Pistols");
        ImGui::TableSetupColumn("Mid-Tier");
        ImGui::TableSetupColumn("Rifles");
        ImGui::TableSetupColumn("Grenades");
        ImGui::TableHeadersRow();

        
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(3); 

        for (const auto& weapon : categoryRifles) {
            
            ImGui::PushID(weapon.command.c_str());
            
            
            if (ImGui::Button("", ImVec2(180, 70))) {
                
                std::string engineCommand = weapon.command + "\n";
                
                std::cout << "[ACTION] Executed: " << engineCommand;
            }

            
            ImVec2 minPos = ImGui::GetItemRectMin();
            ImGui::GetWindowDrawList()->AddImage(
                (void*)(intptr_t)weapon.textureID, 
                ImVec2(minPos.x + 10, minPos.y + 10), 
                ImVec2(minPos.x + 138, minPos.y + 55)
            );
            
            
            ImGui::GetWindowDrawList()->AddText(
                ImVec2(minPos.x + 10, minPos.y + 50), 
                IM_COL32(255, 215, 0, 255), 
                ("$" + std::to_string(weapon.price)).c_str()
            );

            ImGui::PopID();
        }

        ImGui::EndTable();
    }

    ImGui::End();
}