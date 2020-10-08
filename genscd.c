#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "genscd.h"
///
/// \param frequency frequency (in hz) for the sine wave to be output
/// \param sample_rate the rate (in hz) at which the sine wave will be sampled
/// \param time_duration the amount of time (s) for which the wave will be output

float * getOutputArray(float frequency, float sample_rate, float time_duration){
    float time_step = 1/sample_rate;
    float * outputs;

    outputs = (float *) malloc((int)(time_duration / time_step)* sizeof(float));
    for(int i = 0; i*time_step <= time_duration; i++)
    {
       outputs[i] = sin(2*M_PI*frequency*i*time_step);
    }
    return outputs;
}
void gensine(float frequency, float sample_rate, float time_duration){ // function which will output the y-coordinates of a sine wave given these parameters
    float * outputs;
    outputs = getOutputArray(frequency, sample_rate, time_duration);
    for(int i = 0; i < time_duration*sample_rate; i++){
         printf("%0.4f\n", outputs[i]);
    }
}

sound * gensine2(float hertz, float sample_rate, float duration){
    float * outputs;
    outputs = getOutputArray(hertz, sample_rate, duration);

    sound * sound1;
    sound1->samples = outputs;
    sound1->length = duration*sample_rate;
    sound1->rate = sample_rate;
    return sound1;
}

sound * genDTMF2(char key, float sample_rate, float duration){
    sound * sound1 = malloc(sizeof(sound));   // variable to represent
    sound1->rate = sample_rate;
    sound1->length = duration * sample_rate;
    sound1->samples = returnStandardTone(key, sample_rate, duration);
    return sound1;
}

void silence(float sample_rate, float time_duration){ // function which will output the y-coordinates of a sine wave given these parameters
    for(int i = 0; i < time_duration*sample_rate; i++){
        printf("%0.4f\n", 0.0);
    }
}

sound * genSilence(float sample_rate,float duration){
    float * silenceArray = (float *) malloc((int)(duration * sample_rate)* sizeof(float));
    for(int i = 0; i < duration*sample_rate; i++){
        silenceArray[i] = 0;
    }
    sound * sound1;
    sound1->length = duration*sample_rate;
    sound1->rate = sample_rate;
    sound1->samples = silenceArray;
    return sound1;
}

int outputSound( sound *s, FILE *f){
    if(f == NULL){
        return 1;
    }
    float * outputs = s->samples;
    for(int i = 0; i < s->length; i++){
        fprintf(f, "%0.4lf\n", outputs[i]);
    }
    return 0;
}

void outputSoundToStdout( sound *s ){
    float * outputs = s->samples;
    for(int i = 0; i < s->length; i++){
        printf("%0.4lf\n", outputs[i]);
    }
}



float * returnStandardTone(char key, float rate, float duration){
    double tones[2][4] = {
            {1209.0, 1336.0, 1477.0, 1633.0},
            {697.0, 770.0, 852.0, 941.0},
    };
    float sample_rate = rate;
    float time_duration = duration;
    float * outputArray1, * outputArray2; // variables for the waves to compose the output wave

    // Sets the appropriate values for the composing sine waves
    switch (key){
        case '1':
            outputArray1 = getOutputArray(697, sample_rate, time_duration);
            outputArray2 = getOutputArray(1209, sample_rate, time_duration);
            break;
        case '2':
            outputArray1 = getOutputArray(697, sample_rate, time_duration);
            outputArray2 = getOutputArray(1336, sample_rate, time_duration);
            break;
        case '3':
            outputArray1 = getOutputArray(697, sample_rate, time_duration);
            outputArray2 = getOutputArray(1477, sample_rate, time_duration);
            break;
        case 'A':
            outputArray1 = getOutputArray(697, sample_rate, time_duration);
            outputArray2 = getOutputArray(1633, sample_rate, time_duration);
            break;
        case '4':
            outputArray1 = getOutputArray(770, sample_rate, time_duration);
            outputArray2 = getOutputArray(1209, sample_rate, time_duration);
            break;
        case '5':
            outputArray1 = getOutputArray(770, sample_rate, time_duration);
            outputArray2 = getOutputArray(1336, sample_rate, time_duration);
            break;
        case '6':
            outputArray1 = getOutputArray(770, sample_rate, time_duration);
            outputArray2 = getOutputArray(1477, sample_rate, time_duration);
            break;
        case 'B':
            outputArray1 = getOutputArray(770, sample_rate, time_duration);
            outputArray2 = getOutputArray(1633, sample_rate, time_duration);
            break;
        case '7':
            outputArray1 = getOutputArray(852, sample_rate, time_duration);
            outputArray2 = getOutputArray(1209, sample_rate, time_duration);
            break;
        case '8':
            outputArray1 = getOutputArray(852, sample_rate, time_duration);
            outputArray2 = getOutputArray(1336, sample_rate, time_duration);
            break;
        case '9':
            outputArray1 = getOutputArray(852, sample_rate, time_duration);
            outputArray2 = getOutputArray(1477, sample_rate, time_duration);
            break;
        case 'C':
            outputArray1 = getOutputArray(852, sample_rate, time_duration);
            outputArray2 = getOutputArray(1633, sample_rate, time_duration);
            break;
        case '*':
            outputArray1 = getOutputArray(941, sample_rate, time_duration);
            outputArray2 = getOutputArray(1209, sample_rate, time_duration);
            break;
        case '0':
            outputArray1 = getOutputArray(941, sample_rate, time_duration);
            outputArray2 = getOutputArray(1336, sample_rate, time_duration);
            break;
        case '#':
            outputArray1 = getOutputArray(941, sample_rate, time_duration);
            outputArray2 = getOutputArray(1477, sample_rate, time_duration);
            break;
        case 'D':
            outputArray1 = getOutputArray(941, sample_rate, time_duration);
            outputArray2 = getOutputArray(1633, sample_rate, time_duration);
            break;
    }


    float * resultantArray = (float *) malloc((int)(time_duration * sample_rate)* sizeof(float));
    for(int i = 0; i < time_duration * sample_rate; i++){
        resultantArray[i] = (outputArray1[i] + outputArray2[i])/2; // Adding waves and normalizing to keep magnitude<1
    }

    free(outputArray1);
    free(outputArray2);
    return resultantArray;
}

// This method prints the DTMF wave for the given character to standard out
void printStandardTones(char c){
    double tones[2][4] = {
            {1209.0, 1336.0, 1477.0, 1633.0},
            {697.0, 770.0, 852.0, 941.0},
    };
    float sample_rate = 8000;
    float time_duration = .5;
    float * outputArray1, * outputArray2; // variables for the waves to compose the output wave

    // Sets the appropriate values for the composing sine waves
    switch (c){
        case '1':
            outputArray1 = getOutputArray(697, 8000, .5);
            outputArray2 = getOutputArray(1209, 8000, .5);
            break;
        case '2':
            outputArray1 = getOutputArray(697, 8000, .5);
            outputArray2 = getOutputArray(1336, 8000, .5);
            break;
        case '3':
            outputArray1 = getOutputArray(697, 8000, .5);
            outputArray2 = getOutputArray(1477, 8000, .5);
            break;
        case 'A':
            outputArray1 = getOutputArray(697, 8000, .5);
            outputArray2 = getOutputArray(1633, 8000, .5);
            break;
        case '4':
            outputArray1 = getOutputArray(770, 8000, .5);
            outputArray2 = getOutputArray(1209, 8000, .5);
            break;
        case '5':
            outputArray1 = getOutputArray(770, 8000, .5);
            outputArray2 = getOutputArray(1336, 8000, .5);
            break;
        case '6':
            outputArray1 = getOutputArray(770, 8000, .5);
            outputArray2 = getOutputArray(1477, 8000, .5);
            break;
        case 'B':
            outputArray1 = getOutputArray(770, 8000, .5);
            outputArray2 = getOutputArray(1633, 8000, .5);
            break;
        case '7':
            outputArray1 = getOutputArray(852, 8000, .5);
            outputArray2 = getOutputArray(1209, 8000, .5);
            break;
        case '8':
            outputArray1 = getOutputArray(852, 8000, .5);
            outputArray2 = getOutputArray(1336, 8000, .5);
            break;
        case '9':
            outputArray1 = getOutputArray(852, 8000, .5);
            outputArray2 = getOutputArray(1477, 8000, .5);
            break;
        case 'C':
            outputArray1 = getOutputArray(852, 8000, .5);
            outputArray2 = getOutputArray(1633, 8000, .5);
            break;
        case '*':
            outputArray1 = getOutputArray(941, 8000, .5);
            outputArray2 = getOutputArray(1209, 8000, .5);
            break;
        case '0':
            outputArray1 = getOutputArray(941, 8000, .5);
            outputArray2 = getOutputArray(1336, 8000, .5);
            break;
        case '#':
            outputArray1 = getOutputArray(941, 8000, .5);
            outputArray2 = getOutputArray(1477, 8000, .5);
            break;
        case 'D':
            outputArray1 = getOutputArray(941, 8000, .5);
            outputArray2 = getOutputArray(1633, 8000, .5);
            break;
    }


    float * resultantArray = (float *) malloc((int)(time_duration * sample_rate)* sizeof(float)); 
    for(int i = 0; i < time_duration * sample_rate; i++){
        resultantArray[i] = (outputArray1[i] + outputArray2[i])/2; // Adding waves and normalizing to keep magnitude<1
        printf("%0.4lf\n", resultantArray[i]);
    }
}
