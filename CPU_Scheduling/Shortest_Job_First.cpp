#include<iostream>
#include<limits.h>
using namespace std;

class Process
{
    public:
    int pid;
    int arrival;
    int burst;
    int completion;
    int tat;
    int wt;
    void getData()
    {
        cout<<"Enter Process ID: ";
        cin>>pid;cout<<endl;
        cout<<"Enter Arrival Time: ";
        cin>>arrival;cout<<endl;
        cout<<"Enter Burst Time: ";
        cin>>burst;cout<<endl;
    }
    
};

void findSJF(Process p[], int n)
{
        //Array of n objects
        //sort the array according to the arrival time
        //Using bubble sort
        for(int i=0;i<n-1;i++)
        {
            for(int j=0;j<n-i-1;j++)
            {
                if(p[j].arrival>p[j+1].arrival)
                {
                    //Swap Process p[j] with p[j+1]
                    Process t=p[j];
                    p[j]=p[j+1];
                    p[j+1]=t;
                }
            }
        }
        int arrival=p[0].arrival;
        //Sort the Processes with this arrival time according to burst time
        for(int i=0;i<n-1;i++)
        {
            for(int j=0;j<n-i-1;j++)
            {
                if((p[j].arrival==arrival && p[j+1].arrival==arrival) && p[j].burst>p[j+1].burst)
                {
                    //swap p[j] with p[j+1]
                    Process t=p[j];
                    p[j]=p[j+1];
                    p[j+1]=t;
                }
                if(p[j+1].arrival>p[j].arrival)
                {
                    arrival=p[j+1].arrival;
                }
            }
        }
        //Completion time is arrival time + burst time
        p[0].completion=p[0].arrival+p[0].burst;
        //Turn around time is completion time - arrival time
        p[0].tat=p[0].completion-p[0].arrival;
        //Waiting time is turn around time-burst time
        p[0].wt=p[0].tat-p[0].burst;
        int completion=p[0].completion;
        int isComplete[n];
        for(int i=0;i<n;i++)
        {
            isComplete[i]=0;
        }
        isComplete[0]=1;
        
        //Calculate completion, turnaround, waiting time for the remaining processes
        for(int i=1;i<n;i++)
        {
            int minBurst=INT_MAX;
            int index=-1;

            //find the process with the minimum burst time provided it has arrived and it is not complete
            for(int j=1;j<n;j++)
            {
                if(!isComplete[j] && p[j].arrival<=completion && p[j].burst<minBurst)
                {
                    minBurst=p[j].burst;
                    index=j;
                }
               
            }
                //Now the index has the index of the process that has arrived and has the minimum burst time, run this process
                if(index!=-1)
                {
                    //completion time of the new process is the completion time of the previous process+ burst time of current process
                    p[index].completion=completion+p[index].burst;
                    p[index].tat=p[index].completion-p[index].arrival;
                    p[index].wt=p[index].tat-p[index].burst;
                    completion=p[index].completion;
                    isComplete[index]=1;
                }
        }
        cout<<"\nPID\tArrival\tBurst\tCompletion\tTAT\tWT\t\n";
        for(int i=0;i<n;i++)
        {
            cout<<p[i].pid<<"\t"<<p[i].arrival<<"\t"<<p[i].burst<<"\t"<<p[i].completion<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\n";

        }
}

int main()
{
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;cout<<endl;
    Process p[n];
    for(int i=0;i<n;i++)
    {
        p[i].getData();
    }
    findSJF(p,n);
}
