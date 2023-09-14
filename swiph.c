/*

swiph.c - Sorta-working-interpreter, please help

- jump to special spot(memory address stored in register)
- Ability for parser to pass over comments
- A way to save a memory state
- Add argument flags to do things like dump the system memory after tokenizing

I don't know enough about computers to know what to call this,
but it would be nice to have a sway to store the current state
of the "cpu" and load it again later. A command linux keyboard to store registers
and memory into a file that could be loaded later would be nice.

Probably not on this version, but a way to index where each instruction
starts instead of just keeping track in memory. Probably another hash
that just includes the instruction number and it's position in memory

Memory Layout:
0-31 -> Internal State
32-x -> Program
x-y  -> RAM..or whatever you call it

*/

#include "swiph.h"

/* initialize program memory */
int mem[MEM_SIZE];

/* prints all registers in a readable format */
void reg_dump(void) {
    printf("┏━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┓\n");
    printf("┃ ra ┃ rb ┃ rc ┃ rd ┃ re ┃ rf ┃ rg ┃ rh ┃\n");
    printf("┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃\n",\
            RA, RB, RC, RD, RE, RF, RG, RH);
    printf("┣━━━━╋━━━━╋━━━━╋━━━━╋━━━━┻━━━━┻━━━━┻━━━━┛\n");
    printf("┃ PC ┃ FL ┃ AC ┃ RO ┃\n");
    printf("┃ %02d ┃ %02d ┃ %02d ┃ %02d ┃\n",\
            PC, FL, AC, RO);
    printf("┗━━━━┻━━━━┻━━━━┻━━━━┛\n");
}

/* empties all general purpose registers */
void reg_empty(void) {
    for(int i = 0; i < REG_NUM; i++) {
        mem[i] = 0;
    }
}

/* prints memory to the screen */
void mem_dump(void) {
    for(int i = 0; i < MEM_SIZE; i++) {
        printf("%02d %02d\n", i, mem[i]);
    }
}

/* sets all memory to 0 */
void mem_empty(void){
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
		printf("Couldn't open %s. Exiting...\n", program);
        return 0;
	}

    // int comment_mode = 0;

    int i = 0;
    while (fscanf(file, "%s", word) != EOF) {

        if(comment_mode) {
            if() {

            }
        }
        
        // load integers directly into memory
        if(valid_int(word)) {
            mem[i+PROG_ENTRY] = atoi(word);
            i++;
            continue;
        }
       
        // load tranlated integer token into memory
        mem[i+PROG_ENTRY] = t_match(word);
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


    // load passed program into memory
    mem_load(argv[1]);

    // initialize program counter to the program entry point
    PC = PROG_ENTRY;

    while(PC <= MEM_SIZE) {
        switch(mem[PC]) {
            // HLT
            case 0:
                return 0;
                break;
            // LDI
            case 1:
                // Register Operand 1 = Immediate Operand 2
                mem[mem[PC+1]] = mem[PC+2];
                PC += 3;
                continue;
            // INC
            case 2:
                mem[mem[PC+1]]++;
                PC += 2;
                continue;
            // DEC
            case 3:
                mem[mem[PC+1]]--;
                PC += 2;
                continue;
            // ADD
            case 4:
                RO = mem[mem[PC+1]] + mem[mem[PC+2]];
                PC += 3;
                continue;
            // SUB
            case 5:
                RO = mem[mem[PC+1]] - mem[mem[PC+2]];
                PC += 3;
                continue;
            // MOV
            case 6:
                mem[mem[PC+1]] = mem[mem[PC+2]];
                mem[mem[PC+2]] = 0;
                PC += 3;
                continue;
            // CPY
            case 7:
                mem[mem[PC+1]] = mem[mem[PC+2]];
                PC += 3;
                continue;
            // JMP
            case 8:
                PC = mem[PC+1]+PROG_ENTRY;
                continue;
            // JNZ
            case 9:
                if(mem[mem[PC+2]] != 0) {
                    PC = mem[PC+1]+PROG_ENTRY;
                } else {
                    PC += 3;
                }
                continue;
            // SWI
            case 10:
                mem[mem[PC+1]] = mem[mem[PC+1]] + mem[mem[PC+2]];
                mem[mem[PC+2]] = mem[mem[PC+1]] - mem[mem[PC+2]];
                mem[mem[PC+1]] = mem[mem[PC+1]] - mem[mem[PC+2]];
                PC += 3;
                break;
            // SAV - saves memory to a text file
            case 11:
                FILE* snapshot;
                snapshot = fopen("snapshot.sav", "w");
                for(int i = 0; i < MEM_SIZE; i++) {
                    // fprintf(snapshot, "%02d -> %02d\n", i, mem[i]);
                    fprintf(snapshot, "%d\n", mem[i]);
                }
                fclose(snapshot);
                PC += 1;
                break;
            // PRI
            case 12:
                printf("%d\n", mem[mem[PC+1]]);
                PC += 2;
                break;
            default:
                printf("Fatal Error! Token not recognized. Exiting program...\n");
                return 0;
        } // End of  switch statement
    } // End of instruction loop

    return 0;
}

