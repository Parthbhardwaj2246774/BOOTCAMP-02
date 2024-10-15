#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Define the queue structure
typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

// Function to initialize the queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Function to check if the queue is full
int isFull(Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Function to add a floor request to the queue
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add more floor requests.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    printf("Floor %d requested.\n", value);
}

// Function to remove a floor request from the queue
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("No more floor requests.\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return value;
}

// Function to display the current queue of requests
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("No floor requests.\n");
        return;
    }
    printf("Current floor requests: ");
    int i = q->front;
    while (i != q->rear) {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX;
    }
    printf("%d\n", q->items[q->rear]);
}

// Simulate the lift movement
void liftMovement(Queue *q, int currentFloor) {
    while (!isEmpty(q)) {
        int nextFloor = dequeue(q);
        printf("Lift moving from floor %d to floor %d.\n", currentFloor, nextFloor);
        currentFloor = nextFloor;
    }
    printf("All requests processed. Lift is idle at floor %d.\n", currentFloor);
}

int main() {
    Queue q;
    initQueue(&q);

    int currentFloor = 0;  // Start at ground floor (0)

    int choice, floor;
    while (1) {
        printf("\n1. Request a floor\n2. Process requests\n3. Display requests\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the floor number: ");
                scanf("%d", &floor);
                enqueue(&q, floor);
                break;
            case 2:
                liftMovement(&q, currentFloor);
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

