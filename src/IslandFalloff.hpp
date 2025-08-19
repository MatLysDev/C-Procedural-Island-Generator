#pragma once
#include <vector>
#include "MathUtility.hpp"  

class IslandFalloff
{
public:
    IslandFalloff(float edgeMarginPercent = 0.2f, float minIslandSpacing = 20.0f);

    std::vector<std::vector<float>> GenerateFalloffMap(
        int width,
        int height,
        int seed,
        int minIslands,
        int maxIslands,
        float minIslandSizeFactor,
        float maxIslandSizeFactor
    );

private:
    float edgeMarginPercent;
    float minIslandSpacing;

    float ApplyFalloffCurve(float value);
};
