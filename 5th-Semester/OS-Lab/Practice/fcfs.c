#include <stdio.h>
#define max 30
int  main(){
        int i, j, n, bt[max], at[max],wt[max], tat[max], temp[max];
        float awt=0,atat =0;
        printf("enter the number of process");
        scanf("%d", &n);
        printf("enter the bt");
        for(i=0;i<n;i++){
        scanf("%d", &bt[i]);
        }
        printf("enter the at");
        for(i=0;i<n;i++){
        scanf("%d", &at[i]);
        }
        temp[0]=0;
        for(i=0;i<n;i++){
        wt[i]=0;
        tat[i]=0;
        temp[i+1]=temp[i]+bt[i];
        wt[i]=temp[i]-at[i];
        tat[i] =wt[i]+bt[i];
        awt = awt+wt[i];
        atat= atat+tat[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d",i+1, bt[i], at[i], wt[i], tat[i]);
        }
        awt= awt/n;
        atat= atat/n;
        printf("avg waiting time = %f\n",awt);
        printf("avg tat time = %f\n",atat);
        return -1 ;

}