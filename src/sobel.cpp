// Name: Kevin Kim
// Description: this file contains implementations for Sobel Edge Detector functions.
#include "sobel.h"
#include "util.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Normalize a float array to [0,255] using min-max normalization.
static RawImage NormalizeToU8(const vector<float> &src, int w, int h)
{
    RawImage out = MakeImage(w, h, 1, 0);
    if (src.empty())
        return out;

    float mn = numeric_limits<float>::infinity();
    float mx = -numeric_limits<float>::infinity();

    for (float v : src)
    {
        if (v < mn)
            mn = v;
        if (v > mx)
            mx = v;
    }

    // Avoid division by zero if flat
    if (!(mx > mn))
    {
        // all same => output all zeros
        return out;
    }

    const float scale = 255.0f / (mx - mn);

    // Write normalized
    for (int i = 0; i < w * h; i++)
    {
        float nv = (src[static_cast<size_t>(i)] - mn) * scale;
        out.data[static_cast<size_t>(i)] = ClampU8(nv);
    }
    return out;
}

// Choose threshold so that "edgePercent" of pixels are classified as edges (top magnitudes).
// Example: edgePercent=10 => threshold at 90th percentile (keep top 10% as edges).
static float ThresholdFromTopPercent(const vector<float> &mags, float edgePercent)
{
    if (mags.empty())
        return 0.0f;

    float p = edgePercent;
    if (p < 0.0f)
        p = 0.0f;
    if (p > 100.0f)
        p = 100.0f;

    // If p==0 => no edges, set threshold above max
    if (p == 0.0f)
    {
        float mx = *max_element(mags.begin(), mags.end());
        return mx + 1.0f;
    }

    // If p==100 => all edges, set threshold below min
    if (p == 100.0f)
    {
        float mn = *min_element(mags.begin(), mags.end());
        return mn - 1.0f;
    }

    // Keep top p% => threshold at (100-p) percentile
    const float keepTop = p / 100.0f;
    const float cut = 1.0f - keepTop; // e.g. 0.90 for top 10%
    size_t n = mags.size();
    size_t k = static_cast<size_t>(floor(cut * static_cast<float>(n - 1)));

    vector<float> tmp = mags;
    nth_element(tmp.begin(), tmp.begin() + static_cast<long>(k), tmp.end());
    return tmp[k];
}

SobelResult SobelEdgeDetector(const RawImage &gray, float edgePercent)
{
    SobelResult res;

    if (gray.channels != 1)
    {
        cerr << "[SobelEdgeDetector] Input must be grayscale (1 channel).\n";
        return res;
    }
    if (gray.width <= 0 || gray.height <= 0 || gray.data.empty())
    {
        cerr << "[SobelEdgeDetector] Invalid image.\n";
        return res;
    }

    const int w = gray.width;
    const int h = gray.height;

    // Sobel kernels (classic 3x3)
    // Gx:
    // -1  0  1
    // -2  0  2
    // -1  0  1
    //
    // Gy:
    //  1  2  1
    //  0  0  0
    // -1 -2 -1
    static const int kx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};
    static const int ky[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}};

    vector<float> gx(static_cast<size_t>(w) * static_cast<size_t>(h), 0.0f);
    vector<float> gy(static_cast<size_t>(w) * static_cast<size_t>(h), 0.0f);
    vector<float> mag(static_cast<size_t>(w) * static_cast<size_t>(h), 0.0f);

    // handle borders by clamping coordinates.
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float sx = 0.0f;
            float sy = 0.0f;

            for (int j = -1; j <= 1; j++)
            {
                int yy = ClampInt(y + j, 0, h - 1);
                for (int i = -1; i <= 1; i++)
                {
                    int xx = ClampInt(x + i, 0, w - 1);
                    uint8_t p = At(gray, xx, yy, 0);

                    sx += static_cast<float>(kx[j + 1][i + 1]) * static_cast<float>(p);
                    sy += static_cast<float>(ky[j + 1][i + 1]) * static_cast<float>(p);
                }
            }

            size_t idx = static_cast<size_t>(y) * static_cast<size_t>(w) + static_cast<size_t>(x);
            gx[idx] = sx;
            gy[idx] = sy;
            mag[idx] = sqrtf(sx * sx + sy * sy);
        }
    }

    // Normalize gx, gy, mag for visualization outputs (0-255)
    res.gx_norm = NormalizeToU8(gx, w, h);
    res.gy_norm = NormalizeToU8(gy, w, h);
    res.mag_norm = NormalizeToU8(mag, w, h);

    // Threshold magnitude using percentage rule (top P% => edges)
    res.mag_threshold = ThresholdFromTopPercent(mag, edgePercent);

    // create binary edge map: 0=edge, 255=background
    res.edge_binary = MakeImage(w, h, 1, 255);
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            size_t idx = static_cast<size_t>(y) * static_cast<size_t>(w) + static_cast<size_t>(x);
            if (mag[idx] >= res.mag_threshold)
            {
                res.edge_binary.data[idx] = 0; // edge
            }
            else
            {
                res.edge_binary.data[idx] = 255; // background
            }
        }
    }

    return res;
}
