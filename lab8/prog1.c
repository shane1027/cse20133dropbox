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

int main()
{
    char * read_music(const char *file, int * SIZE);
    double time_music(char * music_data, int array_length);
    char * music_data;
    const char FILENAME[] = "song.music";
    int i = 0, length = 0, catch;
    double time;

    // read in file using function read_music
    music_data = read_music(FILENAME, &length);
    if (music_data == NULL) {
        printf("error 1\n");
    }

    for (i = 0; i < length; i++) {
        printf("\n%c", music_data[i]);
    }
    
    // calculate the length (in seconds) of the music
    time = time_music(music_data, length);
    if (time == 0) {
        printf("error2\n");
    }
    
    printf("\n%lf", time);

    // now pass music data to decoding / writing function
    // catch = write_music(music_data, &length);

    printf("\n");

    free(music_data);
    return 0;
}


/***************************************
 * Author: Shane Ryan
 * Name: read_music
 * Purpose: read length of .music file,
 * allocate an array of proper length
 * to store it, then read it in.
 * Input: const char FILENAME, pointer
 * to access array, pointer to size
 * Output: pointer to created array
 * ************************************/

char * read_music(const char *file, int * SIZE)
{
    int j = 0;
    FILE * music;
    char * music_data;
    char current_char;

    // open file and return error if not found
    music = fopen(file, "r");
    if (music == NULL) {
        printf("File not found.\n");
        return NULL;
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
            *SIZE = *SIZE + 1; 
        }
    }

    // printf("%d\n", SIZE); // remove after debugging

    // now we can allocate an array to store the music data efficiently
    // (in terms of memory)
    music_data = calloc(*SIZE, sizeof(char));

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
            // printf("\n%c", music_data[j]);
            j++;
        }
    }

    // printf("\n");
    
    // always free memory and close files!!
    fclose(music);
    // free(music_data);
    // don't free it when we still need it elsewhere^^
    // free at end of main function though

    return music_data;
}


/***************************************
 * Author: Shane Ryan
 * Name: time_music
 * Purpose: read length of music in 
 * seconds.,
 * Input: char[]
 * Output: int length
 * ************************************/

double time_music(char * music_data, int array_length)
{
    int i;
    double time = 0, delta_time;
    

    for (i = 0; i < array_length; i++) {
        switch (music_data[i])
        {
            case 'a':
                time = time + delta_time;
                break;
            case 'A':
                time = time + delta_time;
                break;
            case 'b':
                time = time + delta_time;
                break;
            case 'B':
                time = time + delta_time;
                break;
            case 'c':
                time = time + delta_time;
                break;
            case 'C':
                time = time + delta_time;
                break;
            case 'd':
                time = time + delta_time;
                break;
            case 'D':
                time = time + delta_time;
                break;
            case 'e':
                time = time + delta_time;
                break;
            case 'E':
                time = time + delta_time;
                break;
            case 'f':
                time = time + delta_time;
                break;
            case 'F':
                time = time + delta_time;
                break;
            case 'g':
                time = time + delta_time;
                break;
            case 'G':
                time = time + delta_time;
                break;
            case '.':
                time = time + delta_time;
                break;
            case 1:
                delta_time = 2;
                break;
            case 2:
                delta_time = 1;
                break;
            case 4:
                delta_time = .5;
                break;
            case 8:
                delta_time = .25;
                break;
            case 6:
                delta_time = .15;
                break;
        }
    }

        return time;
}
