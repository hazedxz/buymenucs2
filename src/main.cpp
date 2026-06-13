#include <metahook.h>
#include <iostream>

// External function declarations from other modules
void InitializeBuyMenu();
void RenderBuyMenu(bool* pOpen);
void InstallOpenGLHooks();

// Global state variables
bool g_isMenuOpen = false;

// Define g_pMetaHookAPI here — declared extern in metahook.h but never defined in the SDK
metahook_api_t* g_pMetaHookAPI = nullptr;

void IPluginsV3::Init(metahook_api_t* pAPI, mh_interface_t* pInterface, mh_enginesave_t* pSave) {
    g_pMetaHookAPI = pAPI;

    std::cout << "\n";
    std::cout << "[SYSTEM] ==================================" << std::endl;
    std::cout << "[SYSTEM] CS2 Liquid Menu Plugin Loaded" << std::endl;
    std::cout << "[SYSTEM] Engine version: GoldSrc" << std::endl;
    std::cout << "[SYSTEM] Injecting core hooks..." << std::endl;

    InstallOpenGLHooks();

    std::cout << "[SYSTEM] Initializing asset textures..." << std::endl;
    InitializeBuyMenu();

    std::cout << "[SYSTEM] UI Initialization complete." << std::endl;
    std::cout << "[SYSTEM] ==================================\n" << std::endl;
}

void IPluginsV3::Shutdown(void) {
    std::cout << "[SYSTEM] Shutting down Liquid Menu..." << std::endl;
}

void IPluginsV3::LoadEngine(cl_enginefunc_t* pEngineFuncs) {
}

void IPluginsV3::LoadClient(cl_exportfuncs_t* pExportFuncs) {
}

void IPluginsV3::ExitGame(int iResult) {
}

EXPOSE_SINGLE_INTERFACE(IPluginsV3, IPluginsV3, METAHOOK_PLUGIN_API_VERSION_V3);