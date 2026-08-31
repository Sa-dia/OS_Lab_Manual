#include <stdio.h>

#include <limits.h>



int main() {

    int n;



    printf("Enter number of processes: ");

    scanf("%d", &n);



    int at[n], bt[n], rt[n];

    int ct[n], tat[n], wt[n];





    for (int i = 0; i < n; i++) {

        printf("\nProcess P%d\n", i + 1);



        printf("Arrival Time: ");

        scanf("%d", &at[i]);



        printf("Burst Time: ");

        scanf("%d", &bt[i]);



        rt[i] = bt[i];

    }



    int completed = 0;

    int currentTime = 0;





    while (completed < n) {



        int shortest = -1;

        int minRemaining = INT_MAX;





        for (int i = 0; i < n; i++) {

            if (at[i] <= currentTime &&

                rt[i] > 0 &&

                rt[i] < minRemaining) {



                minRemaining = rt[i];

                shortest = i;

            }

        }





        if (shortest == -1) {

            currentTime++;

            continue;

        }





        rt[shortest]--;

        currentTime++;





        if (rt[shortest] == 0) {

            completed++;



            ct[shortest] = currentTime;

            tat[shortest] = ct[shortest] - at[shortest];

            wt[shortest] = tat[shortest] - bt[shortest];

        }

    }





    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");



    float avgWT = 0, avgTAT = 0;



    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",

               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);



        avgWT += wt[i];

        avgTAT += tat[i];

    }



    printf("\nAverage Waiting Time = %.2f", avgWT / n);

    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);



    return 0;

}
