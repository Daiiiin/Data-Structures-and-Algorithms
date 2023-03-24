/*
	A varuant of the circular queue records the position of the front element and the
	length of the array (or number of elements) where length is less than or equal to
	the size of the array. Given below is the definition of the queue.

	Write the code of function enqueueIfUnique(). The function will enqueue an element
	into the queue if the element does not yet exist in the queue. Note: No additional/
	temporary queue or any data structure will be used in the code. Manipulate the given
	queue.

	NOTE: I added file for practice, does not affect function enqueueIfUnique().
		I don't know if I used it correctly though. :(
*/

#include <stdio.h>
#define SIZE 10

typedef struct{
	char elem[SIZE];
	int front;	// index of the front element
	int length;	// length of the queue <= SIZE
}Queue;

void initQueue(Queue *q){
	q->front = 1;
	q->length = 0;
}

void dequeue(Queue *q){
	if((q->length + 1) % SIZE != q->front){
		q->front = (q->front + 1) % SIZE;
	}
}

/* 
	Note: if check = 0, then data is unique, otherwise, 
			if check = 1, then data already exists
	1. Check if queue is full
	2. If queue is not full
	3. Loop (while front != end && data is not found)
		3.3. increment rear(length)
		3.4. move front data to rear(length)
		3.5. increment front
	End loop.
		3.4. if front == end (if the loop was able to reach the end, then data does not yet exist.)
			3.4.1. increment rear(length)
			3.4.2. enqueue data
	4. Loop (while front != end) rearrange order of data 
		4.1. increment rear(length)
		4.2. move front data to rear(length)
		4.3. increment front
	5. If queue is full
		5.1. print "queue is full"
*/

void enqueueIfUnique(Queue *q, char data){
	int end = (q->length + 1) % SIZE;
	
	if((q->length + 2) % SIZE != q->front){
		while(q->front != end && q->elem[q->front] != data){
			q->length = (q->length + 1) % SIZE;
			q->elem[q->length] = q->elem[q->front];
			q->front = (q->front + 1) % SIZE;
		}
		if(q->front == end){
			q->length = (q->length + 1) % SIZE;
			q->elem[q->length] = data;
		}else{
			printf("Data already exist: %c\n", data);
		}
		while(q->front != end){
			q->length = (q->length + 1) % SIZE;
			q->elem[q->length] = q->elem[q->front];
			q->front = (q->front + 1) % SIZE;
		}
	}else{
		printf("Cannot enqueue %c, queue is full.\n", data);
	}
}

void displayQueue(Queue q){
	int end = (q.length + 1) % SIZE;
	if(end != q.front){
		printf("Front: %d\nLength: %d\n", q.front, q.length);
		while(q.front != end){
			printf("%c ", q.elem[q.front]);
			q.length = (q.length + 1) % SIZE;
			q.elem[q.length] = q.elem[q.front];
			q.front = (q.front + 1) % SIZE;
		}
	}
	printf("\n");
}

int main(){
	Queue Q;
	FILE *fp;
	
	initQueue(&Q);
	enqueueIfUnique(&Q,'A');
	enqueueIfUnique(&Q,'B');
	enqueueIfUnique(&Q,'C');
	enqueueIfUnique(&Q,'A');
	enqueueIfUnique(&Q,'D');
	enqueueIfUnique(&Q,'C');
	enqueueIfUnique(&Q,'F');
	enqueueIfUnique(&Q,'E');
	enqueueIfUnique(&Q,'H');
	enqueueIfUnique(&Q,'K');
	enqueueIfUnique(&Q,'B');
	enqueueIfUnique(&Q,'M');
	enqueueIfUnique(&Q,'Z');
	enqueueIfUnique(&Q,'Y');
	
	printf("\nQueue:\n");
	displayQueue(Q);
	
	fp = fopen("queueData.txt", "w");
	if(fp != NULL){
		fwrite(&Q, sizeof(Q), 1, fp);
		fclose(fp);
	}
	
	fp = fopen("queueData.txt", "r+");
	if(fp != NULL){
		while(fread(&Q, sizeof(Q), 1, fp)){
			enqueueIfUnique(&Q,'X');
			dequeue(&Q);
			enqueueIfUnique(&Q,'Y');
		}
		fwrite(&Q, sizeof(Q), 1, fp);
		fclose(fp);
	}
	
	printf("\nQueue:\n");
	displayQueue(Q);
	
	enqueueIfUnique(&Q,'U');
	
	return 0;
}

/*
	Note: if check = 0, then data is unique, otherwise, 
			if check = 1, then data already exists
	1. Check if queue is full
	2. If queue is not full
	3. Loop (while front != end)
		3.1. check if front == data
		3.2. if front == data
			3.2.1.	check = 1;
		3.3. increment rear(length)
		3.4. move front data to rear(length)
		3.5. increment front
	End loop.
		3.4. if check != 1
			3.4.1. increment rear(length)
			3.4.2. enqueue data
	4. If queue is full
		4.1. print "queue is full"
	
	int check = 0;	
	if((q->length + 2) % SIZE != q->front){
		while(q->front != end){
			if(q->elem[q->front] == data){
				check = 1;
			}
			q->length = (q->length + 1) % SIZE;
			q->elem[q->length] = q->elem[q->front];
			q->front = (q->front + 1) % SIZE;
		}
		if(check != 1){
			q->length = (q->length + 1) % SIZE;
			q->elem[q->length] = data;
		}else{
			printf("Data already exist: %c\n", data);
		}
	}else{
		printf("Cannot enqueue %c, queue is full.\n", data);
	}
*/