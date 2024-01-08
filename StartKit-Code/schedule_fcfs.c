#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "cpu.h"
#include "schedulers.h"
#include "list.h"

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
    newTask->next = NULL;    
    tail = newTask;
}
}

void schedule() {
int totalBurstTime = 0;
float totalTurnAroundTime = 0;
float totalWaitTime = 0;
float totalResponseTime = 0;
float averageTurnaround=0;
float averageResponseTime=0;
float averageWaitime=0;
struct node *current = head;    
while (current !=NULL) {
    numOfTasks++;
    run(current->task,current->task->burst);  
    totalBurstTime+= current->task->burst;
    totalTurnAroundTime+= totalBurstTime; 
    if (current->next !=NULL) {
        totalResponseTime+= totalBurstTime;
    }

    current = current->next;    
}
totalWaitTime = totalTurnAroundTime - totalBurstTime;
averageWaitime=totalWaitTime/numOfTasks;
averageResponseTime=totalResponseTime/numOfTasks;
averageTurnaround=totalTurnAroundTime/numOfTasks;
printf("\nAverage waiting time = %0.2f\n" ,averageWaitime);    
printf("Average turnaround time = %0.2f\n" ,averageTurnaround);    
printf("Average response time = %0.2f\n" ,averageResponseTime);    

}






