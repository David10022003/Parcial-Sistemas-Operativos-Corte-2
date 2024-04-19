#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10 
#define TOTAL_PROCESSES 90 


typedef struct {
    int id;
    int burst_time;
    int priority; 
    int time_slice; 
    int waiting_time; 
} Process;


typedef struct {
    Process *queue[MAX_PROCESSES];
    int front, rear;
} Queue;


void initializeQueue(Queue *q) {
    q->front = q->rear = -1;
}


int isEmpty(Queue *q) {
    return (q->front == -1);
}


int isFull(Queue *q) {
    return (q->rear == MAX_PROCESSES - 1);
}


int enqueue(Queue *q, Process *process) {
    if (isFull(q)) {
        return 0; 
    }

    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->queue[q->rear] = process;
    return 1;
}


Process *dequeue(Queue *q) {
    if (isEmpty(q)) {
        return NULL;
    }

    Process *process = q->queue[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return process;
}


void processExecution(Queue *queues[], Process *waitingList[], int *waitingCount) {
    for (int i = 0; i < 3; i++) {
        Queue *q = queues[i];
        if (!isEmpty(q)) {
            Process *process = dequeue(q);
            printf("Proceso %d en ejecución con tiempo de burst %d, prioridad %d y tiempo de espera %d\n", process->id, process->burst_time, process->priority, process->waiting_time);
            process->time_slice += 1;
            process->burst_time -= 1;

            if (process->time_slice >= 3) {
                process->priority = (process->priority > 0) ? process->priority - 1 : 0;
                process->time_slice = 0;
            }

            if (process->burst_time > 0) {
                enqueue(queues[process->priority], process);
            } else {
                free(process);
            }

            break;
        }
    }

    // Intentar encolar procesos en espera
    for (int i = 0; i < *waitingCount; i++) {
        Process *process = waitingList[i];
        process->waiting_time += 1;
        if (enqueue(queues[process->priority], process)) {
            for (int j = i; j < *waitingCount - 1; j++) {
                waitingList[j] = waitingList[j + 1];
            }
            (*waitingCount)--;
            i--;
        }
    }
}

int main() {
    Queue highPriority, mediumPriority, lowPriority;
    initializeQueue(&highPriority);
    initializeQueue(&mediumPriority);
    initializeQueue(&lowPriority);

    Queue *queues[3] = {&highPriority, &mediumPriority, &lowPriority};
    Process *waitingList[TOTAL_PROCESSES];
    int waitingCount = 0;

    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        Process *process = malloc(sizeof(Process));
        process->id = i + 1;
        process->burst_time = 10 - (i % 3);
        process->priority = 2 - (i % 3);
        process->time_slice = 0;
        process->waiting_time = 0;

        if (!enqueue(queues[process->priority], process)) {
            waitingList[waitingCount++] = process;
        }
    }

    while (!isEmpty(&highPriority) || !isEmpty(&mediumPriority) || !isEmpty(&lowPriority) || waitingCount > 0) {
        processExecution(queues, waitingList, &waitingCount);
    }

    return 0;
}
