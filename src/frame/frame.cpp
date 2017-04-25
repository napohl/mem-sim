/**
 * This file contains implementations for methods in the Frame class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "frame/frame.h"

using namespace std;


void Frame::set_page(Process* process, size_t page_number) {
    if (process->is_valid_page(page_number)) {
        contents = process->pages[page_number];
    }
    else {
        contents = nullptr;
    }
    Frame::process = process;
    Frame::page_number = page_number;
}
