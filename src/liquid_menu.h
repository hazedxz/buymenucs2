#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <string>
#include <vector>


GLuint LoadSVGTexture(const char* filepath, int targetWidth, int targetHeight);


struct BuyMenuItem {
    std::string displayName;
    std::string command; 
    int price;
    GLuint textureID;
};


void InitializeBuyMenu();
void RenderBuyMenu(bool* pOpen);
void ApplyDarkCinematicStyle();
