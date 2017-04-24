/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <getopt.h>
#include <unistd.h>


using namespace std;

//used for flags
const struct option options[] = 
{
    {"strategy", required_argument, NULL, 't'},
    {"verbose", no_argument, NULL, 'v'},
    {"max_frames", required_argument, NULL, 'a'},
    {"help", no_argument, NULL, 'h'},
    {0,0,0,0}
};

void print_usage() {
    /*
    cout <<
        "Usage: mem-sim [options] filename\n"
        "\n"
        "Options:\n"
        "  -v, --verbose\n"
        "      Output information about every memory access.\n"
        "\n"
        "  -s, --strategy (FIFO | LRU)\n"
        "      The replacement strategy to use. One of FIFO or LRU.\n"
        "\n"
        "  -f, --max-frames <positive integer>\n"
        "      The maximum number of frames a process may be allocated.\n"
        "\n"
        "  -h --help\n"
        "      Display a help message about these flags and exit\n"
        "\n";
        */
}


bool parse_flags(int argc, char** argv, FlagOptions& flags) {
    int flag, index;
    int frames;
    string strat;
    //if there are no arguments, return false
    if (argc == 0) {
        return false;
    }
    for (int i = 0; i < argc; i++) {
        index = 0;
        flag = getopt_long(argc, argv, "hvf:s:", options, &index);
        if (flag == -1) return false;

        switch (flag) {
            case 'v':
                flags.verbose = true;
                break;
            case 'f':
                frames = stoi(optarg);
                if (frames > 0) {
                    flags.max_frames = frames;    
                }
                else {
                    //print_usage();
                    //exit(EXIT_FAILURE);
                    return false;
                }
                break;
            case 's':
                strat = optarg;
                if (strat == "FIFO") {
                    flags.strategy = ReplacementStrategy::FIFO;
                }
                else if (strat == "LRU") {
                    flags.strategy = ReplacementStrategy::LRU;
                }
                else {
                    //print_usage();
                    //exit(EXIT_FAILURE);
                    return false;
                }
                break;
            case 'h':
                //print_usage();
                //exit(0);
                //break;
            default:
                print_usage();
                return false;
                //exit(EXIT_FAILURE);
        }
    }
    return true;
}
