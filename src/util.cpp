// Name: Kevin Kim
// Description: this file contains implementations for utility functions.
#include "util.h"
#include "image_io.h"
#include <algorithm>
#include <iostream>

using namespace std;

int ClampInt(int v, int lo, int hi)
{
    if (v < lo)
        return lo;
    if (v > hi)
        return hi;
    return v;
}

uint8_t ClampU8(float v)
{
    if (v < 0.0f)
        v = 0.0f;
    if (v > 255.0f)
        v = 255.0f;
    return static_cast<uint8_t>(v + 0.5f);
}

RawImage RgbToGray(const RawImage &rgb)
{
    if (rgb.channels != 3)
    {
        cerr << "[RgbToGray] Input must be RGB (3 channels)\n";
        return {};
    }

    RawImage gray = MakeImage(rgb.width, rgb.height, 1, 0);

    const float wr = 0.299f;
    const float wg = 0.587f;
    const float wb = 0.114f;

    for (int y = 0; y < rgb.height; y++)
    {
        for (int x = 0; x < rgb.width; x++)
        {
            const uint8_t r = At(rgb, x, y, 0);
            const uint8_t g = At(rgb, x, y, 1);
            const uint8_t b = At(rgb, x, y, 2);
            const float v = wr * r + wg * g + wb * b;
            At(gray, x, y, 0) = ClampU8(v);
        }
    }
    return gray;
}
