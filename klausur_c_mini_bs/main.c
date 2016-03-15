//
//  main.c
//  klausur_c_mini_bs
//
//  Created by ursus on 15.03.16.
//  Copyright © 2016 Ursus Schneider. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _task task_t;
typedef struct _task {
    
    void (* init) (task_t * self, uint taskID, uint16_t eventID);
    void (* poll) (task_t * self);
    void (* processEvent) (task_t * self, uint16_t taskID);
    int taskID;
    uint16_t eventID;
    task_t * next_task;
    
} task_t;

void init (task_t * self, uint taskID, uint16_t eventID) {
    printf ("in init. taskID: %i    eventID: %i\n", taskID, eventID);
    self->taskID = taskID;
    self->eventID = eventID;
}
void myPoll (task_t * self) {
    printf ("in polling. taskID: %i\n", self->taskID);
}
void processEvent (task_t * self, uint16_t taskID) {
    if (taskID == self->taskID) {
        printf ("in process. taskID: %i not my task!", self->taskID);
    } else {
        printf ("in process. taskID: %i YAY my task (%i)!", self->taskID, taskID);
    }
}

void createTask (task_t ** taskList, uint16_t eventID) {

    static int taskID = 1;
    
    // create a new task
    task_t * newTask = NULL;
    newTask = malloc (sizeof(task_t));
    newTask->init = &init;
    newTask->poll = &myPoll;
    newTask->processEvent = &processEvent;
    newTask->init (newTask, taskID, eventID);
    taskID++;
    
    // get the end of the list
    if (*taskList == NULL) {
        *taskList = newTask;
    } else {
        task_t * lastElement;
        lastElement = *taskList;
        while (lastElement->next_task != NULL)
            lastElement = lastElement->next_task;
        lastElement->next_task = newTask;
    }
    
}

int main(int argc, const char * argv[]) {

    // head of list
    task_t * tasks = NULL;

    // create your tasks
    createTask (&tasks, 10);
    createTask (&tasks, 20);
    createTask (&tasks, 30);
    
    uint16_t i = 10;
    while (1 == 1) {
        task_t * currElement;
        currElement = tasks;
        while (currElement != NULL) {
            
            currElement->poll (currElement);
            currElement->processEvent (currElement, i);
            i++;
            currElement = currElement->next_task;
        
        }
    }

}
