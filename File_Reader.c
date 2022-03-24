#include <stdlib.h>
#include <stdio.h>

#define MAX_CHAR 256
#define MAX_ARRAY 100
int main(int argc, const char* argv[]) {

    FILE* finput;
    int btArray[MAX_ARRAY];
    int atArray[MAX_ARRAY];
    int jobArray[MAX_ARRAY][3];
    int fileCount, burstTime, arrivalTime, numProcesses = 0;
    int status, btMax;

    // --------------------------------------------Reading the file input-------------------------------------------- //
        // Store each line into respective arrays NOT TAKING ACCOUNT OF ARRIVAL TIME    
    finput = fopen(argv[1], "r");

    if (finput == NULL) {
        printf("Error Reading file");
        return 1;
    }

    printf("Reading file %s\n", argv[1]);

    while (1) {
        if (feof(finput)) {
            break;
        }
        status = fscanf(finput, "%d %d", &arrivalTime, &burstTime);
        atArray[fileCount] = arrivalTime;
        btArray[fileCount] = burstTime;
        printf("btArray[%d] = %d\n", fileCount, burstTime);
        jobArray[fileCount][0] = fileCount;
        jobArray[fileCount][1] = arrivalTime;
        jobArray[fileCount][2] = burstTime;
        fileCount += 1;
    }

    fclose(finput);
    // ------------------------------------------- Reading the file input ------------------------------------------- //
    numProcesses = fileCount;
    printf("No. of processes = %d\n", numProcesses);
    // Get Max Burst Time
    btMax = btArray[0];
    for (int i = 0; i < numProcesses; i++) {
        // printf("Process %d\n", i+1);
        // printf("Burst Time = %d\n", btArray[i]);
        if (btArray[i] > btMax) {
            btMax = btArray[i];
        }
    }
    //so we got max bt, so get 0.8th percentile of max for quantum time
    printf("\nMax Burst Time = %d\n", btMax);
    int qt = 0.8 * btMax;
    printf("\nQuantum Time = %d\n", qt);
    //run processes that are <= qt, store remaining to remainingProcess
    // int j = 1;
    // while (j<=numProcesses){
    //     printf("Process %d\n", j);
    //     if (j < numProcesses){
    //         if (btArray[j-1] <= qt){

    //         }
    //     }
    // }

    //check the arrival time against quantum time

    //check if burst time > qt
    int temp, tempBT[MAX_ARRAY], waitingTime, turnaroundTime = 0;
    for (int j = 0; j < numProcesses; j++) {
        if (btArray[j] > qt) {
            //store into temp for value > Quantum Time
            temp = btArray[j];
        }
        //add BT to waiting & turnaround time


    }

    //bruh
    // -------------------------------------------- Sort by Burst Time --------------------------------------------- //

    return 0;
}