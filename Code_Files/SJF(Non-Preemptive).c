#include <stdio.h>



struct process {

    int pid;

    int at;

    int bt;

    int ct;

    int tat;

    int wt;

    int flag;

};



int main() {

    int n, i, j;

    int time = 0, count = 0;

    float avg_tat = 0, avg_wt = 0;



    printf("Enter number of processes: ");

    scanf("%d", &n);



    struct process p[n];





    for (i = 0; i < n; i++) {

        p[i].pid = i + 1;

        scanf("%d %d", &p[i].at, &p[i].bt);

        p[i].flag = 0;

    }





    while (count < n) {



        int min_index = -1;





        for (i = 0; i < n; i++) {



            if (p[i].flag== 0 &&

                p[i].at <= time) {



                if (min_index == -1 ||

                    p[i].bt < p[min_index].bt) {



                    min_index = i;

                }

            }

        }





        if (min_index == -1) {

            time++;

            continue;

        }





        time += p[min_index].bt;



        p[min_index].ct = time;



        p[min_index].tat =p[min_index].ct - p[min_index].at;



        p[min_index].wt =p[min_index].tat - p[min_index].bt;



        p[min_index].flag = 1;



        count++;



    }





    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");



    for (i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",

               p[i].pid,

               p[i].at,

               p[i].bt,

               p[i].ct,

               p[i].tat,

               p[i].wt);

    }





    return 0;

}
