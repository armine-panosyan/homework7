
#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

typedef struct {
    int pid;
    int start;
    int finish;
} Slot;

void show_results(const char *title, Process p[],
                  int order[], int n, Slot slots[], int count)
{
    double total_wait = 0;
    double total_turn = 0;
    double total_response = 0;

    printf("\n=== %s ===\n", title);

    printf("Gantt Chart: ");
    for (int i = 0; i < count; i++) {
        if (slots[i].pid == 0)
            printf("| IDLE ");
        else
            printf("| P%d ", slots[i].pid);
    }
    printf("|\n");

    printf("Time: ");
    if (count > 0)
        printf("%d", slots[0].start);

    for (int i = 0; i < count; i++)
        printf("  %d", slots[i].finish);

    printf("\n\nPID\tAT\tBT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++) {
        Process q = p[order[i]];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               q.pid, q.arrival_time, q.burst_time,
               q.waiting_time, q.turnaround_time,
               q.response_time);

        total_wait += q.waiting_time;
        total_turn += q.turnaround_time;
        total_response += q.response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wait / n);
    printf("Average Turnaround Time: %.2f\n", total_turn / n);
    printf("Average Response Time: %.2f\n", total_response / n);
}

void run_fcfs(Process input[], int n)
{
    Process p[MAX_PROCESSES];
    int order[MAX_PROCESSES];
    Slot slots[MAX_PROCESSES * 2];

    int count = 0;
    int current = 0;

    for (int i = 0; i < n; i++) {
        p[i] = input[i];
        order[i] = i;
    }

    // Sort by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Process a = p[order[i]];
            Process b = p[order[j]];

            if (b.arrival_time < a.arrival_time ||
               (b.arrival_time == a.arrival_time &&
                b.pid < a.pid)) {

                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        Process *q = &p[order[i]];

        if (current < q->arrival_time) {
            slots[count++] = (Slot){0, current, q->arrival_time};
            current = q->arrival_time;
        }

        int start = current;
        current += q->burst_time;

        q->response_time = start - q->arrival_time;
        q->waiting_time = q->response_time;
        q->turnaround_time = current - q->arrival_time;

        slots[count++] = (Slot){q->pid, start, current};
    }

    show_results("First Come First Served (FCFS)",
                 p, order, n, slots, count);
}

void run_sjf(Process input[], int n)
{
    Process p[MAX_PROCESSES];
    int order[MAX_PROCESSES];
    int done[MAX_PROCESSES] = {0};
    Slot slots[MAX_PROCESSES * 2];

    int current = 0;
    int count = 0;

    for (int i = 0; i < n; i++)
        p[i] = input[i];

    for (int k = 0; k < n; k++) {
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (done[i] || p[i].arrival_time > current)
                continue;

            if (best == -1 ||
                p[i].burst_time < p[best].burst_time ||
               (p[i].burst_time == p[best].burst_time &&
                p[i].arrival_time < p[best].arrival_time) ||
               (p[i].burst_time == p[best].burst_time &&
                p[i].arrival_time == p[best].arrival_time &&
                p[i].pid < p[best].pid)) {

                best = i;
            }
        }

        // CPU idle if no process is ready
        if (best == -1) {
            int next = INT_MAX;

            for (int i = 0; i < n; i++) {
                if (!done[i] && p[i].arrival_time < next)
                    next = p[i].arrival_time;
            }

            slots[count++] = (Slot){0, current, next};
            current = next;
            k--;
            continue;
        }

        Process *q = &p[best];

        int start = current;
        current += q->burst_time;

        q->response_time = start - q->arrival_time;
        q->waiting_time = q->response_time;
        q->turnaround_time = current - q->arrival_time;

        slots[count++] = (Slot){q->pid, start, current};

        done[best] = 1;
        order[k] = best;
    }

    show_results("Shortest Job First (SJF)",
                 p, order, n, slots, count);
}

int main(void)
{
    Process processes[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int at, bt;

        printf("Enter the arrival time and burst time for process %d: ", i + 1);

        if (scanf("%d %d", &at, &bt) != 2 ||
            at < 0 || bt <= 0 ||
            at > INT_MAX - bt ||
            at > INT_MAX / 2) {
            printf("Invalid arrival or burst time.\n");
            return 1;
        }

        processes[i] = (Process){i + 1, at, bt, 0, 0, 0};
    }

    run_fcfs(processes, n);
    run_sjf(processes, n);

    return 0;
}
