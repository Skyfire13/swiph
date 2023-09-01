/*

swiph.c - Sorta-working-interpreter, please help

Implement:
STR - Store value in memory
LOD - Load value from memory into register
SWI - Switch the vaue of two registers

- Some sort of print function
- A way to save a memory state

Probably not on this version, but a way to index where each instruction
starts instead of just keeping track in memory. Probably another hash
that just includes the instruction number and it's position in memory

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.c"

#define MEM_SIZE 32
#define REG_NUM 12

#define PC reg[8]
#define FL reg[9]
#define AC reg[10]
#define RO reg[11]


/* initialize program memory */
int mem[MEM_SIZE];
int reg[REG_NUM];


/* prints all registers in a readable format */
void reg_dump() {
    printf("┏━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┓\n");
    printf("┃ ra ┃ rb ┃ rc ┃ rd ┃ re ┃ rf ┃ rg ┃ rh ┃\n");
    printf("┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃\n",\
            reg[0], reg[1], reg[2], reg[3],
            reg[4], reg[5], reg[6], reg[7]);
    printf("┣━━━━╋━━━━╋━━━━╋━━━━╋━━━━┻━━━━┻━━━━┻━━━━┛\n");
    printf("┃ PC ┃ FL ┃ AC ┃ RO ┃\n");
    printf("┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃\n",\
            PC, reg[9], reg[10], reg[11]);
    printf("┗━━━━┻━━━━┻━━━━┻━━━━┛\n");
}


/* empties all general purpose registers */
void reg_empty() {
    for(int i = 0; i < REG_NUM; i++) {
        reg[i] = 0;
    }
}


/* prints memory to the screen */
void mem_dump() {
    for(int i = 0; i < MEM_SIZE; i++) {
        printf("%d\n", mem[i]);
    }
}


/* prints memory to the screen, stops when PC hits zeros */
void mem_dump_filled() {
    int zeros = 0;
    for(int i = 0; i < MEM_SIZE; i++) {
        // Stop printing after 5 zeros in a row
        if(zeros > 5) {
            break;
        }
        if(mem[i] == 0) {
            zeros++;
        } else {
            zeros = 0;
        }

        //printf("0x%02x -> 0x%02x\n", i, mem[i]);
        printf("%02d -> %02d\n", i, mem[i]);
    }
}


/* sets all memory to 0 */
void mem_empty(){
    for(int i = 0; i < MEM_SIZE; i++) {
        mem[i] = 0;
    }
}

/* loads the program into memory */
void mem_load(char* program) {

    // clear memory
    mem_empty();

    // char filename[] = "asm/add";
	FILE* file;
	char word[20];

	file = fopen(program, "r");

	if (NULL == file) {
		printf("%s can't be opened\n", program);
        return;
	}

    int i = 0;
    while (fscanf(file, "%s", word) != EOF) {
        
        // load integers directly into memory
        if(valid_int(word)) {
            mem[i] = atoi(word);
            i++;
            continue;
        }
       
        // load tranlated integer token into memory
        mem[i] = t_match(word);
        i++;
    }

	// close file
	fclose(file);
}

int main(int argc, char* argv[]) {

    if(argc == 1) {
        printf("You gotta give me a file chief. Exiting...\n");
        exit(1);
    }

    // initialize registers to 0
    reg_empty();

    // load passed program into memory
    mem_load(argv[1]);

    while(PC < MEM_SIZE) {
        switch(mem[PC]) {
            // HLT
            case 0:
                reg_dump();
                exit(1);
                break;
            // LDI
            case 1:
                reg[mem[PC+1]] = mem[PC+2];
                PC += 3;
                continue;
            // INC
            case 2:
                reg[mem[PC+1]]++;
                PC += 2;
                continue;
            // DEC
            case 3:
                reg[mem[PC+1]]--;
                PC += 2;
                continue;
            // ADD
            case 4:
                RO = reg[PC+1] + reg[PC+2];
                reg[11] = reg[mem[PC+1]] + reg[mem[PC+2]];
                PC += 3;
                continue;
            // SUB
            case 5:
                reg[11] = reg[mem[PC+1]] - reg[mem[PC+2]];
                PC += 3;
                continue;
            // MOV
            case 6:
                reg[mem[PC+1]] = reg[mem[PC+2]];
                reg[mem[PC+2]] = 0;
                PC += 3;
                continue;
            // CPY
            case 7:
                reg[mem[PC+1]] = reg[mem[PC+2]];
                PC += 3;
                continue;
            // JMP
            case 8:
                PC = mem[PC+1];
                continue;
            // JNZ
            case 9:
                if(reg[mem[PC+2]] != 0) {
                    PC = mem[PC+1];
                } else {
                    PC += 3;
                }
                continue;
            default:
                printf("Fatal Error! Token not recognized. Exiting program...\n");
        } // End of  switch statement
    } // End of instruction loop

    return 0;
}

