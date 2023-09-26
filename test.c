#include <stdio.h>
#include <string.h>

int main(void) {

    FILE* input_file;
    char word[30];

    input_file = fopen("text_file", "r");

    int comment_mode = 0;
    char comment = ';';

    while(fscanf(input_file, "%s", word) != EOF) {

        if(*word == ';' && comment_mode == 0) {
            comment_mode = 1;
        }

        if(*word == ';' && comment_mode == 1) {
            comment_mode = 0;
        }

        if(comment_mode) {
            continue;
        }

        printf("%s -> %d\n", word, comment_mode);
    }


    fclose(input_file);

    return 0;
}
