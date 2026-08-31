#include <stdio.h>

struct process {



    int pid;



    int at;



    int bt;



    int ct;



    int tat;



    int wt;



};

int main() {



    int n;



    float avg_wt = 0, avg_tat = 0;







    printf("Enter number of processes: ");



    scanf("%d", &n);



  struct process p[n];



 for (int i = 0; i < n; i++) {



        p[i].pid = i + 1;



        scanf("%d %d", &p[i].at, &p[i].bt);



    }



    for (int i = 0; i < n - 1; i++) {



        for (int j = i + 1; j < n; j++) {



            if (p[i].at > p[j].at) {



                struct process temp = p[i];



                p[i] = p[j];



                p[j] = temp;



            }



        }



    }

 int time = 0;



  for (int i = 0; i < n; i++) {



        if (time < p[i].at)



            time = p[i].at;



        time += p[i].bt;



        p[i].ct = time;



        p[i].tat = p[i].ct - p[i].at;



        p[i].wt = p[i].tat - p[i].bt;





    }

printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");



    for (int i = 0; i < n; i++) {



        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",



               p[i].pid, p[i].at, p[i].bt,



               p[i].ct, p[i].tat, p[i].wt);



    }



  return 0;



}
