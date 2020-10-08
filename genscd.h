#include <stdio.h>

// getOutputArray will take a frequency, sample rate, and time duration and return an array of the outputs
// of the sine function with given frequency at each time interval (1/sample_rate seconds) for the duration 
float * getOutputArray(float frequency, float sample_rate, float time_duration);

// gensine will output the values of a sine function with frequency given sampled at the given rate to standard out
void gensine(float frequency, float sample_rate, float time_duration);

// this function will output silence to the standard out for the specified duration 
void silence(float sample_rate, float time_duration);

// returns the array of values for the specified key sampled at the given rate for the given duration
float * returnStandardTone(char key, float rate, float duration);

// prints to standard out the tone specified by the character
void printStandardTones(char c);

typedef struct sound_t{

    float * samples; // pointer ot float array
    int length; // number of samples in the float array
    float rate; // sample rate for the sequence of samples

} sound;

// generates a DTMF sound for the given key
sound * genDTMF2(char key, float sample_rate, float duration);

// Generates a sine wave sound object from the given parameters
sound * gensine2(float hertz, float sample_rate, float duration);

// Returns a silent sound at the given sample rate for the specified duration
sound * genSilence(float sample_rate,float duration);

// Writes a sound to the given file, returns 0 if successful write and 1 if failed
int outputSound( sound *s, FILE *f);

// Prints a sound to standard out
void outputSoundToStdout( sound *s );
