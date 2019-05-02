#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node* next;
	struct Node* previous;		
} Node;

typedef struct Stack {
	int size;
	struct Node* stackPointer;
} Stack;


Stack* stackCreate() {
	
	Stack* stack = malloc(sizeof(Stack));
	
	if (stack != NULL) {
		stack->stackPointer = NULL;
		stack->size = 0;
	}
	
	return stack;
}

int stackIsEmpty(Stack* stack) {
	
	if (stack->size == 0)
		return 1;
	else
		return 0;
}

int stackSize(Stack* stack) {
	
	return stack->size;
	
}

int stackPush(Stack* stack, int value) {
	
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL)
		return 0;
	
	newNode->key = value;
	newNode->next = NULL;
	
	if (stack->stackPointer == NULL) {
		
		newNode->previous = NULL;
		stack->stackPointer = newNode;
		stack->size++;
		
		return 1;
	}
	
	else {
		
		newNode->previous = stack->stackPointer;
		stack->stackPointer->next = newNode;
		stack->stackPointer = newNode;
		stack->size++;
		
		return 1;
	}
		
}

int stackPop(Stack* stack) {
	
	int value = stack->stackPointer->key;
	
	if (stack->size == 1) {
		
		free(stack->stackPointer);
		stack->stackPointer = NULL;
		stack->size = 0;
		
	}
	
	else if (stack->size > 1) {
		
		Node* node = stack->stackPointer;
		stack->stackPointer = stack->stackPointer->previous;
		stack->stackPointer->next = NULL;
		free(node);
		stack->size--;
	}
	
	return value;
}


int main() {
	
	Stack* stack = stackCreate();
	
	stackPush(stack, 1);
	stackPush(stack, 2);
	stackPush(stack, 3);
	stackPush(stack, 4);
	stackPush(stack, 5);
	
	
	printf("Stack size: %d\n", stackSize(stack));
	
	int size = stackSize(stack);
	int i;

	for (i = 0; i < size; i++) {
		printf("%d\n", stackPop(stack));
	}
	
	printf("Stack size: %d\n", stackSize(stack));
	
	return 0;
}
