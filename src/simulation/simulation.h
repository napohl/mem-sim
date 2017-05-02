/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "virtual_address/virtual_address.h"
#include "flag_parser/flag_parser.h"
#include "physical_address/physical_address.h"
#include <cstdlib>
#include <fstream>
#include <vector>


/**
 * Class responsible for running the memory simulation.
 */
class Simulation {
// PUBLIC CONSTANTS
public:

  /**
   * The maximum number of frames in the simulated system (512).
   */
  static const size_t NUM_FRAMES = 512;

// PUBLIC API METHODS
public:

  /**
   * Constructor
   */
  Simulation(FlagOptions flags, std::vector<int> pids, std::vector<Process*> processes, std::vector<Frame> frames) : flags(flags), pids(pids), processes(processes), frames(frames) {}

  /**
   * Runs the simulation.
   */
  void run(std::ifstream& file, int& totalUsedFrames);

// PRIVATE METHODS
private:

  /**
   * Performs a memory access for the given virtual address, translating it to
   * a physical address and loading the page into memory if needed. Returns the
   * byte at the given address.
   */
  char performMemoryAccess(const VirtualAddress& address);

  /**
   * Handles a page fault, attempting to load the given page for the given
   * process into memory.
   */
  void handlePageFault(Process* process, size_t page);

  /**
   * Helper function to print out details when verbose flag is set.
   * Fault is used to determine if it should print a page fault or in memory
   * RSS is passed from the process that is being accessed to show the RSS of the process
   */
  void printAccess(bool fault, PhysicalAddress& address, int rss);

// INSTANCE VARIABLES
private:

  FlagOptions flags;
  std::vector<int> pids;
  std::vector<Process*> processes;
  std::vector<Frame> frames;

};
