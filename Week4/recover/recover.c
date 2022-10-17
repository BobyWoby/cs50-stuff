#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 512
typedef uint8_t BYTE;
void readFile(FILE *file);
bool checkIfJpeg(unsigned char bytes[]);
int counter = 0;
int main(int argc, char *argv[])
{
    if(argc == 2){
        FILE *file = fopen(argv[1], "r");
        readFile(file);
        fclose(file);
    }
    else{
        printf("Usage: ./recover filename \n");
        return 1;
    }
    return 0;
}
void readFile(FILE *file){
    BYTE buffer[BLOCK_SIZE];
    int fileNum = 0;
    //starts as a NULL pointer so it shouldn't be able to write anything ito until its actually a jpg
    FILE *jpg = NULL;
    while(fread(buffer, sizeof(char), BLOCK_SIZE, file) == BLOCK_SIZE){
        if(checkIfJpeg(buffer)){
            char str[8];
            sprintf(str, "%03i.jpg", counter++);
            if(jpg != NULL){
                fclose(jpg);
            }
            jpg = fopen(str, "w");
        }
        //checks if there is a jpg file to write into
        if(jpg != NULL){
            //writes into the jpg file
            fwrite(buffer, sizeof(BYTE)*512, 1, jpg);
        }
    }
    if(jpg != NULL){
        fclose(jpg);
    }
}
bool checkIfJpeg(unsigned char bytes[]){
    if(bytes[0] == 0xff &&
        bytes[1] == 0xd8 &&
        bytes[2] == 0xff &&
        (bytes[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}