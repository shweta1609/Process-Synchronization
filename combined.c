//Sameer Chavan - 903315375
//Shweta Singhal - 903412345

#include<stdio.h>
#include <stdlib.h>
#include<omp.h>
#include <string.h>
#include<mpi.h>
#include<math.h>

struct CountingBarrier{
    int TotalRunningThreads;
    int countForBarrierInversion;
};

void initialize_CentralizedBarrier(struct CountingBarrier *struct_cBarrier,int *noOfThreads);

int dissemination_Barrier(int *rounds,int *processID,int *numofproccess);

void CentralizedBarrier();

int main(int argc, char *argv[])
{

//MPI ============
    int processID, numOfProcess;
    
    if(MPI_Init(&argc, &argv) || MPI_Comm_rank(MPI_COMM_WORLD,&processID) || MPI_Comm_size(MPI_COMM_WORLD,&numOfProcess))
    {
        printf("Error occurred while initializing MPI \nExiting....");
        exit(0);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    else
    {
        int rounds = (int)ceil(log(numOfProcess)/log(2));
        // if(processID==0)
        // printf("rounds  ======= %d\n",rounds);
        double start = MPI_Wtime();
        int abc = dissemination_Barrier(&rounds,&processID,&numOfProcess);
        
        if(abc)
        {
        printf("MPI Time = %f  ~ processID = %d\n",MPI_Wtime()-start,processID);    
        }
    }

    int /*factorial = 1,*/ i /*, factorialOF =15*/;
    struct CountingBarrier struct_cBarrier;
    int n=8;
    //numOfProcess = n;
    for(i =1;i<argc;i++)
    {
        if (!strcmp(argv[i],"-n"))
        {
            n= atoi(argv[i+1]);
            //printf("itheeeee     ===== %d",n);
        }
    }
    //printf("Start Time= %f",omp_get_wtime());
    //
    double time1=0;
    double totaltime=0;
    initialize_CentralizedBarrier(&struct_cBarrier,&n);
    #pragma omp parallel num_threads(n) private(time1) shared(totaltime) 
    {
        time1 =omp_get_wtime();
        if(omp_get_num_threads()!=n)
        {
            printf("Could not allocate the required number of threads\nExiting....");
            exit(0);
        }        
        // #pragma omp for lastprivate(i) nowait
        // for (i=1;i<=factorialOF;i++)
        // {
        //     #pragma omp critical
        //     factorial *=i;
        // //printf("Factorial = %d, thread num = %d\n",factorial,omp_get_thread_num());
        // }

        CentralizedBarrier(&struct_cBarrier);
        totaltime += omp_get_wtime()-time1;
    //printf("Factorial of %d is %d\n",i-1,factorial);
    }
    printf("Threads barrier time (Openmp) = %f  on processorID = %d\n",totaltime/n,processID);
    
    MPI_Finalize();
    return 0;
}

void initialize_CentralizedBarrier(struct CountingBarrier *struct_cBarrier,int *noOfThreads)
{
    struct_cBarrier->TotalRunningThreads = *noOfThreads;
    struct_cBarrier->countForBarrierInversion = *noOfThreads;
    //printf("Number of Threads %d\n",*noOfThreads );
}

void CentralizedBarrier(struct CountingBarrier *struct_cBarrier)
{
    #pragma omp critical
    {
        struct_cBarrier->countForBarrierInversion--;
        if(struct_cBarrier->countForBarrierInversion==0)
        {
            //printf("Thread no %d arrivied at barrier and is releasing others \n", omp_get_thread_num());
                struct_cBarrier->countForBarrierInversion =struct_cBarrier->TotalRunningThreads ;
        }
        else
        {
            //printf("Thread no %d arrived at barrier and waiting.....\n",omp_get_thread_num());
        }
    }
    //printf("Thread no %d arrived at barrier\n",omp_get_thread_num());
    while(struct_cBarrier->countForBarrierInversion!=struct_cBarrier->TotalRunningThreads);
    //printf("Thread no %d crossed Barrier\n",omp_get_thread_num());
}

int dissemination_Barrier(int *rounds,int *processID,int *numofproccess)
{
    int i=0;
    for(i = 0; i<*rounds;i++)
    {
        //if(*rounds==(i+1) && *processID==0)
        //printf("Everyone knows about everyone reaching barrier.....\nThreads can leave the barrier now\n");
        int toreceiveFrom,error;
            toreceiveFrom = *processID - pow(2,i) ;
            if(toreceiveFrom<0)
            {
                toreceiveFrom+=*numofproccess;
            } 
            int send = (*processID + pow(2,i));
            send = send % (*numofproccess);
            //printf("Process %d sending to %d , round =%d\n",*processID,send,i);
            MPI_Send(processID,1,MPI_INT,send,0,MPI_COMM_WORLD);
            int received;
            MPI_Status status;
            error =MPI_Recv(&received,1,MPI_INT,toreceiveFrom,0,MPI_COMM_WORLD,&status);
            if(error!=MPI_SUCCESS)
            {
                printf("Failed to receive message... Exiting...");
                exit(0);
            }
            //printf("Process %d received from %d , round =%d \n",*processID,received,i);
            // else
            // printf("failed na rao");
    }
    return 1;
}