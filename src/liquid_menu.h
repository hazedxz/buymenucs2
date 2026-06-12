#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <string>
#include <vector>

// Forward declaration of our texture loader
GLuint LoadSVGTexture(const char* filepath, int targetWidth, int targetHeight);

// Structure to hold individual weapon data
struct BuyMenuItem {
    std::string displayName;
    std::string command; // This also matches the .svg filename
    int price;
    GLuint textureID;
};

// Main functions to hook into the game loop
void InitializeBuyMenu();
void RenderBuyMenu(bool* pOpen);
void ApplyDarkCinematicStyle();