/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <sstream>

using namespace std;


string PhysicalAddress::to_string() const {
    stringstream stream;
    stream << frame << offset;
    return stream.str();
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
    //stringstream stream;
    //stream << frame << offset << " [frame: " << frame << "; offset: " << offset << "]";
    return out;
}
