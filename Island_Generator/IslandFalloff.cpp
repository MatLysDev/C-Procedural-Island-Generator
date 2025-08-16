#include "IslandFalloff.h"
#include <cmath>      
#include <random>     
#include <algorithm>  

IslandFalloff::IslandFalloff(float edgeMarginPercent, float minIslandSpacing)
    : edgeMarginPercent(edgeMarginPercent), minIslandSpacing(minIslandSpacing) {
}

std::vector<std::vector<float>> IslandFalloff::GenerateFalloffMap(
    int width,
    int height,
    int seed,
    int minIslands,
    int maxIslands,
    float minIslandSizeFactor,
    float maxIslandSizeFactor
)
{
    std::vector<std::vector<float>> falloffMap(width, std::vector<float>(height, 0.0f));
    std::mt19937 prng (seed);
    std::uniform_real_distribution<float> dist01(0.0f, 1.0f); //

    int islandCount = minIslands + (prng() % (maxIslands - minIslands + 1));
    std::vector<Vector2> islandCenters(islandCount);
    std::vector<float> islandSizes(islandCount);

    // Generate island positions and sizes
    for (int i = 0; i < islandCount; i++)
    {
        float x = 0, y = 0;
        float sizeFactor = minIslandSizeFactor + dist01(prng) * (maxIslandSizeFactor - minIslandSizeFactor);

        if (i == 0)
        {
            x = width / 2.0f + (dist01(prng) - 0.5f) * 0.1f * width;
            y = height / 2.0f + (dist01(prng) - 0.5f) * 0.1f * height;
        }
        else
        {
            const int maxAttempts = 100;
            int attempts = 0;
            float bestMinDistance = 0.0f;
            float bestX = 0, bestY = 0;
            bool positionOk = false;

            while (!positionOk && attempts < maxAttempts)
            {
                attempts++;
                float px = edgeMarginPercent + dist01(prng) * (1.0f - 2.0f * edgeMarginPercent);
                float py = edgeMarginPercent + dist01(prng) * (1.0f - 2.0f * edgeMarginPercent);

                float testX = px * width;
                float testY = py * height;

                float minDistToOthers = 1e9f;
                for (int j = 0; j < i; j++)
                {
                    Vector2 other = islandCenters[j];
                    float dx = testX - other.x;
                    float dy = testY - other.y;
                    float dist = std::sqrt(dx * dx + dy * dy);
                    if (dist < minDistToOthers)
                        minDistToOthers = dist;
                }

                if (minDistToOthers >= minIslandSpacing)
                {
                    x = testX;
                    y = testY;
                    positionOk = true;
                }
                else if (minDistToOthers > bestMinDistance)
                {
                    bestMinDistance = minDistToOthers;
                    bestX = testX;
                    bestY = testY;
                }
            }

            if (!positionOk)
            {
                if (bestMinDistance > minIslandSpacing * 0.2f)
                {
                    x = bestX;
                    y = bestY;
                }
                else
                {
                    continue; 
                }
            }
        }

        islandCenters[i] = Vector2(x, y);
        islandSizes[i] = sizeFactor;
    }

    // Fill the falloff map
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float value = 0.0f;
            for (int i = 0; i < islandCount; i++)
            {
                Vector2 center = islandCenters[i];
                float dx = (x - center.x) / width;
                float dy = (y - center.y) / height;
                float dist = std::sqrt(dx * dx + dy * dy) / islandSizes[i];

                float island = std::max(0.0f, 1.0f - dist);
                island = ApplyFalloffCurve(island);
                value = std::max(value, island);
            }
            falloffMap[x][y] = 1.0f - value;
        }
    }

    return falloffMap;
}

float IslandFalloff::ApplyFalloffCurve(float value)
{
    return std::pow(value, 2.5f);
}
