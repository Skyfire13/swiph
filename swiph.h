#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

#define MEM_SIZE 64
#define REG_NUM 12
#define PROG_ENTRY 16

#define PC mem[0]
#define FL mem[1]
#define AC mem[2]
#define RO mem[3]
#define RA mem[4]
#define RB mem[5]
#define RC mem[6]
#define RD mem[7]
#define RE mem[8]
#define RF mem[9]
#define RG mem[10]
#define RH mem[11]

#define DEST_REG mem[mem[PC+1]]
#define SRC_REG mem[mem[PC+2]]

