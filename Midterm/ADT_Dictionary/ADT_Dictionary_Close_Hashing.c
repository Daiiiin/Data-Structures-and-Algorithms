#include <stdio.h>
#include <ctype.h>
#define MAX 0xA // Dictionary Size
#define data_size 7 // data array size
#define DELETED '#'
#define EMPTY '?'

typedef char Dictionary[MAX];
typedef enum {FALSE, TRUE}boolean;

void initDic(Dictionary d){
	int i;
	for(i = 0; i < MAX; i++){
		d[i] = EMPTY;
	}
}

int hash(char elem){
	return (toupper(elem) - 'A') % MAX;
}

void insert(Dictionary d, char data){
	int key, ctr = 0;
	for(key = hash(data); d[key] != DELETED && d[key] != EMPTY && ctr < MAX; key = (key + 1) % MAX, ctr++){}
	if(d[key] == EMPTY || ctr < MAX){
		d[key] = toupper(data);
	}else{
		printf("\nDictionary is full.\n");
	}
}

void deleteMem(Dictionary d, char data){
	int key, ctr = 0;
	for(key = hash(data); d[key] != toupper(data) && ctr < MAX; key = (key + 1) % MAX, ctr++){}
	if(ctr != MAX){
		d[key] = DELETED;
	}
}

boolean isMember(Dictionary d, char data){
	int key, ctr = 0;
	for(key = hash(data); toupper(data) != d[key] && ctr < MAX; key = (key + 1) % MAX, ctr++){}
	return (data == d[key])? TRUE : FALSE;
}

void populateDic(Dictionary d){
	char data[data_size] = {'a','b','c','d','a','g','d'};
	int i;
	for(i = 0; i < data_size; i++){
		insert(d, data[i]);
	}
}

void displayDic(Dictionary d){
	int i;
	printf("Data:\t\tHash Value:\n");
	for(i = 0; i < MAX; i++){
		printf("Index[%d]: %c", i, d[i]);
		if(d[i] == EMPTY){
			printf("\t%c\n", EMPTY);	
		}else if(d[i] == DELETED){
			printf("\t%c\n", DELETED);
		}else{
			printf("\t%d\n", hash(d[i]));
		}
	}
}

int main(){
	Dictionary D;
	
	initDic(D);
	populateDic(D);
	printf("Insert Memeber:\n");
	displayDic(D);
	
	printf("\nDELETE C:\n");
	deleteMem(D,'c');
	displayDic(D);
	
	printf("\nSearch Member:\n");
	printf("TRUE = 1, FALSE = 0\n");
	printf("Is Member? G: %d\n", isMember(D,'G'));
	printf("Is Member? C: %d\n", isMember(D,'C'));
	
	printf("\nInsert Member: J, I, H, H, B\n");
	insert(D,'J');
	insert(D,'I');
	insert(D,'H');
	insert(D,'H');
	insert(D,'B');
	displayDic(D);
	
	return 0;
}