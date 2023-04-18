/******************************************************************
 * Project Name:  List, Set and Dictionary                        *
 * Programmer  :  Matthew Dave Desabelle                          *
 * Date Completed: March 25, 2023                                 *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE     0XC    //size of Virtual Heap
#define OPEN_DSIZE  0XA    //size of Open Hash Table
#define CLOSE_DSIZE 0XC    //size of Close Hash Table
#define LIST_SIZE   0XF    //size of the array implementation of List
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  
	char name[24];          // Chocolate name  
 	int  weight;            // Chocolate weight in grams  
}chocoDesc;
 
typedef struct {
   char prodID[8];          //  product ID uniquely identifies the products; EMPTY or DELETED   
  	chocoDesc prodDesc;     //  product description 
 	float prodPrice;        //  product price 
  	int prodQty;            //  product count or quantity   
}product;                   //  product record  

typedef struct {
	product elem;            
	int next;                
}prodNode;                 // Product node, used in cursor-based implementation of Set  


/************************
 * Virtual Heap         *
 ************************/
typedef struct {
   prodNode VH_node[VH_SIZE];
   int avail;
}VHeap;

/******************************************
 * Cursor-Based Implementation of SET     *
 ******************************************/
typedef struct {
   int elemIndex;        // index of the 1st element in the set  
   int count;            // holds the actual number of elements in the set  
   VHeap *VHptr;         // holds the pointer to the virtual heap  
}cursorSet;            

/********************************************
 * Open Hashing Implementation of Dictionary*
 ********************************************/
typedef struct {
	int header[OPEN_DSIZE];  // array of sets   
	int count;               // total number of elements in the dictionary  
	VHeap *dicVHptr;         // holds the pointer to the virtual heap  
}openDic;


/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY   "empty"     // stored in product ID field  
#define DELETED  "del"      // stored in product ID field * 
 
typedef product closeDic[CLOSE_DSIZE];   //Definition of the closed hash dictionary
  
typedef struct {
	product prod[LIST_SIZE];
	int last;   //index of the last element; -1 if list is empty	
}List;



/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//---Problem #1 ---
void initVHeap(VHeap *VH);	// DONE
cursorSet initCursorSet(VHeap *VH);	// DONE
void displayVHeap(VHeap V);	// DONE
void displaySet(cursorSet A);	// DONE

//---Problem #2 ---
int mallocInVHeap(VHeap *VH);	// DONE
void insertSorted(cursorSet *A, product P);	// DONE
void populateSet(cursorSet *A);	// DONE

//---Problem #3 ---
int openHash(char *IDen);	// DONE
openDic initOpenDict(VHeap *VH);	// DONE
openDic convertToOpenDict(cursorSet *A);	// DONE
void displayOpenDict(openDic D);	// DONE

//---Problem #4 ---
void freeInVHeap(VHeap *VH, int ndx);	// DONE
void deleteDict(openDic *D, char *IDen);	// DONE

//---Problem #5 ---
int closeHash(char *ID);	// DONE
void initCloseDict(closeDic CD);	// DONE
closeDic * convertToCloseDict(openDic *D);	
void displayCloseDict(closeDic CD);


 
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *                                                                                  *
 ***********************************************************************************/
 int main( ) 
 {	
 /*---------------------------------------------------------------------------------
 * 	Problem #1 ::  1) Initializes the virtual heap and the cursor Set             *
 *                 2) Displays the contents  virtual heap and cursor Set          *
 *--------------------------------------------------------------------------------*/
 	printf("\n\n\nProblem #1:: "); 
 	printf("\n------------");
 	//Declare variables needed for Problem #1
 	VHeap VH;
	cursorSet CS;
 	//Function Calls for Problem #1
 	initVHeap(&VH);
 	CS = initCursorSet(&VH);
 	displayVHeap(VH);
	displaySet(CS);

/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  1) Populates the Cursor set which is sorted in ascending order *
 *                    according to ID                                             *
 *                 2) Displays the Cursor set                                     * 
 *--------------------------------------------------------------------------------*/	 
 	printf("\n\n\nProblem #2:: "); 
 	printf("\n------------");
	//Declare variables needed for Problem #2
 	

 	//Function Calls for Problem #2
	populateSet(&CS);
	displaySet(CS);

/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  1) Converts the Cursor set into an Open Hash Dictionary        *      
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the empty Cursor set.                              * 
 *--------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #3:: "); 
 	printf("\n------------");
	//Declare variables needed for Problem #3
 	openDic OD;

 	//Function Calls for Problem #3
 	OD = convertToOpenDict(&CS);
	displayOpenDict(OD);
	displaySet(CS);

/*---------------------------------------------------------------------------------
 * 	Problem #4 ::  1) Perform 3 delete operations on the Open Hash Dictionary     *
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the Virtual Heap                                   * 
 *--------------------------------------------------------------------------------*/	
 	printf("\n\n\nProblem #4:: "); 
 	printf("\n------------");	
 //Declare variables needed for Problem #4
    char delete01[] = "1703";
    char delete02[] = "1358";    
	char delete03[] = "1601";
	
 
//Function Calls for Problem #4	    
    deleteDict(&OD, delete01);
    deleteDict(&OD, delete02);
    deleteDict(&OD, delete03);
    displayOpenDict(OD);
    displayVHeap(VH);
    
/*------------------------------------------------------------------------------------
 * 	Problem #5 :: 1) Converts the Open Hash Dictionary into a Closed Hash Dictionary *
 *                2) Displays the Closed Hash Dictionary                             * 
 *                3) Displays the virtual heap                                       *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #5:: ");
    printf("\n------------");
    //Declare variables needed for Problem #5

    
    //Function Calls for Problem #5

	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
 void initVHeap(VHeap *V)
 {
 	int i;
 	for(i = VH_SIZE - 1; i >= 0; i--){
		V->VH_node[i].next = i - 1;
	}
	V->VH_node[0].next = -1;
	V->avail = VH_SIZE - 1;
 }

cursorSet initCursorSet(VHeap *VH)
{
	cursorSet retVal = {-1, 0, VH};
	return retVal;
}

void displayVHeap(VHeap V)
{
	//Variable Declaration here
	int i;

    printf("\n\nDetails of the Virtual Heap :: ");
    printf("\n------------------------------");
    printf("\nAvailable Index  ::  %d",  V.avail);       //Complete this statement
	printf("\nVHeap Address    ::  %d",  &V);       //Complete this statemet
	
    printf("\n\n%10s", "Index");
    printf("%10s", "Prod ID");
    printf("%15s", "Next Field");
	printf("\n%10s%10s%15s", "-----", "-------","----------");	
     
    //Write your code here 
	for(i = 0; i < VH_SIZE; i++){
		printf("\n%10d", i);
		if(V.VH_node[i].elem.prodID == " "){
			printf("%10s", V.VH_node[i].elem.prodID);
		}
		printf("%20d", V.VH_node[i].next);
	}
	printf("\n\n"); system("Pause");
}

void displaySet(cursorSet A)
{
	int x;
	product p;
	
	printf("\n\nDetails of the Set :: ");
	printf("\n---------------------");
	printf("\nNo. of elements ::  %d", A.count);      //Complete this code
	printf("\n\n%-7s", "ID");
	printf("%-12s","Choco Name");
	printf("%-15s","Choco Weight");
	printf("%-10s","VHeap Index");
	printf("\n%-7s%-12s%-15s%-10s", "--", "----------", "------------", "-----------");

	//Write your code here
	for(x = A.elemIndex; x != -1; x = A.VHptr->VH_node[x].next){
		printf("\n%-7s", A.VHptr->VH_node[x].elem.prodID);
		printf("%-12s", A.VHptr->VH_node[x].elem.prodDesc.name);
		printf("%-15d", A.VHptr->VH_node[x].elem.prodDesc.weight);
		printf("%-10d", x);
	}
	printf("\n\n"); system("Pause");	
}

/************************************************************
 *  Problem 2:: Function Definitions                         *
 ************************************************************/
int mallocInVHeap(VHeap *VH)
{
	int retVal = VH->avail;
	if(retVal != -1){
		VH->avail = VH->VH_node[retVal].next;
	}
	return retVal;
}

void insertSorted(cursorSet *A, product P)
{
	int *trav, temp;
	// checks if product ID already exists
	for(trav = &A->elemIndex; *trav != -1 && strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) != 0; trav = &A->VHptr->VH_node[*trav].next){}
	
	if(strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) != 0){
		// sorts product by ID
		for(trav = &A->elemIndex; *trav != -1 && strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) < 0; trav = &A->VHptr->VH_node[*trav].next){}
		temp = mallocInVHeap(A->VHptr);
		// checks if there is space
		if(temp != -1){
			A->VHptr->VH_node[temp].elem = P;
			A->VHptr->VH_node[temp].next = *trav;
			A->count++;
			*trav = temp;
		}else{
			printf("\nNo available space. Product with ID: %s cannot be inserted\n", P.prodID);
		}
	}else{
		printf("\nProduct with ID: %s already exists in the set.\n", P.prodID);
	}
}

void populateSet(cursorSet *A)
{
	const int COUNT = 15;
	product data[] = { 	{"1701", {"Toblerone", 135}, 150.75, 20},
						{"1356", {"Ferrero", 200}, 250.75, 85},
						{"1109", {"Patchi", 50}, 99.75, 35},
						{"1550", {"Cadbury", 120}, 200.00, 30},
						{"1807", {"Mars", 100}, 150.75, 20},
						{"1201", {"Kitkat", 50}, 97.75, 40},
						{"1450", {"Ferrero", 100},150.50, 50},
						{"1701", {"Toblerone", 50}, 90.75, 80},
						{"1601", {"Meiji", 75}, 75.50, 60},
						{"1310", {"Nestle", 100}, 124.50, 70},
						{"1807", {"Valor", 120}, 149.50, 90},
						{"1455", {"Tango", 75}, 49.50, 100},
						{"1703", {"Toblerone", 100}, 125.75, 60},
						{"1284", {"Lindt", 100}, 250.75, 15},
						{"1688", {"Guylian", 50}, 99.75, 35},
					
		              };
    //Inserts each element of the array to the cursor set
    //Write your code here!!
    int i;
    for(i = 0; i < COUNT; i++){
    	insertSorted(A, data[i]);
	}
}

/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
int openHash(char * prodID)               
{ 
    // n - 48
    int i, retVal = 0;
	for(i = 0; prodID[i] != '\0'; i++){
		retVal += prodID[i] - 48;
	}
	return retVal %= OPEN_DSIZE; 
}

openDic initOpenDict(VHeap *VH)
{
	openDic retVal = {.count = 0, .dicVHptr = VH};
	int i;
	for(i = 0; i < OPEN_DSIZE; i++){
		retVal.header[i] = -1;
	}
	return retVal;
}

openDic convertToOpenDict(cursorSet *A)
{
	int *trav, temp; // cursorSet
	int key, *dtrav; // open dictionary
	openDic	retVal = initOpenDict(A->VHptr);
	for(trav = &A->elemIndex; *trav != -1;){
		key = openHash(A->VHptr->VH_node[*trav].elem.prodID);
		for(dtrav = &retVal.header[key]; *dtrav != -1 && strcmp(retVal.dicVHptr->VH_node[*dtrav].elem.prodID, A->VHptr->VH_node[*trav].elem.prodID) < 0; dtrav = &retVal.dicVHptr->VH_node[*dtrav].next){}
		temp = *trav;
		*trav = A->VHptr->VH_node[temp].next;
		retVal.dicVHptr->VH_node[temp].next = *dtrav;
		*dtrav = temp;
		retVal.count++;
		A->count--;
	}
	return retVal;
}

void displayOpenDict(openDic D)
{
	//Variable declaration here 
	int i, j;
	
	printf("\n\nDetails of the Open Hash Dictionary:: ");
	printf("\n-------------------------------------");
	
	printf("\nNo. of elements :: %d", D.count);
	printf("\n\n%-7s", "GROUPS");
	printf("%15s","ID Numbers");
	printf("\n%-7s%15s", "------","----------");
	
	//Write your code here
	for(i = 0; i < OPEN_DSIZE; i++){
		printf("\nGroup[%d] :: ", i);
		for(j = D.header[i]; j != -1; j = D.dicVHptr->VH_node[j].next){
			printf("%-7s", D.dicVHptr->VH_node[j].elem.prodID);	
		}
	}
    printf("\n\n"); system("Pause");	
}

/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
void freeInVHeap(VHeap *VH, int ndx)
{
	if(ndx < VH_SIZE && ndx >= 0){
		VH->VH_node[ndx].next = VH->avail;
		VH->avail = ndx;	
	}
}

void deleteDict(openDic *D, char *IDen)
{
	int *trav, temp;
	int key = openHash(IDen);
	for(trav = &D->header[key]; *trav != -1 && strcmp(D->dicVHptr->VH_node[*trav].elem.prodID, IDen) != 0; trav = &D->dicVHptr->VH_node[*trav].next){}
	if(*trav != -1){
		temp = *trav;
		*trav = D->dicVHptr->VH_node[temp].next;
		D->count--;
		freeInVHeap(D->dicVHptr, temp);
		printf("\nProduct with ID: %s is successfully deleted.\n", IDen);
	}else{
		printf("\nProduct with ID: %s is not in the dictionary\n", IDen);
	}
}

 /************************************************************
 *  Problem 5:: Function Definitions                        *
 ************************************************************/
int closeHash(char *ID)
{
	int i, retVal = 0;
	for(i = 0; ID[i] != '\0'; i++){
		retVal += ID[i] - 48;
	}
	return retVal %= CLOSE_DSIZE;
}

void initCloseDict(closeDic CD)
{


}
 
closeDic * convertToCloseDict(openDic *D)
{

}	

void displayCloseDict(closeDic CD)
{
 	//Variable declaration here
 	int i;
 	
	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "ChocoID");
	printf("%-15s", "Choco Name");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------"); 
	
	//Write your code here
	for(i = 0; i < CLOSE_DSIZE; i++){
		printf("\n%-6d", i);
		printf("%-10s", CD[i].prodID);
	}
	
	printf("\n\n"); system("Pause");
 
}
 
