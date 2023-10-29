#include <stdlib.h>
#include <stdio.h>

int main() {
    int pn = 0;
    int CPU = 0;
    int allTime = 0;

    printf("No. of Processes: ");
    scanf("%d", &pn);

    int AT[pn];
    int ATt[pn];
    int NoP = pn;
    int PT[pn];
    int PP[pn];
    int PPt[pn];
    int waittingTime[pn];
    int turnaroundTime[pn];

    int i = 0;
    for (i = 0; i < pn; i++) {
        printf("\nBurst Time P%d: ", i + 1);
        scanf("%d", &PT[i]);
        printf("Priority P%d: ", i + 1);
        scanf("%d", &PP[i]);
        PPt[i] = PP[i];
        printf("Arrival Time P%d: ", i + 1);
        scanf("%d", &AT[i]);
        ATt[i] = AT[i];
    }

    int LAT = 0;
    for (i = 0; i < pn; i++)
        if (AT[i] > LAT)
            LAT = AT[i];

    int MAX_P = 0;
    for (i = 0; i < pn; i++)
        if (PPt[i] > MAX_P)
            MAX_P = PPt[i];

    int ATi = 0;
    int P1 = PPt[0];
    int P2 = PPt[0];
    int j = -1;

    while (NoP > 0 && CPU <= 1000) {
        for (i = 0; i < pn; i++) {
            if ((ATt[i] <= CPU) && (ATt[i] != (LAT + 10))) {
                if (PPt[i] != (MAX_P + 1)) {
                    P2 = PPt[i];
                    j = 1;
                    if (P2 < P1) {
                        j = 1;
                        ATi = i;
                        P1 = PPt[i];
                        P2 = PPt[i];
                    }
                }
            }
        }

        if (j == -1) {
            CPU = CPU + 1;
            continue;
        } else {
            waittingTime[ATi] = CPU - ATt[ATi];
            CPU = CPU + PT[ATi];
            turnaroundTime[ATi] = CPU - ATt[ATi];
            ATt[ATi] = LAT + 10;
            j = -1;
            PPt[ATi] = MAX_P + 1;
            ATi = 0;
            P1 = MAX_P + 1;
            P2 = MAX_P + 1;
            NoP = NoP - 1;
        }
    }

    printf("\nPN\tPT\tPP\tAT\tWT\tTT\n\n");
    for (i = 0; i < pn; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, PT[i], PP[i], AT[i], waittingTime[i], turnaroundTime[i]);
    }

    int AvgWT = 0;
    int AVGTaT = 0;
    for (i = 0; i < pn; i++) {
        AvgWT = waittingTime[i] + AvgWT;
        AVGTaT = turnaroundTime[i] + AVGTaT;
    }

    printf("Avg Waitting Time = %d\nAvg Turnaround Time = %d\n", AvgWT / pn, AVGTaT / pn);

    return 0;
}

