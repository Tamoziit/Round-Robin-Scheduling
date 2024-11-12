# Round-Robin-Scheduling
Round Robin Scheduling Algorithm Simulation in C

## Project Structure
- `main.c`: The main control file that initializes & creates threads, and manages scheduling.
- `table1.c`: Displays initial process information.
- `processSorter.c`: Contains functions for sorting processes based on arrival time.
- `ReadyQueue.c`: Implements a queue data structure for process management.
- `scheduler.c`: Contains the logic for the scheduling algorithm.
- `table2.c`: Displays the final process table with computed metrics.
- `processDef.h` and `queueDef.h`: Header files with type definitions for processes & queues.

## Compilation
To compile the program, use the following script:

```bash
gcc main.c table1.c processSorter.c ReadyQueue.c scheduler.c table2.c -o RR.out -lpthread
