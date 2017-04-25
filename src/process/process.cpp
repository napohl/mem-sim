/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
    char c;
    size_t totalSize = 0;
    vector<Page*> inputPages;

    while (true) {
        Page* page = Page::read_from_input(in);
        //if the datastream is empty, we will get back a nullptr
        if (page == nullptr) {
            break;
        }
        inputPages.push_back(page);
        totalSize += page->size();
    }
    Process* process = new Process(totalSize, inputPages);

    return process;
}


size_t Process::size() const {
    return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
    if (index >= pages.size()) {
        return false;
    }
    else {
        return true;
    }
}

size_t Process::get_rss() const {
    return page_table.get_present_page_count();
}


double Process::get_fault_percent() const {
    if (memory_accesses == 0) {
        return 0;
    }
    double val = (double) page_faults / (double) memory_accesses;
    //multiply by 100 to get percentage
    return val * 100;
}
