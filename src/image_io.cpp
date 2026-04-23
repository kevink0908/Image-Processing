// Name: Kevin Kim
// Description: this file contains implementations for RAW image I/O functions and utilities.
#include "image_io.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

void read_raw(const string &filename,
              vector<uint8_t> &buffer,
              int width, int height, int channels)
{
    size_t total_bytes = static_cast<size_t>(width) *
                         static_cast<size_t>(height) *
                         static_cast<size_t>(channels);

    buffer.resize(total_bytes);

    ifstream fin(filename, ios::binary);
    if (!fin)
    {
        cerr << "Error: cannot open input file " << filename << endl;
        exit(1);
    }

    fin.read(reinterpret_cast<char *>(buffer.data()), static_cast<std::streamsize>(total_bytes));

    if (!fin)
    {
        cerr << "Error: failed to read raw file " << filename << endl;
        exit(1);
    }

    fin.close();
}

void write_raw(const string &filename,
               const vector<uint8_t> &buffer)
{
    ofstream fout(filename, ios::binary);
    if (!fout)
    {
        cerr << "Error: cannot open output file " << filename << endl;
        exit(1);
    }

    fout.write(reinterpret_cast<const char *>(buffer.data()),
               static_cast<std::streamsize>(buffer.size()));

    if (!fout)
    {
        cerr << "Error: failed to write raw file " << filename << endl;
        exit(1);
    }

    fout.close();
}
