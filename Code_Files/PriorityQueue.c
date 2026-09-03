#include <stdio.h>
#include <limits.h>

#define MAX 100

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[MAX], bt[MAX], pr[MAX];
    int remaining[MAX], started[MAX] = {0};
    int ct[MAX], tat[MAX], wt[MAX], response[MAX];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, priority (lower = higher) for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        remaining[i] = bt[i];
    }

    int time = 0, completed = 0, running = -1;
    float total_tat = 0, total_wt = 0;

    printf("\n--- Execution Trace ---\n");

    while (completed < n) {

        /* Step 1: find highest-priority process among arrived, unfinished processes */
        int candidate = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining[i] > 0) {
                if (candidate == -1 || pr[i] < pr[candidate]) {  /* checking weither eligible candidate is arrived or not*/
                    candidate = i;
                } else if (pr[i] == pr[candidate] && at[i] < at[candidate]) {
                    candidate = i;   /* tie-break: earlier arrival wins */
                }
            }
        }

        /* Step 2: nobody has arrived yet -> fast-forward time */
        if (candidate == -1) {
            time++;
            continue;
        }

        /* Step 3: detect a context switch */
        if (candidate != running) {
            printf("Time %d: switch to P%d (priority %d)\n", time, candidate + 1, pr[candidate]);
            running = candidate;
        }
        if (!started[candidate]) {
            response[candidate] = time - at[candidate];
            started[candidate] = 1;
        }

        /* Step 4: run for exactly one time unit */
        remaining[candidate]--;
        time++;

        /* Step 5: if finished, record stats */
        if (remaining[candidate] == 0) {
            ct[candidate] = time;
            tat[candidate] = ct[candidate] - at[candidate];
            wt[candidate] = tat[candidate] - bt[candidate];
            total_tat += tat[candidate];
            total_wt += wt[candidate];
            completed++;
            running = -1;
            printf("Time %d: P%d completed\n", time, candidate + 1);
        }
    }

    printf("\nP\tAT\tBT\tPr\tCT\tTAT\tWT\tRT(resp)\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i], response[i]);

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT  = %.2f\n", total_wt / n);

    return 0;
}
