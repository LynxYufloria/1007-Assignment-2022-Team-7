#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CHAR 256
#define MAX_ARRAY 100
#define NO_OF_QUEUE 2
#define TIMEQUANTUM_QUARTILE 0.8

struct job{
    int jobID;
    int burstTime;
    int arrivalTime;
    int remainingBT;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

int roundNo(float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}

void sortjobArray(struct job jobArray[], int fileCount) {
    struct job temp;
    for (int i = 0; i < fileCount-1; i++) {
        for (int j = 0; j < fileCount-1; j++){
            if (jobArray[j].burstTime > jobArray[j+1].burstTime) {
                temp = jobArray[j];
                jobArray[j] = jobArray[j+1];
                jobArray[j+1] = temp;
            }
        }
    }
}
int main() {
    
    FILE* finput;
    struct job jobArray [MAX_ARRAY];
    int fileCount = 0;
    int burstTime = 0;
    int arrivalTime = 0;
    char fileName[MAX_CHAR];
    char fileLine[MAX_ARRAY];
    int splitIndex;
    int queueTQArray [NO_OF_QUEUE];
    int splitTimeQuantum;
    bool queuefinishCheck = false;
    int startQueue = 0;
    int endQueue = 0;
    int time = 0;

    printf("Enter name of the file: ");
    scanf("%s", fileName);

//Opening the file
    finput = fopen(fileName, "r");
    
    if (finput == NULL) {
        printf("Error Reading file");
        return 1;
    }
    
    printf("Reading file %s\n", fileName);
//Reading line by line  
    while (fgets(fileLine, MAX_CHAR, finput)){
        if (fileLine == " \n"){
            break;
        }
        sscanf(fileLine, "%d %d\n", &arrivalTime, &burstTime);
//Filling up struct array
        jobArray[fileCount].jobID = fileCount;
        jobArray[fileCount].burstTime = burstTime;
        jobArray[fileCount].remainingBT = burstTime;
        jobArray[fileCount].arrivalTime = arrivalTime;
        fileCount += 1;
    }
    
    fclose(finput);

//Sorting the jobArray by the burstTime

    sortjobArray(jobArray, fileCount);

//Define where the jobArray is split
    splitIndex = roundNo(fileCount/NO_OF_QUEUE);

//Define time quantums of each queue
    for (int a = 0; a < NO_OF_QUEUE; a++){
        splitTimeQuantum = roundNo(splitIndex*TIMEQUANTUM_QUARTILE)-1;
        if (a==NO_OF_QUEUE-1) {
            splitTimeQuantum = roundNo((splitIndex+(fileCount-splitIndex*NO_OF_QUEUE))*TIMEQUANTUM_QUARTILE)-1;
        }
        queueTQArray[a] = jobArray[splitIndex*a + splitTimeQuantum].burstTime;
        printf("%d\n",queueTQArray[a]);
    }

    startQueue = 0;
    endQueue = splitIndex;
//Calculate Turnaround time and Response Time
    for(int b = 0; b < NO_OF_QUEUE; b++){
        queuefinishCheck = false;
        while(!queuefinishCheck){
            for(int c = startQueue; c < endQueue; c++){
                if(jobArray[c].arrivalTime <= time){
                    if(jobArray[c].remainingBT != 0){
                        if(jobArray[c].remainingBT == jobArray[c].burstTime)
                            jobArray[c].responseTime = time;

                        if(jobArray[c].remainingBT > queueTQArray[b]){
                            jobArray[c].remainingBT -= queueTQArray[b];
                            time = time + queueTQArray[b];
                        } else {
                            time = time + jobArray[c].remainingBT;
                            jobArray[c].remainingBT = 0;
                            jobArray[c].turnaroundTime = time;
                        }
                    }
                }
            }
            if (jobArray[endQueue-1].remainingBT <= 0)
                queuefinishCheck = true;
        }
        startQueue = endQueue;
        endQueue = endQueue+splitIndex;
        if(b == NO_OF_QUEUE-1){
            endQueue = fileCount;
        }
    }

//Calculate Waiting time
    for(int d = 0; d < fileCount; d++)
        jobArray[d].waitingTime = jobArray[d].turnaroundTime - jobArray[d].arrivalTime - jobArray[d].burstTime;
    
//Print output
    printf("ProcessID\t\tArrivalTime\t\tBurstTime\t\tTurnaroundTime\t\tWaitingTime\t\tResponseTime\n");
    for(int e = 0; e < fileCount; e++){
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", jobArray[e].jobID, jobArray[e].arrivalTime, jobArray[e].burstTime, jobArray[e].turnaroundTime,
        jobArray[e].waitingTime, jobArray[e].responseTime, jobArray[e].remainingBT);
    }
    
    return 0;
}
