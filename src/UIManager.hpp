#pragma once
#include "NoiseParams.hpp"
#include "TileManager.hpp"
#include "imgui.h"
#include <string>

struct UIResult {
    bool regenerate = false;
    bool savePNG = false;
    std::string saveFilename;
};

class UIManager {
public:
    // Show UI, return what actions to take
    UIResult Show(NoiseParams& params, TileManager& tileManager);

private:
    char filename[128] = "Island"; // persistent buffer for input
};
