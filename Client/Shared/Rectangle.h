#pragma once
#include "pch.h"
class RectangleJson
{
    
public:
    RectangleJson(float x, float y, float width, float height)
    {
        X = x;
        Y = y;
        W = width;
        H = height;
    }
    std::string Type = "Rectangle";
    float X;
    float Y;
    float W;
    float H;

    void ToJson(json& j) const
    {
        j = json{
            {"Type", Type},
            {"X", X},
            {"Y", Y},
            {"Width", W},
            {"Height",H}
        };
    }

    // Convert JSON to Entity object
    void FromJson(const json& j)
    {
        Type = j["Type"];
        X = j["X"];
        Y = j["Y"];
        W = j["Width"];
        H = j["Height"];
    }
};