//Kevin Druciak kdrucia1
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <cstdint>
#include "cache.h"

void lruExecute(Cache& cache, uint32_t curSet, uint32_t tag, bool found, uint32_t hit, uint32_t LRU, char access, uint32_t numBytes, uint32_t time, int variation);
void fifoExecute(Cache& cache, uint32_t curSet, uint32_t tag, char access, uint32_t numBytes, int variation, uint32_t numBlocks);
bool findBlockFIFO(Cache& cache, uint32_t numBlocks, uint32_t curSet, uint32_t tag);
uint32_t findBlockLRU(Cache& cache, uint32_t numBlocks, uint32_t curSet, uint32_t tag, bool& found);
uint32_t getLRU(Cache& cache, uint32_t numBlocks, uint32_t curSet, uint32_t time);
void runSimulator(Cache cache, uint32_t offset, uint32_t index, uint32_t numBlocks, uint32_t numBytes);

#endif
