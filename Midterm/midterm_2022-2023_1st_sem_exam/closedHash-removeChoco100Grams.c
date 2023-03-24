#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CSIZE 0x3E8 // close hash table size
#define OSIZE 0xF // open hash table size
#define EMPTY "000000" // assign to ID field
#define DELETED "xxxxxx" // assign to ID field

typedef struct{
	char name[24];
	int weight;
}chocoDesc;

typedef struct{
	char prodID[8]; // product ID uniquely identifies the product; EMPTY or DELETED
	chocoDesc prodDesc; // product description
	float prodPrice; // product price
	int prodQty;
}product; // product record

typedef struct node{
	product prod;
	struct node *pLink;
}*prodPtr;

typedef struct{
	prodPtr Header[OSIZE];
	int count; // hold the number of elements
}OpenHash; // Open hashing

typedef struct{
	product HTable[CSIZE];
	int elemCtr; // holds the number of elements
}CloseHash; // Closed hashing

void initCloseHash(CloseHash *h){
	int i;
	for(i = 0; i < CSIZE; i++){
		strcpy(h->HTable[i].prodID, EMPTY);
	}
	h->elemCtr = 0;
}

void initOpenHash(OpenHash *op){
	int i;
	for(i = 0; i < OSIZE; i++){
		op->Header[i] = NULL;
	}
	op->count = 0;
}

/*
	Function closedHash(). The function will compute and return to the calling the hash
	value. From the given product ID, the middle character digit is extracted, or 2
	middle character digits are extracted if the number of digits in the ID is even.
	Convert the extracted digit/s to its equivalent integer value which should be between
	0 to 99, inclusive. Square the integer value obtained and perform additional operation
	to make it an acceptable hash value for closed hashing. Note: Only efficient code
	gets full credit.
	Constraints:
	1) There should be 1 return statement only.
	2) No break or continue statement will be used.
	3) Cannot use any library functions.
*/

/*
	1) if ID is even extract 2 middle characters
	2) if ID is odd extract middle character
	3) convert extracted digit/s to integer equivalent (0 to 99)
	4) square the value
	5) value % size
	6) return
*/

int closedHash(char *ID){
	int len, mid, val;
	for(len = 0; ID[len] != '\0' && len != sizeof(ID); len++){} // gets # of digits in ID
	mid = len / 2;
	val = (len % 2 == 0)? ID[mid] + ID[mid - 1] : ID[mid];
	val *= val;
	return val % CSIZE;
}

/*
	Function Specification: The function will remove all chocolate records whose weights
	are at most 100 grams from the given dictionary implemented using open hashing
	and put them in a newly created dictionary implemented using closed hashing. The newly
	created dictionary will be returned to the calling function.
	Note: Only efficient code gets full credit. Describe the task through line comments
	to improve readability
	
	Constraints:
	1) There should be 1 return statement only.
	2) No break or continue statement will be used.
*/

/*
	1) create closeHash dictionary
	2) initialize closeHash dictionary
	3) loop through open dictionary array
		3.1) loop through open dictionary linked list
		3.2) check if product weights <= 100
			3.2.1) copy product
			3.2.2) remove product
			3.2.3) reduce product count in open dictionary
			3.2.4) move product to close dictionary
			3.2.5) find hash value of ID
			3.2.6) copy product to close dictionary with hash value as index
			3.2.7) if index is already occupied, loop through dictionary until EMPTY indes is found.
			3.2.8) increase product count in close dictionary
		3.3) else increment loop
	4) return close dictionary to calling function
*/

CloseHash removeChocoGrams(OpenHash *op){
	CloseHash retVal;
	prodPtr *trav, temp;
	product prod;
	int key, ctr = 0;
	int i;
	// initialize close dictionary
	for(i = 0; i < CSIZE; i++){
		strcpy(retVal.HTable[i].prodID, EMPTY);
	}
	retVal.elemCtr = 0;
	
	for(i = 0; i < OSIZE && retVal.elemCtr < CSIZE; i++){ // loop array
		for(trav = &op->Header[i]; *trav != NULL && retVal.elemCtr < CSIZE;){ // loop linked list
			if((*trav)->prod.prodDesc.weight <= 100){
				// copy product
				prod = (*trav)->prod;
				// remove product from open dictionary
				temp = *trav;
				*trav = temp->pLink;
				free(temp);
				// reduce product count in open dictionary
				op->count--;
				// move product to close dictionary
				for(key = closedHash(prod.prodID); strcmp(retVal.HTable[key].prodID, DELETED) != 0 && strcmp(retVal.HTable[key].prodID, EMPTY) != 0 && ctr != CSIZE; key = (key + 1) % CSIZE, ctr++){}
				if(strcmp(retVal.HTable[key].prodID, EMPTY) != 0 || ctr < CSIZE){
					retVal.HTable[key] = prod;
					// increase product count in close dictionary
					retVal.elemCtr++;
				}
			}else{
				trav = &(*trav)->pLink;
			}
		}
	}

	return retVal;
}

void insertOP(OpenHash *op, product prod){
	prodPtr *trav, temp;
	int key = closedHash(prod.prodID);
	key = key % OSIZE;
	temp = (prodPtr)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->prod = prod;
		temp->pLink = op->Header[key];
		op->Header[key] = temp;
		op->count++;
	}
}

void populateOP(OpenHash *op){
	product prods[6] = {	{"A2001", {"Choco1", 51}, 20.00, 5},
							{"B1912", {"Choco2", 101}, 30.50, 10},
							{"C1854", {"Choco3", 110}, 15.25, 20},
							{"D2332", {"Choco4", 80}, 22.15, 25},
							{"E2265", {"Choco5", 60}, 60.25, 30},
							{"I5903", {"Choco6", 120}, 10.05, 2}
						};
	int i;
	for(i = 0; i < 6; i++){
		insertOP(op, prods[i]);
	}
}

void displayOP(OpenHash op){
	int i;
	prodPtr trav;
	printf("Open Hash count: %d\n", op.count);
	for(i = 0; i < OSIZE; i++){
		printf("Index[%d]: ", i);
		for(trav = op.Header[i]; trav != NULL; trav = trav->pLink){
			printf("[ID: %s Prod Name: %s Weight: %d Price: %f Quantity: %d] -> ", 
					trav->prod.prodID, 
					trav->prod.prodDesc.name, 
					trav->prod.prodDesc.weight,
					trav->prod.prodPrice,
					trav->prod.prodQty);
		}
		printf("NULL\n");
	}
}

void displayCL(CloseHash cl){
	int i;
	printf("Product Count: %d\n", cl.elemCtr);
	printf("Index:\t\t\tHash Value:\n");
	for(i = 0; i < CSIZE; i++){
		printf("[%d]: %s", i, cl.HTable[i].prodID);
		
		if(strcmp(cl.HTable[i].prodID, EMPTY) == 0){
			printf("\t\t%s\n", "EMPTY");	
		}else if(strcmp(cl.HTable[i].prodID, DELETED) == 0){
			printf("\t\t%s\n", "DELETED");
		}else{
			printf("\t\t%d\n", closedHash(cl.HTable[i].prodID));
		}
	}
}

int main(){
	OpenHash OP;
	initOpenHash(&OP);
	populateOP(&OP);
	displayOP(OP);
	
	printf("\nClose Hash:\n");
	CloseHash CL = removeChocoGrams(&OP);
	displayCL(CL);
	
	printf("\nNew Open Dictionary:\n");
	displayOP(OP);
	
	return 0;
}