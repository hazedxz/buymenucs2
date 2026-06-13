# CS2-Style Buy Menu for CS 1.6

A modern, scalable weapon buy menu for **Counter-Strike 1.6**, inspired by the **Counter-Strike 2** interface. Built with **Dear ImGui** and **NanoSVG** for high-fidelity vector rendering.

##  Features

- **CS2 Aesthetic**: Replicates the clean, modern look of the Counter-Strike 2 buy menu.
- **Vector-Based Icons**: Uses **NanoSVG** to render weapon icons (SVG) directly, ensuring perfect scaling at any resolution without pixelation.
- **Lightweight & Fast**: Minimal overhead using **Dear ImGui** (Immediate Mode GUI) and header-only libraries.
- **High DPI Support**: Crisp visuals on 1080p, 2K, and 4K displays.
- **Customizable**: Easy to add new weapons, categories, or modify the layout.
- **Seamless Integration**: Designed to work with existing CS 1.6 clients or as a standalone overlay.

##  Tech Stack

- **UI Framework**: [Dear ImGui](https://github.com/ocornut/imgui)
- **SVG Rasterization**: [NanoSVG](https://github.com/memononen/nanosvg)
- **Language**: C++
- **Graphics API**: OpenGL / DirectX (depending on your hook/renderer)

##  Installation

### Prerequisites
- C++ Compiler (MSVC, GCC, or Clang)
- CMake (optional, for building dependencies)
- Counter-Strike 1.6 installed
- Metahook

### Building from Source

1. **Clone the repository**:
   ```bash
   git clone https://github.com/hazedxz/buy-menu-cs2.git
   cd cs2-buy-menu-cs16   
