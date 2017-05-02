/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include <iostream>
#include <bitset>
#include <sstream>

using namespace std;


void Simulation::run(ifstream& file, int& totalUsedFrames) {
    //all the frames in memory are created here
    vector<Frame> allFrames;
    for (int i = 0; i < NUM_FRAMES) {
        Frame frame;
        allFrames.push_back(frame);
    }

    Simulation::frames = allFrames;

    int pid;
    bitset<16> address;
    string line;

    while(!file.eof()) {
        stringstream loop;
        getline(file, line);
        loop << line;
        //first entry is pid, second entry is memory access
        loop >> pid;
        loop >> address;
        cout << "pid: " << pid << "\taddress: " << address << endl;
    }
}


char Simulation::performMemoryAccess(const VirtualAddress& address) {
    //use virtual address to get page number of process (use the pid)
    //bool fault = !page in memory
    //if fault handlePageFault
    //find physical address
    //get char from offset
    //if verbose print(fault, physcial, rss)
    //return char




    return 0;
}


void Simulation::handlePageFault(Process* process, size_t page) {
    //if the process has no more free frames release one depending on replacement strategy
    if (process->get_rss() == flags.max_frames) {
        size_t pageNum;
        if (flags.strategy == ReplacementStrategy::FIFO) {
            pageNum = process->page_table.get_oldest_page();
        }
        else {
            pageNum = process->page_table.get_least_recently_used_page();
        }
        //now that we know the page num, we find this page in the frame and replace it
        for (int i = 0; i < NUM_FRAMES; i++) {
            if (frames[i].process == process && frames[i].page_number == pageNum) {
                frames[i].set_page(process, page);
                //changed frame to new page, no need to add to an empty frame with code below
                return;
            }
        }
    }

    //find the first free frame
    //only executed if there were free frames left for process
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i].process == nullptr) {
            //place page at free frame, then break
            frames[i].set_page(process, page);
            break;
        }
    }
}

void Simulation::printAccess(bool fault, PhysicalAddress& address, int rss) {
    if (fault) {
        cout << "  -> PAGE FAULT\n";
    }
    else {
        cout << "  -> IN MEMORY\n";
    }
    cout << "  -> physical address " << address << endl;
    cout << "  -> RSS: " << rss << endl << endl;
}
