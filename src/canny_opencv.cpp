// Description: this file contains implementations for Canny Edge Detector functions.
#include "canny_opencv.h"
#include "image_io.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

static string MakeOutPath(const string &prefix, int lowT, int highT)
{
    // Example: out/Deer_canny_L50_H150.raw
    ostringstream oss;
    oss << prefix << "_canny_L" << lowT << "_H" << highT << ".raw";
    return oss.str();
}

int RunCannyEdgeDetector(const std::string &inJpgPath,
                         const std::string &outPrefix,
                         int lowThresh,
                         int highThresh)
{
    if (lowThresh < 0 || highThresh < 0 || lowThresh > 255 || highThresh > 255)
    {
        cerr << "[canny_edge_detector] thresholds must be in [0,255]\n";
        return 1;
    }
    if (lowThresh >= highThresh)
    {
        cerr << "[canny_edge_detector] expected low < high\n";
        return 1;
    }

    // Read JPG/PNG
    cv::Mat bgr = cv::imread(inJpgPath, cv::IMREAD_COLOR);
    if (bgr.empty())
    {
        cerr << "[canny_edge_detector] failed to read: " << inJpgPath << "\n";
        return 1;
    }

    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY);

    // Run Canny (output is 0 or 255; 255 indicates edges)
    cv::Mat edges;
    cv::Canny(gray, edges, lowThresh, highThresh);

    // Copy to a flat buffer and write as RAW (1 channel)
    const int w = edges.cols;
    const int h = edges.rows;

    vector<uint8_t> buf(static_cast<size_t>(w) * static_cast<size_t>(h));
    for (int y = 0; y < h; y++)
    {
        const uint8_t *row = edges.ptr<uint8_t>(y);
        for (int x = 0; x < w; x++)
        {
            buf[static_cast<size_t>(y) * static_cast<size_t>(w) + static_cast<size_t>(x)] = row[x];
        }
    }

    const string outPath = MakeOutPath(outPrefix, lowThresh, highThresh);

    write_raw(outPath, buf);

    cout << "[canny_edge_detector] OK. w=" << w << " h=" << h
         << " low=" << lowThresh << " high=" << highThresh
         << " -> " << outPath << "\n";

    return 0;
}
