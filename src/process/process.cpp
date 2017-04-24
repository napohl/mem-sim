/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
    char c;
    int totalSize = 0;
    vector<Page*> inputPages;

    while (in.get(c)) {
        Page* page = Page::read_from_input(in);
        inputPages.push_back(page);
        totalSize += page->size();
    }
    Process* process = new Process(totalSize, inputPages);

    //while istream
    //Page = read_from_input
    //add to vector
    //add page size to total size
    //end while
    //make constructor

    return process;
}


size_t Process::size() const {
    return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
    // TODO: implement me
    return false;
}

//i don't know what resident set size is yet
size_t Process::get_rss() const {
    // TODO: implement me
    return 0;
}


double Process::get_fault_percent() const {
    if (memory_accesses == 0) {
        return 0;
    }
    double val = page_faults / memory_accesses;
    //multiply by 100 to get percentage
    return val * 100;
}
