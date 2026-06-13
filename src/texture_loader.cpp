#include <windows.h>
#include <gl/GL.h>
#include <iostream>

// Strict single-definition for NanoSVG implementation
#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION

#include "../vendor/nanosvg/nanosvg.h"
#include "../vendor/nanosvg/nanosvgrast.h"

// Loads an SVG from disk, scales it, and pushes it to OpenGL VRAM
GLuint LoadSVGTexture(const char* filepath, int targetWidth, int targetHeight) {
    
    // Parse the mathematical vectors from the file
    NSVGimage* image = nsvgParseFromFile(filepath, "px", 96.0f);
    if (!image) {
        std::cout << "[ERROR] Failed to load SVG file: " << filepath << std::endl;
        return 0; 
    }

    // Initialize the rasterizer engine
    NSVGrasterizer* rast = nsvgCreateRasterizer();
    if (!rast) {
        std::cout << "[ERROR] Failed to initialize SVG rasterizer." << std::endl;
        nsvgDelete(image);
        return 0;
    }

    // Dynamic scaling to maintain perfect aspect ratio regardless of category
    float scaleX = (float)targetWidth / image->width;
    float scaleY = (float)targetHeight / image->height;
    float scale = (scaleX < scaleY) ? scaleX : scaleY; 

    // Allocate memory for raw pixels (RGBA format)
    unsigned char* imgData = (unsigned char*)malloc(targetWidth * targetHeight * 4);
    if (!imgData) {
        std::cout << "[ERROR] Memory allocation failed for texture." << std::endl;
        nsvgDeleteRasterizer(rast);
        nsvgDelete(image);
        return 0;
    }
    
    // Convert math curves to pixels
    nsvgRasterize(rast, image, 0, 0, scale, imgData, targetWidth, targetHeight, targetWidth * 4);

    // OpenGL Texture Generation
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Hardware filtering for crisp UI edges
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Upload to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, targetWidth, targetHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    // Crucial cleanup: Free system RAM immediately to save resources
    free(imgData);
    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);

    return textureID;
}