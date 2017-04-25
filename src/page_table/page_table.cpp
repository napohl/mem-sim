/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
    size_t presentCount = 0;
    for (size_t i = 0; i < rows.size(); i++) {
        if (rows[i].present) {
            presentCount++;
        }
    }
    return presentCount;
}

//fifo
size_t PageTable::get_oldest_page() const {
    size_t oldest = -1;
    size_t index = 0;
    for (size_t i = 0; i < rows.size(); i++) {
        //if the oldest has not been set yet, we set it the first time we see a page present in memory
        if (rows[i].present && oldest == -1) {
            oldest = rows[i].loaded_at;
            index = i;
        }
        else if (rows[i].present && rows[i].loaded_at < oldest) {
            oldest = rows[i].loaded_at;
            index = i;
        }
    }
    return index;
}

//lru
size_t PageTable::get_least_recently_used_page() const {
    size_t oldest = -1;
    size_t index = 0;
    for (size_t i = 0; i < rows.size(); i++) {
        if (rows[i].present && oldest == -1) {
            oldest = rows[i].last_accessed_at;
            index = i;
        }
        else if (rows[i].present && rows[i].last_accessed_at < oldest) {
            oldest = rows[i].last_accessed_at;
            index = i;
        }
    }
    return index;
}
