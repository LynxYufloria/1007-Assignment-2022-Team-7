#include <stdlib.h>
#include <stdio.h>

#define MAX_CHAR 256
#define MAX_ARRAY 100


int main(int argc, const char* argv[]) {

    FILE* finput;
    int btArray[MAX_ARRAY]; //burst time array
    int atArray[MAX_ARRAY]; //arrival time array
    int jobArray[MAX_ARRAY][3];
    int fileCount = 0;
    int burstTime = 0;
    int arrivalTime = 0;
    int status;

    int i = 0, j = 0, timeSlice = 0, minBurstTime = 0, maxBurstTime = 0, temp = 0, pos = 0;
    int  backupBurstTime[MAX_ARRAY] = { 0 }, waitTime[MAX_ARRAY] = { 0 }, turnAroundTime[MAX_ARRAY] = { 0 },
        responseTime[MAX_ARRAY] = { 0 }, process[MAX_ARRAY] = { 0 }, exitTime[MAX_ARRAY] = { 0 };
    float avgWaitTime = 0.0, avgTurnAroundTime = 0.0, avgResponseTime = 0.0;

    finput = fopen(argv[1], "r");

    if (finput == NULL) {
        printf("Error Reading file");
        return 1;
    }

    printf("Reading file %s\n", argv[1]);

    while (1) {
        status = fscanf(finput, "%d %d", &arrivalTime, &burstTime);
        btArray[fileCount] = burstTime;
        atArray[fileCount] = arrivalTime;
        jobArray[fileCount][0] = fileCount; //process 1 ,2, 3
        jobArray[fileCount][1] = arrivalTime; //arrival time
        jobArray[fileCount][2] = burstTime; //burst time


        //haven solve the part on the stop the count,if there is a space
        fileCount += 1;

        if (feof(finput)) {
            break;
        }

    }

    //bt stored up in backupbt 
    for (i = 0; i < fileCount; i++)
    {
        backupBurstTime[i] = jobArray[i][2]; //burst time stored in the backupbursttime
        process[i] = i + 1;
    }



    //find the min bust time
    minBurstTime = jobArray[0][2];
    for (i = 1; i < fileCount; i++) {
        if (jobArray[i][2] < minBurstTime)
            minBurstTime = jobArray[i][2];
    }

    printf("\n The min burst time: %.2d ", minBurstTime); //correct output


    //sorting burst time from min to max
    for (i = 0; i < fileCount; i++)
    {
        pos = i;
        for (j = i + 1; j < fileCount; j++)
        {
            //if you want min to max just change the ">" sign
            if (backupBurstTime[j] < backupBurstTime[pos]) //comparing the burst time between the next process
                pos = j;
        }
        //sorting between 1 and 0, and 2 and 1
        //sorting the burst time
        temp = backupBurstTime[i];
        backupBurstTime[i] = backupBurstTime[pos];
        backupBurstTime[pos] = temp;
        //sorting the process order
        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }


    printf("\nCurrent Process Print out after sort from MIN to Max\n");
    for (i = 0; i < fileCount; i++)
    {
        printf("\t P%d \t\t %d \t\t \n",
            process[i], backupBurstTime[i]);
    }


    int MediumCountno = fileCount / 2;//Position of medium for the whole process
    printf("%d", MediumCountno);


    //split into two queue
    int SmallerQueueProcess[MAX_ARRAY] = { 0 };
    int SmallerQueueBurst[MAX_ARRAY] = { 0 };
    int SmallQTLength = 0;
    int BiggerQueueProcess[MAX_ARRAY] = { 0 };
    int BiggerQueueBurst[MAX_ARRAY] = { 0 };
    int BigQTLength = 0;


    //first  queue
    for (int i = 0; i < MediumCountno;i++)
    {
        SmallerQueueProcess[i] = process[i];
        SmallerQueueBurst[i] = backupBurstTime[i];
        SmallQTLength++;
        printf("\n SmallQueue -  Process is %.d and its BT is %.d", SmallerQueueProcess[i], SmallerQueueBurst[i]); //process 2 and 1
    }
    //second queue

    for (int i = MediumCountno; i < fileCount; i++)
    {

        BiggerQueueProcess[i] = process[i];
        BiggerQueueBurst[i] = backupBurstTime[i];
        BigQTLength++;
        printf("\n BigQueue - Process is %.d and its BT is %.d", BiggerQueueProcess[i], BiggerQueueBurst[i]);

    }

    //find the avg time quantum for each queue. 
    //small queue
    int TotalTimeQFirstQueue = 0;
    int AvgTimeQFirstQueue = 0;

    for (int i = 0;i < SmallQTLength;i++) {
        TotalTimeQFirstQueue += SmallerQueueBurst[i];

        printf("\n TotalTimeQFirstQueue %.d", TotalTimeQFirstQueue);
    }

    AvgTimeQFirstQueue = TotalTimeQFirstQueue / SmallQTLength;
    printf("\n\n Time Quantum for First Queue %.d\n", AvgTimeQFirstQueue);


    //big queue
    int AvgTimeQSecondQueue = 0;
    int TotalTimeQSecondQueue = 0;
    for (int i = MediumCountno;i < fileCount;i++) {
        TotalTimeQSecondQueue += BiggerQueueBurst[i];
        printf("\n TotalTimeQSecondQueue %.d", TotalTimeQSecondQueue);
    }

    AvgTimeQSecondQueue = TotalTimeQSecondQueue / BigQTLength;
    printf("\n Time Quantum for Second Queue %.d", AvgTimeQSecondQueue);


    //rr

    // store queues into array? then run into while loop
    // while array q not empty,
    // keep calculating wait time and turnaround time

    //shortest process wait time = 0;
    //wait time = turn around - burst time
    //waitTime[0] = 0; 
    int tempval = 0;

    //printf("\n\n\nTemp = %d\nNo of process in small q = %d", tempval, MediumCountno);
/*--------------------------------------------------------- calculate Smaller Queue ---------------------------------------------------------*/
    printf("\n\nCALCULATING TURNAROUND TIME FOR SMALL QUEUE");
    for (i = 0; i < MediumCountno; i++) { // 2
        printf("\n\nBurst Time Process %d = %d", SmallerQueueProcess[i], SmallerQueueBurst[i]);
        while (SmallerQueueBurst[i] != 0)
        {
            if (SmallerQueueBurst[i] <= AvgTimeQFirstQueue)
            {
                turnAroundTime[i] = tempval + SmallerQueueBurst[i];
                tempval = tempval + SmallerQueueBurst[i];
                SmallerQueueBurst[i] = 0;
            }
            else
            {
                SmallerQueueBurst[i] = SmallerQueueBurst[i] - AvgTimeQFirstQueue;
                tempval = tempval + AvgTimeQFirstQueue;
            }
        }
        printf("\nTurnaround Process %d = %d", SmallerQueueProcess[i], turnAroundTime[i]);
        waitTime[i] = 0;
        for (j = 0;j < i;j++) {
            waitTime[i] += backupBurstTime[j]; //adding up the wait time
        }
        // avgWaitTime += waitTime[i]; //avg time must be place here   

    }

    /*--------------------------------------------------------- calculate Bigger Queue ---------------------------------------------------------*/
    printf("\n\nCALCULATING TURNAROUND TIME FOR BIGGER QUEUE");
    for (int i = MediumCountno; i < fileCount; i++)
    {
        printf("\n\nBurst Time Process %d = %d", BiggerQueueProcess[i], BiggerQueueBurst[i]);
        while (BiggerQueueBurst[i] != 0)
        {
            if (SmallerQueueBurst[i] <= AvgTimeQSecondQueue)
            {
                turnAroundTime[i] = tempval + BiggerQueueBurst[i];
                tempval = tempval + BiggerQueueBurst[i];
                BiggerQueueBurst[i] = 0;
            }
            else
            {
                BiggerQueueBurst[i] = BiggerQueueBurst[i] - AvgTimeQSecondQueue;
                tempval = tempval + AvgTimeQSecondQueue;
            }
        }
        printf("\nTurnaround Process %d = %d", BiggerQueueProcess[i], turnAroundTime[i]);
        waitTime[i] = 0;
        for (j = 0;j < i;j++) {
            waitTime[i] += backupBurstTime[j]; //adding up the wait time
        }
        // avgWaitTime += waitTime[i]; //avg time must be place here
    }

    /*
            //turn around time
            for(i=0; i< fileCount; i++){
            //turn around time = burst time + waiting time
            //turn around time = exit time - arrival time
                turnAroundTime[i] = backupBurstTime[i] + waitTime[i];
                //exitTime[i] =  turnAroundTime[i] + jobArray[fileCount][1];
                avgTurnAroundTime += turnAroundTime[i];
            }
            */



            /////////////////bottom output is not based on the algo yet
    printf("\n\t Output Below is not finalised, wrongg!!!\n");
    printf("\n\t PROCESS\t BURST TIME\t WAITING TIME\t TURNAROUND TIME\n");
    for (i = 0; i < fileCount; i++)
        printf("\t P%d \t\t %d \t\t %d \t\t %d \n",
            process[i], backupBurstTime[i], waitTime[i], turnAroundTime[i]);
    //Calculate and print the ‘average waiting time’,‘average turn-around-time’, and 'average response time' 
    printf("\n\t The Average Waiting time: %.2f\n", avgWaitTime / fileCount);
    printf("\n\t The Average Turnaround time: %.2f\n", avgTurnAroundTime / fileCount);


    fclose(finput);



    return 0;
}



