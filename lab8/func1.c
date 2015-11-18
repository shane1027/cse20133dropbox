#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#define FILENAME "song.music"

int main()
{
    int i = 0;
    int SIZE = 0;
    FILE * music;
    char * music_data;

    music = fopen(FILENAME, "r");
    if (music == NULL) {
        printf("File not found.\n");
        return EXIT_FAILURE;
    }

    while (fgetc(music) != EOF) {
       i++; 
    }

    music_data = calloc(SIZE, sizeof(char));

    for (i=0; i<SIZE; i++) {
        printf("\n%d", music_data[i]);
    }

    printf("\n");

    return 0;
}
