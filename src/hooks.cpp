#include <metahook.h>
#include <windows.h>
#include <gl/GL.h>
#include <iostream>


#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_win32.h"
#include "../vendor/imgui/imgui_impl_opengl2.h"


extern bool g_isMenuOpen;
void RenderBuyMenu(bool* pOpen);


typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC hdc);
wglSwapBuffers_t g_pfn_wglSwapBuffers = nullptr;

k
bool g_bImGuiInitialized = false;
HWND g_hWindow = NULL;
WNDPROC g_pfnOriginalWndProc = nullptr;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (g_bImGuiInitialized) {
        if (g_isMenuOpen) {
            ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

            if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_MOUSEMOVE ||
                uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP ||
                uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP ||
                uMsg == WM_MOUSEWHEEL) {
                return TRUE;
            }
        }
    }
    return CallWindowProc(g_pfnOriginalWndProc, hWnd, uMsg, wParam, lParam);
}


BOOL WINAPI Hooked_wglSwapBuffers(HDC hdc) {
    if (!g_bImGuiInitialized) {
        g_hWindow = WindowFromDC(hdc);
        if (g_hWindow) {
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.IniFilename = NULL;

            ImGui_ImplWin32_Init(g_hWindow);
            ImGui_ImplOpenGL2_Init();

            g_pfnOriginalWndProc = (WNDPROC)SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)Hooked_WndProc);

            g_bImGuiInitialized = true;

            std::cout << "[SYSTEM] ImGui Context initialized." << std::endl;
            std::cout << "[SYSTEM] Window sub-classed successfully." << std::endl;
        }
    }

    if (g_bImGuiInitialized) {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (g_isMenuOpen) {
            RenderBuyMenu(&g_isMenuOpen);
        }

        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

    return g_pfn_wglSwapBuffers(hdc);
}


void InstallOpenGLHooks() {
    HMODULE hOpenGL = GetModuleHandleA("opengl32.dll");
    if (hOpenGL) {
        void* p_wglSwapBuffers = (void*)GetProcAddress(hOpenGL, "wglSwapBuffers");
        if (p_wglSwapBuffers && g_pMetaHookAPI) {
            // InlineHook signature: hook_t*(void* pOld, void* pNew, void** pOriginal)
            void* pOriginal = nullptr;
            g_pMetaHookAPI->InlineHook(p_wglSwapBuffers, (void*)Hooked_wglSwapBuffers, &pOriginal);
            g_pfn_wglSwapBuffers = (wglSwapBuffers_t)pOriginal;

            std::cout << "[SYSTEM] OpenGL wglSwapBuffers hook injected." << std::endl;
        } else {
            std::cout << "[ERROR] Hook injection failed: Invalid pointers." << std::endl;
        }
    } else {
        std::cout << "[ERROR] opengl32.dll not found." << std::endl;
    }
}
