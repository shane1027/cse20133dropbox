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

	for(i=0;i<length;i++) {
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume*sin(frequency*t*2*M_PI);
	}
    

	wavfile_write(f,waveform,length);
	wavfile_close(f);

	return 0;
}
