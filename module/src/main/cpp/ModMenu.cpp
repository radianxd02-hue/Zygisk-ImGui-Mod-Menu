//
// Updated for GymFlex PUBG by Radian
//
#include <Headers/ModMenu.hpp>
#include <Headers/Drawing.hpp>
#include <Headers/Utility.hpp>

#include "imgui.h"

// Ganti dari libil2cpp.so (ML/Unity) ke libUE4.so (PUBG/Unreal Engine)
#define TARGET_LIBRARY "libUE4.so"

// Variabel global untuk nyimpan Base Address
uintptr_t libBase = 0;

void ModMenu::DrawMenu(int width, int height) {
    // Desain UI ImGui GymFlex
    ImGui::Begin("GymFlex PUBG Injector", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Status: Injected Successfully");
    
    // Nampilin Base Address biar kelihatan pro
    if (libBase != 0) {
        ImGui::Text("libUE4 Base: 0x%lX", libBase);
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Waiting for libUE4.so...");
    }
    
    ImGui::Separator();

    // Fitur-fitur Menu
    static bool enableESP = false;
    static bool enableAimbot = false;
    static float recoilControl = 0.0f;

    ImGui::Checkbox("Enable ESP Box", &enableESP);
    ImGui::Checkbox("Aimbot (Safe Mode)", &enableAimbot);
    ImGui::SliderFloat("Less Recoil", &recoilControl, 0.0f, 100.0f, "%.0f%%");

    ImGui::Separator();

    // Tombol Scan Peta (Nanti disambungin ke fungsi Scanner)
    if (ImGui::Button("Scan Peta (GWorld)", ImVec2(200, 30))) {
        // Nanti logika KittyMemory/Pattern Scanner ditaruh di sini
    }

    ImGui::End();
}

void ModMenu::HackThread() {
    Drawing::InitMenu(DrawMenu);

    // Looping tunggu sampai libUE4.so muncul di memori
    do {
        LOGI("Menunggu libUE4.so ter-load...");
        sleep(1);
    } while (Utility::GetBaseAddress(TARGET_LIBRARY) == 0); 
    // ^ Diubah pakai GetBaseAddress biar logikanya lebih solid

    // Kalau udah ter-load, simpan angkanya ke variabel libBase
    libBase = Utility::GetBaseAddress(TARGET_LIBRARY);
    LOGI("Target library %s loaded at 0x%lu", TARGET_LIBRARY, libBase);

    // Hooks and Patches (Scanner GWorld dll) bakal jalan dari sini nantinya

    LOGI("GymFlex ModMenu initialized");
}
