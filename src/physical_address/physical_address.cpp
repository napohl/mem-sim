/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <sstream>
#include <bitset>

using namespace std;


string PhysicalAddress::to_string() const {
    string address;
    //frame is 10 bits, so size is 10 bits
    bitset<10> frameBit(frame);
    //offset is 6 bits, so size is 6 bits
    bitset<6> offsetBit(offset);
    address = frameBit.to_string() + offsetBit.to_string();
    return address;
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
    out << address.to_string() << " [frame: " << address.frame << "; offset: " << address.offset << "]";
    return out;
}
