#include <stdio.h>
#include "genscd.c"
#include <ctype.h>
#include <string.h>
// This program will take a 10 digit telephone number and prints to standard out the DTMF tones and 
// silence that would dial that number
int main() {
    char phoneNumber[10];
    printf("Input the 10-digit telephone number\n");

    scanf("%s", phoneNumber);

    printf("\n");


    int stringLength = strlen(phoneNumber);

    if(stringLength != 10){
        fprintf(stderr, "the phone number is not 10 digits long!\n");
        exit(0);
    }
    char newNumber[stringLength];
    strcpy(newNumber, phoneNumber);
    int k = 0;
    while(newNumber[k]){
        newNumber[k] = toupper(newNumber[k]);
        k++;
    }
    int isValid = 1;
    for(int i = 0; i < stringLength; i++){
        if(!isdigit(newNumber[i]) == 1){
            char c = newNumber[i];
            newNumber[i] = c;
            if(c != 'A' && c!= 'B' && c!= 'C' && c!= 'D' && c!='#' && c!= '*') {
                isValid = 0;
            }
        }
    }
    if(isValid == 0){
        fprintf( stderr, "not all valid phone digits!\n");
        exit(0);
    }
    else{
        // This loop will print the standard tones for each digit in the phone number separated by a silent pause
        printStandardTones(newNumber[0]);
        for(int i = 1; i < 10; i++){
            silence(8000, .25);
            printStandardTones(newNumber[i]);
        }
        return 0;
    }
}
