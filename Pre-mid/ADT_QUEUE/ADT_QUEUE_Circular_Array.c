#include <stdio.h>
#define MAX 0xA
#define size_arr 0xA

typedef struct{
	char data[MAX];
	int front;
	int rear;
}Queue;

void initQueue(Queue *q){
	q->front = 1;
	q->rear = 0;
}

void enqueue(Queue *q, char elem){
	if((q->rear + 2) % MAX != q->front){
		q->rear = (q->rear + 1) % MAX;
		q->data[q->rear] = elem;
	}else{
		printf("Queue is full.\n");
	}
}

void dequeue(Queue *q){
	if((q->rear + 1) % MAX != q->front){
		q->front = (q->front + 1) % MAX;
	}
}

char front(Queue q){
	return ((q.rear + 1) % MAX != q.front)? q.data[q.front] : '\0';
}

void insertSorted(Queue *q, char elem){
	int end = (q->rear + 1) % MAX;
	
	if((q->rear + 2) % MAX != q->front){
		while(q->front != end && elem > q->data[q->front]){
			q->rear = (q->rear + 1) % MAX;
			q->data[q->rear] = q->data[q->front];
			q->front = (q->front + 1) % MAX;
		}
		q->rear = (q->rear + 1) % MAX;
		q->data[q->rear] = elem;
		while(q->front != end){
			q->rear = (q->rear + 1) % MAX;
			q->data[q->rear] = q->data[q->front];
			q->front = (q->front + 1) % MAX;
		}
	}
}

void populateQueue(Queue *q){
	char data[size_arr] = {'a','f','d','n','z','e','l','j','k','s'};
	int i;
	for(i = 0; i < size_arr; i++){
		enqueue(q,data[i]);
	}
}

void displayQueue(Queue q){
	int end = (q.rear + 1) % MAX;
	if(end != q.front){
		while(q.front != end){
			printf("%c ", q.data[q.front]);
			q.rear = (q.rear + 1) % MAX;
			q.data[q.rear] = q.data[q.front];
			q.front = (q.front + 1) % MAX;
		}
	}
}

int main(){
	Queue Q;
	
	initQueue(&Q);
	populateQueue(&Q);
	printf("Initial Queue:\n");
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
	displayQueue(Q);
	printf("\n\n");
	
	printf("Dequeue 2:\n");
	dequeue(&Q);
	dequeue(&Q);
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
	displayQueue(Q);
	printf("\n\n");
	
	printf("Enqueue 1: y\n");
	enqueue(&Q,'y');
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
	displayQueue(Q);
	printf("\n\n");
	
	printf("Enqueue 1: b\n");
	enqueue(&Q,'b');
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
	displayQueue(Q);
	printf("\n\n");
	
	printf("Enqueue 1: g\n");
	enqueue(&Q,'g');
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
	displayQueue(Q);
	printf("\n\n");
	
	printf("Dequeue 1:\n");
	dequeue(&Q);
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
	displayQueue(Q);
	printf("\n\n");
	
	printf("Insert Sorted: z\n");
	insertSorted(&Q,'z');
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
	displayQueue(Q);
	printf("\n\n");
	
	return 0;
}