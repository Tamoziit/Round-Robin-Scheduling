# Round-Robin-Scheduling
Round Robin Scheduling Algorithm Simulation in C

## Project Structure
- `main.c`: The main control file that initializes & creates threads, and manages scheduling.
- `table1.c`: Displays initial process information.
- `processSorter.c`: Contains functions for sorting processes based on arrival time.
- `ReadyQueue.c`: Implements a queue data structure for process management.
- `scheduler.c`: Contains the logic for the scheduling algorithm.
- `scheduler2.c`: Alternative Scheduling logic for testing purpose.
- `table2.c`: Displays the final process table with computed metrics.
- `processDef.h` and `queueDef.h`: Header files with type definitions for processes & queues.

## Getting Started
1. Clone the repository:
    ```bash
    git clone https://github.com/Tamoziit/Round-Robin-Scheduling.git

2. Navigate to the root of your project directory & compile the program, use the following script:
    ```bash
    gcc main.c table1.c processSorter.c ReadyQueue.c scheduler.c table2.c -o RR.out -lpthread

3. Execute the program:
    ```bash
    ./RR.out