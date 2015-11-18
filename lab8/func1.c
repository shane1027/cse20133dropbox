#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#define FILENAME "song.music"

int main()
{
    int j = 0;
    int SIZE = 0;
    FILE * music;
    char * music_data;

    // open file and return error if not found
    music = fopen(FILENAME, "r");
    if (music == NULL) {
        printf("File not found.\n");
        return EXIT_FAILURE;
    }

    // increment the SIZE variable for every character
    // added: other than whitespace
    while (fgetc(music) != EOF) {
       SIZE++; 
    }
    printf("%d\n", SIZE); // remove after debugging

    // now we can allocate an array to store the music data efficiently
    // (in terms of memory)
    music_data = calloc(SIZE, sizeof(char));

    // remove after debugging, filling array to print
    for (j=0; j<SIZE; j++) {
        music_data[j] = j;
        printf("\n%d", music_data[j]);
    }

    printf("\n");
    
    // always free memory and close files!!
    fclose(music);
    free(music_data);

    return 0;
}
