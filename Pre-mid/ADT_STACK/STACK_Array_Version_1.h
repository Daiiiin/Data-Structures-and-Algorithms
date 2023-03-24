/* Written by: MATTHEW DAVE DESABELLE */
#ifndef STACK_ARR
#define STACK_ARR
#define MAX 0xA

typedef struct{
	char data[MAX];
	int top;
}Stack;

typedef enum{TRUE, FALSE} boolean;

void initStack(Stack *s){
	s->top = -1;
}

boolean isFull(Stack s){
	return s.top == MAX - 1? TRUE : FALSE;
}

boolean isEmpty(Stack s){
	return s.top == -1? TRUE : FALSE;
}

void push(Stack *s, char elem){
	if(isFull(*s) == FALSE){
		s->top++;
		s->data[s->top] = elem;	
	}else{
		printf("\nOut of space.\n");
	}
}

void pop(Stack *s){
	if(isEmpty(*s) == FALSE){
		s->top--;
	}
}

char top(Stack s){
	char retVal = '\0';
	if(isEmpty(s) == FALSE){
		retVal = s.data[s.top];
	}
	return retVal;
}

void display(Stack s){
	int i;
	Stack temp;
	while(isEmpty(s) != TRUE){
		printf("Index[%d]: %c\n", s.top, top(s));
		push(&temp,top(s));
		pop(&s);
	}
	while(isEmpty(temp) != TRUE){
		push(&s, top(temp));
		pop(&temp);
	}
}

#endif