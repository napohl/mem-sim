/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <map>

//project files
#include "flag_parser/flag_parser.h"
#include "frame/frame.h"
#include "page/page.h"
#include "page_table/page_table.h"
#include "physical_address/physical_address.h"
#include "process/process.h"
#include "simulation/simulation.h"
#include "virtual_address/virtual_address.h"

using namespace std;

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
    // TODO: add i/o for file argument, create a flag options struct first, then parse flags
    //if return false, print help menu and exit

    //todo, print size of all processes in bytes
    //todo, print the firtual addresses the file contains

    FlagOptions flags;

    //parse the flags, if it returns false, print usage, and exit
    if (!parse_flags(argc, argv, flags)) {
        print_usage();
        return EXIT_FAILURE;
    }

    //continue to file io

    ///////////////////////////////////////////////////////////////////////////
    //the following code is for deliverable one!

    //process_1.txt should be of size 2002
    //process_2.txt should be of size 68

    ifstream memAccess(flags.filename);
    if (memAccess.fail()) {
        cout << "Could not open file: " << flags.filename << endl;
        return EXIT_FAILURE;
    }
    //use stringstream to get all values from input file
    stringstream stream;
    string line;
    //keep track of number of processes
    int numProcesses = 0;
    //keep a list of all memory access numbers
    vector<bitset<16>> accesses;
    //map keeps track of pid and the pointer to the process
    map<int, Process*> allProcesses;

    //first line is number of processes
    getline(memAccess, line);
    stream << line;
    stream >> numProcesses;

    //iterate through number of processes to get pid and input file,
    //then construct process using the input file
    for (int i = 0; i < numProcesses; i++) {
        int pid;
        string file;
        stringstream loop;
        getline(memAccess, line);
        loop << line;
        loop >> pid;
        loop >> file;

        //start new fileio to get all data from the input file
        ifstream processAccess(file);
        if (processAccess.fail()) {
            cout << "Could not open file: " << file << endl;
            return EXIT_FAILURE;
        }
        Process* process = Process::read_from_input(processAccess);
        //allProcesses.insert(pid, process);
        cout << "Process " << pid << " is size " << process->size() << endl;


    }

    //go through rest of file getting all memory accesses
    int pid;
    bitset<16> address;

    //skip one line
    getline(memAccess, line);

    while(!memAccess.eof()) {
        stringstream loop;
        getline(memAccess, line);
        loop << line;
        //first entry is pid, second entry is memory access
        loop >> pid;
        loop >> address;
        cout << "Memory access for process " << pid << " at " << address << endl;
    }

    ///////////////////////////////////////////////////////////////////////////

    
    return EXIT_SUCCESS;
}
