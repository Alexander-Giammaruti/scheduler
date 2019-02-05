#ifndef _priorityQ_H
#define _priorityQ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct process{
	int ID, arrival, priority, burst, currBurstTime, completionTime;	
};
typedef struct process *pPointer;

struct qNode{
	pPointer thisOne;
	struct qNode *next;
};
typedef struct qNode *qPointer;

qPointer newQNode(pPointer toInsert);
void insertQueue(qPointer toInsert, qPointer *head);
void removeQueue(qPointer *head);
void printQueue(qPointer head);
void dropQueue(qPointer head);
#endif
