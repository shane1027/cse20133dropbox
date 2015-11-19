/**************************************************
 * Author: Shane Ryan  sryan8@nd.edu
 * Name: prog1.c
 * Purpose: decode .music file and output .wav file
 * ************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "wavfile.h"

const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);

int main()
{
	short waveform[NUM_SAMPLES];
	double frequency = 440.0;
	int volume = 32000;
    FILE * f;
	int length = NUM_SAMPLES;

	int i;
	f = wavfile_open("sound.wav");
	if(!f) {
		printf("couldn't open sound.wav for writing: %s",strerror(errno));
		return 1;
	}

	for(i=0;i<length;i = i+3) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume*sin(frequency*t*2*M_PI);
	}

	for(i=1;i<length;i = i+3) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = (volume*(.3333))*sin(frequency*(.3333)*t*2*M_PI);
	}
    
	for(i=2;i<length;i = i+3) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = (volume*(.6666))*sin(frequency*(.5)*t*2*M_PI);
	 }
    

	wavfile_write(f,waveform,length);
	wavfile_close(f);

	return 0;
}
