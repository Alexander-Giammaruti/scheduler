#include"priorityQ.h"

int main(){
	
	qPointer head = NULL;
	
	int numProc, arrival, priority, burst;
	int totalTime = 0, timePassed = 0;
	int currCPU = -1; 
	float avgTA = 0.0;
	printf("Enter the number of processes: ");
	scanf("%d", &numProc);

	struct process processes[numProc];
	
	for(int i = 1; i <= numProc; i++){
		printf("Enter process %d arrival, priority, and burst: ", i);
		scanf("%d %d %d", &arrival, &priority, &burst);
		processes[i-1].ID = i;
		processes[i-1].arrival = arrival;
		processes[i-1].priority = priority;
		processes[i-1].burst = burst;
		processes[i-1].currBurstTime = 0;
		totalTime += processes[i-1].burst;
	}// end for	
	
	totalTime += processes[0].arrival;	
	int CPU[totalTime];
	for(int i = 0; i < totalTime; i++){
		CPU[i] = 0;
	}
		
	while(totalTime >= timePassed){ // begin simulation
		
		printf("\n\nTime %d begin\n\n", timePassed);
		//check for arrivals 
		if(timePassed <= processes[numProc-1].arrival){
			for(int i = 0; i < numProc; i++){
				if(processes[i].arrival == timePassed){
					insertQueue(newQNode(&processes[i]), &head);
					printf("Process %d arrived at time: %d\n", i+1, timePassed);
				}// end if
			}// end for
		}// end if (check for arrivals)
		
		if(head!=NULL){	
			currCPU = (*(*head).thisOne).ID-1;		
				
			printf("Process %d currently running\n", currCPU+1);
			//check for process exit
			if(processes[currCPU].burst == 0){
			printf("Process %d completed at time %d\n", currCPU+1, timePassed);
			processes[currCPU].completionTime = timePassed;
			removeQueue(&head);
			if(totalTime  >  timePassed){
				currCPU = (*(*head).thisOne).ID-1;
				printf("Process %d dispatched to CPU\n", currCPU+1);
				}
			}// end if	
		
			//check for preemption
			//if(currCPU+1 != (*(*head).thisOne).ID){	// check for priority preempt
			//	printf("Process %d preempted by process %d at time %d\n", currCPU+1, (*(*head).thisOne).ID, timePassed);
			//	currCPU = (*(*head).thisOne).ID;
			
			/*}else*/ if(head != NULL && (*head).next != NULL){		//check for round robin preempt
				if( (*(*head).thisOne).priority == (*(*(*head).next).thisOne).priority && processes[currCPU].currBurstTime >= 2){
					removeQueue(&head);
					insertQueue(newQNode(&processes[currCPU]), &head);
					printf("Process %d preempted by process %d at time %d\n", currCPU+1, (*(*head).thisOne).ID, timePassed);
					processes[currCPU].currBurstTime = 0;
					currCPU = (*(*head).thisOne).ID-1;
				}// end if	
			}// end if	
			

			if(currCPU != -1){
				processes[currCPU].currBurstTime++;
				processes[currCPU].burst--;
				CPU[timePassed] = currCPU+1;	
			}// end if
		}// end if
		sleep(1);
		timePassed++;
	}// end while (sim)

	processes[currCPU].completionTime = timePassed-1;
	
	printf("\n\nGantt chart (0 indicates empty space):\n\t");
	for(int i=0; i < totalTime; i++){
		if(i < 10){
			printf("%d___", i);
		}else if(i < 100 && i >= 10){
			printf("%d__", i);
		}else{
			printf("%d", i);
		}// end if
	}printf("%d\n\t", totalTime);

	for(int i=0; i < totalTime; i++){
		printf("|_%d_", CPU[i]);
	}printf("|\n\n");

	for(int i = 0; i < numProc; i++){
		printf("Process %d turnaround: %d\n", i+1, processes[i].completionTime - processes[i]. arrival);
		avgTA = avgTA + (processes[i].completionTime - processes[i].arrival);	
	}
	avgTA = avgTA / numProc;

	printf("Average turnaround  : %.3f\n", avgTA);
}
