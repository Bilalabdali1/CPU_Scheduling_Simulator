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
void sortList(struct node **head) {
    struct node *sorted = NULL;
    struct node *current = *head;
    struct node *prev = NULL;
    struct node *temp = NULL;

    while (current != NULL) {
        temp = current->next;
        if (sorted == NULL || sorted->task->priority < current->task->priority) {
            current->next = sorted;
            sorted = current;
        } else {
            prev = sorted;
            while (prev->next != NULL && prev->next->task->priority >= current->task->priority) {
                prev = prev->next;
            }
            current->next = prev->next;
            prev->next = current;
        }
        current = temp;
    }
    *head = sorted;
}

int countPriorityTasks(struct node* head, int priority) {
    int count = 0;
    struct node* temp = head;
    while (temp != NULL) {
        if (temp->task->priority == priority && temp->task->burst > 0) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void schedule() {
sortList(&head);  
struct node *current;
float totalTurnaroundTime = 0;
float totalResponseTime = 0;
float totalWaitTime = 0;
int tasksRemaining = numOfTasks;
int currentTime = 0;
int currentPriority;
float averageTurnaround=0;
float averageResponseTime=0;
float averageWaitime=0;
if (head != NULL) {
    currentPriority = head->task->priority;
} 
else {
    currentPriority = -1;
}
    while (tasksRemaining > 0) {
        int processedInThisRound = 0;
        int nextPriority = -1;
        current = head;
        while (current != NULL) {
            if (current->task->priority == currentPriority && current->task->burst > 0) {
                int tasksWithCurrentPriority = countPriorityTasks(head, currentPriority);
                int responseTime = currentTime;
                int executionTime;
                if (tasksWithCurrentPriority == 1) {
                    executionTime = current->task->burst; 
                } else {
                    if (current->task->burst > 10) {
                    executionTime = 10;
    }   
                    else {
            executionTime = current->task->burst;
}
                }
                run(current->task, executionTime);
                current->task->burst -= executionTime;
                totalTurnaroundTime += (tasksRemaining * executionTime);
                totalWaitTime += ((tasksRemaining - 1) * executionTime);
                
                if (current->task->responseFlag == 0) {
                    totalResponseTime += responseTime;
                    current->task->responseFlag = 1;
                }
                if (current->task->burst == 0) {
                    tasksRemaining--;
                } else {
                    processedInThisRound++;
                }
                currentTime += executionTime;
            } 
            else if (current->task->priority < currentPriority && (nextPriority == -1 || current->task->priority > nextPriority)) {
                nextPriority = current->task->priority;
            }
            current = current->next;
        }
        if (processedInThisRound == 0 && nextPriority != -1) {
            currentPriority = nextPriority;
        }
    }
averageTurnaround=totalTurnaroundTime / numOfTasks;
averageWaitime=totalWaitTime/numOfTasks;
averageResponseTime=totalResponseTime/numOfTasks;
    printf("\nAverage waiting time = %0.2f\n", averageWaitime);    
    printf("Average turnaround time = %0.2f\n", averageTurnaround);    
    printf("Average response time = %0.2f\n", averageResponseTime);    
}