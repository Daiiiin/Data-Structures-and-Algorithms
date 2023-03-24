#include <stdio.h>

void displayBitPattern(short int data){
	int bit, gap;
	unsigned int mask;

	bit = (sizeof(data) << 3) - 1;

	for(gap = 1, mask = 1<<bit; mask != 0; mask >>= 1, gap++){
		printf("%d", (data & mask)? 1 : 0);
		if(gap % 4 == 0){
			printf(" ");
		}
	}
}

int main(){
	short int x = 132;

	displayBitPattern(x);
	
	return 0;
}