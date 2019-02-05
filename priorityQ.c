#include "priorityQ.h"

qPointer newQNode(pPointer toInsert){
	qPointer temp = malloc(sizeof(struct qNode));
	(*temp).thisOne = toInsert;
	(*temp).next = NULL;
	return temp;
}

void insertQueue(qPointer toInsert, qPointer *head){
	qPointer P1 = *head, P2 = *head;
	
	while((P1 != NULL) && ((*(*toInsert).thisOne).priority >= (*(*P1).thisOne).priority)){
		P2 = P1; P1 = (*P1).next;		

	}// end while
	if(P1 == *head){
		(*toInsert).next = *head;
		*head = toInsert;
	}else{
		(*P2).next = toInsert;
		(*toInsert).next = P1;

	}// end if
	
}// end insertQueue

void removeQueue(qPointer *head){
	qPointer del = *head;
	*head = (*del).next; 
	free(del);
}// end removeQueue

void printQueue(qPointer head){
	qPointer printIt = head;
	while(printIt != NULL){
		printf("\tPID: %d --> ",(*(*printIt).thisOne).ID);
		printIt = (*printIt).next;
	}// end while
	printf("\n");
}

void dropQueue(qPointer head){
	qPointer del;
	while(head != NULL){
        	del = head;
		head = (*head).next;
		free(del);
	}// end while

}

	//FOR TESTING PURPOSES LEAVE COMMENTED AND COMPILE ALONGSIDE MAIN.C IN A MAKEFILE
/*
int main(){
	qPointer head = NULL;
	struct process arr[5];
	for(int i = 0; i < 5; i++){
	scanf("%d %d %d", &arr[i].arrival, &arr[i].priority, &arr[i].burst);
	arr[i].ID = i;
	printf("attempting to insert\n");
	insertQueue(newQNode(&arr[i]), &head);
	printf("%d inserted\n", i);
	printQueue(head);
	}// end for
	removeQueue(&head);
	printQueue(head);	
}
*/
