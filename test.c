#include <stdio.h>

#define MEM_SIZE 25

char mem[MEM_SIZE];

void load_memory() {
    FILE* file = fopen("asm/jnz", "r");
    char buff[20];

    int i = 0;
    while(fscanf(file, "%s", buff) != EOF) {
        mem[i] = i*2;
        i++;
    }

    fclose(file);
}

void save_memory() {
    FILE* file = fopen("asm/mem_jnz", "wb");

    for(int i = 0; i < MEM_SIZE; i++) {
        fwrite(mem, sizeof(char), MEM_SIZE, file);
    }

    fclose(file);
}

int main() {
    
    load_memory();

    for(int i = 0; i < MEM_SIZE; i++) {
        printf("%d", mem[i]);
    }

    save_memory();

    return 0;
}


