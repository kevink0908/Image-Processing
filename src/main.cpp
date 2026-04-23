// Programmer: Kevin Kim
// Project: Image Processing: Edge Detection and Half-toning

#include <iostream>
#include <string>
#include <vector>
#include "canny_opencv.h"
#include "image_io.h"
#include "util.h"
#include "sobel.h"

using namespace std;

static void PrintUsage()
{
    cout
        << "EE569 HW2 - hw2\n"
        << "Usage:\n"
        << "  ./hw2 --help\n"
        << "  ./hw2 copy_raw <in.raw> <out.raw> <w> <h> <c>\n"
        << "  ./hw2 rgb2gray <in_rgb.raw> <out_gray.raw> <w> <h>\n"
        << "  ./hw2 sobel_edge_detector <in_rgb.raw> <out_prefix> <w> <h> <edgePercent>\n"
        << "  ./hw2 canny_edge_detector <in.jpg> <out_prefix> <lowThresh> <highThresh>\n"
        << "\n"
        << "Notes:\n"
        << "  - edgePercent is 0..100 (e.g., 10 means keep top 10% magnitudes as edges)\n"
        << "  - sobel outputs:\n"
        << "      <out_prefix>_gx.raw\n"
        << "      <out_prefix>_gy.raw\n"
        << "      <out_prefix>_mag.raw\n"
        << "      <out_prefix>_edge.raw   (0=edge, 255=background)\n"
        << "  - canny outputs:\n"
        << "      <out_prefix>_canny_L<low>_H<high>.raw   (0=background, 255=edge)\n";
}

static bool ParseInt(const string &s, int &out)
{
    try
    {
        out = stoi(s);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

static bool ParseFloat(const string &s, float &out)
{
    try
    {
        out = stof(s);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        PrintUsage();
        return 0;
    }

    string cmd = argv[1];
    if (cmd == "--help" || cmd == "-h")
    {
        PrintUsage();
        return 0;
    }

    if (cmd == "copy_raw")
    {
        if (argc != 7)
        {
            PrintUsage();
            return 1;
        }

        string inPath = argv[2];
        string outPath = argv[3];
        int w, h, c;

        if (!ParseInt(argv[4], w) || !ParseInt(argv[5], h) || !ParseInt(argv[6], c))
        {
            cerr << "Invalid w/h/c\n";
            return 1;
        }

        RawImage img = MakeImage(w, h, c, 0);
        read_raw(inPath, img.data, w, h, c);
        write_raw(outPath, img.data);

        cout << "[copy_raw] OK\n";
        return 0;
    }

    if (cmd == "rgb2gray")
    {
        if (argc != 6)
        {
            PrintUsage();
            return 1;
        }

        string inPath = argv[2];
        string outPath = argv[3];
        int w, h;

        if (!ParseInt(argv[4], w) || !ParseInt(argv[5], h))
        {
            cerr << "Invalid w/h\n";
            return 1;
        }

        RawImage rgb = MakeImage(w, h, 3, 0);
        read_raw(inPath, rgb.data, w, h, 3);

        RawImage gray = RgbToGray(rgb);
        write_raw(outPath, gray.data);

        cout << "[rgb2gray] OK\n";
        return 0;
    }

    if (cmd == "sobel_edge_detector")
    {
        // ./hw2 sobel_edge_detector <in_rgb.raw> <out_prefix> <w> <h> <edgePercent>
        if (argc != 7)
        {
            PrintUsage();
            return 1;
        }

        string inPath = argv[2];
        string outPrefix = argv[3];
        int w, h;
        float edgePercent;

        if (!ParseInt(argv[4], w) || !ParseInt(argv[5], h) || !ParseFloat(argv[6], edgePercent))
        {
            cerr << "Invalid w/h/edgePercent\n";
            return 1;
        }

        RawImage rgb = MakeImage(w, h, 3, 0);
        read_raw(inPath, rgb.data, w, h, 3);

        RawImage gray = RgbToGray(rgb);

        SobelResult r = SobelEdgeDetector(gray, edgePercent);

        write_raw(outPrefix + "_gx.raw", r.gx_norm.data);
        write_raw(outPrefix + "_gy.raw", r.gy_norm.data);
        write_raw(outPrefix + "_mag.raw", r.mag_norm.data);
        write_raw(outPrefix + "_edge.raw", r.edge_binary.data);

        cout << "[sobel_edge_detector] OK. mag_threshold=" << r.mag_threshold << "\n";
        return 0;
    }

    if (cmd == "canny_edge_detector")
    {
        // Usage:
        // ./hw2 canny_edge_detector <input.jpg> <out_prefix> <lowThresh> <highThresh>
        // Example:
        // ./hw2 canny_edge_detector data/Deer.jpg out/Deer 50 150

        if (argc != 6)
        {
            PrintUsage();
            return 1;
        }

        string inPath = argv[2];
        string outPrefix = argv[3];

        int lowT = 0, highT = 0;
        if (!ParseInt(argv[4], lowT) || !ParseInt(argv[5], highT))
        {
            cerr << "Invalid thresholds\n";
            return 1;
        }

        return RunCannyEdgeDetector(inPath, outPrefix, lowT, highT);
    }

    cerr << "Unknown command: " << cmd << "\n";
    PrintUsage();
    return 1;
}
