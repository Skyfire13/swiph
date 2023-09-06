/* Op_map structure for int token lookup */
typedef struct T_map{
    char word[10];
    int int_token;

} T_map;

/* Hash of opcodes and their corresponding integers */
struct T_map t_map[] = {
    {"hlt",  0},
    {"ldi",  1},
    {"inc",  2},
    {"dec",  3},
    {"add",  4},
    {"sub",  5},
    {"mov",  6},
    {"cpy",  7},
    {"jmp",  8},
    {"jnz",  9},
    {"swi", 10},
    {"sav", 11},
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
}

int valid_int(char* str) {
    while(*str) {
        if(!isdigit(*str)) {
            return 0;
        } else {
            ++str;
        }
    }
    return 1;
}


