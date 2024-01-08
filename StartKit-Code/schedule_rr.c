
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

int numOfTasks = 0;
struct node *head = NULL;
struct node *newTask = NULL;
struct node *tail = NULL;
void add(char *name, int priority, int burst) {

if (head == NULL) {
    head = malloc(sizeof(struct node));
    tail = malloc(sizeof(struct node));
    head->task = malloc(sizeof(struct task));
    head->task->name = name;
    head->task->priority=priority;
    head->task->responseFlag=0;
    head->task->burst = burst;
    head->next = NULL;
    tail = head;
}    
else {
    
    newTask =  malloc(sizeof(struct node));    
    tail->next = newTask ;
    newTask->task = malloc(sizeof(struct task));
    newTask->task->name = name;
    newTask->task->priority = priority;
    newTask->task->burst = burst;
    newTask->task->responseFlag=0;
    newTask->next = NULL;    
    tail = newTask;
    
}
    numOfTasks++;
}

void schedule() {
struct node *current = head;
float totalTurnaroundTime = 0;
    float totalResponseTime = 0;
    float totalWaitTime = 0;
    float averageTurnaround=0;
    float averageResponseTime=0;
    float averageWaitime=0; 
    int tasksRemaining = numOfTasks;
    int currentTime = 0; 

     while (tasksRemaining > 0) {
        if (current == NULL) {
            current = head;
        }
        if (current->task->burst > 0) {
            int responseTime = currentTime;
    int executionTime;
    if (current->task->burst > 10) {
        executionTime = 10;
    } else {
        executionTime = current->task->burst;
}            

run(current->task, executionTime);
            current->task->burst -= executionTime;

            totalTurnaroundTime += (tasksRemaining * executionTime);
            totalWaitTime += ((tasksRemaining - 1) * executionTime);
            if(current->task->responseFlag==0){
            totalResponseTime += responseTime; 
            }
 
            if (current->task->burst == 0) {
                tasksRemaining--;
            }
            currentTime += executionTime;
                    current->task->responseFlag=1;

        }
        current = current->next;
    }
 averageWaitime=totalWaitTime/ numOfTasks;
averageTurnaround=totalTurnaroundTime/ numOfTasks;
averageResponseTime=totalResponseTime/ numOfTasks;
printf("\nAverage waiting time = %0.2f\n" ,averageWaitime);    
printf("Average turnaround time = %0.2f\n" ,averageTurnaround);    
printf("Average response time = %0.2f\n" ,averageResponseTime);    

}
