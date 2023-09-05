#include <stdio.h>

#define MEM_SIZE 5

#define itoc(n) n + 48

int mem[MEM_SIZE] = {5, 2, 3, 9, 7};

void mem_snapshot() {
    FILE* file;

    file = fopen("mem_snapshot.txt", "w");

    for(int i; i < MEM_SIZE; i++) {
        fprintf(file, "%c", mem[i] + 48);
    }

    fclose(file);
}

int main() {

    mem_snapshot();

    return 0;
}


