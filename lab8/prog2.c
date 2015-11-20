/***************************************
 * Author: Shane Ryan
 * Name: prog2.c
 * Purpose: read in a .music file and
 * convert it to a .wav file like a 
 * player piano, w/ instrument funcs.
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
    catch = write_music(music_data, length, time_total);
    if (catch != 0) {
        printf("\nerror3\n");
        return EXIT_FAILURE;
    }

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
    

    // complex switch statement for every character in the array.
    // counts total valid notes and sums their durations.
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
    short * waveform_gen(double frequency, double length);
    short * spaceage_gen(double frequency, double length);
    int i;
    double octave = 1;
    double note_length = 1;
    double file_length;    short * waveform;

    music_output = wavfile_open("song.wav");
    if (music_output == NULL) {
        return 1;
    }

    // step through the array and use complex switch statement to 
    // select desired output note
    for (i = 0; i < length; i++) {
        file_length = note_length*WAVFILE_SAMPLES_PER_SECOND;
        switch (music_data[i])
        {
            case 'A':
                waveform = spaceage_gen(440*octave,note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'a':
                waveform = spaceage_gen(415.3*octave,note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'B':
                waveform = spaceage_gen(493.88*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'b':
                waveform = spaceage_gen(466.16*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'C':
                waveform = spaceage_gen(523.25*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'D':
                waveform = spaceage_gen(587.33*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'd':
                waveform = spaceage_gen(554.37*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'E':
                waveform = spaceage_gen(659.26*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'e':
                waveform = spaceage_gen(622.25*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'F':
                waveform = spaceage_gen(698.46*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'G':
                waveform = spaceage_gen(783.99*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'g':
                waveform = spaceage_gen(739.99*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case '.':
                waveform = spaceage_gen(0, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case '+':
                octave = octave*2;
                break;
            case '-':
                octave = octave*(.5);
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

/***************************************
 * Func name: waveform_gen
 * Purpose: translate data to an array
 * compatible with .wav output..
 * Input: double freq, double length
 * Output: pointer to short to data
 * ************************************/

short * waveform_gen(double frequency, double length)
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
        waveform[i] = volume*sin(frequency*t*2*M_PI);
    }
    return waveform;
}

/***************************************
 * Func name: spaceage_gen
 * Purpose: translate data to an array
 * compatible with .wav output.
 * Input: double freq, double length
 * Output: pointer to short to data
 * ************************************/

short * spaceage_gen(double frequency, double length)
{
    #include <math.h>

    int volume = 32000, i = 0;
    double t;
    short * waveform;

    waveform = calloc(WAVFILE_SAMPLES_PER_SECOND*length,sizeof(short));

    for (i = 0; i < (WAVFILE_SAMPLES_PER_SECOND*length); i = i+4) {
        // first find out the time we're at in the waveform in seconds 
        t = (double) i / WAVFILE_SAMPLES_PER_SECOND; 
        // now we can fill the waveform accordingly, depending on
        // the note chosen, octave, length, etc.
        waveform[i] = volume*(.66)*sin(frequency*(.5)*t*2*M_PI);
    }
// superimpose multiple sin waves onto each other for desired harmonics
    for (i = 1; i < (WAVFILE_SAMPLES_PER_SECOND*length); i = i+4) {
        t = (double) i / WAVFILE_SAMPLES_PER_SECOND; 
        waveform[i] = volume*(.5)*sin(frequency*(.666)*t*2*M_PI);
    }

    for (i = 2; i < (WAVFILE_SAMPLES_PER_SECOND*length); i = i+4) {
        t = (double) i / WAVFILE_SAMPLES_PER_SECOND; 
        waveform[i] = volume*sin(frequency*t*2*M_PI);
    }

    for (i = 3; i < (WAVFILE_SAMPLES_PER_SECOND*length); i = i+4) {
        t = (double) i / WAVFILE_SAMPLES_PER_SECOND; 
        waveform[i] = volume*(.25)*sin(frequency*(.333)*t*2*M_PI);
    }

    return waveform;
}
