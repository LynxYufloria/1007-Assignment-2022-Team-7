#include <stdlib.h>
#include <stdio.h>

#define MAX_CHAR 256
#define MAX_ARRAY 100
int main(int argc, const char * argv[]) {
    
    FILE* finput;
    int btArray[MAX_ARRAY];
    int atArray[MAX_ARRAY];
    int jobArray [MAX_ARRAY][3];
    int fileCount = 0;
    int burstTime = 0;
    int arrivalTime = 0;
    int status;
    char fileLine[MAX_ARRAY];
    
    finput = fopen(argv[1], "r");
    
    if (finput == NULL) {
        printf("Error Reading file");
        return 1;
    }
    
    printf("Reading file %s\n", argv[1]);
    
    while (fgets(fileLine, MAX_CHAR, finput)){
        if (fileLine = " \n"){
            break;
        }
        sprintf(fileLine, MAX_CHAR, "%d %d\n", burstTime, arrivalTime);
        btArray[fileCount] = burstTime;
        atArray[fileCount] = arrivalTime;
        jobArray[fileCount][0] = fileCount;
        jobArray[fileCount][1] = burstTime;
        jobArray[fileCount][2] = arrivalTime;
        fileCount += 1;
        
    }
    
    fclose(finput);
    //gg
    
    return 0;
}
