/* Written by: MATTHEW DAVE DESABELLE */
#ifndef STACK_LL
#define STACK_LL

typedef struct node{
	char data;
	struct node *link;
}*StackL;

typedef enum{TRUE, FALSE} boolean;

void initStack(StackL *s){
	*s = NULL;
}

boolean isEmpty(StackL s){
	return s == NULL? TRUE : FALSE;
}

void push(StackL *s, char elem){
	StackL temp;
	temp = (StackL)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->data = elem;
		temp->link = *s;
		*s = temp;
	}
}

void pop(StackL *s){
	StackL temp;
	if(isEmpty(*s) == FALSE){
		temp = *s;
		*s = temp->link;
		free(temp);
	}	
}

char top(StackL s){
	char retVal = '\0';
	if(isEmpty(s) == FALSE){
		retVal = s->data;
	}
	return retVal;
}

void display(StackL s){
	for(; s != NULL; s = s->link){
		printf("%c\n", s->data);
	}
}

#endif
