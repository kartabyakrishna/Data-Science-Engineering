#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int rem_time;
    int priority;
} Process;

Process *Entry()
{
    printf("No. of Processes:");
    int n;
    scanf("%d", &n);
    Process *p = (Process *)malloc((n + 1) * sizeof(Process));
    printf("Enter PID, Arrival Time, Burst Time, Priority\n");
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Process %d :", i + 1);
        scanf("%d %d %d %d", &p[i].pid, &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].rem_time = p[i].burst_time;
    }
    p[n].pid = -1;
    return p;
}

void RR()
{
    Process *p = Entry();
    int n = 0;
    while (p[n].pid != -1)
        n++;
    int q;
    printf("Enter Time Slice:");
    scanf("%d", &q);
    int timer = 0;
    int done = 0;
    float TAT = 0;
    float WAT = 0;
    while (done != n)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            int count = q;
            int start = timer;
            while (p[i].rem_time > 0 && p[i].arrival_time <= timer && count > 0)
            {
                timer++;
                p[i].rem_time--;
                count--;
            }
            if (start != timer)
            {
                printf("%d -> (%d %d)\n", p[i].pid, start, timer);
                if (p[i].rem_time == 0)
                {
                    TAT += (timer - p[i].arrival_time);
                    WAT += (timer - p[i].arrival_time - p[i].burst_time);
                    done++;
                }
            }
        }
    }
    TAT = TAT / n;
    WAT = WAT / n;
    printf("Turnaround Time = %0.2f ms \n", TAT);
    printf("Waiting Time = %0.2f ms\n\n\n", WAT);
}

int main()
{
    RR();
    return 0;
}

