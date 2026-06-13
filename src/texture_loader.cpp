#include <windows.h>
#include <gl/GL.h>
#include <iostream>


#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION

#include "../vendor/nanosvg/nanosvg.h"
#include "../vendor/nanosvg/nanosvgrast.h"


GLuint LoadSVGTexture(const char* filepath, int targetWidth, int targetHeight) {
    

    NSVGimage* image = nsvgParseFromFile(filepath, "px", 96.0f);
    if (!image) {
        std::cout << "[ERROR] Failed to load SVG file: " << filepath << std::endl;
        return 0; 
    }

  
    NSVGrasterizer* rast = nsvgCreateRasterizer();
    if (!rast) {
        std::cout << "[ERROR] Failed to initialize SVG rasterizer." << std::endl;
        nsvgDelete(image);
        return 0;
    }

 
    float scaleX = (float)targetWidth / image->width;
    float scaleY = (float)targetHeight / image->height;
    float scale = (scaleX < scaleY) ? scaleX : scaleY; 

    
    unsigned char* imgData = (unsigned char*)malloc(targetWidth * targetHeight * 4);
    if (!imgData) {
        std::cout << "[ERROR] Memory allocation failed for texture." << std::endl;
        nsvgDeleteRasterizer(rast);
        nsvgDelete(image);
        return 0;
    }
    
    
    nsvgRasterize(rast, image, 0, 0, scale, imgData, targetWidth, targetHeight, targetWidth * 4);

    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, targetWidth, targetHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    
    free(imgData);
    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);

    return textureID;
}
