#include <iostream>
#include <string>
#include <vector>

static void PrintUsage()
{
    std::cout
        << "EE569 HW2 - hw2\n"
        << "Usage:\n"
        << "  ./hw2 --help\n"
        << "  ./hw2 <subcommand> [args...]\n\n"
        << "Subcommands (to be implemented):\n"
        << "  sobel_raw\n"
        << "  canny_jpg\n"
        << "  ht_thresh\n"
        << "  ht_random\n"
        << "  ht_bayer\n"
        << "  ht_ed_fs\n"
        << "  ht_ed_jjn\n"
        << "  ht_ed_stucki\n"
        << "  color_sep_fs\n"
        << "  color_mbvq_fs\n";
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        PrintUsage();
        return 0;
    }

    std::string cmd = argv[1];
    if (cmd == "--help" || cmd == "-h")
    {
        PrintUsage();
        return 0;
    }

    std::vector<std::string> args;
    for (int i = 2; i < argc; i++)
        args.emplace_back(argv[i]);

    std::cout << "[hw2] cmd: " << cmd << "\n";
    std::cout << "[hw2] argc: " << argc << "\n";
    for (size_t i = 0; i < args.size(); i++)
    {
        std::cout << "  arg[" << i << "] = " << args[i] << "\n";
    }

    std::cout << "[hw2] OK (placeholder)\n";
    return 0;
}
