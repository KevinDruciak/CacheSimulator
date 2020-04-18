//Kevin Druciak kdrucia1

#include "functions.h"
#include "variables.h"

#include <string>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <iostream>

using std::stoul;
using std::cout;
using std::endl;

void displayStatistics() {
  cout << "Total loads: " << totalLoads << endl;
  cout << "Total stores: " << totalStores << endl;
  cout << "Load hits: " << loadHits << endl;
  cout << "Load Misses: " << loadMisses << endl;
  cout << "Store hits: " << storeHits << endl;
  cout << "Store Misses: " << storeMisses << endl;
  cout << "Total cycles: " << totalCycles << endl;
}

bool getPolicies(char *argv[]) {
  bool ret = true;
  strcmp(argv[4], "write-allocate") == 0 ? writeAllocate = true
    : strcmp(argv[4], "no-write-allocate") == 0 ? noWriteAllocate = true 
    : ret = false;
  strcmp(argv[5], "write-through") == 0 ? writeThrough = true
    : strcmp(argv[5], "write-back") == 0 ? writeBack = true
    : ret = false;
  strcmp(argv[6], "lru") == 0? lru = true
    : strcmp(argv[6], "fifo") == 0 ? fifo = true
    : ret = false;
  return ret;
}

bool isPowerTwo(uint32_t x) {
  return (x != 0) && ((x & (x - 1)) == 0);
}

bool parseParameters(int argc, char *argv[], uint32_t& ns, uint32_t& nl, uint32_t& nb) {
  if (argc < 7) {
    return false;
  }

  ns = stoul(argv[1]);
  nl = stoul(argv[2]);
  nb = stoul(argv[3]);
  
  if (!isPowerTwo(ns) || !isPowerTwo(nl) || !isPowerTwo(nb) || nb < 4) {
    return false;
  }
  return getPolicies(argv);
}
