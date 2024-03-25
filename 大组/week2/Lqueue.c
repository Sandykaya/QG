#include <stdio.h>
#include <stdlib.h>

// Define structure for queue node
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Define structure for queue
typedef struct {
    Node* front; // Front pointer of the queue
    Node* rear; // Rear pointer of the queue
    size_t length; // Length of the queue
} Queue;

// Create a queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->length = 0;
    return queue;
}

// Check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Enqueue operation
void enqueue(Queue* queue, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
    queue->length++;
}

// Dequeue operation
void* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        exit(1);
    }
    Node* temp = queue->front;
    void* data = temp->data;
    queue->front = temp->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->length--;
    return data;
}

// Get the front element of the queue
void* getFront(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        exit(1);
    }
    return queue->front->data;
}

// Get the length of the queue
size_t getLength(Queue* queue) {
    return queue->length;
}

// Clear the queue
void clearQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

// Destroy the queue
void destroyQueue(Queue* queue) {
    clearQueue(queue);
    free(queue);
}

int main() {
    Queue* queue = createQueue();

    int choice;
    do {
        printf("\nChoose operation:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Get front element\n");
        printf("4. Get queue length\n");
        printf("5. Clear queue\n");
        printf("6. exit\n");
        printf("Enter operation number: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                int* data = (int*)malloc(sizeof(int));
                printf("Enter integer to enqueue: ");
                scanf("%d", data);
                enqueue(queue, data);
                break;
            }
            case 2: {
                if (!isEmpty(queue)) {
                    int* data = (int*)dequeue(queue);
                    printf("Dequeued element: %d\n", *data);
                    free(data);
                } else {
                    printf("Queue is empty, cannot dequeue!\n");
                }
                break;
            }
            case 3: {
                if (!isEmpty(queue)) {
                    printf("Front element: %d\n", *(int*)getFront(queue));
                } else {
                    printf("Queue is empty!\n");
                }
                break;
            }
            case 4: {
                printf("Queue length: %zu\n", getLength(queue));
                break;
            }
            case 5: {
                clearQueue(queue);
                printf("Queue cleared!\n");
                break;
            }
            case 6: {
                destroyQueue(queue);
                printf("exiting program.\n");
                break;
            }
            default:
                printf("Invalid operation number, please try again!\n");
        }
    } while(choice != 6);

    return 0;
}
