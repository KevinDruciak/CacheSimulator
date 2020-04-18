//Kevin Druciak kdrucia1

#include "functions.h"
#include "variables.h"
#include "simulator.h"

#include <cstdio>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {
  uint32_t numSets;
  uint32_t numBlocks;
  uint32_t numBytes;

  if (!parseParameters(argc, argv, numSets, numBlocks, numBytes)) {
    return 1;
  }
  
  uint32_t offset = log2(numBytes);
  uint32_t index = log2(numSets);
  
  Cache cache(numSets, numBlocks);
  runSimulator(cache, offset, index, numBlocks, numBytes);
  displayStatistics();
  return 0; 
}
 
