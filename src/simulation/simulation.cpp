/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"

using namespace std;


void Simulation::run(FlagOptions flags, ifstream file, int& totalUsedFrames) {
    // TODO: implement me
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
    // TODO: implement me
    return 0;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
    // TODO: implement me
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
