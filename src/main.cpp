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
 * helper function for printing out results of the simulation
 */
void printEndResults(vector<int> pids, vector<Process*> processes, int totalMemAccess, int totalPageFaults, int totalUsedFrames) {
    cout << "\nDONE!\n\n";
    //pids and processes should be the same size and correlate correctly
    for (int i = 0; i < pids.size(); i++) {
        cout << "Process\t" << pids[i] << ":\tACCESSES: " << processes[i]->memory_accesses << "\tFAULTS: " << processes[i]->page_faults;
        cout << "\tFAULT_RATE: " << processes[i]->get_fault_percent() << "\tRSS: " << processes[i]->get_rss() << endl;
    }

    cout << "\nTotal memory accesses: " << totalMemAccess << endl;
    cout << "Total page faults: " << totalPageFaults << endl;
    //total frames is always 512
    cout << "Free frames remaining: " << 512 - totalUsedFrames << endl << endl;
}

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {

    FlagOptions flags;

    //parse the flags, if it returns false, print usage, and exit
    if (!parse_flags(argc, argv, flags)) {
        print_usage();
        return EXIT_FAILURE;
    }

    //continue to file io

    ///////////////////////////////////////////////////////////////////////////
    /*
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

        processAccess.close();
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

    memAccess.close();
    */

    ///////////////////////////////////////////////////////////////////////////

    int totalMemAccess = 0;
    int totalPageFaults = 0;
    int totalUsedFrames = 0;

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
    //vector of all pids, (useful for last output)
    vector<int> allPids;
    //vector of all Processes, for last output
    vector<Process*> allProcesses;

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

        allPids.push_back(pid);
        allProcesses.push_back(process);
        processAccess.close();
    }

    //go through rest of file getting all memory accesses
    int pid;
    bitset<16> address;

    //skip one line
    getline(memAccess, line);

    //might put this code in simulation::Run()
    while(!memAccess.eof()) {
        stringstream loop;
        getline(memAccess, line);
        loop << line;
        //first entry is pid, second entry is memory access
        loop >> pid;
        loop >> address;
    }

    memAccess.close();

    printEndResults(allPids, allProcesses, totalMemAccess, totalPageFaults, totalUsedFrames);
    
    return EXIT_SUCCESS;
}
