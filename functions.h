//Kevin Druciak kdrucia1
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <cstdio>

void displayStatistics();
bool getPolicies(char *argv[]);
bool isPowerTwo(uint32_t x);
bool parseParameters(int argc, char *argv[], uint32_t& ns, uint32_t& nl, uint32_t& nb);

#endif
