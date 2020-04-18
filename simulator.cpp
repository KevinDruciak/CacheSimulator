//Kevin Druciak kdrucia1
#include "variables.h"
#include "simulator.h"
#include "cache.h"

#include <math.h>
#include <iostream>
#include <cstdio>

using std::cin;
using std::hex;

bool findBlockFIFO(Cache& cache, uint32_t numBlocks, uint32_t curSet, uint32_t tag) {
  for (uint32_t i = 1; i < numBlocks + 1; i++) {
    if (cache.getCache(curSet, i) == tag && cache.getValid(curSet, i) == 1) {
      return true;
    }
  }
  return false;
}
uint32_t findBlockLRU(Cache& cache, uint32_t numBlocks, uint32_t curSet, uint32_t tag, bool& found) {
  for (uint32_t i = 1; i < numBlocks + 1; i++) {
    if (cache.getCache(curSet, i) == tag && cache.getValid(curSet, i) == 1) {
      found = true;
      return i;
    }
  }
  found = false;
  return 1;
}

uint32_t getLRU(Cache& cache, uint32_t numBlocks, uint32_t curSet, uint32_t time) {
  uint32_t min = time;
  uint32_t LRU = 1;
  for (uint32_t i = 1; i < numBlocks + 1; i++) {
    if (cache.getLRU(curSet, i) < min) {
      min = cache.getLRU(curSet, i);
      LRU = i;
    }
  }
  return LRU;
}

void lruExecute(Cache& cache, uint32_t curSet, uint32_t tag, bool found, uint32_t hit, uint32_t LRU, char access, uint32_t numBytes, uint32_t time, int variation) {
  if (!found) {
    if (access == 'l') {
      cache.setCache(curSet, LRU, tag);
      cache.setValid(curSet, LRU, 1);
      cache.setLRU(curSet, LRU, time);
      totalCycles += numBytes / 4 * 100 + 1;
      totalLoads++;
      loadMisses++;
    } else {
      if (variation == 1) {
	cache.setCache(curSet, LRU, tag);
	cache.setValid(curSet, LRU, 1);
	cache.setLRU(curSet, LRU, time);
	totalCycles += numBytes / 4 * 100 + 100;
	totalStores++;
	storeMisses++;
      } else if (variation == 2) {
	storeMisses++;
	totalCycles += 100;
	totalStores++;
      }
    }
  } else {
    if (access == 'l') {
      cache.setLRU(curSet, hit, time);
      loadHits++;
      totalCycles++;
      totalLoads++;
    } else {
      cache.setLRU(curSet, hit, time);
      storeHits++;
      totalCycles += 100;
      totalStores++;
    }
  }
}

void fifoExecute(Cache& cache, uint32_t curSet, uint32_t tag, char access, uint32_t numBytes, int variation, uint32_t numBlocks) {
  int temp = cache.getCache(curSet, 0);
  if (!findBlockFIFO(cache, numBlocks, curSet, tag)) {
    if (access == 'l') {
      loadMisses++;
      cache.setCache(curSet, temp + 1, tag);
      cache.setValid(curSet, temp + 1, 1);
      cache.setCache(curSet, 0, (temp + 1) % numBlocks);	
      totalCycles += numBytes / 4 * 100 + 1;		     
      totalLoads++;
    } else {
      if (variation == 1) {
	cache.setCache(curSet, temp + 1, tag);
	cache.setValid(curSet, temp + 1, 1);
	cache.setCache(curSet, 0, (temp + 1) % numBlocks);
	totalCycles += numBytes / 4 * 100 + 100;
	totalStores++;
	storeMisses++;
      } else if (variation == 2) {
	totalCycles += 100;
	totalStores++;
	storeMisses++;
      }
    }
  } else {
    if (access == 'l') {
      loadHits++;
      totalCycles++;
      totalLoads++;
    } else {
      storeHits++;
      totalCycles += 100;
      totalStores++;
    }
  }
}

void runSimulator(Cache cache, uint32_t offset, uint32_t index, uint32_t numBlocks, uint32_t numBytes) {
  char access;
  uint32_t address;
  uint32_t padding;
  uint32_t time = 1;
  while (cin >> access) {
    cin >> hex >> address;
    cin >> padding;    
    uint32_t tag = address >> (offset + index);
    uint32_t curSet = (address >> offset) & (uint32_t)(pow(2, index) - 1);
    if (writeAllocate) {
      if (writeThrough) {
	if (lru) {
	  bool found = true;
	  uint32_t hit = findBlockLRU(cache, numBlocks, curSet, tag, found);
	  uint32_t LRU = getLRU(cache, numBlocks, curSet, time);
	  lruExecute(cache, curSet, tag, found, hit, LRU, access, numBytes, time, 1);
	  time++;
	} else if (fifo) {
	  fifoExecute(cache, curSet, tag, access, numBytes, 1, numBlocks);
	}
      } else if (writeBack) {
	if (lru) {
	  bool found = true;
	  uint32_t hit = findBlockLRU(cache, numBlocks, curSet, tag, found);
	  uint32_t LRU = getLRU(cache, numBlocks, curSet, time);
	  lruExecute(cache, curSet, tag, found, hit, LRU, access, numBytes, time, 1);
	  time++;
	} else if (fifo) {
	  fifoExecute(cache, curSet, tag, access, numBytes, 1, numBlocks);
	}	  
      }
    } else if (noWriteAllocate) {
      if (writeThrough) {
	if (lru) {
	  bool found = true;
	  uint32_t hit = findBlockLRU(cache, numBlocks, curSet, tag, found);
	  uint32_t LRU = getLRU(cache, numBlocks, curSet, time);
	  lruExecute(cache, curSet, tag, found, hit, LRU, access, numBytes, time, 2);
	  time++;
	} else if (fifo) {
	  fifoExecute(cache, curSet, tag, access, numBytes, 2, numBlocks);
	}
      } else if (writeBack) {
	exit(1);
      }
    }
  }
}
