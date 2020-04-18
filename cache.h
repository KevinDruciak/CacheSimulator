//Kevin Druciak kdrucia1
#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstdint>

class Cache {
 private:
  std::vector<std::vector<uint32_t>> dirty;
  std::vector<std::vector<uint32_t>> valid;
  std::vector<std::vector<uint32_t>> lru;
  std::vector<std::vector<uint32_t>> cache;

 public:
  Cache(uint32_t numSets, uint32_t numBlocks);
  
  uint32_t getCache(uint32_t i, uint32_t j);
  uint32_t getValid(uint32_t i, uint32_t j);
  uint32_t getLRU(uint32_t i, uint32_t j);
  uint32_t getDirty(uint32_t i, uint32_t j);
  
  void setCache(uint32_t i, uint32_t j, uint32_t val);
  void setValid(uint32_t i, uint32_t j, uint32_t val);
  void setLRU(uint32_t i, uint32_t j, uint32_t val);
  void setDirty(uint32_t i, uint32_t j, uint32_t val);
};

#endif
