/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <getopt.h>
#include <unistd.h>
#include <stdexcept>


using namespace std;

//used for flags
const struct option options[] = 
{
    {"strategy", required_argument, NULL, 's'},
    {"verbose", no_argument, NULL, 'v'},
    {"max-frames", required_argument, NULL, 'f'},
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
    int flag, index = 0;
    int frames;
    string strat;
    //if there are no arguments, return false
    if (argc == 0) {
        return false;
    }
    while ((flag = getopt_long(argc, argv, "hvf:s:", options, &index)) != -1) {
    //for (int i = 0; i < argc; i++) {
        //flag = getopt_long(argc, argv, "hvf:s:", options, &index);

        switch (flag) {
            case 'v':
                flags.verbose = true;
                break;
            case 'f':
                try {
                    frames = stoi(optarg);
                }
                catch(invalid_argument& e) {
                    //if we recieve an invalid argument (like "one") return false
                    return false;
                }
                //cout << "optarg = " << optarg << "\tframes = " << frames << endl;
                if (frames > 0) {
                    flags.max_frames = frames;    
                }
                else {
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
                    return false;
                }
                break;
            case 'h':
                return false;
                break;
            default:
                return false;
        }
    }
    for (int i = optind; i < argc; i++) {
        flags.filename = argv[i];
    }
    if (flags.filename == "") {
        return false;
    }
    return true;
}
