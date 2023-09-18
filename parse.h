/* Op_map structure for int token lookup */
typedef struct T_map{
    char word[10];
    int int_token;

} T_map;

/* Hash of opcodes and their corresponding integers */
/* could you use a certain type of number to ensure "type safety" for integer
 * token? For example, EVEN numbers for registers and memory locations and
 * ODD numbers for opcodes. Or maybe just add an extra data type to the
 * T_map struct.*/
struct T_map t_map[] = {
    {"hlt",  0}, /* Halt - Stops the program */
    {"ldi",  1}, /* Load Immediate - Loads an immediate into a register  */
    {"inc",  2}, /* Increment - Increments the destination register */
    {"dec",  3}, /* Decrement - Decrements the destination register */
    {"add",  4}, /* Add - Adds two registers together and stores the result in the output register */
    {"sub",  5}, /* Substract - Subtracts two registers together and stores the result in the output register */
    {"mov",  6}, /* Move - Sets destination to source register then clears source regsiter */
    {"cpy",  7}, /* Copy - Sets destination to source register */
    {"jmp",  8}, /* Jump - Sets program counter to source */
    {"jnz",  9}, /* Jump Not Zero */
    {"swi", 10}, /* Switch - Switches the value of two registers */
    {"sav", 11}, /* Save - Saves memory state of program to a text file */
    {"pri", 12}, /* Print - Prints register to the screen */
    {"str", 13}, /* Store Register -  */
    {"sti", 14}, /* Store Immediate */
    {"pc",   0}, 
    {"fl",   1}, 
    {"ac",   2}, 
    {"ro",   3}, 
    {"ra",   4}, 
    {"rb",   5}, 
    {"rc",   6}, 
    {"rd",   7}, 
    {"re",   8}, 
    {"rf",   9}, 
    {"rg",  10}, 
    {"rh",  11}  
};

/* Takes an opcode string and returns it's corresponding integer */
int t_match(char* str) {
    for(int i = 0; i < sizeof(t_map); i++) {
        if(strcmp(t_map[i].word, str) == 0) {
            return(t_map[i].int_token);
        }
    }

    return 0;
}

int valid_int(char* str) {
    while(*str) {
        if(!isdigit(*str)) {
            return 0;
        } else {
            str++;
        }
    }
    return 1;
}


