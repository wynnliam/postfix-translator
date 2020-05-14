// Liam Wynn, 5/14/2020, Stack Machine

#include "./program.h"

#define MAX_INSTRUCTIONS	1000

static struct instruction program[MAX_INSTRUCTIONS];
static int num_instructions = 0;

// Program counter - keeps track of the current instruction we
// are on. Needed for control flow instructions.
static int pc = 0;
