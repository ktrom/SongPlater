#include <stdio.h>
#include "genscd.c"

// this program will prompt the user for a frequency, a sample rate, and a time duration
// output the function values of the sine wave for that duration with the specified
// frequency sampled at the given rate
int main() {
    float frequency = 0;
    float sample_rate = 0;
    float time_duration = 0;

    printf("Input the frequency in hz, sample rate in hz, and time duration in seconds for which you want an output sine wave\n");
    scanf("%f %f %f", &frequency, &sample_rate, &time_duration);
    printf("\n");
    gensine(frequency, sample_rate, time_duration); // feeds the variables into the function which will display output values
    return 0;
}
