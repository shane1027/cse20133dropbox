/***************************************
 * Author: Shane Ryan
 * Name: prog1.c
 * Purpose: read in a .music file and
 * convert it to a .wav file like a 
 * player piano.
 * ************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#define FILENAME "song.music"

int main()
{
    void read_file(char const FILENAME, char * music_data);
    char * music_data;
    int catch, i = 0;

    catch = read_file(FILENAME, music_data);
    if (catch != 0) {
        printf("error 1\n")
    }

    for (i = 0; i < (sizeof(*music_data)/sizeof(char)); i++) {
        printf("\n%c", music_data[i]);
    }

    return 0;
}


/***************************************
 * Author: Shane Ryan
 * Name: read_file
 * Purpose: read length of .music file,
 * allocate an array of proper length
 * to store it, then read it in.
 * Input: char const FILENAME
 * Output: pointer to created array
 * ************************************/

void read_file(char const FILENAME, char * music_data)
{
    int j = 0;
    int SIZE = 0;
    FILE * music;
    char current_char;

    // open file and return error if not found
    music = fopen(FILENAME, "r");
    if (music == NULL) {
        printf("File not found.\n");
        return EXIT_FAILURE;
    }

    // increment the SIZE variable for every character
    // added: other than whitespace
    while(1) {
        current_char = fgetc(music);
        if (feof(music)) {
            break;
        }
        if (current_char != '\n' && current_char != ' ' &&
                current_char != '\t') {
            SIZE++; 
        }
    }

    printf("%d\n", SIZE); // remove after debugging

    // now we can allocate an array to store the music data efficiently
    // (in terms of memory)
    music_data = calloc(SIZE, sizeof(char));

    // reset where we are in the file, and fill that array up!
    // (note: probably could've combined this while loop with
    // the above one by creating an array and realloc'ing it
    // with every additional character scanned until eof :(
    fseek(music, 0, SEEK_SET);
    while(1) {
        current_char = fgetc(music);
        if (feof(music)) {
            break;
        }
        if (current_char != '\n' && current_char != ' ' &&
                current_char != '\t') {
            music_data[j] = current_char; 
            printf("\n%c", music_data[j]);
            j++;
        }
    }

    printf("\n");
    
    // always free memory and close files!!
    fclose(music);
    // free(music_data);
    // don't free it when we still need it elsewhere^^
    // free at end of main function though

    return 0;
}
