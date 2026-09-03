#include <stdio.h>

#define MAX 100

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[MAX], bt[MAX], rt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int queue[MAX * 10], front = 0, rear = 0;
    int visited[MAX] = {0};
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    /* Simple simulation: at each time step, build/update the queue */
    queue[rear++] = 0;
    visited[0] = 1;
    time = at[0];

    while (completed < n) {
        int idx = queue[front++];

        if (rt[idx] > 0) {
            int slice = (rt[idx] < tq) ? rt[idx] : tq;
            time += slice;
            rt[idx] -= slice;

            /* Add any newly arrived processes to the queue */
            for (int i = 0; i < n; i++) {
                if (!visited[i] && at[i] <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            if (rt[idx] > 0) {
                queue[rear++] = idx;   /* not finished, go to back of queue */
            } else {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                total_tat += tat[idx];
                total_wt += wt[idx];
                completed++;
            }
        }

        /* If queue empties but processes remain, jump time to next arrival */
        if (front == rear && completed < n) {
            int next = -1;
            for (int i = 0; i < n; i++)
                if (!visited[i] && (next == -1 || at[i] < at[next]))
                    next = i;
            if (next != -1) {
                time = at[next] > time ? at[next] : time;
                queue[rear++] = next;
                visited[next] = 1;
            }
        }
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT  = %.2f\n", total_wt / n);
    return 0;
}
