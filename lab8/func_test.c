#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "wavfile.h"


int main()
{
    char music_data[] = /*"AAA"; */ "4EEFGGFEDCCDE4E8EDDX";
    int length = 20;
    FILE * music_output;
    short * waveform_gen(double frequency, double length);
    int i;
    double octave = 1;
    double note_length = 1;
    double file_length;
    short * waveform;

    music_output = wavfile_open("song.wav");
    if (music_output == NULL) {
        return 1;
    }

    for (i = 0; i < length; i++) {
        file_length = note_length*WAVFILE_SAMPLES_PER_SECOND;
        switch (music_data[i])
        {
            case 'A':
                waveform = waveform_gen(440*octave, note_length);
                wavfile_write(music_output, waveform,file_length); 
                break;
            case 'a':
                waveform = waveform_gen(415.3*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'B':
                waveform = waveform_gen(493.88*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'b':
                waveform = waveform_gen(466.16*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'C':
                waveform = waveform_gen(523.25*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'D':
                waveform = waveform_gen(587.33*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'd':
                waveform = waveform_gen(554.37*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'E':
                waveform = waveform_gen(659.26*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'e':
                waveform = waveform_gen(622.25*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'F':
                waveform = waveform_gen(698.46*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'G':
                waveform = waveform_gen(783.99*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case 'g':
                waveform = waveform_gen(739.99*octave, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case '.':
                waveform = waveform_gen(0, note_length);
                wavfile_write(music_output, waveform, file_length);
                break;
            case '+':
                octave = octave*2;
                break;
            case '-':
                octave = octave*(0.5);
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


short * waveform_gen(double frequency, double length)
{
    #include <math.h>

    int volume = 32000;
    int i = 0;
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
