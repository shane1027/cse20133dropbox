#include <stdio.h>
#include <stdlin.h>
#define FILENAME 'song.music'

int main()
{
    int i = 0;
    int SIZE = 0;
    FILE * music;

    music = fopen(FILENAME, "r");

    while (fget != EOF) {
       i++; 
    }

    music_data = calloc(SIZE, sizeof(char));

    for (i=0; i<SIZE; i++) {
        printf("\n%d", music_data[i]);
    }

    printf("\n");

    return 0;
}
