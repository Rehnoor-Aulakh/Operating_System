#include<iostream>
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
};

void findRoundRobin(Process p[], int n)
{
    //First sort the Processes according to the arrival time
    //Bubble Sort
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].arrival>p[j+1].arrival)
            {
                //swap p[j] with p[j+1]
                Process t=p[j];
                p[j]=p[j+1];
                p[j+1]=t;
            }
        }
    }
    int remainingBurst[n];
    for(int i=0;i<n;i++)
    {
        remainingBurst[i]=p[i].burst;
    }
    int index=0;
    //Index of the process to be executed
    int currentTime=0;
    //Run the first process for one time quantum
    if(p[0].arrival<=currentTime)
    {
        remainingBurst[0]--;
        currentTime++;
    }
    else
    {
        currentTime=p[0].arrival;
        currentTime++;
        remainingBurst[0]--;
    }
    int completed=0;
    if(remainingBurst[0]==0)
    {
        completed++;
        p[0].completion=currentTime;
        p[0].tat=p[0].completion-p[0].arrival;
        p[0].wt=p[0].tat-p[0].burst;
    }
    index++;
    while(completed!=n)
    {

        //Execute the index process provided it has arrived
        if(p[index].arrival<=currentTime && remainingBurst[index]>0)
        {
            currentTime++;
            remainingBurst[index]--;
            if(remainingBurst[index]==0)
            {
                completed++;
                p[index].completion=currentTime;
                p[index].tat=p[index].completion-p[index].arrival;
                p[index].wt=p[index].tat-p[index].burst;
            }
            index=(index+1)%n;
        }
        else
        {
            //Next process has either not arrived or the burst time of the index process is 0
            if(remainingBurst[index]==0 && completed!=n)
            {
                while(remainingBurst[index]==0)
                {
                    index=(index+1)%n;
                }
            }
            else
            {
                //Next Process has not arrived, simply increment current Time
                currentTime++;
            }
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
    cout<<"Enter the Number of processes: ";
    cin>>n;cout<<endl;
    Process p[n];
    for (int i = 0; i < n; i++) 
    {
        cout << "\nEnter details for Process " << i + 1 << ":\n";
        cout<<endl;
        cout << "Process ID: ";
        cin >> p[i].pid;cout<<endl;
        cout << "Arrival Time: ";
        cin >> p[i].arrival;cout<<endl;
        cout << "Burst Time: ";
        cin >> p[i].burst;cout<<endl;
    }
    findRoundRobin(p,n);

}