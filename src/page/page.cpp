/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
    
//    return nullptr;

    char c;
    vector<char> data;

    //
    while (in.get(c)) {
        data.push_back(c);
        if (data.size() == PAGE_SIZE) {
            //if we have hit the page limit, we break. 
            //we can't hold any more data than the page size.
            break;
        }
    }
    if (data.size() == 0) {
        //if there is no data to be added to the page, we return a null pointer
        return nullptr;
    }
    Page* page = new Page(data);
    return page;
}


size_t Page::size() const {
    return bytes.size();
    //return 0;
}


bool Page::is_valid_offset(size_t offset) const {
    bool valid = (offset < size());
    return valid;
}


char Page::get_byte_at_offset(size_t offset) {
    char c = bytes[offset];
    return c;
}
