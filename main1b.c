#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "genscd.c"

int main(int argc, char *argv[]){
    FILE * fp;
    if(argc < 1){
        fprintf( stderr, "phone number not provided\n");
    }
    else {
        char *phoneNumber = argv[1];
        char * fileName = argv[2];
        if(phoneNumber == NULL){
		fprintf(stderr, "no phone digits given!\n");
		exit(0);
	}
	int stringLength = strlen(phoneNumber);
	
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
        else {
            if (fp = fopen(fileName, "r")) {
                fclose(fp);
                fp = fopen(fileName, "w");
                for(int i =0 ; i < stringLength - 1; i++){
                    outputSound(genDTMF2(newNumber[i], 8000, .5), fp);
                    outputSound(genSilence(8000, .25), fp);
                }
                outputSound(genDTMF2(newNumber[stringLength - 1], 8000, .5), fp);
                fclose(fp);
            } else {
                for(int i =0 ; i < stringLength - 1; i++){
                    outputSoundToStdout(genDTMF2(newNumber[i], 8000, .5));
                    outputSoundToStdout(genSilence(8000, .25));
                }
                outputSoundToStdout(genDTMF2(newNumber[stringLength - 1], 8000, .5));
	    }
        }
    }
}

