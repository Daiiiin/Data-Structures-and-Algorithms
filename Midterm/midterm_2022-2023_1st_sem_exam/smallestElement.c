/*
	Given the definition of the set implemented using computer word.
		typedef unsigned long int setCompWord;
	
	Write the code of the function that will return to the calling function the smallest
	element of the set if the set is not empty; otherwise return -1. Note: Only effucient
	code gets full credit.
	
	Constraints:
	1) There should be 1 return statement only.
	2) No break or continue statement will be used.
*/

#include <stdio.h>

typedef unsigned long int setCompWord;

int smallestElem(setCompWord set){
	int retVal = -1, bit, gap;
	unsigned int mask;

	bit = (sizeof(set) << 3) - 1;

	for(gap = 1, mask = 1<<bit; mask != 0; mask >>= 1, gap++){
		if(set & mask){
			retVal = set & mask;			
		}
	}

//	for(gap = 1, mask = 1<<bit; mask != 0; mask >>= 1, gap++){
//		printf("%d", (set & mask)? 1 : 0);
//		if(gap % 4 == 0){
//			printf(" ");
//		}
//		if(set & mask){
//			retVal = set & mask;			
//		}
//	}
	return retVal;
}

int main(){
	setCompWord A = 24;
	
	printf("Set: %d\n\n", A);
	printf("Size of set: %d bits", (sizeof(A) << 3));
	int retVal = smallestElem(A);
	printf("\n\nSmallest Element: %d\n", retVal);
	
	return 0;
}