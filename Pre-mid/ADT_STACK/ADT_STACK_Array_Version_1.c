#include <stdio.h>
#include "STACK_Array_Version_1.h"
#define arr_size 0xA

void populateStack(Stack *s){
	char data[arr_size] = {'a','b','c','d','e','f','g','h','i','j'};
	int i;
	for(i = 0; i < arr_size; i++){
		push(s,data[i]);
	}
}

void insertSorted(Stack *s, char elem){
	Stack temp;
	initStack(&temp);
	
	if(isFull(*s) != TRUE){
		while(isEmpty(*s) != TRUE && s->data[s->top] > elem){
			push(&temp,top(*s));
			pop(s);
		}
		push(s,elem);
		while(isEmpty(temp) != TRUE){
			push(s,top(temp));
			pop(&temp);
		}	
	}else{
		printf("\nFULL\n");
	}
}

int main(){
	Stack S;
	
	initStack(&S);
	populateStack(&S);
	printf("TOP: %d\n\n", S.top);
	printf("STACK:\n");
	display(S);
	
	printf("\nPOP 2 then PUSH z,s,n:");
	pop(&S);
	pop(&S);
	push(&S,'z');
	push(&S,'s');
	push(&S,'n');
	display(S);

	printf("\nPOP 1:\n");
	pop(&S);
	display(S);

	printf("\nInsert Sorted: c\n");
	insertSorted(&S,'c');
	display(S);

	printf("\nInsert Sorted when stack is FULL:\n");
	insertSorted(&S,'a');
	display(S);
	printf("\n\nTOP: %d\n", S.top);
	
	return 0;
}