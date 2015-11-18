#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#define FILENAME "song.music"

int main()
{
    int j = 0;
    int SIZE = 0;
    FILE * music;
    int * music_data;

    music = fopen(FILENAME, "r");
    if (music == NULL) {
        printf("File not found.\n");
        return EXIT_FAILURE;
    }

    while (fgetc(music) != EOF) {
       SIZE++; 
    }
    printf("%d\n", SIZE);

    music_data = calloc(SIZE, sizeof(int));

    for (j=0; j<SIZE; j++) {
        music_data[j] = j;
        printf("\n%d", music_data[j]);
    }

    printf("\n");
    fclose(music);
    free(music_data);

    return 0;
}
