#include <stdlib.h>
#include <stdio.h>

#define MAX_CHAR 256
#define MAX_ARRAY 100


int main(int argc, const char * argv[]) {
    
    FILE* finput;
    int btArray[MAX_ARRAY]; //burst time array
    int atArray[MAX_ARRAY]; //arrival time array
    int jobArray [MAX_ARRAY][3];  
    int fileCount = 0;
    int burstTime = 0;
    int arrivalTime = 0;
    int status;

    int i = 0, j = 0, timeSlice = 0, minBurstTime=0, maxBurstTime = 0, temp = 0,pos = 0;
    int  backupBurstTime[MAX_ARRAY]={0}, waitTime[MAX_ARRAY]={0}, turnAroundTime[MAX_ARRAY]={0},
    responseTime[MAX_ARRAY]={0}, process[MAX_ARRAY]={0}, exitTime[MAX_ARRAY]={0};
    float avgWaitTime = 0.0, avgTurnAroundTime = 0.0, avgResponseTime = 0.0;
    
    finput = fopen(argv[1], "r");
    
    if (finput == NULL) {
        printf("Error Reading file");
        return 1;
    }
    
    printf("Reading file %s\n", argv[1]);
    
    while (1){
        status = fscanf(finput, "%d %d", &arrivalTime, &burstTime);
        btArray[fileCount] = burstTime;
        atArray[fileCount] = arrivalTime;
        jobArray[fileCount][0] = fileCount; //process 1 ,2, 3
        jobArray[fileCount][1] = arrivalTime; //arrival time
        jobArray[fileCount][2] = burstTime; //burst time
        
       

        fileCount += 1;
        
         if (feof(finput)){
            break;
        }
        
    }
    
  
        //bt stored up in backupbt 
        for (i = 0; i < fileCount; i++)
        {
        backupBurstTime[i] =  jobArray[i][2]; //burst time stored in the backupbursttime
        process[i] = i+1; 
        }
    
  

      //find the max bust time
        maxBurstTime = jobArray[0][2]; 
        for (i = 1; i < fileCount; i++){
            if (jobArray[i][2] > maxBurstTime )
                maxBurstTime = jobArray[i][2];
                }

        printf("\n The max burst time: %.2d ", maxBurstTime); //correct output

        //0.8 times of the BT MAX
        int QuantumTime =  0.8 * maxBurstTime;
        printf("\n The 0.8* max burst time: %.2d ", QuantumTime);
  
        //sorting burst time from max to min
        for(i=0; i<fileCount; i++)
            {
            pos=i;
            for(j=i+1; j<fileCount; j++)
            {   
                //if you want min to max just change the ">" sign
                if(backupBurstTime[j]>backupBurstTime[pos]) //comparing the burst time between the next process
                    pos=j; 
            }
            //sorting between 1 and 0, and 2 and 1
            //sorting the burst time
            temp = backupBurstTime[i];
            backupBurstTime[i]=backupBurstTime[pos];
            backupBurstTime[pos]=temp;
            //sorting the process order
            temp=process[i];
            process[i]=process[pos];
            process[pos]=temp;
        }
    
        //compare QT with the rest of the BT
        int SmallerQT[MAX_ARRAY]={0};
        int SmallQTLength = 0; 
        int GreaterQT[MAX_ARRAY]= {0};
        int BigQTLength = 0; 
        int combinedQT[MAX_ARRAY];
        for (i = 0; i < fileCount; i++)
        {
            if(backupBurstTime[i] < QuantumTime)
            {
                //store it in 1 array
                SmallerQT[i] = process[i];
                SmallQTLength++;
                printf("\n Small QT Process is %.d ", SmallerQT[i]); //successfully separate
            }
            else{
                //store it in another array
                GreaterQT[i] = process[i];
                BigQTLength++;
                printf("\n Big QT Process is %.d ",  GreaterQT[i]); //successfully separate
            }

         
        }
         printf("\n Small QT Process Length is %.d ", SmallQTLength); //successfully separate
         printf("\n Big  QT Process Length is %.d ", BigQTLength); //successfully separate

        for (i = 0; i < SmallQTLength; i++)
        {
            combinedQT[i] = SmallerQT[i];
            printf("\n combined QT Process is %.d ", combinedQT[i]); //successfully separate
        }

     
/*
        //sort arrival time
        for(i=0; i<fileCount ; i++){
            for(j=0; j<fileCount;j++){
                if(jobArray[j][1] > jobArray[j+1][1]) //compare the arrival time between each process
                {
                    temp=process[j];
                    process[j]=process[j+1];
                    process[j+1]=temp; 
                }
            }
        }*?
        
/*
        for(i=0;i< fileCount;i++){
            int sum;
            sum = sum + backupBurstTime[i];
            turnAroundTime[i]= sum;
             avgTurnAroundTime += turnAroundTime[i]; 
        }

  */
        //shorest process wait time = 0;
        //wait time = turn around - burst time
        waitTime[0] = 0; 
        for(i=1; i < fileCount; i++){
            waitTime[i] = 0; 
            for(j=0;j<i;j++){
                waitTime[i] += backupBurstTime[j]; //adding up the wait time
            }
            avgWaitTime += waitTime[i]; //avg time must be place here   
            
        }

    
    
    
        //turn around time
        for(i=0; i< fileCount; i++){
        //turn around time = burst time + waiting time 
        //turn around time = exit time - arrival time
            turnAroundTime[i] = backupBurstTime[i] + waitTime[i];
            //exitTime[i] =  turnAroundTime[i] + jobArray[fileCount][1];
            avgTurnAroundTime += turnAroundTime[i]; 
        }
    

    
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
 



