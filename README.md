# CPU Scheduling Algorithms Simulator

## Project Overview

This project is a comprehensive simulator for various common CPU scheduling algorithms. The simulator is designed to emulate the behavior of a CPU scheduler by assigning a set of predefined tasks and scheduling them based on different algorithms. Each task is associated with a specific priority and CPU burst duration.

### Implemented Scheduling Algorithms:

- **First-Come, First-Served (FCFS):** Schedules tasks in the order they request the CPU.
- **Shortest-Job-First (SJF):** Prioritizes tasks with the shortest next CPU burst.
- **Priority Scheduling:** Schedules tasks based on their priority.
- **Round-Robin (RR):** Each task runs for a set time quantum or the remainder of its CPU burst.
- **Priority with Round-Robin:** Combines priority scheduling and round-robin for tasks with equal priority.

### Task Prioritization

- Priorities are assigned from 1 to 10 (10 being the highest priority).
- For RR scheduling, the time quantum is set to 10 milliseconds.

## Implementation

The implementation is done in C, with program files provided in the `StartKit-Code` folder. The files handle task scheduling, list management, and invocation of the scheduler algorithms.

### Task Format

Tasks are formatted as `[task name][priority][CPU burst]`. For example:
    
    T1, 4, 20   
    T2, 2, 25   
    T3, 3, 25   
    T4, 3, 15   
    T5, 10, 10  
    
Processes should be run in the order they appear in the input. Processes with equal priorities or burst times should be 
executed in the order they appear in the input.

## Implementation Details
The file `driver.c` reads in the schedule of tasks, inserts each task into a linked list, and invokes the process 
scheduler by calling the `schedule()` function. The `schedule()` function executes each task according to the specified 
scheduling algorithm. Tasks selected for execution on the CPU are determined by the `pickNextTask()` function and are 
executed by invoking the `run()` function defined in the `CPU.c` file. A `Makefile` is used to determine the specific 
scheduling algorithm that will be invoked by driver. For example, to build the FCFS scheduler, we would enter:
        
    make fcfs  
and would execute the scheduler (using the schedule of tasks `schedule.txt`) as follows:  
    
    ./fcfs schedule.txt 

## Evaluating  Implementation
You can see the correct outputs for all algorithms for a sample input [here](CorrectOutput.md).
