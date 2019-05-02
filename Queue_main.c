#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node* next;
} Node;

typedef struct Queue {
	int size;
	struct Node* front;
	struct Node* back;
} Queue;

Queue* createQueue() {
	
	Queue* queue = malloc(sizeof(Queue));
	
	if (queue != NULL) {
		
		queue->size = 0;
		queue->front = NULL;
		queue->back = NULL;
		
	}
	
	return queue;
}

int isEmpty(Queue* queue) {
	
	if (queue->size == 0)
		return 1;
	else
		return 0;
		
}

int size(Queue* queue) {
	
	return queue->size;
	
}

int front(Queue* queue) {
	
	return queue->front->key;

}

int enqueue(Queue* queue, int value) {
	
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL)
		return 0;
		
	newNode->key = value;
	
	if (queue->size == 0) {
		
		queue->front = newNode;
		queue->back = newNode;
		newNode->next = NULL;
		queue->size++;
		
		return 1;
		
	}
	
	else {
	
		newNode->next = queue->back;
		queue->back = newNode;
		queue->size++;
		
		return 1;
		
	}
	
}

int dequeue(Queue* queue) {
	
	if (queue->front == queue->back) {
		
		int value = queue->front->key;
		free(queue->front);
		queue->front = NULL;
		queue->back = NULL;
		queue->size--;
		
		return value;
		
	}
	
	else {
		
		int value = queue->front->key;
		
		Node* node = queue->back;
		
		while (node->next != queue->front) {
			node = node->next;
		}
		
		queue->front = node;
		free(node->next);
		node->next = NULL;
		queue->size--;
		
		return value;
		
	}
}

int main() {
	
	Queue* q = createQueue();
	
	enqueue(q, 10);
	enqueue(q, 2);
	enqueue(q, 4);
	
	printf("Front:%d\n", front(q));
	
	printf("Size:%d\n\n", size(q));
	
	int queueSize = size(q);
	int i;
	for(i = 0; i < queueSize; i++) {
		printf("%d\n", dequeue(q));
	}
	
	printf("\n\nSize after dequeue:%d\n", size(q));
	
	
	return 0;
}
