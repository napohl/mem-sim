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

bool const DEBUG = false;
//used to keep track of when a page was accessed or loaded
int TIME = 0;
//exit program if this is set to true
bool SEGFAULT = false;

int Simulation::run(ifstream& file, int& totalUsedFrames) {
    //all the frames in memory are created here
    vector<Frame> allFrames;
    for (int i = 0; i < NUM_FRAMES; i++) {
        Frame frame;
        allFrames.push_back(frame);
    }

    Simulation::frames = allFrames;

    int pid;
    string addressString;
    string line;

    while(!file.eof()) {
        stringstream loop;
        getline(file, line);
        loop << line;
        //first entry is pid, second entry is memory address
        loop >> pid;
        loop >> addressString;
        
        VirtualAddress address = VirtualAddress::from_string(pid, addressString);

        char value = performMemoryAccess(address);
        if (SEGFAULT == true) {
            return EXIT_FAILURE;
        }

        if (DEBUG) {
            cout << "Char value = " << value << endl << endl;
        }
        TIME++;

    }

    //count how many frames were used
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i].process == nullptr) {
            totalUsedFrames = i;
            break;
        }
    }

    return EXIT_SUCCESS;
}


char Simulation::performMemoryAccess(const VirtualAddress& address) {
    char value;
    int pid = address.process_id;
    size_t page = address.page;
    int frame = 0;
    int offset = address.offset;
    bool fault = false;
    Process* process;
    //iterate through pids to find which entry in processes matches the pid
    for (int i = 0; i < pids.size(); i++) {
        if (pids[i] == pid) {
            process = processes[i];
            break;
        }
    }
    //check if page exists, if not don't try to add it to frame
    if (!process->is_valid_page(page)) {
        SEGFAULT = true;
        value = '0';
    }
    else {

        //if the page is present, there is no fault so we use '!'
        fault = !process->page_table.rows[page].present;
        if (fault) {
            handlePageFault(process, page);
        }
        //find the frame where this process now is
        for (int i = 0; i < NUM_FRAMES; i++) {
            if (frames[i].process == process && frames[i].page_number == page) {
                frame = i;
                break;
            }
        }
        PhysicalAddress physical(frame, offset);
        process->page_table.rows[page].present = true;
        process->page_table.rows[page].last_accessed_at = TIME;
        process->memory_accesses++;


        if (DEBUG) {
            cout << "process page is present? " << process->page_table.rows[page].present << endl;
        }

        if (!SEGFAULT && process->pages[page]->is_valid_offset(offset)) {
            value = frames[frame].contents->get_byte_at_offset(offset);


            if (flags.verbose) {
                cout << address << endl;

                printAccess(fault, physical, process->get_rss());
            }
        }
        //if it not a valid offset, we segfault
        else {
            SEGFAULT = true;

        }

    }

    if (flags.verbose && SEGFAULT) {
        cout << address << endl;
    }



    return value;
}


void Simulation::handlePageFault(Process* process, size_t page) {
    //if the process has no more free frames release one depending on replacement strategy
    process->page_faults++;
    process->page_table.rows[page].loaded_at = TIME;
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
