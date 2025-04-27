#include <stdio.h>
#include <ctype.h>

typedef struct {
    int lines;
    int words;
    int characters;
} Stats;

Stats count_file_stats(const char *filename) {
    Stats stats = {0, 0, 0};
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return stats;
    }

    char ch;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        stats.characters++;

        if (ch == '\n')
            stats.lines++;

        if (isspace(ch))
            in_word = 0;
        else if (in_word == 0) {
            stats.words++;
            in_word = 1;
        }
    }

    fclose(file);
    return stats;
}

void save_stats(const char *filename, Stats stats) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot create output file %s\n", filename);
        return;
    }

    fprintf(file, "Lines: %d\n", stats.lines);
    fprintf(file, "Words: %d\n", stats.words);
    fprintf(file, "Characters: %d\n", stats.characters);

    fclose(file);
}

int main() {
    char input_file[100];
    char output_file[100];

    printf("Enter input file name: ");
    scanf("%s", input_file);

    Stats stats = count_file_stats(input_file);

    printf("\nFile Statistics:\n");
    printf("Lines: %d\n", stats.lines);
    printf("Words: %d\n", stats.words);
    printf("Characters: %d\n", stats.characters);

    printf("\nEnter output file name to save statistics: ");
    scanf("%s", output_file);

    save_stats(output_file, stats);

    return 0;
}
