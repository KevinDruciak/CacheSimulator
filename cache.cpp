//Kevin Druciak kdrucia1
#include "cache.h"

#include <cstdint>

Cache::Cache(uint32_t numSets, uint32_t numBlocks) {
  dirty.resize(numSets);
  valid.resize(numSets);
  lru.resize(numSets);
  cache.resize(numSets);
  for (uint32_t i = 0; i < numSets; i++) {
    dirty[i].resize(1 + numBlocks);
    valid[i].resize(1 + numBlocks);
    lru[i].resize(1 + numBlocks);
    cache[i].resize(1 + numBlocks);
    for (uint32_t j = 1; j < numBlocks + 1; j++) {
      dirty[i][j] = 0;
      valid[i][j] = 0;
      lru[i][j] = 0;
      cache[i][j] = 0;
    }
  }
}

uint32_t Cache::getCache(uint32_t i, uint32_t j) {
  return cache[i][j];
}

uint32_t Cache::getValid(uint32_t i, uint32_t j) {
  return valid[i][j];
}

uint32_t Cache::getLRU(uint32_t i, uint32_t j) {
  return lru[i][j];
}

uint32_t Cache::getDirty(uint32_t i, uint32_t j) {
  return dirty[i][j];
}

void Cache::setCache(uint32_t i, uint32_t j, uint32_t val) {
  cache[i][j] = val;
}

void Cache::setValid(uint32_t i, uint32_t j, uint32_t val) {
  valid[i][j] = val;
}

void Cache::setLRU(uint32_t i, uint32_t j, uint32_t val) {
  lru[i][j] = val;
}

void Cache::setDirty(uint32_t i, uint32_t j, uint32_t val) {
  dirty[i][j] = val;
}
