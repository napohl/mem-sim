/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"
#include <string>
#include <bitset>

using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
    string pageStr = address.substr(0, 10);
    string offsetStr = address.substr(10, 6);
    int pageInt = stoi(pageStr, nullptr, 2);
    int offsetInt = stoi(offsetStr, nullptr, 2);
    return VirtualAddress(process_id, pageInt, offsetInt);
}


string VirtualAddress::to_string() const {
    string address;
    //page is 10 bits
    bitset<10> pageBit(page);
    //offset is 6 bits
    bitset<6> offsetBit(offset);
    address = pageBit.to_string() + offsetBit.to_string();
    return address;
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
    out << "PID " << address.process_id << " @ " << address.to_string() << " [page: " << address.page << "; offset: " << address.offset << "]";
    return out;
}
