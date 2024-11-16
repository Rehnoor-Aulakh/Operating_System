#include<iostream>
using namespace std;

class Process
{
    public:
    int pid;
    int arrival;
    int burst;
    int completion;
    int wt;
    int tat;
};

void findFCFS(Process p[], int n)
{
    //First sort the array according to the arrival time
    //Bubble sort
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].arrival>p[j+1].arrival)
            {
                //swap p[j] and p[j+1]
                Process t=p[j];
                p[j]=p[j+1];
                p[j+1]=t;
            }
        }
    }
    //Now that the Processes are sorted, we can begin calculation of completion time, waiting time and turnaround time
    //Running the first process
    //completion time is arrival time+ burst time
    int completion=p[0].arrival+p[0].burst;
    p[0].completion=completion;
    p[0].tat=p[0].completion-p[0].arrival;
    p[0].wt=p[0].tat-p[0].burst;
    //Now compute the following for the remaining processes provided they have arrived
    for(int i=1;i<n;i++)
    {
        if(p[i].arrival<=completion)
        {
            p[i].completion=completion+p[i].burst;
            p[i].tat=p[i].completion-p[i].arrival;
            p[i].wt=p[i].tat-p[i].burst;
            //update the completion time
            completion=p[i].completion;
        }
        else
        {
            //The process has not yet arrived
            completion=p[i].arrival+p[i].burst;
            p[i].tat=p[i].completion-p[i].arrival;
            p[i].wt=p[i].tat-p[i].burst;
        }
    }
    cout << "\nPID\tArrival\tBurst\tCompletion\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].completion << "\t\t" << p[i].tat << "\t" << p[i].wt << "\n";
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
        cout<<"Enter Process ID: ";
        cin>>p[i].pid;
        cout<<endl<<"Enter Arrival Time: ";
        cin>>p[i].arrival;
        cout<<endl<<"Enter Burst Time: ";
        cin>>p[i].burst;cout<<endl;

    }
    findFCFS(p,n);
}
