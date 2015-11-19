/***************************************
 * Author: Shane Ryan
 * Name: prog1.c
 * Purpose: read in a .music file and
 * convert it to a .wav file like a 
 * player piano.
 * ************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "wavfile.h"

int main()
{
    char * read_music(const char *file, int * SIZE);
    double time_music(char * music_data, int array_length, int* notes);
    int write_music(char * music_data, int lenth, double song_length); 
    char * music_data;
    const char FILENAME[] = "song.music";
    int i = 0, length = 0, catch, notes = 0;
    double time_total;

    // read in file using function read_music
    music_data = read_music(FILENAME, &length);
    if (music_data == NULL) {
        printf("error 1\n");
    }

    for (i = 0; i < length; i++) {
        printf("\n%c", music_data[i]);
    }
    
    // calculate the length (in seconds) of each note
    time_total = time_music(music_data, length, &notes);
    if (time_total == 0) {
        printf("\nerror2\n");
        return EXIT_FAILURE;
    }
    
    printf("\n%lf", time_total);
    printf("\n%d", notes);

    // now pass music data to decoding / writing function
    /* catch = write_music(music_data, length, time_total);
    if (catch != 0) {
        printf("\nerror3\n");
        return EXIT_FAILURE;
    }*/

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
    // const char valid_notes[] = ".AaBbCcDdEeFfGg";
    

    // open file and return error if not found
    music = fopen(file, "r");
    if (music == NULL) {
        printf("File not found.\n");
        return NULL;
    }

    // increment the SIZE variable for every character
    // added: other than whitespace
    // added also: increment notes everytime a valid note appears
    while(1) {
        current_char = fgetc(music);
        if (feof(music)) {
            break;
        }
        // if there's a valid character, increment size variable
        if (current_char != '\n' && current_char != ' ' &&
                current_char != '\t') {
            *SIZE = *SIZE + 1; 
        }
        // if the character is a note (matches the array notes[])
        // then increment the couter for number of notes
        /* if (strpbrk(valid_notes, &current_char) == 0) {
            *notes = *notes + 1; 
        } */
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
 * Output: double length
 * ************************************/

double time_music(char * music_data, int array_length, int* notes)
{
    int i;
    double time = 0;
    double delta_time = 1;
    

    for (i = 0; i < array_length; i++) {
        switch (music_data[i])
        {
            case 'a':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'A':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'b':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'B':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'c':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'C':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'd':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'D':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'e':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'E':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'f':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'F':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'g':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case 'G':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case '.':
                time = time + delta_time;
                *notes = *notes + 1;
                break;
            case '1':
                delta_time = 2;
                break;
            case '2':
                delta_time = 1;
                break;
            case '4':
                delta_time = .5;
                break;
            case '8':
                delta_time = .25;
                break;
            case '6':
                delta_time = .15;
                break;
            default:
                break;
        }
    }

    return time;
}

/***************************************
 * Func name: write_music
 * Purpose: translate the array of music
 * data into a .wav file.
 * Input: char[], length of char[], time
 * Output: int for status, writes .wav
 * ************************************/

int write_music(char * music_data, int length, double song_length) 
{
    FILE * music_output;
    short * waveform_gen(double frequency,double octave,double length);
    int i;
    double octave = 1;
    double note_length = 1;
    short * waveform;

    music_output = wavfile_open("song.wav");
    if (music_output == NULL) {
        return 1;
    }

    for (i = 0; i < length; i++) {
        switch (music_data[i])
        {
            case 'A':
                waveform = waveform_gen(440*octave,octave,note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'a':
                waveform = waveform_gen(415.3*octave,octave,note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'B':
                waveform = waveform_gen(493.88*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'b':
                waveform = waveform_gen(466.16*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'C':
                waveform = waveform_gen(523.25*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'D':
                waveform = waveform_gen(587.33*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'd':
                waveform = waveform_gen(554.37*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'E':
                waveform = waveform_gen(659.26*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'e':
                waveform = waveform_gen(622.25*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'F':
                waveform = waveform_gen(698.46*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'G':
                waveform = waveform_gen(783.99*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case 'g':
                waveform = waveform_gen(739.99*octave, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case '.':
                waveform = waveform_gen(0, octave, note_length);
                wavfile_write(music_output, waveform, note_length);
                break;
            case '+':
                octave = octave*2;
                break;
            case '-':
                octave = octave*(1/2);
                break;
            case '1':
                note_length = 2;
                break;
            case '2':
                note_length = 1;
                break;
            case '4':
                note_length = .5;
                break;
            case '8':
                note_length = .25;
                break;
            case '6':
                note_length = .125;
                break;
        }
    }

    wavfile_close(music_output);

    return 0;
}


short * waveform_gen(double frequency, double octave, double length)
{
    #include <math.h>

    int volume = 32000, i = 0;
    double t;
    short * waveform;

    waveform = calloc(WAVFILE_SAMPLES_PER_SECOND*length,sizeof(short));

    for (i = 0; i < (WAVFILE_SAMPLES_PER_SECOND*length); i++) {
        // first find out the time we're at in the waveform in seconds 
        t = (double) i / WAVFILE_SAMPLES_PER_SECOND; 
        // now we can fill the waveform accordingly, depending on
        // the note chosen, octave, length, etc.
        waveform[i] = volume*sin(frequency*t*length*octave*M_PI);
    }
    return waveform;
}
