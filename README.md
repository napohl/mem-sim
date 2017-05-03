Nathan Pohl

# Project 3

A simulation of a trival OS memory manager.

List of files:
main: Takes input flags, runs basic IO and runs simulation
simulation: handles the simulation, making memory swaps, maintaining frames and updating processes
flag_parser: helper functions to handle flag inputs and arguments
frame: component of main memory, holds a page of a process
page: piece of a process, contains the data of the process
page_table: holds data on which pages of a process are in memory, and when each one was loaded or 	last accessed
physical_address: contains the physical address of the byte being accessed (in main memory)
process: contains a page table and pages of itself, which get put into main memory
virtual_address: virtual address of the process on disk

I probably put 12 hours into this project.

Belady's anomaly is the phenomenon where given a specific sequence of pages to access, when the number of available frames is increased, the number of page faults increases along with it. Using the file I have provided, "sim.txt", you can see this happen when maxing out the frame limit at 3, and then at 4. With a frame limit of 3, the pages being accessed will result in 9 page faults. With a frame limit of 4, the number of page faults goes up to 10.

This anomaly happens because when we increase the number of pages we have available, recently requested pages can stay at the bottom of the FIFO queue longer, because the order the items would be removed has changed. This can create a scenario where additional page faults occur because of a suboptimal ordering of page accesses.