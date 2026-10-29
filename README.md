# Process Scheduling Simulation — FCFS & SJF

## Description

This assignment implements two CPU scheduling algorithms in C:

- First Come First Served (FCFS)
- Shortest Job First (SJF), non-preemptive

The program takes the arrival time and burst time of each process and calculates waiting time, turnaround time, and response time. It also displays a Gantt chart and the average times for both algorithms.

## Requirements

- Linux operating system
- GCC compiler

## How to Run

**1. Compile the program:**

```bash
gcc scheduler.c -o scheduler
```

**2. Run the program:**

```bash
./scheduler
```

**3. Enter the process information:**

```text
Enter the number of processes: 4
Enter the arrival time and burst time for process 1: 0 8
Enter the arrival time and burst time for process 2: 1 4
Enter the arrival time and burst time for process 3: 2 9
Enter the arrival time and burst time for process 4: 3 5
```

## Algorithms

### FCFS

Processes execute in order of arrival time. Once a process starts, it runs until completion.

### SJF

The scheduler selects the process with the shortest burst time among the processes that have already arrived. Once execution starts, the process cannot be interrupted.

## Calculations

- Turnaround Time = Completion Time - Arrival Time
- Waiting Time = Turnaround Time - Burst Time
- Response Time = Start Time - Arrival Time

## Sample Results

| Metric | FCFS | SJF |
|---|---|---|
| Average Waiting Time | 8.75 | 7.75 |
| Average Turnaround Time | 15.25 | 14.25 |
| Average Response Time | 8.75 | 7.75 |

## Features

- Supports up to 100 simulated processes
- Handles processes arriving at the same time
- Handles CPU idle time
- Displays Gantt charts
- Calculates individual and average scheduling times
- Validates user input

## Screenshots

Add screenshots of the program running in the Linux terminal.

## Files

- `scheduler.c` — C source code
- `README.md` — Project documentation
- `screenshots/` — Execution screenshots
